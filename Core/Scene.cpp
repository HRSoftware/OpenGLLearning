#include "Scene.h"
#include <glm/detail/_noise.hpp>


bool Scene::initScene(::GLFWwindow& wnd, glm::vec2 screenInfo)
{
	_window = &wnd;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	// Check for Valid Context
	if (_window == nullptr) {
		fprintf(stderr, "Failed to Create OpenGL Context");
		return false;
	}

	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init. OpenGL Context" << std::endl;
		return false;
	}

	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	_currentCamera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	_screenDimensions = screenInfo;
	_renderDetails = RenderDetails(_currentCamera, _screenDimensions.x, _screenDimensions.y);

	return true;
}

void Scene::loadResources()
{
	_modelManager.loadModeltoMemory("House/house_obj.obj", "Building1");
	_modelManager.loadModeltoMemory("Old_House/Old House.obj", "Building3");

	_shaderVec.insert_or_assign("BasicShader", Shader("basicShader"));
	_shaderVec.insert_or_assign("shadowMapShaderShader" ,Shader("shadowMapShader", true));
	_shaderVec.insert_or_assign("materialShader" ,Shader("materialShader"));
	_shaderVec.insert_or_assign("skyboxShader" ,Shader("skyboxShader", true));
	_shaderVec.insert_or_assign("gridShader" ,Shader("gridShader"));
	_shaderVec.insert_or_assign("debugDepth" ,Shader("debugDepth"));
	_shaderVec.insert_or_assign("framebufferShader" ,Shader("framebufferShader"));
	_shaderVec.insert_or_assign("lightingShader" ,Shader("basicLighting"));
	_shaderVec.insert_or_assign("modelLoadingShader" ,Shader("modelLoadingShader", true));


	_GOVec.insert_or_assign("Building1", GameObject(_modelManager.getModelByName("Building1"), _shaderVec["modelLoadingShader"], _renderDetails));
	_GOVec.insert_or_assign("Building2", GameObject(_modelManager.getModelByName("Building1"), _shaderVec["modelLoadingShader"], _renderDetails));
	_GOVec.insert_or_assign("Building3", GameObject(_modelManager.getModelByName("Building2"), _shaderVec["modelLoadingShader"], _renderDetails));

	_GOVec["Building1"]->setPosition({ 0.1f, 0.f, -0.2f });
	_GOVec["Building1"]->setScale({ 0.005f, 0.005f, 0.005f }); 
					   
	_GOVec["Building2"]->setPosition({ 10.f, 0.f, 10.f });
	_GOVec["Building2"]->setScale({ 0.005f, 0.005f, 0.005f });
	_GOVec["Building2"]->setAngle(90, { 0.0, 1.f, 0.0f });
					
	_GOVec["Building3"]->setPosition({ 25.f, 0.f, 5.f });
	_GOVec["Building3"]->setScale({ 0.05f, 0.05f, 0.05f});


	_sunLight = DirectionalLight(glm::vec3(.2f, 0.2f, 0.2f), 4.f, { 10.f, 15.f, 4.f });
	_sunLight.setAmbient({ 0.2f, 0.2f, 0.2f });
	_sunLight.setDiffuse({ 0.5f, 0.5f, 0.5f}); 
	_sunLight.setSpecular({ 0.1f,0.1f, 0.1f });
	_sunLight.setDirection({ -0.2f, -1.0f, -0.3f });

	_shaderVec["modelLoadingShader"].setFloat("shininess", 10.0f);
	_shaderVec["modelLoadingShader"].setVec3("light.position", _sunLight.getPosition());
	_shaderVec["modelLoadingShader"].setVec3("light.ambient", _sunLight.getAmbient());
	_shaderVec["modelLoadingShader"].setVec3("light.diffuse", _sunLight.getDiffuse());
	_shaderVec["modelLoadingShader"].setFloat("light.intensity", _sunLight.getStrength());
	_shaderVec["modelLoadingShader"].setVec3("light.specular", _sunLight.getSpecular());

	_shaderVec["lightingShader"].setFloat("shininess", 10.f);
	_shaderVec["lightingShader"].setVec3("light.position", _sunLight.getPosition());
	_shaderVec["lightingShader"].setVec3("light.ambient", _sunLight.getAmbient());
	_shaderVec["lightingShader"].setVec3("light.diffuse", _sunLight.getDiffuse());
	//_shaderVec["lightingShader"].setFloat("light.intensity", sunLight.getStrength());
	_shaderVec["lightingShader"].setVec3("light.specular", _sunLight.getSpecular());

	_floorGrid = FloorGrid(_shaderVec["gridShader"], _renderDetails);

	skybox.setShader(_shaderVec["skyboxShader"]);

	_GOVec.insert_or_assign("floorGrid", _floorGrid);


}

void Scene::run()
{
	while (glfwWindowShouldClose(_window) == false)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(_window);

		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		float near_plane = 0.01f, far_plane = 1000.f;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
		// render scene from light's point of view
		_shaderVec["newShadowRenderShader"].use();
		_shaderVec["newShadowRenderShader"].setMat4("lightSpaceMatrix", lightSpaceMatrix);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);


		//Building1.Draw(newShadowRenderShader);
		//Building2.Draw(newShadowRenderShader);
		//Building3.Draw(newShadowRenderShader);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);


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

		if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS)
			_GOVec["Building2"]->moveXBy(0.1f);

		if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS)
			_GOVec["Building2"]->moveXBy(-0.1f);

		if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			_GOVec["Building2"]->moveZBy(0.1f);

		if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS)
			_GOVec["Building2"]->moveZBy(-0.1f);

		_GOVec["Building1"]->Draw(_shaderVec["newShadowRenderShader"] );
		_GOVec["Building2"]->Draw(_shaderVec["lightingShader"]);
		_GOVec["Building2"]->Draw(_shaderVec["newShadowRenderShader"]);
		_GOVec["floorGrid"]->Draw();

		skybox.Draw(view, projection);

		glfwPollEvents();


		//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		//glViewport(0, 0, WIDTH / 2, HEIGHT/ 2);
		//Building1.Draw(newShadowRenderShader, false);
		//Building2.Draw();
		//Building3.Draw(false);


		glfwSwapBuffers(_window);		// Flip Buffers and Draw
	}
}
void Scene::stop()
{
	
}
void Scene::save()
{
	
}


void Scene::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		_currentCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		_currentCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		_currentCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		_currentCamera.ProcessKeyboard(RIGHT, deltaTime);



	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		_currentCamera.MovementSpeed = _currentCamera.boostSpeed;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		_currentCamera.MovementSpeed = _currentCamera.normalSpeed;



}

void Scene::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	_currentCamera.ProcessMouseMovement(xoffset, yoffset);
}

void Scene::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	_currentCamera.ProcessMouseScroll(yoffset);
}
