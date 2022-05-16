#pragma once

#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "macros.h"

class ResourceManager
{
public:
	static ResourceManager& instance();
	ResourceManager(const ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;

	Font& getFont() { return m_font; }
	Sprite& getSprite() { return m_catSprite; }
	Texture& getTexture() { return m_catTexture; }

private:
	ResourceManager();
	void loadResourceManager();

	Font m_font;
	Sprite m_catSprite;
	Texture m_catTexture;
};