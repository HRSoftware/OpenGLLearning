#include "stdafx.h"
#pragma once

#include "../../../include/Core/Data_Structures/Material.h"
#include "../../../include/Helpers/ShaderFunctions.h"
#include "../../../include/Core/Data_Structures/Mesh.h"
#include "../../../include/Core/Data_Structures/GameObject.h"
#include "../../../include/Core/Data_Structures/Model.h"
#include "../../../include/Core/Data_Structures/Shader.h"
#include "../../../include/Core/Lighting.h"
#include "../../../include/Core/Camera.h"
#include "../../../include/Core/System/Renderer.h"
#include "../../../include/Core/Material.h"



void Renderer::setCamera(std::shared_ptr<Camera> cam)
{
    Globals::RenderSystem::currentCamera = cam;
}

void Renderer::addLightToScene(std::shared_ptr<IBaseLight> light)
{
   _sceneLights.push_back(std::move(light));
}

void Renderer::initDepthRender()
{  
   glGenFramebuffers(1, &_framebufferDepth);
   glBindFramebuffer(GL_FRAMEBUFFER, _framebufferDepth);


  			//attach depth texture to FBO
                                                               //Creating Texture
   glGenTextures(1, &_depthTexture);
   glBindTexture(GL_TEXTURE_2D, _depthTexture);
   //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _SHADOW_WIDTH, _SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
   glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, _shadowWidth, _shadowHeight);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
   /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);*/

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL);
   //glBindTexture(GL_TEXTURE_2D, 0);

   //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _shadowTexture, 0);
   glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _depthTexture, 0);

   glDrawBuffer(GL_DEPTH_ATTACHMENT);
   glReadBuffer(GL_NONE);

   glGenRenderbuffers(1, &_depthRenderBufferObject);
   glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBufferObject);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _shadowWidth, _shadowHeight);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBufferObject);


   if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
   else
      std::cout << "Framebuffer is complete!" << std::endl;

   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderMesh(int VAO, int indiceCount)
{
    glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}



void Renderer::renderGameObject_ToDepthBuffer(GameObject gameobj)
{
    for ( auto mesh : gameobj._model.get()->meshes)
    {
       renderMesh(mesh->VAO, mesh->_indices.size());
    }
}

void Renderer::renderBatch_ToDepthBuffer(std::map<std::string, GameObject>& renderBatch, std::shared_ptr<Shader> shader)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferDepth);
    MaterialHelper::useMaterial(Globals::RenderSystem::activeMaterial);
    glViewport(0, 0, _shadowWidth, _shadowHeight);
    

   for (auto _light : _sceneLights) {
      _light->useLight();

       //shader.setVec3("viewPos", _light->getPosition());
      ShaderHelper::setMat4(shader, LOC_MATRIX_MVP, _light->getShadowViewProjectionMatrix(true));

      for (auto GO : renderBatch) {
        ShaderHelper::setMat4(shader,LOC_MATRIX_MODEL, GO.second.getModelMatrix());
        renderGameObject_ToDepthBuffer(GO.second);
         
      }
   }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderBatch(std::map<string, GameObject>& renderBatch, bool textured)
{
    for (auto GO = renderBatch.begin(); GO != renderBatch.end(); GO++) {
        for(auto mesh : GO->second._model->meshes)
        {
            if (mesh->_material != Globals::RenderSystem::activeMaterial) 
                MaterialHelper::useMaterial(mesh->_material);
            
            renderGameObject(GO->second, textured, false);
        }
    }
}

void Renderer::renderGameObject(GameObject gameobj, bool texture) {}

void Renderer::renderGameObject(GameObject gameObj, bool texture = true, bool requiredShaderSetUp = false)
{
    //if(requiredShaderSetUp)
    for(auto mesh : gameObj._model->meshes)
    {
        auto currentMat = mesh->_material;
        if (currentMat->name != Globals::RenderSystem::activeMaterial->name)
               MaterialHelper::useMaterial(currentMat);

            
       ShaderHelper::setMat4(Globals::RenderSystem::activeMaterial->shader, LOC_MATRIX_VIEW, _currentCamera->GetViewMatrix());
       ShaderHelper::setMat4(Globals::RenderSystem::activeMaterial->shader, LOC_MATRIX_MODEL, gameObj.getModelMatrix());
    }
        

    
    for ( auto m : gameObj._model->meshes )
    {
        renderMesh(m->VAO, m->_indices.size());
    }
}
