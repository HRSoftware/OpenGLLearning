#pragma once
#include <map>
#include <string>
#include <glad/glad.h>
#include <vector>

class TextureManager
{
	public:
		 TextureManager()
		{
			
		}
	GLuint getTextureByName(std::string texName);
	GLuint addTexture(std::string);
	void removeTextureByName(std::string textureToDestroy);
	void removeTextureByID(GLuint id);

private:
	std::map<std::string, GLuint> _textureMap;

	GLuint nextNewID = 1;
	std::vector<GLuint> _reusableIDs;

	GLuint getNextID();
};

