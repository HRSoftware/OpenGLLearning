#pragma once
#include "Interfaces/IBaseLight.h"
#include <vector>
#include "GameObject.h"

class ShadowRender
{
	public:
		ShadowRender(Shader shader) : _shadowShader(shader)
		{
			init();
			_shadowBiasMatrix={
				0.5, 0.0, 0.0, 0.0,
				0.0, 0.5, 0.0, 0.0,
				0.0, 0.0, 0.5, 0.0,
				0.5, 0.5, 0.5, 1.0
			};
		};
		void castShadows(std::vector<GameObject*> &renderableObjects);
		void addLight(IBaseLight& light);

		void init();
		GLuint _shadowTexture;
		GLuint _shadowFbo;
	private:

		std::vector<IBaseLight*> _staticLights;
		std::vector<IBaseLight*> _dynamicLights;
		GLuint _preRenderedShadows;

		GLuint _renderBO;
		const GLuint _SHADOW_WIDTH = 1024;
		const GLuint _SHADOW_HEIGHT = 1024;
		glm::mat4 _shadowMatrixWithBias;
		Shader _shadowShader;
		glm::mat4 _shadowBiasMatrix;


		
};

