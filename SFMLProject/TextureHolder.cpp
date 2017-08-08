#include "stdafx.h"
#include "TextureHolder.h"
#include <assert.h>
//Initialise the static pointer
TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);//Check if m_s_Instance is null
	m_s_Instance = this; //if null assign the instance to current object
}

TextureHolder::~TextureHolder()
{}

Texture& TextureHolder::GetTexture(std::string const& filename)
{
	//Get a reference to the m_Textures using the m_s_Instance
	auto& map = m_s_Instance->m_Textures;
	//auto here is equivalent to map<string,Texture>
	//note in future if you changed to hashtable no changes needed

	//Create an iterator to hold the key-value pair
	//search for the required key using the file passed in
	auto keyValuePair = map.find(filename);
	//note auto here is map<string,Texture>::iterator

	//Did we find a match?
	if (keyValuePair != map.end())
	{
		//Yes: Found
		return keyValuePair->second;//Second is the value
	}
	else
	{
		//No: Not found
		//load the texture from the file
		auto& texture = map[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}



