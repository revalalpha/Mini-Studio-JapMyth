#include "PlayerShip.h"

#include <iostream>

#include "Game.h"
#include "Projectile.h"
#include "OrbitalProjectile.h"


Vec2 getPlayerShipSize() { return { 72.f, 32.f }; }
float getPlayerShipThrust() { return 3000.f; }
float getPlayerShipRateOfTurn() { return 0.08f; }
float getPlayerShipFluidFrictionCoef() { return 10.0f; }
float getPlayerShipMaxVelocity() { return 650.f; }


PlayerShip::PlayerShip(IGameObjectContainer& game, const Vec2& position)
    : IGameObject(game)
    , PlayerSheet(512.f, 512.f, getOwner().getGame().getTextureCache().getTexture("Shinigami personnage principale.png"))
    , m_HP(20)
    , m_MaxHP(m_HP)
    , m_angle(-90.f * 3.14 / 180)
	, m_mouseAngle(0.f)
    , m_position(position)
    , m_velocity(0.f, 0.f)
    , m_isDead(false)
    , m_isAccelerating(false)
    , m_isDecelerating(false)
    , m_isTurningLeft(false)
    , m_isTurningRight(false)
    , m_firerate(0.7f)
    , m_Shooting(false)
    , m_daching(false)
    , m_isInvincible(false)
    , m_invincibility(0.6f)
    , m_dashCooldown(1.5f)
    , m_dashTime(0.3f)
    , isKick(false)
    , KBTime(0.5f)
	, m_meleerate(0.5f)
	, m_Attacking(false)
	, spawnBoss(true)
	, m_view(sf::Vector2f(m_position.x, m_position.y), sf::Vector2f(1920, 1080))

{
    m_lifeBar.setTexture(getOwner().getGame().getTextureCache().getTexture("katana vieJ.png"));
    m_sprite = PlayerSheet.Animation(1.f / 60.f, 1, 1, 1, 0.f, true);
    m_view.zoom(0.8f);
}
void PlayerShip::handleInputs(const sf::Event& event)
{
    m_elapsedTimeFire =m_clockFire.getElapsedTime();
    

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if (m_elapsedTimeFire.asSeconds() >= m_firerate)
        {
            m_Shooting = true;
            m_clockFire.restart();
        }

    }
    m_elapsedTimeMelee = m_clockMelee.getElapsedTime();


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (m_elapsedTimeMelee.asSeconds() >= m_meleerate)
        {
            m_Attacking = true;
            m_clockMelee.restart();
        }

    }
    m_elapsedTimeDashCooldown = m_clockDashCooldown.getElapsedTime();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (m_elapsedTimeDashCooldown.asSeconds() >= m_dashCooldown)
        {

            m_daching = true;
            m_clockDashCooldown.restart();
            m_clockDashTime.restart();
        }

    }


    m_isAccelerating = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    m_isDecelerating = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    m_isTurningLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    m_isTurningRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

}

void PlayerShip::update(float deltaTime)
{
    if (m_score>500)
    {
        m_owner.getGame().m_SpawnTime = 3.f;

    }
    if (m_score > 1000)
    {
        if (spawnBoss)
        {
	        m_owner.getGame().spawnBoss1 = true;
            spawnBoss = false;
        }
    }

    if (m_score > 2500)
    {
        m_owner.getGame().m_SpawnTime = 1.f;
        
    }

    acceleration={ 0.f, 0.f };
    if (m_Shooting)
    {
        m_Shooting = false;
        new Projectile(m_owner, this, m_position, Vec2{ 250.f * std::cos(m_mouseAngle) ,  250.f * std::sin(m_mouseAngle) },PLAYERprojectile_TYPE,"kunai.png",{0.12f,0.12f });
        if (m_mouseAngle / 3.14159265f * 180.f < -160.f || m_mouseAngle / 3.14159265f * 180.f > 160.f)
        {

            PlayerSheet.interruptAnimation();
            m_sprite = PlayerSheet.Animation(1.f / 60.f, 11, 1, 3, 0.1f, true);

        }
        if (m_mouseAngle / 3.14159265f * 180.f < -20.f && m_mouseAngle / 3.14159265f * 180.f > -160.f)
        {
            PlayerSheet.interruptAnimation();
            m_sprite = PlayerSheet.Animation(1.f / 60.f, 13, 1, 3, 0.1f, true);

        }
        if (m_mouseAngle / 3.14159265f * 180.f < 160.f && m_mouseAngle / 3.14159265f * 180.f > 20.f)
        {
            PlayerSheet.interruptAnimation();
            m_sprite = PlayerSheet.Animation(1.f / 60.f, 12, 1, 3, 0.1f, true);

        }

        if (m_mouseAngle / 3.14159265f * 180.f < 20.f && m_mouseAngle / 3.14159265f * 180.f > -20.f)
        {
            PlayerSheet.interruptAnimation();
            m_sprite = PlayerSheet.Animation(1.f / 60.f, 10, 1, 3, 0.1f, true);

        }
    }

    if (m_Attacking)
    {
        m_Attacking = false;

        if (m_mouseAngle / 3.14159265f * 180.f < -160.f || m_mouseAngle / 3.14159265f * 180.f > 160.f)
        {

            PlayerSheet.interruptAnimation();
            m_sprite = PlayerSheet.Animation(1.f / 60.f, 7, 1, 3, 0.2f, true);
            new OrbitalProjectile(m_owner, this, -160.f, 40.f, -7.f, 65, 120.f, 20.f, PLAYERmelee_TYPE);
        }
        if (m_mouseAngle / 3.14159265f * 180.f < -20.f && m_mouseAngle / 3.14159265f * 180.f > -160.f)
        {
            PlayerSheet.interruptAnimation();
            m_sprite = PlayerSheet.Animation(1.f / 60.f, 6, 1, 3, 0.2f, true);
            new OrbitalProjectile(m_owner, this, -60.f, 40.f, -7.f, 65, 120.f, 20.f, PLAYERmelee_TYPE);
        }
        if (m_mouseAngle / 3.14159265f * 180.f < 160.f && m_mouseAngle / 3.14159265f * 180.f > 20.f)
        {
            PlayerSheet.interruptAnimation();
            m_sprite = PlayerSheet.Animation(1.f / 60.f, 5, 1, 3, 0.2f, true);
            new OrbitalProjectile(m_owner, this, 120.f, 40.f, -7.f, 65, 120.f, 20.f, PLAYERmelee_TYPE);
        }

        if (m_mouseAngle / 3.14159265f * 180.f < 20.f && m_mouseAngle / 3.14159265f * 180.f > -20.f)
        {
            PlayerSheet.interruptAnimation();
            m_sprite = PlayerSheet.Animation(1.f / 60.f, 8, 1, 3, 0.2f, true);
            new OrbitalProjectile(m_owner, this, -60.f, 40.f, 7.f, 65, 120.f, 20.f, PLAYERmelee_TYPE);
        }
    }



  
	
    

    if (!m_isAccelerating|| !m_isDecelerating|| !m_isTurningLeft ||! m_isTurningRight)
        acceleration = -getPlayerShipFluidFrictionCoef() * m_velocity;

    if (m_daching)
    {
        m_elapsedTimeDashTime = m_clockDashTime.getElapsedTime();

        if (m_elapsedTimeDashTime.asSeconds() >= m_dashTime)
        {

            m_daching = false;
            m_clockDashTime.restart();
        }


        acceleration += 7000 * Vec2{ std::cos(m_mouseAngle), std::sin(m_mouseAngle) };

    }
    if (m_isInvincible)
    {
        m_elapsedTimeHit = m_clockHit.getElapsedTime();

        if (m_elapsedTimeHit.asSeconds() >= m_isInvincible)
        {

            m_isInvincible = false;
            m_clockHit.restart();
        }
    }

    if (m_isTurningRight && m_isAccelerating)
    {
        acceleration += getPlayerShipThrust() * Vec2 { std::cos(m_angle + (90.f * 3.14f / 180.f)), std::sin(m_angle ) };
        m_sprite = PlayerSheet.Animation(deltaTime, 2, 2, 3, 0.1f, true);
    }
    else if (m_isTurningLeft && m_isAccelerating)
    {
        acceleration += getPlayerShipThrust() * Vec2 { std::cos(m_angle - (90.f * 3.14f / 180.f)), std::sin(m_angle) };
        m_sprite = PlayerSheet.Animation(deltaTime, 2, 2, 3, 0.1f, true);
    }

    else if (m_isTurningRight && m_isDecelerating)
    {
        acceleration -= getPlayerShipThrust() * Vec2 { std::cos(m_angle - (90.f * 3.14f / 180.f)), std::sin(m_angle) };
        m_sprite = PlayerSheet.Animation(deltaTime, 1, 2, 3, 0.1f, true);
    }
    else if (m_isTurningLeft && m_isDecelerating)
    {
        acceleration -= getPlayerShipThrust() * Vec2 { std::cos(m_angle + (90.f * 3.14f / 180.f)), std::sin(m_angle) };
        m_sprite = PlayerSheet.Animation(deltaTime, 1, 2, 3, 0.1f, true);
    }

    else if (m_isTurningLeft)
    {
        acceleration += getPlayerShipThrust() * Vec2 { std::cos((m_angle - (90.f * 3.14f / 180.f))), 0 };
        m_sprite = PlayerSheet.Animation(deltaTime, 3, 1, 3, 0.1f, true);
    }
    else if (m_isTurningRight)
    {
        acceleration -= getPlayerShipThrust() * Vec2 { std::cos((m_angle - (90.f * 3.14f / 180.f))), 0 };
        m_sprite = PlayerSheet.Animation(deltaTime, 4, 1, 3, 0.1f, true);
    }
    else if (m_isAccelerating)
    {
        acceleration += getPlayerShipThrust() * Vec2 { std::cos(m_angle), std::sin(m_angle) };
        m_sprite = PlayerSheet.Animation(deltaTime, 2, 2, 3, 0.1f, true);
    }
    else if (m_isDecelerating)
    {
        acceleration -= getPlayerShipThrust() * Vec2 { std::cos(m_angle), std::sin(m_angle) };
        m_sprite = PlayerSheet.Animation(deltaTime, 1, 2, 3, 0.1f, true);
    }
    else
		m_sprite = PlayerSheet.Animation(deltaTime, 1, 1, 1, 0.0f, true);
    
    Vec2 PreviousPos = m_position;
    if (m_position.x > m_owner.getGame().getWindowSize().x - 300.f)
        m_position = { PreviousPos.x - 0.5f,PreviousPos.y };
    else if (m_position.y > m_owner.getGame().getWindowSize().y - 260.f)
        m_position = { PreviousPos.x ,PreviousPos.y - 0.5f };
    else if (m_position.x < 300)
        m_position = { PreviousPos.x + 0.5f ,PreviousPos.y };
    else if (m_position.y < 360)
        m_position = { PreviousPos.x ,PreviousPos.y + 0.5f };

    else if (m_position.x > (m_owner.getGame().getWindowSize().x / 2.f - 490.f)&& m_position.x < (m_owner.getGame().getWindowSize().x / 2.f + 490.f)&& m_position.y >(m_owner.getGame().getWindowSize().y / 2.f - 650.f)&& m_position.y < (m_owner.getGame().getWindowSize().y / 2.f + 550.f))
    {
	    
        
        if (m_position.y > (m_owner.getGame().getWindowSize().y / 2.f - 650.f)&& m_position.y < (m_owner.getGame().getWindowSize().y / 2.f - 630.f))
            m_position = { PreviousPos.x ,PreviousPos.y - 0.5f };
        if (m_position.y < (m_owner.getGame().getWindowSize().y / 2.f + 550.f)&& m_position.y > (m_owner.getGame().getWindowSize().y / 2.f + 530.f))
            m_position = { PreviousPos.x  ,PreviousPos.y + 0.5f };
        if (m_position.x > (m_owner.getGame().getWindowSize().x / 2.f - 490.f)&& m_position.x < (m_owner.getGame().getWindowSize().x / 2.f - 470.f))
            m_position = { PreviousPos.x - 0.5f,PreviousPos.y };
        if (m_position.x < (m_owner.getGame().getWindowSize().x / 2.f + 490.f)&& m_position.x > (m_owner.getGame().getWindowSize().x / 2.f + 470.f))
            m_position = { PreviousPos.x + 0.5f ,PreviousPos.y };
    }
    else
		m_position += m_velocity * deltaTime;

    m_velocity += acceleration * deltaTime;

    if (m_velocity.getLength() > getPlayerShipMaxVelocity()&&!m_daching)
        m_velocity = m_velocity * (getPlayerShipMaxVelocity() / m_velocity.getLength());
   
}

void PlayerShip::render(sf::RenderWindow& window)
{

    m_sprite.setColor(sf::Color(255, 255, 255, 255));
    if (m_daching )
    {
	    m_sprite.setColor(sf::Color(50, 50, 50, 128));
    	
    }
    if (m_isInvincible)
    {
        m_sprite.setColor(sf::Color(128, 50, 50, 128));

    }

    m_sprite.setScale(0.2f, 0.2f);
    m_sprite.setOrigin(m_sprite.getLocalBounds().getSize().x / 2.f, m_sprite.getLocalBounds().getSize().y / 2.f);
    m_sprite.setPosition(m_position.x, m_position.y);
    m_view.setCenter(sf::Vector2f(m_position.x, m_position.y));

    m_lifeBar.setOrigin(m_lifeBar.getGlobalBounds().getSize().x, m_lifeBar.getGlobalBounds().getSize().y);
    m_lifeBar.setPosition(m_position.x - 400, m_position.y - 300);

    sf::RectangleShape rec({-11.f *(m_MaxHP-m_HP), m_lifeBar.getGlobalBounds().getSize().y - 20});
    rec.setFillColor(sf::Color::Black);
    rec.setPosition(m_position.x - 433, m_position.y - 322);

    //sf::Text HP("HP : "+std::to_string(m_HP)+" / "+ std::to_string(m_MaxHP),m_owner.getGame().font,20);
    //HP.setPosition(m_position.x-500, m_position.y - 300);

    sf::Text Score("Score : " + std::to_string(m_score) , m_owner.getGame().font, 20);
    Score.setPosition(m_position.x + 500, m_position.y + 300);

    window.draw(m_sprite);
    //window.draw(HP);
    window.draw(Score);
    window.draw(m_lifeBar);
    window.draw(rec);
    window.setView(m_view);
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
    m_mouseAngle = atan2( mousePos.y - m_position.y,  mousePos.x - m_position.x);

    
    
}

OBB PlayerShip::getBoundingBox() const
{
    Vec2 size = getPlayerShipSize();
    return {
        m_position,
        size / 2.0f,
        m_angle
    };
}

GameObjectType PlayerShip::gameObjectType()
{
    if (m_daching)
        return INVICIBLE_TYPE;
    return PLAYERSHIP_TYPE;
}

void PlayerShip::takeDamage(int dmg)
{
    m_elapsedTimeHit = m_clockHit.getElapsedTime();
    
    if (m_elapsedTimeHit.asSeconds() >= m_invincibility&&!m_daching)
    {
        m_isInvincible = true;
        m_clockDashTime.restart();
        m_HP -= dmg;
        if (m_HP <= 0)
            die();
        m_clockHit.restart();
    }

    
}

void PlayerShip::die()
{
    if (m_isDead)
        return;

    m_isDead = true;

    destroy();
}

Vec2 PlayerShip::getPositon() const
{
    return m_position;
}

int PlayerShip::getHP() const
{
    return m_HP;
}

float PlayerShip::getAngle() const
{
    return m_mouseAngle;
}

