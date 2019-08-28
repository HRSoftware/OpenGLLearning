#pragma once
#include <map>
#include <string>
#include <vector>

class TextureManager
{
	public:
		 TextureManager()
		{
			
		}
		 unsigned int getTextureByName(std::string texName);
		 unsigned int addTexture(std::string);
	void removeTextureByName(std::string textureToDestroy);
	void removeTextureByID(unsigned int id);

private:
	std::map<std::string, unsigned int> _textureMap;

	unsigned int nextNewID = 1;
	std::vector<unsigned int> _reusableIDs;

	unsigned int getNextID();
};

