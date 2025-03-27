#pragma once

#include "IGameObject.h"

#include <SFML/Graphics.hpp>

class IGameObjectContainer;

class Projectile : public IGameObject
{
public:
    Projectile(IGameObjectContainer& game, IGameObject* owner, const Vec2& position, const Vec2& velocity, const GameObjectType& type, const std::string& textureFile, Vec2 Scale={1.f,1.f});

    void handleInputs(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    OBB getBoundingBox() const override;
    GameObjectType gameObjectType() override;


    
private:
    sf::Sprite m_sprite;
    IGameObject* m_owner;
    Vec2 m_position;
    Vec2 m_velocity;
    float m_angle;
    GameObjectType m_type;

    float getOwnerAngle() const;

    bool IsOwnerDead() const;
};


