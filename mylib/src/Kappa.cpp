#include "Kappa.h"

#include "KappaBehavior.h"
#include "Projectile.h"
#include "Game.h"
#include "OrbitalProjectile.h"


int getKappaPistolBulletSpeed() { return 400; }
float getKappaFluidFrictionCoef() { return 5.0f; }

Vec2 getKappaSize()
{
    return { 60.f, 60.f };
}

Vec2 getKappaVelo() { return { 32.f, 32.f }; }

Kappa::Kappa(IGameObjectContainer& game, const Vec2& position)
    : IGameObject(game)
    , m_position(position)
	,m_rootNode(this)
	, EnemySheet(512.f, 512.f, getOwner().getGame().getTextureCache().getTexture("kappa.png"))

{

    //m_sprite = EnemySheet.testt();
    
    //m_sprite.setTexture(getOwner().getGame().getTextureCache().getTexture("Shinigami personnage principale.png"));
    auto* behavior = new BT::Retry(&m_rootNode);


    
    auto* run_away = new BT::PlayerDictanceKappa(behavior, 0.f, 500.f);
    auto* Shoot = new BT::PlayerDictanceKappa(behavior, 510.f, 800.f);
    auto* come_towards = new BT::PlayerDictanceKappa(behavior, 810.f, 10000.f);


    new BT::WalkKappa(come_towards);

    auto* DistanceSequence = new BT::Sequence(Shoot);
    new BT::IdleKappa(DistanceSequence);
    new BT::WaitKappa(DistanceSequence, 0.3f);
    new BT::FireKappa(DistanceSequence);
    new BT::WaitKappa(DistanceSequence, 2.f);



    new BT::OppositeWalkKappa(run_away);

    auto* dead = new BT::IsDeadKappa(behavior);
    auto* death = new BT::Retry(dead);
    new BT::IsPlayerDeadKappa(death);

    new BT::IsPlayerDeadKappa(behavior);

    
}

Vec2 Kappa::getDistanceToPlayer() const
{
    return m_currentTarget->getPositon() - m_position;
}
float Kappa::calculateAngleToTarget() const
{
    if (!m_currentTarget)
        return m_angle;


    Vec2 directionToPlayer = getDistanceToPlayer();
    return std::atan2(directionToPlayer.y, directionToPlayer.x);
}

bool Kappa::findValidTarget()
{
    

    for (auto& target : m_allGameObjects)
    {
        if (target->gameObjectType()==PLAYERSHIP_TYPE || target->gameObjectType() == INVICIBLE_TYPE)
        {
            m_currentTarget = static_cast<PlayerShip*>(target);
            if (isCurrentTargetValid())
				return true;

        }

    }
    return false;

}

bool Kappa::isCurrentTargetValid() const
{
    if (m_currentTarget->getHP() <= 0)
        return false;

    return true;
}
void Kappa::setSpeed(const int& Speed)
{
    m_speed = Speed;
}

void Kappa::fireWithPistol()
{
    
    new Projectile(m_owner,this, m_position, Vec2{ getKappaPistolBulletSpeed() * std::cos(m_angle) ,  getKappaPistolBulletSpeed() * std::sin(m_angle) },ENEMYprojectile_TYPE,"bubble.png",{0.12f,0.12f});

    if (m_angle / 3.14159265f * 180.f < -160.f || m_angle / 3.14159265f * 180.f > 160.f)
    {

        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f / 60.f, 7, 1, 3, 0.2f, true);
        
    }
    if (m_angle / 3.14159265f * 180.f < -20.f && m_angle / 3.14159265f * 180.f > -160.f)
    {
        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f / 60.f, 9, 1, 3, 0.2f, true);
        
    }
    if (m_angle / 3.14159265f * 180.f < 160.f && m_angle / 3.14159265f * 180.f > 20.f)
    {
        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f / 60.f, 8, 1, 3, 0.2f, true);
       
    }

    if (m_angle / 3.14159265f * 180.f < 20.f && m_angle / 3.14159265f * 180.f > -20.f)
    {
        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f / 60.f, 6, 1, 3, 0.2f, true);
        
    }

}


void Kappa::RightMelee()
{

    


    if (m_angle / 3.14159265f * 180.f < -160.f || m_angle / 3.14159265f * 180.f > 160.f)
    {

        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f/60.f, 6, 1, 3, 0.2f, true);
        new OrbitalProjectile(m_owner, this, -160.f, 40.f, -7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }
    if (m_angle / 3.14159265f * 180.f < -20.f && m_angle / 3.14159265f * 180.f > -160.f)
    {
        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f / 60.f, 8, 1, 3, 0.2f, true);
        new OrbitalProjectile(m_owner, this, -60.f, 40.f, -7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }
    if (m_angle / 3.14159265f * 180.f < 160.f && m_angle / 3.14159265f * 180.f > 20.f)
    {
        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f / 60.f, 7, 1, 3, 0.2f, true);
        new OrbitalProjectile(m_owner, this, 120.f, 40.f, -7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }

    if (m_angle / 3.14159265f * 180.f < 20.f && m_angle / 3.14159265f * 180.f > -20.f)
    {
        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f / 60.f, 5, 1, 3, 0.2f, true);
        new OrbitalProjectile(m_owner, this, -60.f, 40.f, 7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }
}


Vec2 Kappa::getPosition() const
{
    return m_position;
}



void Kappa::handleInputs(const sf::Event& event)
{
    
}

void Kappa::update(float deltaTime)
{


    m_allGameObjects = getOwner().getAllGameOjects();
    findValidTarget();
    m_rootNode.tick();

	m_angle = calculateAngleToTarget();

    

    if (m_angle / 3.14159265f * 180.f < -160.f || m_angle / 3.14159265f * 180.f > 160.f && m_velocity != Vec2{ 0.f,0.f })
    {
        m_sprite = EnemySheet.Animation(deltaTime, 3, 2, 3, 0.1f, true);
    }
    if (m_angle / 3.14159265f * 180.f < -20.f && m_angle / 3.14159265f * 180.f > -160.f && m_velocity != Vec2{ 0.f,0.f })
    {

	    m_sprite = EnemySheet.Animation(deltaTime, 2, 2, 3, 0.1f, true);
    }
    if (m_angle / 3.14159265f * 180.f < 160.f && m_angle / 3.14159265f * 180.f > 20.f && m_velocity != Vec2{ 0.f,0.f })
    {
	    m_sprite = EnemySheet.Animation(deltaTime, 1, 2, 3, 0.1f, true);
    }
    
    if (m_angle / 3.14159265f * 180.f < 20.f && m_angle / 3.14159265f * 180.f > -20.f && m_velocity != Vec2{ 0.f,0.f })
    {
	    m_sprite = EnemySheet.Animation(deltaTime, 4, 2, 3, 0.1f, true);
    }



    if (m_isInvincible)
    {
        m_elapsedTimeHit = m_clockHit.getElapsedTime();

        if (m_elapsedTimeHit.asSeconds() >= m_invincibility)
        {

            m_isInvincible = false;
            m_clockHit.restart();
        }
    }



    Vec2 acceleration{ 0.f, 0.f };

    if (m_speed==0)
        acceleration = -getKappaFluidFrictionCoef() * m_velocity;

    if (m_speed>0)
		acceleration += m_speed * Vec2 { std::cos(m_angle), std::sin(m_angle) };
    if (m_speed < 0)
        acceleration += m_speed * Vec2{ std::cos(m_angle), std::sin(m_angle) };

    Vec2 PreviousPos = m_position;
    if (m_position.x > m_owner.getGame().getWindowSize().x - 300.f)
        m_position = { PreviousPos.x - 0.5f,PreviousPos.y };
    else if (m_position.y > m_owner.getGame().getWindowSize().y - 260.f)
        m_position = { PreviousPos.x ,PreviousPos.y - 0.5f };
    else if (m_position.x < 300)
        m_position = { PreviousPos.x + 0.5f ,PreviousPos.y };
    else if (m_position.y < 360)
        m_position = { PreviousPos.x ,PreviousPos.y + 0.5f };
    else if (m_position.x > (m_owner.getGame().getWindowSize().x / 2.f - 490.f) && m_position.x < (m_owner.getGame().getWindowSize().x / 2.f + 490.f) && m_position.y >(m_owner.getGame().getWindowSize().y / 2.f - 650.f) && m_position.y < (m_owner.getGame().getWindowSize().y / 2.f + 550.f))
    {


        if (m_position.y > (m_owner.getGame().getWindowSize().y / 2.f - 650.f) && m_position.y < (m_owner.getGame().getWindowSize().y / 2.f - 640.f))
            m_position = { PreviousPos.x ,PreviousPos.y - 0.5f };
        if (m_position.y < (m_owner.getGame().getWindowSize().y / 2.f + 550.f) && m_position.y >(m_owner.getGame().getWindowSize().y / 2.f + 540.f))
            m_position = { PreviousPos.x  ,PreviousPos.y + 0.5f };
        if (m_position.x > (m_owner.getGame().getWindowSize().x / 2.f - 490.f) && m_position.x < (m_owner.getGame().getWindowSize().x / 2.f - 480.f))
            m_position = { PreviousPos.x - 0.5f,PreviousPos.y };
        if (m_position.x < (m_owner.getGame().getWindowSize().x / 2.f + 490.f) && m_position.x >(m_owner.getGame().getWindowSize().x / 2.f + 480.f))
            m_position = { PreviousPos.x + 0.5f ,PreviousPos.y };
    }
    else
        m_position += m_velocity * deltaTime;
    m_velocity += acceleration * deltaTime;

    if (m_velocity.getLength() > SpeedLimit)
        m_velocity = m_velocity * (SpeedLimit / m_velocity.getLength());



    if (m_angle / 3.14159265f * 180.f < -160.f || m_angle / 3.14159265f * 180.f > 160.f && m_velocity == Vec2{0.f,0.f})
    {
        m_sprite = EnemySheet.Animation(deltaTime, 3, 1, 1, 0.f, true);
    }
    if (m_angle / 3.14159265f * 180.f < -20.f && m_angle / 3.14159265f * 180.f > -160.f && m_velocity == Vec2{ 0.f,0.f })
    {

        m_sprite = EnemySheet.Animation(deltaTime, 2, 1, 1, 0.f, true);
    }
    if (m_angle / 3.14159265f * 180.f < 160.f && m_angle / 3.14159265f * 180.f > 20.f && m_velocity == Vec2{ 0.f,0.f })
    {
        m_sprite = EnemySheet.Animation(deltaTime, 1, 1, 1, 0.f, true);
    }

    if (m_angle / 3.14159265f * 180.f < 20.f && m_angle / 3.14159265f * 180.f > -20.f && m_velocity == Vec2{ 0.f,0.f })
    {
        m_sprite = EnemySheet.Animation(deltaTime, 4, 1, 1, 0.f, true);
    }


    if (m_isDead)
    {
        
        

        m_elapsedTimedeath = m_clockdeath.getElapsedTime();

        if (m_elapsedTimedeath.asSeconds() >= m_timetodie)
        {
            destroy();
            m_clockdeath.restart();
        }
        m_sprite = EnemySheet.Animation(deltaTime, 5, 1, 3, 0.33f, true);
        m_velocity = { 0.f,0.f };
    }

}

void Kappa::render(sf::RenderWindow& window)
{
    m_sprite.setColor(sf::Color(255, 255, 255, 255));
    if (m_isInvincible)
    {
	    m_sprite.setColor(sf::Color(255, 50, 50, 128));
    	
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

OBB Kappa::getBoundingBox() const
{
    Vec2 size = getKappaSize();
    return {
        m_position,
        size / 2.0f,
        m_angle
    };
}

GameObjectType Kappa::gameObjectType()
{
    return KAPPA_TYPE;
}


void Kappa::takeDamage(int dmg)
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

void Kappa::die()
{
    if (m_isDead)
        return;
    m_isDead = true;

    m_currentTarget->m_score += scorePoint;
    m_clockdeath.restart();
	
}

int Kappa::getHP() const
{
    return m_HP;
}
int Kappa::getMaxHP()const
{
    return m_MaxHP;
}

float Kappa::getAngle()const
{
    return m_angle;
}