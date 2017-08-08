#pragma once //This is VC++ equivalent of #ifndef
#ifndef TEXTURE_HOLDER_H //This directive ensure that TEXTURE_HOLDER_H is define once
#define TEXTURE_HOLDER_H
#include "stdafx.h"
#include <map>
class TextureHolder
{
public:
	TextureHolder();
	static sf::Texture& GetTexture(std::string const& filename);
	~TextureHolder();
private:
	//a map container from STL to hold a pair of string and texture
	std::map<std::string, sf::Texture> m_Textures;
	//A pointer to point to one instance only
	static TextureHolder * m_s_Instance;
};
#endif

