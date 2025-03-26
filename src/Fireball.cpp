#include "Fireball.h"

#include "Game.h"
#include "Inugami.h"
#include "Kappa.h"
#include "PlayerShip.h"
#include "Samurai.h"

Vec2 getFireballSize()
{
    return { 16.f, 16.f };
}

Fireball::Fireball(IGameObjectContainer& game, IGameObject* owner, const Vec2& position, const Vec2& velocity,const GameObjectType& type,const std::string& textureFile,Vec2 Scale)
    : IGameObject(game)
	, m_owner(owner)
    , m_position(position)
    , m_velocity(velocity)
	, m_type(type)
	, m_angle(getOwnerAngle())
{
    m_sprite.setTexture(getOwner().getGame().getTextureCache().getTexture(textureFile));
    m_sprite.setScale({Scale.x,Scale.y});
    
}

void Fireball::handleInputs(const sf::Event& event)
{

}

void Fireball::update(float deltaTime)
{
    float dt = 1.f / 60.f;
    m_position += m_velocity * dt;
    
}

void Fireball::render(sf::RenderWindow& window)
{
    m_sprite.setRotation(m_angle / 3.14159265f * 180.f);
    m_sprite.setOrigin(m_sprite.getLocalBounds().getSize().x / 2.f, m_sprite.getLocalBounds().getSize().y / 2.f);
    m_sprite.setPosition(m_position.x, m_position.y);
    window.draw(m_sprite);
}

OBB Fireball::getBoundingBox() const
{
    Vec2 size = getFireballSize();

    float angle = 0.0f;
    if (m_velocity.getLength() > 0.0f) {
        angle = std::atan2(m_velocity.y, m_velocity.x);
    }

    return {
        m_position,
        size / 2.0f,
        angle
    };
}

GameObjectType Fireball::gameObjectType()
{
    return m_type;
}



float Fireball::getOwnerAngle() const
{
    if (!m_owner)
        return 0.f;

    switch (m_owner->gameObjectType())
    {
    case PLAYERSHIP_TYPE:
        return static_cast<PlayerShip*>(m_owner)->getAngle();
    case SAMURAI_TYPE:
        return static_cast<Samurai*>(m_owner)->getAngle();
    case KAPPA_TYPE:
        return static_cast<Kappa*>(m_owner)->getAngle();
    case INUGAMI_TYPE:
        return static_cast<Inugami*>(m_owner)->getAngle();
    default:
        return 0.f;
    }
}

bool Fireball::IsOwnerDead() const
{
    if (!m_owner)
        return true;

    switch (m_owner->gameObjectType())
    {
    case PLAYERSHIP_TYPE:
        return static_cast<PlayerShip*>(m_owner)->getHP() <= 0;
    case SAMURAI_TYPE:
        return static_cast<Samurai*>(m_owner)->getHP() <= 0;
    case KAPPA_TYPE:
        return static_cast<Kappa*>(m_owner)->getHP() <= 0;
    case INUGAMI_TYPE:
        return static_cast<Inugami*>(m_owner)->getHP() <= 0;
    default:
        return true;
    }
}