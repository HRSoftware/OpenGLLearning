#pragma once
#include "../Camera.h"

#include "../GameObject.h"
#include "../Lighting.h"

#include "../Material.h"
#include "../../Core/CurrentSceneStats.h"
#include "../Interfaces/IBaseLight.h"
struct Shader;
struct Material;

class GameObject;
class Camera;
class Model;

//class Renderable
//{
//   private:
//   std::map<std::string, Model> renderableModels;
//   
//   public:
//      std::shared_ptr<Model> getModel(std::string modelName);
//      std::shared_ptr<Model> addModel(std::string fileName);
//};


struct RenderDetails
{
   RenderDetails(): _cam(nullptr), _screenHeight(0), _screenWidth(0)
   {
      
   }

   RenderDetails(std::shared_ptr<Camera> cam, int screenHeight = 768, int screenWidth = 1024)
   {
      _cam = cam;
      _screenHeight = screenHeight;
      _screenWidth = screenWidth;
   }

   std::shared_ptr<Camera> _cam;
   int _screenHeight, _screenWidth;
};

class Renderer
{
   public:
        Renderer(int screenW = 1366, int screenH = 768) : _framebuffer(0), _framebufferDepth(0)
        {
           _screenWidth = screenW;
           _screenHeight = screenH;
           _shadowHeight = screenH / 2;
           _shadowWidth = screenW / 2;
           //initDepthRender();
        }

        void setCamera(std::shared_ptr<Camera> cam);
        void renderGameObject(GameObject gameObj, bool texture, bool requiredShaderSetUp);
        void renderGameObject_ToDepthBuffer(GameObject gameobj);
        void renderMesh(int VAO, int indiceCount);
        void renderBatch_ToDepthBuffer(std::map<std::string, GameObject>& renderBatch, std::shared_ptr<Shader> shader);
        void renderBatch(std::map<std::string, GameObject>& renderBatch, bool textured = true);
        void renderGameObject(GameObject gameobj, bool texture);
        void addLightToScene(std::shared_ptr<IBaseLight> light);
        void initDepthRender();

   private:
        GLuint _framebuffer = 0;
        std::shared_ptr<Camera> _currentCamera = nullptr;
        std::vector<std::shared_ptr<IBaseLight>> _sceneLights{};

        GLuint _framebufferDepth;
        GLuint _depthTexture;
        GLuint _depthRenderBufferObject;


        glm::mat4 _shadowMatrixWithBias;

        GLuint _screenWidth;
        GLuint _screenHeight;
        GLuint _shadowWidth, _shadowHeight;
        std::shared_ptr<Material> activeMaterial = nullptr;


};


