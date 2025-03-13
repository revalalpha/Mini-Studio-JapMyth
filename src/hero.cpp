#include "hero.h"
#include "IGameObject.h"
#include "Game.h"
#include "TextureCache.h"

Hero::Hero(IGameObjectContainer& game, const Vec2& position)
	: IGameObject(game), m_health(100), m_position(position)
{
    setStateTexture();
    m_sprites.setTexture(getOwner().getGame().getTextureCache().getTexture("heroMod.png"));
    m_sprites.setScale(2.f, 2.f);
}

bool Hero::isAlive()
{
    return m_health > 0;
}

bool Hero::isShooting()
{
    return false;
}

bool Hero::isAttacking()
{
    return m_isAttacking;
}

bool Hero::isInvulnerable()
{
    return m_isInvulnerable;
}

bool Hero::isFacingLeft() const
{
    return m_isFacingLeft;
}

bool Hero::isJumping() const
{
    return m_isJumping;
}

bool Hero::isOnGround() const
{
    return m_isOnGround;
}

bool Hero::isMoving() const
{
    return m_horizontalVelocity != 0.f;
}

void Hero::takeDamage(int damage)
{
    if (m_isInvulnerable) return;

    m_health -= damage;

    if (m_health <= 0)
    {
        setState(HeroStateNames::stateName::death);
    }
    else
    {
        setState(HeroStateNames::stateName::hurt);
        setInvulnerable(1.0f);
    }
}


void Hero::setInvulnerable(float duration)
{
    m_isInvulnerable = true;
    m_invulnerabilityTimer.restart();
    m_invulnerabilityDuration = duration;
}

void Hero::updateInvulnerabilityEffect()
{
    if (m_isInvulnerable && m_invulnerabilityTimer.getElapsedTime().asSeconds() >= m_invulnerabilityDuration)
        m_isInvulnerable = false;
}

void Hero::attacking()
{
    if (m_isAttacking)
    {
        m_stateManager.setState(this, stateName::attack);

        if (m_isJumping)
            m_stateManager.setState(this, stateName::jump_attack);
    }
    else
        m_isAttacking = false;
}

void Hero::setState(stateName newState)
{
    m_currentStateName = newState;
    m_stateManager.setState(this, newState);
    m_sprites.setTexture(m_textures[newState]);
}

void Hero::handleInputs(const sf::Event& event)
{
    m_stateManager.handleInput(*this);
}

void Hero::update(float deltaTime)
{
    updateInvulnerabilityEffect();
    m_stateManager.update(*this, deltaTime);
}

void Hero::setSpeed(float speed)
{
    m_speed = speed;
}

int Hero::getHp()
{
    return m_health;
}

int Hero::getDamage() const
{
    return m_attackDmg;
}

float Hero::getSpeed() const
{
    return m_speed;
}

float Hero::getJumpVelocity() const
{
    return m_jumpVelocity;
}

void Hero::setHorizontalVelocity(float velocity)
{
    m_horizontalVelocity = velocity;
}

float Hero::getHorizontalVelocity() const
{
    return m_horizontalVelocity;
}

void Hero::setVerticalVelocity(float velocity)
{
    m_verticalVelocity = velocity;
}

float Hero::getVerticalVelocity() const
{
    return m_verticalVelocity;
}

sf::FloatRect Hero::getHitbox() const
{
    sf::FloatRect spriteRect = m_sprites.getGlobalBounds();
    float width, height, offsetX, y;

    // IDLE STATE
    width = spriteRect.width * 0.2f;
    height = spriteRect.height * 1.0f;

    if (m_isFacingLeft)
        offsetX = spriteRect.width * 0.75f;
    else
        offsetX = spriteRect.width * 0.05f;

    y = spriteRect.top + (spriteRect.height - height) * 0.35f;

    switch (m_currentStateName)
    {
    case stateName::run:
        width = spriteRect.width * 0.3f;
        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.65f;
        else
            offsetX = spriteRect.width * 0.05f;
        break;
    case stateName::attack:
        width = spriteRect.width * 0.47f;
        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.47f;
        else
            offsetX = spriteRect.width * 0.05f;
        break;
    case stateName::jump_attack:
        width = spriteRect.width * 0.54f;
        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.4f;
        else
            offsetX = spriteRect.width * 0.05f;
        break;
    case stateName::dodge:
        width = spriteRect.width * 0.5f;
        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.45f;
        else
            offsetX = spriteRect.width * 0.05f;
        break;
    case stateName::block:
        width = spriteRect.width * 0.3f;
        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.65f;
        else
            offsetX = spriteRect.width * 0.05f;
        break;
    }

    float x = spriteRect.left + offsetX;

    return sf::FloatRect(x, y, width, height);
}

sf::Vector2f Hero::getPlayerPosition()
{
    return m_sprites.getPosition();
}

sf::Vector2f Hero::getPlayerCenter()
{
    return { getHitbox().left + getHitbox().width / 2.f, getHitbox().top + getHitbox().height / 2.f };
}

bool Hero::getAirDodge(bool newResult)
{
    return m_isAirDodging = newResult;
}

bool Hero::getIsJumping(bool newResult)
{
    return m_isJumping = newResult;
}

bool Hero::getIsJumping()
{
    return m_isJumping;
}

bool Hero::getIsHurt(bool newResult)
{
    return m_isHurt = newResult;
}

bool Hero::getIsHurt()
{
    return m_isHurt;
}

bool Hero::getIsDead()
{
    return m_isDead;
}

bool Hero::getIsDead(bool newResult)
{
    return m_isDead = newResult;
}

sf::Texture& Hero::getTexture(const stateName& stateName_)
{
    if (m_textures.find(stateName_) == m_textures.end())
        return m_textures[stateName::idle];

    return m_textures[stateName_];
}

sf::Sprite& Hero::getSprite()
{
    return m_sprites;
}

Hero::stateName Hero::getCurrentState() const
{
    return m_currentStateName;
}

HeroState& Hero::getStateManager()
{
    return m_stateManager;
}

void Hero::move(const sf::Vector2f& offset)
{
    m_sprites.move(offset);
}

void Hero::setFacingLeft(bool left)
{
    m_isFacingLeft = left;
}

void Hero::pushState(stateName newState)
{
    m_currentStateName = newState;
    m_stateManager.pushState(this, newState);
    m_sprites.setTexture(m_textures[newState]);
}

void Hero::popState()
{
    m_stateManager.popState(this);
    m_currentStateName = m_stateManager.getCurrentStateName();
}

void Hero::setOnGround(bool onGround)
{
    m_isOnGround = onGround;
}