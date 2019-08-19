#pragma once
#include "Interfaces/IBaseLight.h"

class DirectionalLight : public IBaseLight
{
	public:
		DirectionalLight(glm::vec3 clr, float intensity, glm::vec3 position = glm::vec3(1.f)) : IBaseLight(clr, intensity, position)
		{
			_lightViewMatrix = glm::lookAt(_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			_lightProjectionMatrix = glm::ortho(-10.f, 10.f, -10.f, 10.f, near_plane, far_plane);
			_lightViewProjectionMatrix = _lightProjectionMatrix * _lightModelMatrix * _lightViewMatrix;
		}

		void useLight();
		

		private:

};
