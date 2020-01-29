#pragma once

#include "Camera.h"
#include "../Managers/ModelManager.h"
#include "Lighting.h"
#include "Skybox.h"
#include "System/InputController.h"


#include "System/Renderer.h"
#include "UI/UI.h"

#include "../Builders/MaterialBuilder.h"
#include "../Builders/ShaderBuilder.h"
#include "../Builders/GameObjectBuilder.h"
#include "../Builders/ModelBuilder.h"
#include "../Managers/ResourceMangager.h"
#include "../Helpers/ShaderFunctions.h"
class Scene
{
public:
	Scene(std::shared_ptr<GLFWwindow> wnd, std::shared_ptr<Renderer> renderer);
	bool initScene(std::shared_ptr<Camera> cam = nullptr);
	void loadResources();
	void run();
	void stop();
	void save();

	private:

	std::shared_ptr<InputController> _inputController;
	std::shared_ptr<Renderer> _renderer;

	std::map<string, Shader> _shaderVec;
	std::map<string, GameObject> _GOVec;
	RenderDetails _renderDetails;

    ResourceCache resourceCache;
    ResourceManager resourceManager;
    
	

	std::shared_ptr<IBaseLight> _sunLight;
	Skybox skybox;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

};

static void processInput(GLFWwindow* _window, float deltaTime);

static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

