#include "Skybox.h"

void Skybox::Draw(glm::mat4 view, glm::mat4 projection)
{
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	skyShader.use();
	skyShader.setInt("skybox", 0);

	skyShader.setMat4("view", glm::mat4(glm::mat3(view)));
	skyShader.setMat4("projection", projection);
	

	glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
	
}	

void Skybox::setShader(Shader shader)
{
	skyShader = shader;
}

void Skybox::setUpBuffers()
{
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);

	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);

	glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(GLfloat), skyboxVertices.data(), GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
}

void Skybox::loadSkyboxMap() {

	glGenTextures(1, &skyboxTextureID);

	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	int width, height, nrChannels;
	for (unsigned int i = 0; i < skyboxTextures.size(); i++)
	{

		unsigned char* data = stbi_load(skyboxTextures[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Skybox texture failed to load at path: " << skyboxTextures[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
}

void Skybox::setVerticies(std::vector<float> verts) {
	skyboxVertices = verts;
	setUpBuffers();
}