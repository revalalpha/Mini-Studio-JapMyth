#pragma once

#include "TextureCache.h"
#include "IGameObject.h"

#include <SFML/Graphics.hpp>

class IGameObject;

#define private_members private
#define private_function private
#define private_friend_function(Cls) private

class Game : public ::IGameObjectContainer
{
public:
    sf::Font font;

    friend class IGameObject;

    Game(sf::RenderWindow& window,const std::string& execPath);
    ~Game();

    void handleInputs(const sf::Event& event);

    void update(const float& deltaTime);

    void render(sf::RenderWindow& window);

    //void run();

    TextureCache& getTextureCache();
    
    virtual Game& getGame() override { return *this; }
    Vec2 getWindowSize()const;
    void renderBoundingBox(sf::RenderWindow& window);
private_function:
    void detectCollision();
    void onCollision(IGameObject* go1, IGameObject* go2);
    

private_members:
    //::sf::RenderWindow m_window;
    TextureCache m_textureCache;
    float m_Width;
    float m_Height;
    
};
