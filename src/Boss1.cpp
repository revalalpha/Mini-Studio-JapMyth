#include "Boss1.h"

#include "Boss1Behavior.h"
#include "Projectile.h"
#include "Game.h"
#include "OrbitalProjectile.h"



float getBoss1FluidFrictionCoef() { return 5.0f; }

Vec2 getBoss1Size()
{
    return { 120.f, 80.f };
}

Vec2 getBoss1Velo() { return { 32.f, 32.f }; }

Boss1::Boss1(IGameObjectContainer& game, const Vec2& position)
    : IGameObject(game)
    , m_position(position)
	,m_rootNode1(this)
	, EnemySheet(512.f, 512.f, getOwner().getGame().getTextureCache().getTexture("boss-cheval.png"))

{
    m_lifeBar.setTexture(getOwner().getGame().getTextureCache().getTexture("katana vieB.png"));
    auto* behavior = new BT::Retry(&m_rootNode1);


    
    auto* Melee = new BT::PlayerDictanceBoss1(behavior, 0.f, 600.f);
    new BT::WalkBoss1(behavior);


    auto* MeleeSequence = new BT::Sequence(Melee);
    new BT::IdleBoss1(MeleeSequence);
    new BT::WaitBoss1(MeleeSequence, 0.3f);
    new BT::SprintBoss1(MeleeSequence);
    new BT::MeleeBoss1(MeleeSequence);
    new BT::WaitBoss1(MeleeSequence,2.f);



    auto* dead = new BT::IsDeadBoss1(behavior);
    auto* death = new BT::Retry(dead);
    new BT::IsPlayerDeadBoss1(death);

    new BT::IsPlayerDeadBoss1(behavior);

    
}

Vec2 Boss1::getDistanceToPlayer() const
{
    return m_currentTarget->getPositon() - m_position;
}
float Boss1::calculateAngleToTarget() const
{
    if (!m_currentTarget)
        return m_angle;


    Vec2 directionToPlayer = getDistanceToPlayer();
    return std::atan2(directionToPlayer.y, directionToPlayer.x);
}

bool Boss1::findValidTarget()
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

bool Boss1::isCurrentTargetValid() const
{
    if (m_currentTarget->getHP() <= 0)
        return false;

    return true;
}
void Boss1::setSpeed(const int& Speed)
{
    m_speed = Speed;
}




void Boss1::RightMelee()
{

    


    if (m_angle / 3.14159265f * 180.f < -160.f || m_angle / 3.14159265f * 180.f > 160.f)
    {

        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f/60.f, 8, 1, 5, 0.3f, true);
        //new OrbitalProjectile(m_owner, this, -160.f, 40.f, -7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }
    if (m_angle / 3.14159265f * 180.f < -20.f && m_angle / 3.14159265f * 180.f > -160.f)
    {
        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f / 60.f, 6, 1, 3, 0.3f, true);
        //new OrbitalProjectile(m_owner, this, -60.f, 40.f, -7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }
    if (m_angle / 3.14159265f * 180.f < 160.f && m_angle / 3.14159265f * 180.f > 20.f)
    {
        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f / 60.f, 5, 1, 3, 0.3f, true);
        //new OrbitalProjectile(m_owner, this, 120.f, 40.f, -7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }

    if (m_angle / 3.14159265f * 180.f < 20.f && m_angle / 3.14159265f * 180.f > -20.f)
    {
        EnemySheet.interruptAnimation();
        m_sprite = EnemySheet.Animation(1.f / 60.f, 7, 1, 5, 0.3f, true);
        //new OrbitalProjectile(m_owner, this, -60.f, 40.f, 7.f, 65, 80.f, 20.f, ENEMYmelee_TYPE);
    }
    m_isSprinting = true;
    m_clockDashTime.restart();
}


Vec2 Boss1::getPosition() const
{
    return m_position;
}



void Boss1::handleInputs(const sf::Event& event)
{
    
}

void Boss1::update(float deltaTime)
{


    m_allGameObjects = getOwner().getAllGameOjects();
    findValidTarget();
    m_rootNode1.tick();

    if (!m_isSprinting)
		m_angle = calculateAngleToTarget();
    else 
    {
        m_elapsedTimeDashCooldown = m_clockDashTime.getElapsedTime();

        if (m_elapsedTimeDashCooldown.asSeconds() >= m_dashTime)
        {

            m_isSprinting = false;
            m_clockDashTime.restart();
        }
    }

    if (m_angle / 3.14159265f * 180.f < -160.f || m_angle / 3.14159265f * 180.f > 160.f && m_velocity != Vec2{ 0.f,0.f })
    {
        m_sprite = EnemySheet.Animation(deltaTime, 4, 1, 5, 0.1f, true);
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
	    m_sprite = EnemySheet.Animation(deltaTime, 3, 1, 5, 0.1f, true);
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
        acceleration = -getBoss1FluidFrictionCoef() * m_velocity;

    if (m_speed>0)
		acceleration += m_speed * Vec2 { std::cos(m_angle), std::sin(m_angle) };


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
        m_sprite = EnemySheet.Animation(deltaTime, 4, 1, 1, 0.f, true);
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
        m_sprite = EnemySheet.Animation(deltaTime, 3, 1, 1, 0.f, true);
    }


    if (m_isDead)
    {
        
        

        m_elapsedTimedeath = m_clockdeath.getElapsedTime();

        if (m_elapsedTimedeath.asSeconds() >= m_timetodie)
        {
            destroy();
            m_clockdeath.restart();
        }
        m_sprite = EnemySheet.Animation(deltaTime, 9, 1, 3, 0.33f, true);
        m_velocity = { 0.f,0.f };
    }

}

void Boss1::render(sf::RenderWindow& window)
{
    m_sprite.setColor(sf::Color(255, 255, 255, 255));
    if (m_isInvincible)
    {
	    m_sprite.setColor(sf::Color(255, 50, 50, 128));
    	
    }
    //m_sprite.setRotation(m_angle / 3.14159265f * 180.f);
    m_sprite.setScale(0.35f, 0.35f);
    m_sprite.setOrigin(m_sprite.getLocalBounds().getSize().x / 2.f, m_sprite.getLocalBounds().getSize().y / 2.f);
    m_sprite.setPosition(m_position.x, m_position.y);
    //sf::Text HP("testHP : " + std::to_string(m_HP) + " / " + std::to_string(m_MaxHP), m_owner.getGame().font,45);
    //HP.setOrigin(HP.getLocalBounds().width /2.f, HP.getLocalBounds().height / 2.f);
    //HP.setPosition(m_owner.getGame().getWindowSize().x / 2.f, m_owner.getGame().getWindowSize().y - 100);
    //HP.setStyle(sf::Text::Bold);

    m_lifeBar.setOrigin(m_lifeBar.getGlobalBounds().getSize().x/2.f, m_lifeBar.getGlobalBounds().getSize().y/2.f);
    m_lifeBar.setPosition(m_currentTarget->getPositon().x, m_currentTarget->getPositon().y + 300);

    sf::RectangleShape rec({ -18.f * (m_MaxHP-m_HP), m_lifeBar.getGlobalBounds().getSize().y - 32 });
    rec.setFillColor(sf::Color::Black);
    rec.setPosition(m_currentTarget->getPositon().x + 192, m_currentTarget->getPositon().y + 287);


    window.draw(m_sprite);
    window.draw(m_lifeBar);
    window.draw(rec);
    //window.draw(HP);
}

OBB Boss1::getBoundingBox() const
{
    Vec2 size = getBoss1Size();
    return {
        m_position,
        size / 2.0f,
        m_angle
    };
}

GameObjectType Boss1::gameObjectType()
{
    return BOSS1_TYPE;
}


void Boss1::takeDamage(int dmg)
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

void Boss1::die()
{
    if (m_isDead)
        return;
    m_isDead = true;

    m_currentTarget->m_score += scorePoint;
    m_clockdeath.restart();
	
}

int Boss1::getHP() const
{
    return m_HP;
}
int Boss1::getMaxHP()const
{
    return m_MaxHP;
}

float Boss1::getAngle()const
{
    return m_angle;
}