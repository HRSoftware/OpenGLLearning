#include "TextureManager.h"


unsigned int TextureManager::getTextureByName(std::string texName)
{
	return _textureMap.find(texName)->second;
}

unsigned int TextureManager::addTexture(std::string texName)
{
	unsigned int tempID = getNextID();
	_textureMap[texName] = tempID;
	return tempID;
}


void TextureManager::removeTextureByName(std::string textureToDestroy)
{
	_reusableIDs.push_back(_textureMap[textureToDestroy]);
	_textureMap[textureToDestroy] = 0;
}

void TextureManager::removeTextureByID(unsigned int id)
{
	for (auto text = _textureMap.begin(); text != _textureMap.end(); ++text) {
		if (text->second == id) {
			_reusableIDs.push_back(id);
			text->second = 0;
		}
	}
}

unsigned int TextureManager::getNextID()
{
	unsigned int tempIDHolder;
	if (!_reusableIDs.empty())
		return _reusableIDs.front();
	else
		tempIDHolder = nextNewID;

	nextNewID++;
	return tempIDHolder;
}
