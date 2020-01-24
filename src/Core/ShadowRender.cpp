
#include "../../include/Core/ShadowRender.h"


void ShadowRender::castShadows(std::vector<GameObject*> &renderableObjects)
{
   glViewport(0, 0, _SHADOW_WIDTH, _SHADOW_HEIGHT);
   
   glClear(GL_DEPTH_BUFFER_BIT);
   glBindFramebuffer(GL_FRAMEBUFFER, _shadowFbo);
   
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   //glEnable(GL_CULL_FACE);
   //glCullFace(GL_BACK);
   
   for ( auto light : _staticLights ) //for each lights render each GameObject
   {
      light->useLight();
      _shadowMatrixWithBias = light->getShadowViewProjectionMatrix(true) * _shadowBiasMatrix;
      HR::setMat4(_shadowMaterial.getShader(), "lightSpaceMatrix", _shadowMatrixWithBias);
      for ( auto renderable : renderableObjects )
      {
          HR::setMat4(_shadowMaterial.getShader(),"model", renderable->getModelMatrix());
      }
   }
   glBindFramebuffer(GL_FRAMEBUFFER, 0);



}
void ShadowRender::addLight(IBaseLight& light)
{
   light.isLightStatic() ? _staticLights.push_back(&light) : _dynamicLights.push_back(&light);
}

void ShadowRender::init()
{
   glGenRenderbuffers(1, &_renderBO);
   glBindRenderbuffer(GL_RENDERBUFFER, _renderBO);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderBO);


   glGenFramebuffers(1, &_shadowFbo);
   glBindFramebuffer(GL_FRAMEBUFFER, _shadowFbo);			//attach depth texture to FBO
                        //Creating Texture
   glGenTextures(1, &_shadowTexture);
   glBindTexture(GL_TEXTURE_2D, _shadowTexture);
   //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _SHADOW_WIDTH, _SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
   glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, _SHADOW_WIDTH, _SHADOW_HEIGHT);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
   /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);*/

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL);
   //glBindTexture(GL_TEXTURE_2D, 0);


   

   //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _shadowTexture, 0);
   glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _shadowTexture, 0);

   glDrawBuffer(GL_DEPTH_ATTACHMENT);
   glReadBuffer(GL_NONE);
   

   if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
   else
      std::cout << "Framebuffer is complete!" << std::endl;


   glBindFramebuffer(GL_FRAMEBUFFER, 0);


}
