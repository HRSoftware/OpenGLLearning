#include "TextureManager.h"


GLuint TextureManager::getTextureByName(std::string texName)
{
	return _textureMap.find(texName)->second;
}

GLuint TextureManager::addTexture(std::string texName)
{
	GLuint tempID = getNextID();
	_textureMap[texName] = tempID;
	return tempID;
}


void TextureManager::removeTextureByName(std::string textureToDestroy)
{
	_reusableIDs.push_back(_textureMap[textureToDestroy]);
	_textureMap[textureToDestroy] = 0;
}

void TextureManager::removeTextureByID(GLuint id)
{
	for (auto text = _textureMap.begin(); text != _textureMap.end(); ++text) {
		if (text->second == id) {
			_reusableIDs.push_back(id);
			text->second = 0;
		}
	}
}

GLuint TextureManager::getNextID()
{
	GLuint tempIDHolder;
	if (!_reusableIDs.empty())
		return _reusableIDs.front();
	else
		tempIDHolder = nextNewID;

	nextNewID++;
	return tempIDHolder;
}
