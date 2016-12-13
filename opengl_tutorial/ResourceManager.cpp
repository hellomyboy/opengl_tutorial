#include "ResourceManager.h"
#include "TextureCache.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(std::string texturePath)
{
	return _textureCache.getTexture(texturePath);
}
