#pragma once

#include "../../include/Helpers/ShaderFunctions.h"
#include "Material.h"


class Skybox
{
public:
	Skybox() {
		setUpBuffers();
		loadSkyboxMap();
	}
	
	Skybox(std::vector<std::string> textures) {
		skyboxTextures = textures;
		setUpBuffers();
		loadSkyboxMap();
	}
	~Skybox(){}
	void Draw(glm::mat4 view, glm::mat4 projection);
	void setMaterial(Material material);
	void setVerticies(std::vector<float> vert);

private:

	GLuint skyboxVAO, skyboxVBO;
	GLuint skyboxTextureID;


	void loadSkyboxMap();
	void setUpBuffers();
	
	Material skyMaterial;

	std::vector<float> skyboxVertices = {
	// positions          

			  -10.0f,  10.0f, -10.0f,
			  -10.0f, -10.0f, -10.0f,
			   10.0f, -10.0f, -10.0f,
			   10.0f, -10.0f, -10.0f,
			   10.0f,  10.0f, -10.0f,
			  -10.0f,  10.0f, -10.0f,

			  -10.0f, -10.0f,  10.0f,
			  -10.0f, -10.0f, -10.0f,
			  -10.0f,  10.0f, -10.0f,
			  -10.0f,  10.0f, -10.0f,
			  -10.0f,  10.0f,  10.0f,
			  -10.0f, -10.0f,  10.0f,

			   10.0f, -10.0f, -10.0f,
			   10.0f, -10.0f,  10.0f,
			   10.0f,  10.0f,  10.0f,
			   10.0f,  10.0f,  10.0f,
			   10.0f,  10.0f, -10.0f,
			   10.0f, -10.0f, -10.0f,

			  -10.0f, -10.0f,  10.0f,
			  -10.0f,  10.0f,  10.0f,
			   10.0f,  10.0f,  10.0f,
			   10.0f,  10.0f,  10.0f,
			   10.0f, -10.0f,  10.0f,
			  -10.0f, -10.0f,  10.0f,

			  -10.0f,  10.0f, -10.0f,
			   10.0f,  10.0f, -10.0f,
			   10.0f,  10.0f,  10.0f,
			   10.0f,  10.0f,  10.0f,
			  -10.0f,  10.0f,  10.0f,
			  -10.0f,  10.0f, -10.0f,

			  -10.0f, -10.0f, -10.0f,
			  -10.0f, -10.0f,  10.0f,
			   10.0f, -10.0f, -10.0f,
			   10.0f, -10.0f, -10.0f,
			  -10.0f, -10.0f,  10.0f,
			   10.0f, -10.0f,  10.0f
};

	std::vector<std::string> skyboxTextures = {	
		"./Resources/Skybox/Default/right.jpg",
		"./Resources/Skybox/Default/left.jpg",
		"./Resources/Skybox/Default/top.jpg",
		"./Resources/Skybox/Default/bottom.jpg",
		"./Resources/Skybox/Default/front.jpg",
		"./Resources/Skybox/Default/back.jpg"		
	};
	

};
