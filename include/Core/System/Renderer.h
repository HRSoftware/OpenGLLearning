#pragma once
#include "../CurrentSceneStats.h"

#include "../GameObject.h"
#include "../Lighting.h"

#include <string>
#include "../Material.h"

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
   RenderDetails()
   {
      
   }

   int _screenHeight = SceneStats::_screenHeight;
   int _screenWidth = SceneStats::_screenWidth;
};

class Renderer
{
   public:
        Renderer(int screenW = 1366, int screenH = 768) : _framebuffer(0), _framebufferDepth(0)
        {
           _screenWidth = SceneStats::_screenWidth;
           _screenHeight = SceneStats::_screenHeight;
           _shadowHeight = screenH / 2;
           _shadowWidth = screenW / 2;
           //initDepthRender();
        }

        void renderGameObject(GameObject gameObj, bool texture, bool requiredShaderSetUp);
        void renderGameObject_ToDepthBuffer(const GameObject& gameobj);
        void renderMesh(int VAO, int indiceCount);
        void setUpShader(Material, bool = true);
        void renderBatch_ToDepthBuffer(std::map<string, GameObject>& renderBatch, Shader shader);
        void renderBatch(std::map<string, GameObject>& renderBatch, bool textured = true);
        void renderGameObject(GameObject gameobj, bool texture);
        void addLightToScene(IBaseLight* light);
        void initDepthRender();

   private:
        GLuint _framebuffer;
        std::vector<IBaseLight*> _sceneLights;

        GLuint _framebufferDepth;
        GLuint _depthTexture;
        GLuint _depthRenderBufferObject;


        glm::mat4 _shadowMatrixWithBias;

        GLuint _screenWidth;
        GLuint _screenHeight;
        GLuint _shadowWidth, _shadowHeight;
        Shader activeShader;
        Material activeMaterial;


};


