#include "TextureCache.h"
#include <iterator>
#include "LoadImage.h"
#include <iostream>

namespace Engine {

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);
		if (mit == _textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			_textureMap.insert(make_pair(texturePath, newTexture));

			std::cout << "use cached texture" << std::endl;

			return newTexture;
		}

		std::cout << "load texture" << std::endl;

		return mit->second;
	}

}