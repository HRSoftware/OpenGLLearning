#include "../../include/Core/Primitive_Shapes/Cube.h"
#include "../../include/Core/Scene.h"
#include "../../include/Builders/GameObjectBuilder.h"



bool Scene::initScene(Camera cam)
{
    glfwGetWindowSize(_window, &_screenWidth, &_screenHeight);
    lastX = _screenWidth / 2;
    lastY = _screenHeight / 2;


    _currentCamera = cam;
    InputController::_camera = &cam;

    _renderDetails = RenderDetails(_currentCamera, _screenWidth, _screenHeight);
    glfwSetCursorPosCallback(_window, mouse_callback);
    

    _renderer->initDepthRender();
    _renderer->setCamera(_currentCamera);

    return true;
}

void Scene::loadResources()
{
    resourceManager.loadNewShader(VERTEX | FRAGMENT, "basicShader");
    resourceManager.loadNewShader(VERTEX | FRAGMENT, "shadowMapShader");
    resourceManager.loadNewShader(VERTEX | FRAGMENT, "materialShader");
    resourceManager.loadNewShader(VERTEX | FRAGMENT, "skyboxShader");
    resourceManager.loadNewShader(VERTEX | FRAGMENT, "gridShader");
    resourceManager.loadNewShader(VERTEX | FRAGMENT, "framebufferShader");
    resourceManager.loadNewShader(VERTEX | FRAGMENT, "lightingShader", "basicLighting");
    resourceManager.loadNewShader(VERTEX | FRAGMENT, "modelLoadingShader");
    resourceManager.loadNewShader(VERTEX | FRAGMENT, "debugDepthShader");

    resourceManager.loadNewModel("Building1", "BlockOfFlats/apartment.fbx");



    
    
    /*_shaderVec.emplace("BasicShader", Shader("basicShader"));
    _shaderVec.emplace("shadowMapShaderShader" ,Shader("shadowMapShader", true));
    _shaderVec.emplace("materialShader" ,Shader("materialShader"));
    _shaderVec.emplace("skyboxShader" ,Shader("skyboxShader", true));
    _shaderVec.emplace("gridShader" ,Shader("gridShader", true));
    _shaderVec.emplace("debugDepth" ,Shader("debugDepth"));
    _shaderVec.emplace("framebufferShader" ,Shader("framebufferShader"));
    _shaderVec.emplace("lightingShader" ,Shader("basicLighting"));
    _shaderVec.emplace("modelLoadingShader" ,Shader("modelLoadingShader", true));*/


    

    resourceCache.gameObjectCache.findGameObject("Building1").getResourcePointer()->setPosition({ 0.1f, 0.f, -0.2f });
    resourceCache.gameObjectCache.findGameObject("Building1").getResourcePointer()->setScale({ 0.005f, 0.005f, 0.005f });

    //resourceCache.gameObjectCache.findGameObject("Building2")->setPosition({ 10.f, 0.f, 10.f });
    //resourceCache.gameObjectCache.findGameObject("Building2")->setScale({ 0.005f, 0.005f, 0.005f });
    //resourceCache.gameObjectCache.findGameObject("Building2")->setAngle(90, { 0.0, 1.f, 0.0f });

    //resourceCache.gameObjectCache.findGameObject("Building3")->setPosition({ 25.f, 0.f, 5.f });
    //resourceCache.gameObjectCache.findGameObject("Building3")->setScale({ 0.05f, 0.05f, 0.05f });

     DirectionalLight _sunLight(glm::vec3(.2f, 0.2f, 0.2f), 4.f, { 10.f, 15.f, 4.f });
    _sunLight.setAmbient({ 0.2f, 0.2f, 0.2f });
    _sunLight.setDiffuse({ 0.5f, 0.5f, 0.5f });
    _sunLight.setSpecular({ 0.1f,0.1f, 0.1f });
    _sunLight.setDirection({ -0.2f, -1.0f, -0.3f });
    
    resourceCache.shaderCache.findShader("modelLoadingShader").getResourcePointer()->setFloat("shininess", 10.0f);
    resourceCache.shaderCache.findShader("modelLoadingShader").getResourcePointer()->setVec3("light.position", _sunLight.getPosition());
    resourceCache.shaderCache.findShader("modelLoadingShader").getResourcePointer()->setVec3("light.ambient", _sunLight.getAmbient());
    resourceCache.shaderCache.findShader("modelLoadingShader").getResourcePointer()->setVec3("light.diffuse", _sunLight.getDiffuse());
    resourceCache.shaderCache.findShader("modelLoadingShader").getResourcePointer()->setFloat("light.intensity", _sunLight.getStrength());
    resourceCache.shaderCache.findShader("modelLoadingShader").getResourcePointer()->setVec3("light.specular", _sunLight.getSpecular());

    resourceCache.shaderCache.findShader("lightingShader").getResourcePointer()->setFloat("shininess", 10.f);
    resourceCache.shaderCache.findShader("lightingShader").getResourcePointer()->setVec3("light.position", _sunLight.getPosition());
    resourceCache.shaderCache.findShader("lightingShader").getResourcePointer()->setVec3("light.ambient", _sunLight.getAmbient());
    resourceCache.shaderCache.findShader("lightingShader").getResourcePointer()->setVec3("light.diffuse", _sunLight.getDiffuse());
    //_shaderVec.at("lightingShader").setFloat("light.intensity", _sunLight.getStrength());
    resourceCache.shaderCache.findShader("lightingShader").getResourcePointer()->setVec3("light.specular", _sunLight.getSpecular());

    skybox.setShader(*resourceCache.shaderCache.findShader("skyboxShader").getResourcePointer());
        

    resourceCache.modelCache.findModel("Building1").getResourcePointer()->setMaterial(resourceCache.materialCache.findMaterial("building1Material"));
    //resourceCache.modelCache.findModel("Building2")->setMaterial(resourceCache.materialCache.findMaterial("building1Material"));
    //resourceCache.modelCache.findModel("Building3")->setMaterial(resourceCache.materialCache.findMaterial("building2Material"));
    //resourceCache.modelCache.findModel("gridFloor")->setMaterial(resourceCache.materialCache.findMaterial("gridFloorMaterial"));
};

namespace ImGui {
    static auto vector_getter = [](void* vec, int idx, const char** out_text)
    {
        auto& vector = *static_cast<std::vector<std::string>*>(vec);
        if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
        *out_text = vector.at(idx).c_str();
        return true;
    };

    bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
    {
        if (values.empty()) { return false; }
        return Combo(label, currIndex, vector_getter,
            static_cast<void*>(&values), values.size());
    }

    bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
    {
        if (values.empty()) { return false; }
        return ListBox(label, currIndex, vector_getter,
            static_cast<void*>(&values), values.size());
    }
}

void Scene::run()
{
    glEnable(GL_DEPTH_TEST);
    InputController::_camera = &_currentCamera;
    _renderer->setCamera(_currentCamera);

    const float near_plane = 0.01f;
    const float far_plane = 1000.f;

    std::vector<IBaseLight*> lightVec;
    lightVec.push_back(&_sunLight);
    _renderer->addLightToScene(&_sunLight);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Cube testCube;

    bool show_demo_window = true;

    while (glfwWindowShouldClose(_window) == false) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        UI::updateUI(_window);
        UI::selectList(_GOVec);

        ImGui::Render();


        processInput(_window, deltaTime);
        
        //shaderCache.findShader("debugDepthShader")->use();
        //_renderer->renderBatch_ToDepthBuffer(_GOVec, *resourceCache.shaderCache.findShader("debugDepthShader"));

        resourceCache.shaderCache.findShader("modelLoadingShader").getResourcePointer()->use();
        resourceCache.shaderCache.findShader("modelLoadingShader").getResourcePointer()->setMat4("lightSpaceMatrix", _sunLight.getShadowViewProjectionMatrix());


        glViewport(0, 0, _screenWidth, _screenHeight);

        glClearColor(0.25f, 0.25f, 0.5f, 1.0f);		// Background Fill Color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(_currentCamera.Zoom, (float)_screenWidth / (float)_screenHeight, 0.01f, 1000.f);
        glm::mat4 view = _currentCamera.GetViewMatrix();

        if (glfwGetKey(_window, GLFW_KEY_T) == GLFW_PRESS)
            //sunLight.setPosition(camera.Position);
            _currentCamera.Position = _sunLight.getPosition();

        if (glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS)
            _GOVec["Building1"].rotateBy(0.1f, { 0, 1, 0 });

        resourceCache.shaderCache.findShader("modelLoadingShader").getResourcePointer()->setMat4("projection", projection);
        _renderer->renderBatch(_GOVec);
        //_renderer->renderGameObject()

        testCube.draw();
        skybox.Draw(view, projection);

        //_renderer->renderGameObject_ToDepthBuffer(lightVec, _GOVec["Building1"], ShaderCache::findShader("lightingShader"));
        
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(_window);		// Flip Buffers and Draw
        glfwPollEvents();
    }
}

void Scene::stop()
{
	
}

void Scene::save()
{
	
}

Camera* Scene::getCurrentCamera() {
	return &_currentCamera;
}


//void Scene::processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		_currentCamera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		_currentCamera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		_currentCamera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		_currentCamera.ProcessKeyboard(RIGHT, deltaTime);
//
//
//
//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//		_currentCamera.MovementSpeed = _currentCamera.boostSpeed;
//
//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
//		_currentCamera.MovementSpeed = _currentCamera.normalSpeed;
//
//
//
//}
//
//void Scene::mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	_currentCamera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void Scene::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	_currentCamera.ProcessMouseScroll(yoffset);
//}
