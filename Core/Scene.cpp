#include "Scene.h"


bool Scene::initScene(glm::vec2 screenInfo, Camera cam)
{
	_screenDimensions = screenInfo;
	_currentCamera = cam;
	InputController::_camera = &cam;
	_renderDetails = RenderDetails(_currentCamera, _screenDimensions.x, _screenDimensions.y);
	glfwSetCursorPosCallback(_window, mouse_callback);
	
	return true;
}

void Scene::loadResources()
{
	_modelManager.loadModeltoMemory("House/house_obj.obj", "Building1");
	_modelManager.loadModeltoMemory("Old_House/Old House.obj", "Building3");

	_shaderVec.emplace("BasicShader", Shader("basicShader"));
	_shaderVec.emplace("shadowMapShaderShader" ,Shader("shadowMapShader", true));
	_shaderVec.emplace("materialShader" ,Shader("materialShader"));
	_shaderVec.emplace("skyboxShader" ,Shader("skyboxShader", true));
	_shaderVec.emplace("gridShader" ,Shader("gridShader", true));
	_shaderVec.emplace("debugDepth" ,Shader("debugDepth"));
	_shaderVec.emplace("framebufferShader" ,Shader("framebufferShader"));
	_shaderVec.emplace("lightingShader" ,Shader("basicLighting"));
	_shaderVec.emplace("modelLoadingShader" ,Shader("modelLoadingShader", true));


	_GOVec.emplace("Building1", new GameObject(_modelManager.getModelByName("Building1"), _shaderVec["modelLoadingShader"], _renderDetails));
	_GOVec.emplace("Building2", new GameObject(_modelManager.getModelByName("Building1"), _shaderVec["modelLoadingShader"], _renderDetails));
	_GOVec.emplace("Building3", new GameObject(_modelManager.getModelByName("Building2"), _shaderVec["modelLoadingShader"], _renderDetails));

	_GOVec.at("Building1")->setPosition({ 0.1f, 0.f, -0.2f });
	_GOVec.at("Building1")->setScale({ 0.005f, 0.005f, 0.005f }); 
	//				   
	//_GOVec["Building2"]->setPosition({ 10.f, 0.f, 10.f });
	//_GOVec["Building2"]->setScale({ 0.005f, 0.005f, 0.005f });
	//_GOVec["Building2"]->setAngle(90, { 0.0, 1.f, 0.0f });
					
	_GOVec.at("Building3")->setPosition({ 25.f, 0.f, 5.f });
	_GOVec.at("Building3")->setScale({ 0.05f, 0.05f, 0.05f});


	_sunLight = DirectionalLight(glm::vec3(.2f, 0.2f, 0.2f), 4.f, { 10.f, 15.f, 4.f });
	_sunLight.setAmbient({ 0.2f, 0.2f, 0.2f });
	_sunLight.setDiffuse({ 0.5f, 0.5f, 0.5f}); 
	_sunLight.setSpecular({ 0.1f,0.1f, 0.1f });
	_sunLight.setDirection({ -0.2f, -1.0f, -0.3f });

	_shaderVec.at("modelLoadingShader").setFloat("shininess", 10.0f);
	_shaderVec.at("modelLoadingShader").setVec3("light.position", _sunLight.getPosition());
	_shaderVec.at("modelLoadingShader").setVec3("light.ambient", _sunLight.getAmbient());
	_shaderVec.at("modelLoadingShader").setVec3("light.diffuse", _sunLight.getDiffuse());
	_shaderVec.at("modelLoadingShader").setFloat("light.intensity", _sunLight.getStrength());
	_shaderVec.at("modelLoadingShader").setVec3("light.specular", _sunLight.getSpecular());

	_shaderVec.at("lightingShader").setFloat("shininess", 10.f);
	_shaderVec.at("lightingShader").setVec3("light.position", _sunLight.getPosition());
	_shaderVec.at("lightingShader").setVec3("light.ambient", _sunLight.getAmbient());
	_shaderVec.at("lightingShader").setVec3("light.diffuse", _sunLight.getDiffuse());
	//_shaderVec.at("lightingShader").setFloat("light.intensity", _sunLight.getStrength());
	_shaderVec.at("lightingShader").setVec3("light.specular", _sunLight.getSpecular());

	//_floorGrid = FloorGrid(_shaderVec["gridShader"], _renderDetails);

	skybox.setShader(_shaderVec["skyboxShader"]);

	//_GOVec.insert_or_assign("floorGrid", _floorGrid);


}

void Scene::run()
{
	
	glEnable(GL_DEPTH_TEST);
	InputController::_camera = &_currentCamera;

	while (glfwWindowShouldClose(_window) == false)
	{
		float near_plane = 0.01f, far_plane = 1000.f;
		glm::mat4 _lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		glm::mat4 _lightView = glm::lookAt(glm::vec3(1.2f, 1.0f, 2.0f), 
										glm::vec3(0.0f, 0.0f, 0.0f),
											glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 _lightSpaceMatrix = _lightProjection * _lightView;


		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(_window, deltaTime);
		
		// render scene from light's point of view
		_shaderVec.at("modelLoadingShader").use();
		_shaderVec.at("modelLoadingShader").setMat4("lightSpaceMatrix", _lightSpaceMatrix);

		//glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		/*glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);*/


		//Building1.Draw(newShadowRenderShader);
		//Building2.Draw(newShadowRenderShader);
		//Building3.Draw(newShadowRenderShader);

		


		//shadowRender.castShadows(buildings);



		glViewport(0, 0, WIDTH, HEIGHT);

		glClearColor(0.25f, 0.25f, 0.5f, 1.0f);		// Background Fill Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glm::mat4 projection = glm::perspective(_currentCamera.Zoom, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.f);
		glm::mat4 view = _currentCamera.GetViewMatrix();

		if (glfwGetKey(_window, GLFW_KEY_T) == GLFW_PRESS)
			//sunLight.setPosition(camera.Position);
			_currentCamera.Position = _sunLight.getPosition();

		if (glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS)
			_GOVec["Building1"]->rotateBy(0.1f, { 0, 1, 0 });

		/*if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS)
			_GOVec["Building2"]->moveXBy(0.1f);

		if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS)
			_GOVec["Building2"]->moveXBy(-0.1f);

		if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			_GOVec["Building2"]->moveZBy(0.1f);

		if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS)
			_GOVec["Building2"]->moveZBy(-0.1f);*/
		_shaderVec.at("modelLoadingShader").setMat4("projection", projection);
		Scene::_GOVec.at("Building1")->Draw(_shaderVec.at("modelLoadingShader"));
		/*Scene::_GOVec["Building2"]->Draw(_shaderVec["lightingShader"]);
		Scene::_GOVec["Building2"]->Draw(_shaderVec["newShadowRenderShader"]);*/
		//Scene::_GOVec["floorGrid"]->Draw();

		//skybox.Draw(view, projection);

		glfwPollEvents();
		

		//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		//glViewport(0, 0, WIDTH / 2, HEIGHT/ 2);
		//Building1.Draw(newShadowRenderShader, false);
		//Building2.Draw();
		//Building3.Draw(false);


		glfwSwapBuffers(_window);		// Flip Buffers and Draw
	}
	glfwTerminate();
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
