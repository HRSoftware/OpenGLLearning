#include "stdafx.h"

#include "../../../include/Core/Material.h"
#include "../../../include/Helpers/ShaderFunctions.h"
#include "../../../include/Core/Mesh.h"
#include "../../../include/Core/GameObject.h"
#include "../../../include/Core/Model.h"
#include "../../../include/Core/Lighting.h"
#include "../../../include/Core/Camera.h"
#include "../../../include/Core/System/Renderer.h"


std::shared_ptr<Model> Renderable::getModel(std::string modelName)
{
    return std::make_shared<Model>(Renderable::RenerableModels.at(modelName));
}

std::shared_ptr<Model> Renderable::addModel(std::string fileName)
{
    std::shared_ptr<Model> model = Renderable::getModel(fileName);
    return model != nullptr ? model : Renderable::getModel(fileName);
}

void Renderer::setCamera(Camera& cam)
{
    _currentCamera = &cam;
}





void Renderer::addLightToScene(IBaseLight* light)
{
   _sceneLights.push_back(light);
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
    for ( auto mesh : gameobj.getMeshes())
    {
       renderMesh(mesh.getVAO(), mesh.getIndices().size());
    }
}

void Renderer::renderBatch_ToDepthBuffer(std::map<std::string, GameObject>& renderBatch, Shader shader)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferDepth);
    ShaderHelper::useProgram(shader.programID);
    glViewport(0, 0, _shadowWidth, _shadowHeight);
    

   for (auto _light : _sceneLights) {
      _light->useLight();

       //shader.setVec3("viewPos", _light->getPosition());
      ShaderHelper::setMat4(shader, "lightSpaceMatrix", _light->getShadowViewProjectionMatrix(true));

      for (auto GO : renderBatch) {
        ShaderHelper::setMat4(shader,"modelMatrix", GO.second.getModelMatrix());
        renderGameObject_ToDepthBuffer(GO.second);
         
      }
   }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderBatch(std::map<string, GameObject>& renderBatch, bool textured)
{
    for (auto GO : renderBatch) {
        for(auto mesh : GO.second.getMeshes())
        {
            if (mesh.getMaterial().getName() != SceneStats::activeMaterial.getName()) {
                SceneStats::activeMaterial =  mesh.getMaterial();
               
                SceneStats::activeMaterial.setUpShader(textured);
                SceneStats::activeMaterial.Use();
            } 
            renderGameObject(GO.second, textured, false);
        }
    }
}

void Renderer::renderGameObject(GameObject gameObj, bool texture = true, bool requiredShaderSetUp = false)
{
    //if(requiredShaderSetUp)
    for(Mesh mesh : gameObj.getMeshes())
    {
        Material currentMat = mesh.getMaterial();
        if (currentMat.getName() != SceneStats::activeMaterial.getName())
            SceneStats::activeMaterial = currentMat;

        SceneStats::activeMaterial.setUpShader(texture);
       ShaderHelper::setMat4(currentMat.getShader(), "view", _currentCamera->GetViewMatrix());
       ShaderHelper::setMat4(currentMat.getShader(), "model", gameObj.getModelMatrix());
    }
        

    
    for ( auto m : gameObj.getMeshes() )
    {
        renderMesh(m.getVAO(), m.getIndices().size());
    }
}
