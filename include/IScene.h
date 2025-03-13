#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "TextureCache.h"


class IScene {
public:
    IScene(sf::RenderWindow* window, const float& framerate, const std::string& execPath);
    virtual ~IScene() = default;

    virtual void processInput(const sf::Event& event) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render() = 0;

    sf::Time getRefreshTime() const;

protected:
    sf::RenderWindow* m_renderWindow;
    sf::Time m_refreshTime;
    TextureCache _m_textureCache;
};
