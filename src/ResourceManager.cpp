#include "ResourceManager.h"

//-------------------------------------
ResourceManager::ResourceManager()
{
	loadResourceManager();
}

//-------------------------------------
ResourceManager& ResourceManager::instance()
{
	static auto resource = ResourceManager();
	return resource;
}
//-------------------------------------
void ResourceManager::loadResourceManager()
{
	m_font.loadFromFile("CrispyTofu.ttf");
	if (!m_catTexture.loadFromFile("cat2.png"))
		std::cout << "fail to load cat\n";
	m_catTexture.setSmooth(true);
	m_catSprite.setTexture(m_catTexture);

}
