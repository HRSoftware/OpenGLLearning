#pragma once
#include "../Data_Structures/Shader.h"


class IBaseLight
{
public:
	IBaseLight(const glm::vec3& colour, float intensity, glm::vec3 position, float shadowMapSize = 1024)
	{
		_colour = colour;
		_strength = intensity;
		_position = position;
		_lightViewMatrix = glm::lookAt(position,glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		_lightProjectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane);
		_lightViewProjectionMatrix = _lightProjectionMatrix * _lightViewMatrix;
		_shadowMapSizePO2 = shadowMapSize;
		_direction = glm::vec3{1.f};
	};


	virtual ~IBaseLight() = default;
	virtual void useLight() = 0;
	virtual void updateViewProjectionMatrix()
	{
		_lightViewMatrix = glm::lookAt(_position,glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		_lightProjectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane);
		_lightViewProjectionMatrix = _lightProjectionMatrix * _lightViewMatrix;
	}
	

	glm::vec3 getPosition() const { return _position; };
	glm::vec3 getDiffuse() const { return _diffuse; }
	glm::vec3 getAmbient() const { return _ambient;  }
	glm::vec3 getSpecular() const { return _specular; }
	glm::mat4 getShadowViewProjectionMatrix(bool boolRecalculate = false)
	{
		if (boolRecalculate || _lightRecalcNeeded)
		{
			updateViewProjectionMatrix();
         _shadowLightViewProjectionMatrix = _shadowBiasMatrix * _lightViewProjectionMatrix;
		}
			
      return _shadowLightViewProjectionMatrix;
	}

	float getStrength() { return _strength; };

	void setAmbient(glm::vec3 ambient)
	{
		_ambient = ambient;
	}
	void setDiffuse(glm::vec3 diffuse)
	{
		_diffuse = diffuse;
	}
	void setSpecular(glm::vec3 specular)
	{
		_specular = specular;
	}
	bool isLightStatic() const
	{
		return _isLightStatic;
	}

	void setDirection(glm::vec3 dir)
	{
		_direction = dir;
	}

protected:
	Shader _shader;
	glm::vec3 _colour;
	
	float _strength;
	
	float _shadowMapSizePO2;
	float _shadowSoftness;
	
	glm::vec3 _ambient;
	glm::vec3  _diffuse;
	glm::vec3 _specular;
	glm::vec3 _direction;
	glm::vec3 _position;


	glm::mat4 _lightModelMatrix = glm::mat4{ 1.f };
	glm::mat4 _lightViewMatrix;
	glm::mat4 _lightProjectionMatrix;
	glm::mat4 _lightViewProjectionMatrix;
   glm::mat4 _shadowLightViewProjectionMatrix;

   glm::mat4 _shadowBiasMatrix={
      0.5, 0.0, 0.0, 0.0,
      0.0, 0.5, 0.0, 0.0,
      0.0, 0.0, 0.5, 0.0,
      0.5, 0.5, 0.5, 1.0
   };

	float near_plane = 0.1f, far_plane = 1000.f;

	bool _isLightStatic = true;
	bool _lightRecalcNeeded = false;

		
};
