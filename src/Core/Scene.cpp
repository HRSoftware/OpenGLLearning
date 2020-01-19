#include "../../include/Core/Primitive_Shapes/Cube.h"
#include "../../include/Core/Scene.h"
#include "../../include/Builders/GameObjectBuilder.h"
#include "../../include/Helpers/OpenGLCalls.h"
#include "../../include/Core/Nodes/Node.h"


bool Scene::initScene(Camera cam)
{
    glfwGetWindowSize(_window, &SceneStats::_screenWidth, &SceneStats::_screenHeight);
    SceneStats::lastX = SceneStats::_screenWidth / 2;
    SceneStats::lastY = SceneStats::_screenHeight / 2;

    glfwSetCursorPosCallback(_window, mouse_callback);
    

    _renderer->initDepthRender();

    return true;
}
void Scene::moreHouses()
{
    int houseNum = 1;
    for(int i = 0; i < 10; i++)
        for ( int j = 0; j < 10; j++ )
        {
            GameObject house = resourceCache.gameObjectCache.findGameObject("Building1");
            house.setPosition({ 10.f * (i + 1), 0, 10.f * (j + 1)});

            _GOVec.insert_or_assign("House" + to_string(houseNum), house);
            houseNum++;
        }
}
void Scene::loadResources()
{
    resourceManager.LoadAllBasicResources();

    _GOVec.insert_or_assign("House", resourceCache.gameObjectCache.findGameObject("Building1"));
    


     DirectionalLight _sunLight(glm::vec3(.2f, 0.2f, 0.2f), 4.f, { 10.f, 15.f, 4.f });
    _sunLight.setAmbient({ 0.2f, 0.2f, 0.2f });
    _sunLight.setDiffuse({ 0.5f, 0.5f, 0.5f });
    _sunLight.setSpecular({ 0.1f,0.1f, 0.1f });
    _sunLight.setDirection({ -0.2f, -1.0f, -0.3f });

    HR::setFloat(resourceCache.shaderCache.findShader("modelLoadingShader"), "shininess", 10.f);
    HR::setVec3(resourceCache.shaderCache.findShader("modelLoadingShader"), "light.position", _sunLight.getPosition());
    HR::setVec3(resourceCache.shaderCache.findShader("modelLoadingShader"), "light.ambient", _sunLight.getAmbient());
    HR::setVec3(resourceCache.shaderCache.findShader("modelLoadingShader"), "light.diffuse", _sunLight.getDiffuse());
    HR::setFloat(resourceCache.shaderCache.findShader("modelLoadingShader"), "light.intensity", _sunLight.getStrength());
    HR::setVec3(resourceCache.shaderCache.findShader("modelLoadingShader"), "light.specular", _sunLight.getSpecular());

    HR::setFloat(resourceCache.shaderCache.findShader("lightingShader"), "shininess", 10.f);
    HR::setVec3(resourceCache.shaderCache.findShader("lightingShader"),"light.position", _sunLight.getPosition());
    HR::setVec3(resourceCache.shaderCache.findShader("lightingShader"),"light.ambient", _sunLight.getAmbient());
    HR::setVec3(resourceCache.shaderCache.findShader("lightingShader"),"light.diffuse", _sunLight.getDiffuse());
    //_shaderVec.at("lightingShader").setFloat("light.intensity", _sunLight.getStrength());
    HR::setVec3(resourceCache.shaderCache.findShader("lightingShader"),"light.specular", _sunLight.getSpecular());

    skybox.setShader(resourceCache.shaderCache.findShader("skyboxShader"));
        
    //resourceCache.modelCache.findModel("House").setMaterial(resourceCache.materialCache.findMaterial("building1Material"));
    //resourceCache.modelCache.findModel("Building2")->setMaterial(resourceCache.materialCache.findMaterial("building1Material"));
    //resourceCache.modelCache.findModel("Building3")->setMaterial(resourceCache.materialCache.findMaterial("building2Material"));

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

    const float near_plane = 0.01f;
    const float far_plane = 1000.f;

    std::vector<IBaseLight*> lightVec;
    lightVec.push_back(&_sunLight);
    _renderer->addLightToScene(&_sunLight);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float numberOfFrames = 0;
    lastFrame = glfwGetTime();
    float drawTime;
    UI::generate_data();


    while (glfwWindowShouldClose(_window) == false) {
        float currentFrame = glfwGetTime();
        SceneStats::deltaTime = currentFrame - lastFrame;
        /*numberOfFrames++;

        if(deltaTime >= 1.0)
        {
            drawTime = 1000.0/float(numberOfFrames);
            numberOfFrames = 0;
            lastFrame += 1.0;
        }*/
        //lastFrame = currentFrame;

        UI::updateUI(_window);
        UI::selectList(_GOVec);
        ImGui::Render();
        processInput(_window, SceneStats::deltaTime);

        HR::useProgram(resourceCache.shaderCache.findShader("modelLoadingShader").programID);
        HR::setMat4(resourceCache.shaderCache.findShader("modelLoadingShader"), "lightSpaceMatrix", _sunLight.getShadowViewProjectionMatrix());


        glViewport(0, 0, SceneStats::_screenWidth, SceneStats::_screenHeight);

        glClearColor(0.25f, 0.25f, 0.5f, 1.0f);		// Background Fill Color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(SceneStats::currentCamera->Zoom, static_cast<float>(SceneStats::_screenWidth) / static_cast<float>(SceneStats::_screenHeight), 0.01f, 1000.f);
        glm::mat4 view = SceneStats::currentCamera->GetViewMatrix();

 
        if (glfwGetKey(_window, GLFW_KEY_T) == GLFW_PRESS)
            //sunLight.setPosition(camera.Position);
            SceneStats::currentCamera->Position = _sunLight.getPosition();

        if (glfwGetKey(_window, GLFW_KEY_M) == GLFW_PRESS)
            moreHouses();

        if (glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS)
            _GOVec["House"].rotateBy(0.1f, { 0, 1, 0 });

        HR::setMat4(resourceCache.shaderCache.findShader("modelLoadingShader"), "projection", projection);
       
        
        skybox.Draw(view, projection);
        _renderer->renderBatch(_GOVec);
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
