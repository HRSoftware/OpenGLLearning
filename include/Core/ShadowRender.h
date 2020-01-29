#pragma once
#include "Interfaces/IBaseLight.h"
#include "GameObject.h"


struct Material;
class GameObject;
class IBaseLight;
class ShadowRender
{
	public:
		ShadowRender(std::shared_ptr<Material> material) : _shadowMaterial(material)
		{
			init();
			_shadowBiasMatrix={
				0.5, 0.0, 0.0, 0.0,
				0.0, 0.5, 0.0, 0.0,
				0.0, 0.0, 0.5, 0.0,
				0.5, 0.5, 0.5, 1.0
			};
		};
		void castShadows(std::vector<std::shared_ptr<GameObject>> renderableObjects);
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
		std::shared_ptr<Material> _shadowMaterial;
		glm::mat4 _shadowBiasMatrix;


		
};

