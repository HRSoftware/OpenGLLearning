
#include "../../../include/Core/System/Renderer.h"
#include "../../../include/Core/Material.h"


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

void Renderer::setUpShader(Material material, bool textured)
{
    activeShader = material.getShader();
    activeShader.use();
    if (textured) {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;

        int _textureIndex = 0;
        for ( auto _texture : material.getAllTextures() )
        {
            glActiveTexture(GL_TEXTURE0 + _textureIndex);

            switch ( _texture.second )
            {
            case aiTextureType_DIFFUSE:
                activeShader.setInt(("texture_diffuse" + std::to_string(diffuseNr++)), _textureIndex);
                break;
            case aiTextureType_SPECULAR:
                activeShader.setInt(("texture_specular" + std::to_string(specularNr++)), _textureIndex);
                break;
            case aiTextureType_NORMALS:
                activeShader.setInt(("texture_normal" + std::to_string(normalNr++)), _textureIndex);
                break;
            case aiTextureType_HEIGHT:
                activeShader.setInt(("texture_height" + std::to_string(heightNr++)), _textureIndex);
                break;
            default:
                break;
            }

            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, _texture.first);
            
            _textureIndex++;
        }
    }
}

void Renderer::renderGameObject_ToDepthBuffer(GameObject gameobj)
{
    for ( auto mesh : gameobj.getMeshes())
    {
       renderMesh(mesh.getVAO(), mesh.getIndices().size());
    }
}

void Renderer::renderBatch_ToDepthBuffer(std::map<string, GameObject>& renderBatch, Shader shader)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferDepth);
    shader.use();
    glViewport(0, 0, _shadowWidth, _shadowHeight);
    

   for (auto _light : _sceneLights) {
      _light->useLight();

       //shader.setVec3("viewPos", _light->getPosition());
      shader.setMat4("lightSpaceMatrix", _light->getShadowViewProjectionMatrix(true));

      for (auto GO : renderBatch) {
        shader.setMat4("modelMatrix", GO.second.getModelMatrix());
        renderGameObject_ToDepthBuffer(GO.second);
         
      }
   }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderBatch(std::map<string, GameObject>& renderBatch, bool textured)
{

    for (auto GO : renderBatch) {
        if (GO.second.getMaterial().getName() != activeMaterial.getName()) {
            activeMaterial = GO.second.getMaterial();
            setUpShader(activeMaterial, textured);
            activeMaterial.Use();
        } 
        renderGameObject(GO.second, textured, false);
    }
}

void Renderer::renderGameObject(GameObject gameObj, bool texture = true, bool requiredShaderSetUp = false)
{
    //if(requiredShaderSetUp)
        setUpShader(gameObj.getMaterial(), texture);

    gameObj.getMaterial().getShader().setMat4("view", _currentCamera->GetViewMatrix());
    gameObj.getMaterial().getShader().setMat4("model", gameObj.getModelMatrix());
    for ( auto m : gameObj.getMeshes() )
    {
        renderMesh(m.getVAO(), m.getIndices().size());
    }
}
