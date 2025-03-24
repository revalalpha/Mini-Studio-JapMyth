#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "MyComponent.h"

class Map : public ComponentGameObject
{
public:
    Map(const std::string& textureFile);
    void load();
    void render(sf::RenderWindow& window) override;

private:
    std::string m_textureFile;
    sf::Sprite m_sprite;
};
