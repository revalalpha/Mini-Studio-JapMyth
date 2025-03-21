#include "Samurai.h"

#include "SamuraiBehavior.h"
#include "Fireball.h"
#include "Game.h"
#include "OrbitalProjectile.h"


int getPistolBulletSpeed() { return 300; }
int getShotGunBulletSpeed() { return 220; }
float getBossFluidFrictionCoef() { return 5.0f; }

Vec2 getBossSize()
{
    return { 60.f, 60.f };
}

Vec2 getVelo() { return { 32.f, 32.f }; }

Samurai::Samurai(IGameObjectContainer& game, const Vec2& position)
    : IGameObject(game)
    , m_position(position)
	,m_rootNode(this)
	, testtt(512.f, 512.f, getOwner().getGame().getTextureCache().getTexture("samurai.png"))

{

    //m_sprite = testtt.testt();
    
    //m_sprite.setTexture(getOwner().getGame().getTextureCache().getTexture("Shinigami personnage principale.png"));
    auto* behavior = new BT::Retry(&m_rootNode);


    //auto* dead = new BT::IsDead(behavior);
    auto* Melee = new BT::PlayerDictance(behavior, 0.f, 100.f);
    auto* Kunai = new BT::PlayerDictance(behavior, 400.f, 600.f);
    new BT::Walk(behavior);


    auto* MeleeSequence = new BT::Sequence(Melee);
    new BT::Idle(MeleeSequence);
    new BT::Wait(MeleeSequence, 0.2f);
    new BT::Melee(MeleeSequence);
    new BT::Wait(MeleeSequence,1.2f);

    new BT::Walk(behavior);
    auto* DistanceSequence = new BT::Sequence(Kunai);
    new BT::FirePistol(DistanceSequence);
    new BT::Wait(DistanceSequence, 0.7f);
    new BT::IsPlayerDead(behavior);

    
}

Vec2 Samurai::getDistanceToPlayer() const
{
    return m_currentTarget->getPositon() - m_position;
}
float Samurai::calculateAngleToTarget() const
{
    if (!m_currentTarget)
        return m_angle;


    Vec2 directionToPlayer = getDistanceToPlayer();
    return std::atan2(directionToPlayer.y, directionToPlayer.x);
}

bool Samurai::findValidTarget()
{
    

    for (auto& target : m_allGameObjects)
    {
        if (target->gameObjectType()==PLAYERSHIP_TYPE)
        {
            m_currentTarget = static_cast<PlayerShip*>(target);
            if (isCurrentTargetValid())
				return true;

        }

    }
    return false;

}

bool Samurai::isCurrentTargetValid() const
{
    if (m_currentTarget->getHP() <= 0)
        return false;

    return true;
}
void Samurai::setSpeed(const int& Speed)
{
    m_speed = Speed;
}

void Samurai::fireWithPistol()
{
    
    new Fireball(m_owner,this, m_position, Vec2{ getPistolBulletSpeed() * std::cos(m_angle) ,  getPistolBulletSpeed() * std::sin(m_angle) },ENEMYprojectile_TYPE,"kunai.png",{0.12f,0.12f});

    if (m_angle / 3.14159265f * 180.f < -160.f || m_angle / 3.14159265f * 180.f > 160.f)
    {

        testtt.interruptAnimation();
        m_sprite = testtt.Animation(1.f / 60.f, 11, 1, 3, 0.2f, true);
        
    }
    if (m_angle / 3.14159265f * 180.f < -20.f && m_angle / 3.14159265f * 180.f > -160.f)
    {
        testtt.interruptAnimation();
        m_sprite = testtt.Animation(1.f / 60.f, 13, 1, 3, 0.2f, true);
        
    }
    if (m_angle / 3.14159265f * 180.f < 160.f && m_angle / 3.14159265f * 180.f > 20.f)
    {
        testtt.interruptAnimation();
        m_sprite = testtt.Animation(1.f / 60.f, 12, 1, 3, 0.2f, true);
       
    }

    if (m_angle / 3.14159265f * 180.f < 20.f && m_angle / 3.14159265f * 180.f > -20.f)
    {
        testtt.interruptAnimation();
        m_sprite = testtt.Animation(1.f / 60.f, 10, 1, 3, 0.2f, true);
        
    }

}


void Samurai::RightMelee()
{

    


    if (m_angle / 3.14159265f * 180.f < -160.f || m_angle / 3.14159265f * 180.f > 160.f)
    {

        testtt.interruptAnimation();
        m_sprite = testtt.Animation(1.f/60.f, 6, 1, 3, 0.2f, true);
        new OrbitalProjectile(m_owner, this, -160.f, 40.f, -7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }
    if (m_angle / 3.14159265f * 180.f < -20.f && m_angle / 3.14159265f * 180.f > -160.f)
    {
        testtt.interruptAnimation();
        m_sprite = testtt.Animation(1.f / 60.f, 8, 1, 3, 0.2f, true);
        new OrbitalProjectile(m_owner, this, -60.f, 40.f, -7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }
    if (m_angle / 3.14159265f * 180.f < 160.f && m_angle / 3.14159265f * 180.f > 20.f)
    {
        testtt.interruptAnimation();
        m_sprite = testtt.Animation(1.f / 60.f, 7, 1, 3, 0.2f, true);
        new OrbitalProjectile(m_owner, this, 120.f, 40.f, -7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }

    if (m_angle / 3.14159265f * 180.f < 20.f && m_angle / 3.14159265f * 180.f > -20.f)
    {
        testtt.interruptAnimation();
        m_sprite = testtt.Animation(1.f / 60.f, 5, 1, 3, 0.2f, true);
        new OrbitalProjectile(m_owner, this, -60.f, 40.f, 7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }
}


Vec2 Samurai::getPosition() const
{
    return m_position;
}



void Samurai::handleInputs(const sf::Event& event)
{

}

void Samurai::update(float deltaTime)
{
    

    m_allGameObjects = getOwner().getAllGameOjects();
    findValidTarget();
    m_rootNode.tick();

	m_angle = calculateAngleToTarget();

    

    if (m_angle / 3.14159265f * 180.f < -160.f || m_angle / 3.14159265f * 180.f > 160.f && m_velocity != Vec2{ 0.f,0.f })
    {
        m_sprite = testtt.Animation(deltaTime, 3, 2, 3, 0.1f, true);
    }
    if (m_angle / 3.14159265f * 180.f < -20.f && m_angle / 3.14159265f * 180.f > -160.f && m_velocity != Vec2{ 0.f,0.f })
    {

	    m_sprite = testtt.Animation(deltaTime, 2, 2, 3, 0.1f, true);
    }
    if (m_angle / 3.14159265f * 180.f < 160.f && m_angle / 3.14159265f * 180.f > 20.f && m_velocity != Vec2{ 0.f,0.f })
    {
	    m_sprite = testtt.Animation(deltaTime, 1, 2, 3, 0.1f, true);
    }
    
    if (m_angle / 3.14159265f * 180.f < 20.f && m_angle / 3.14159265f * 180.f > -20.f && m_velocity != Vec2{ 0.f,0.f })
    {
	    m_sprite = testtt.Animation(deltaTime, 4, 2, 3, 0.1f, true);
    }







    Vec2 acceleration{ 0.f, 0.f };

    if (m_speed==0)
        acceleration = -getBossFluidFrictionCoef() * m_velocity;

    if (m_speed>0)
		acceleration += m_speed * Vec2 { std::cos(m_angle), std::sin(m_angle) };


    Vec2 PreviousPos = m_position;
    if (m_position.x > m_owner.getGame().getWindowSize().x - 200.f)
        m_position = { PreviousPos.x - 0.5f,PreviousPos.y };
    else if (m_position.y > m_owner.getGame().getWindowSize().y - 200.f)
        m_position = { PreviousPos.x ,PreviousPos.y - 0.5f };
    else if (m_position.x < 200)
        m_position = { PreviousPos.x + 0.5f ,PreviousPos.y };
    else if (m_position.y < 200)
        m_position = { PreviousPos.x ,PreviousPos.y + 0.5f };
    else
        m_position += m_velocity * deltaTime;
    m_velocity += acceleration * deltaTime;

    if (m_velocity.getLength() > SpeedLimit)
        m_velocity = m_velocity * (SpeedLimit / m_velocity.getLength());



    if (m_angle / 3.14159265f * 180.f < -160.f || m_angle / 3.14159265f * 180.f > 160.f && m_velocity == Vec2{0.f,0.f})
    {
        m_sprite = testtt.Animation(deltaTime, 3, 1, 1, 0.f, true);
    }
    if (m_angle / 3.14159265f * 180.f < -20.f && m_angle / 3.14159265f * 180.f > -160.f && m_velocity == Vec2{ 0.f,0.f })
    {

        m_sprite = testtt.Animation(deltaTime, 2, 1, 1, 0.f, true);
    }
    if (m_angle / 3.14159265f * 180.f < 160.f && m_angle / 3.14159265f * 180.f > 20.f && m_velocity == Vec2{ 0.f,0.f })
    {
        m_sprite = testtt.Animation(deltaTime, 1, 1, 1, 0.f, true);
    }

    if (m_angle / 3.14159265f * 180.f < 20.f && m_angle / 3.14159265f * 180.f > -20.f && m_velocity == Vec2{ 0.f,0.f })
    {
        m_sprite = testtt.Animation(deltaTime, 4, 1, 1, 0.f, true);
    }
}

void Samurai::render(sf::RenderWindow& window)
{
    m_sprite.setColor(sf::Color(255, 255, 255, 255));
    if (m_isInvincible)
    {
	    m_sprite.setColor(sf::Color(255, 50, 50, 128));
    	m_isInvincible = false;
    }
    //m_sprite.setRotation(m_angle / 3.14159265f * 180.f);
    m_sprite.setScale(0.25f, 0.25f);
    m_sprite.setOrigin(m_sprite.getLocalBounds().getSize().x / 2.f, m_sprite.getLocalBounds().getSize().y / 2.f);
    m_sprite.setPosition(m_position.x, m_position.y);
    //sf::Text HP("testHP : " + std::to_string(m_HP) + " / " + std::to_string(m_MaxHP), m_owner.getGame().font,45);
    //HP.setOrigin(HP.getLocalBounds().width /2.f, HP.getLocalBounds().height / 2.f);
    //HP.setPosition(m_owner.getGame().getWindowSize().x / 2.f, m_owner.getGame().getWindowSize().y - 100);
    //HP.setStyle(sf::Text::Bold);
    window.draw(m_sprite);
    //window.draw(HP);
}

OBB Samurai::getBoundingBox() const
{
    Vec2 size = getBossSize();
    return {
        m_position,
        size / 2.0f,
        m_angle
    };
}

GameObjectType Samurai::gameObjectType()
{
    return ENEMY_TYPE;
}


void Samurai::takeDamage(int dmg)
{
    m_elapsedTimeHit = m_clockHit.getElapsedTime();

    if (m_elapsedTimeHit.asSeconds() >= m_invincibility)
    {
        m_isInvincible = true;
        m_HP -= dmg;
        if (m_HP <= 0)
            die();
        m_clockHit.restart();
    }


}

void Samurai::die()
{
    if (m_isDead)
        return;
    m_isDead = true;

	destroy();
}

int Samurai::getHP() const
{
    return m_HP;
}
int Samurai::getMaxHP()const
{
    return m_MaxHP;
}

float Samurai::getAngle()const
{
    return m_angle;
}