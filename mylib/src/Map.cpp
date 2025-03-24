#include "Map.h"
#include "TextureManager.h"
#include <iostream>

Map::Map(const std::string& textureFile)
    : m_textureFile(textureFile)
{
}

void Map::load()
{
    sf::Texture* texture = TextureManager::getInstance().getTexture("map");
    if (texture)
        m_sprite.setTexture(*texture);
    else
        std::cerr << "Failed to load map texture" << std::endl;
}

void Map::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}