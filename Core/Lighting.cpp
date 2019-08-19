#include "Lighting.h"


void DirectionalLight::useLight()
{

	if (!_isLightStatic) { //dont recalc the matrix
		_lightViewMatrix = glm::lookAt( _position, 
									 glm::vec3(0.0f, 0.0f, 0.0f),
										glm::vec3(0.0f, 1.0f, 0.0f));
		_lightViewProjectionMatrix = _lightProjectionMatrix * _lightViewMatrix;
	}
}







