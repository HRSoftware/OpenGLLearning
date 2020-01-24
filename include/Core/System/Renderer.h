#pragma once
#include "../Camera.h"

#include "../GameObject.h"
#include "../Lighting.h"

#include <string>
#include "../Material.h"
#include "../../Core/CurrentSceneStats.h"

class Renderable
{
   private:
   std::map<std::string, Model> RenerableModels;
   
   public:
      std::shared_ptr<Model> getModel(std::string modelName);
      std::shared_ptr<Model> addModel(std::string fileName);
};


struct RenderDetails
{
   RenderDetails(): _cam(nullptr), _screenHeight(0), _screenWidth(0)
   {
      
   }

   RenderDetails(Camera& cam, int screenHeight = 768, int screenWidth = 1024)
   {
      _cam = &cam;
      _screenHeight = screenHeight;
      _screenWidth = screenWidth;
   }
   Camera* _cam;
   int _screenHeight, _screenWidth;
};

class Renderer
{
   public:
        Renderer(int screenW = 1366, int screenH = 768) : _framebuffer(0), _currentCamera(nullptr), _framebufferDepth(0)
        {
           _screenWidth = screenW;
           _screenHeight = screenH;
           _shadowHeight = screenH / 2;
           _shadowWidth = screenW / 2;
           //initDepthRender();
        }

        void setCamera(Camera& cam);
        void renderGameObject(GameObject gameObj, bool texture, bool requiredShaderSetUp);
        void renderGameObject_ToDepthBuffer(GameObject gameobj);
        void renderMesh(int VAO, int indiceCount);
        void renderBatch_ToDepthBuffer(std::map<string, GameObject>& renderBatch, Shader shader);
        void renderBatch(std::map<string, GameObject>& renderBatch, bool textured = true);
        void renderGameObject(GameObject gameobj, bool texture);
        void addLightToScene(IBaseLight* light);
        void initDepthRender();

   private:
        GLuint _framebuffer;
        Camera* _currentCamera;
        std::vector<IBaseLight*> _sceneLights;

        GLuint _framebufferDepth;
        GLuint _depthTexture;
        GLuint _depthRenderBufferObject;


        glm::mat4 _shadowMatrixWithBias;

        GLuint _screenWidth;
        GLuint _screenHeight;
        GLuint _shadowWidth, _shadowHeight;
        Shader activeShader;
        Material* activeMaterial;


};


