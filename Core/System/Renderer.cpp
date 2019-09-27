#include "Renderer.h"



void Renderer::setCamera(Camera& cam)
{
    _currentCamera = &cam;
}

void Renderer::renderGameObject(GameObject* gameobj, Shader shader, bool texture)
{

    for ( auto m : gameobj->getMeshes() )
    {
        if(texture)
            setUpShader(m.textureHandles, shader, texture);

        shader.setMat4("view", _currentCamera->GetViewMatrix());
        shader.setMat4("model", gameobj->getModelMatrix());
        renderMesh(m.VAO, m.indices.size());
    }
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

void Renderer::setUpShader(map<int, string> textures, Shader shader, bool textured)
{
    if (textured) {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;

        int _textureIndex = 0;
        for ( auto _texture : textures )
        {
            glActiveTexture(GL_TEXTURE0 + _textureIndex);
            std::string number;
            std::string name = _texture.second;


            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            shader.setInt((name + number).c_str(), _textureIndex);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, _texture.first);

            _textureIndex++;
        }


        //for (unsigned int i = 0; i < textures.size(); i++) {
        //    glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        //                                      // retrieve texture number (the N in diffuse_textureN)
        //    std::string number;
        //    std::string name = textures[i]->type;

        //    if (name == "texture_diffuse")
        //        number = std::to_string(diffuseNr++);
        //    else if (name == "texture_specular")
        //        number = std::to_string(specularNr++); // transfer unsigned int to stream
        //    else if (name == "texture_normal")
        //        number = std::to_string(normalNr++); // transfer unsigned int to stream
        //    else if (name == "texture_height")
        //        number = std::to_string(heightNr++); // transfer unsigned int to stream

        //                                             // now set the sampler to the correct texture unit

        //    shader.setInt((name + number).c_str(), i);
        //    // and finally bind the texture
        //    glBindTexture(GL_TEXTURE_2D, textures[i]->ID);
        //}
    }
}

void Renderer::renderGameObject_ToDepthBuffer(GameObject* gameobj)
{
    for ( auto mesh : gameobj->getMeshes())
    {
       renderMesh(mesh.VAO, mesh.indices.size());
    }
}

void Renderer::renderBatch_ToDepthBuffer(std::map<string, GameObject*>& renderBatch, Shader shader)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferDepth);
    shader.use();
    glViewport(0, 0, _shadowWidth, _shadowHeight);
    

   for (auto _light : _sceneLights) {
      _light->useLight();

       //shader.setVec3("viewPos", _light->getPosition());
      shader.setMat4("lightSpaceMatrix", _light->getShadowViewProjectionMatrix(true));

      for (auto GO : renderBatch) {
         if (GO.second->isModelNULL() == false)
         {
            shader.setMat4("modelMatrix", GO.second->getModelMatrix());
            renderGameObject_ToDepthBuffer(GO.second);
         }
      }
   }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderBatch(std::map<string, GameObject*>& renderBatch, Shader shader, bool textured)
{
   shader.use();
    for ( auto GO : renderBatch )
    {
        if(GO.second->isModelNULL() == false)
            renderGameObject(GO.second, shader, textured);
    }
}
