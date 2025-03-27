#include "Game.h"

#include <array>
#include <filesystem>
#include <random>

#include "IGameObject.h"

#include "PlayerShip.h"


#include "Barrier.h"
#include "Boss1.h"
#include "Inugami.h"
#include "Kappa.h"
#include "Samurai.h"



Game::Game(sf::RenderWindow& window, const std::string& execPath)
    :// m_window(sf::VideoMode(), "Boss!", sf::Style::Fullscreen)
     m_textureCache(execPath)
	, m_Width(window.getSize().x)
	, m_Height(window.getSize().y)
{
    //m_window.setFramerateLimit(60);

    m_backgroundSprite.setTexture(this->getTextureCache().getTexture("map.png"));
    m_backgroundSprite.setPosition(window.getPosition().x, window.getPosition().y);
    m_backgroundSprite.setScale(1.4, 1.2);
    
    font.loadFromFile(this->getTextureCache().getAbsoluteFilepath("arial.ttf"));
    new Barrier(*this,
        Vec2((m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.0f, -15.0f),
        Vec2((m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) + 40.0f, 30.0f)
    );

    new Barrier(*this,
        Vec2((m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.0f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) + 14.0f),
        Vec2((m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) + 40.0f, 30.0f)
    );

    new Barrier(*this,
        Vec2(-14.0f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) / 2.0f),
        Vec2(30.0f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) + 40.0f)
    );

    new Barrier(*this,
        Vec2((m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) + 15.0f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) / 2.0f),
        Vec2(30.0f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) + 40.0f)
    );
    
	new Barrier(*this,
        Vec2((m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) / 2.f),
        Vec2(800.f, 1000.f)
    );

    new PlayerShip(*this, {4000.f, 1000.f});



}

Game::~Game()
{
}

Vec2 Game::getWindowSize()const
{
    return { (m_backgroundSprite.getLocalBounds().getSize().x * 1.4f), (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) };
}

void Game::Spawner()
{
    

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> enemy(1, 3);
    std::uniform_int_distribution<std::mt19937::result_type> posx(310, getWindowSize().x - 310.f);
    std::uniform_int_distribution<std::mt19937::result_type> posy(370, getWindowSize().y - 270.f);

    Vec2 position = { static_cast<float>(posx(rng)) ,static_cast<float>(posy(rng)) };
    
    if (position.x > getWindowSize().x / 2.f - 490.f && position.x < getWindowSize().x / 2.f + 490.f && position.y >getWindowSize().y / 2.f - 650.f && position.y < getWindowSize().y / 2.f + 550.f)
    {
        return;
    }
    if (spawnBoss1)
    {
        new Boss1(* this, position);
        spawnBoss1 = false;
    }

    else if (enemy(rng) == 1)
    {
        new Samurai(*this, position);
    }
    else if (enemy(rng) == 2)
    {
        new Kappa(*this, position);
    }
    else if (enemy(rng)==3)
    {
        new Inugami(*this, position);
    }
    

}


void Game::update(const float& delaTime)
{
    m_elapsedTimeSpawn = m_clockSpawnTime.getElapsedTime();

    if (m_elapsedTimeSpawn.asSeconds() >= m_SpawnTime)
    {

        Spawner();
        m_clockSpawnTime.restart();
    }
    

    _deferedAddObjects();

    detectCollision();
    for (auto& gameObject : m_allGameObjects)
        gameObject->update(1.f/ 60.f);

    _cleanObject();
}

void Game::detectCollision()
{
    for (size_t i = 0; i < m_allGameObjects.size(); ++i)
    {
        for (size_t j = i + 1; j < m_allGameObjects.size(); ++j)
        {
            IGameObject* go1 = m_allGameObjects[i];
            IGameObject* go2 = m_allGameObjects[j];

            bool isIntersection = doesIntersect(go1->getBoundingBox(), go2->getBoundingBox());
            if (isIntersection)
                onCollision(go1, go2);
        }
    }
}

void Game::render(sf::RenderWindow& window)
{
    window.clear();
    window.draw(m_backgroundSprite);
    for (auto& gameObject : m_allGameObjects)
        gameObject->render(window);

    renderBoundingBox(window);

    //window.display();
}

void Game::renderBoundingBox(sf::RenderWindow& window)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
    {
        if (m_renderBoundingBox)
            m_renderBoundingBox = false;
        else
			m_renderBoundingBox = true;
        
    }
    if (m_renderBoundingBox)
    {
    	for (const auto& go : m_allGameObjects)
		{
	    sf::RectangleShape rectangle({ m_backgroundSprite.getLocalBounds().getSize().x*1.4f -570.f ,m_backgroundSprite.getLocalBounds().getSize().y * 1.2f-600.f });
        
    	rectangle.setOutlineColor(sf::Color::Green);
    	rectangle.setOutlineThickness(6);
    	rectangle.setOrigin(rectangle.getSize().x/2.f , rectangle.getSize().y/2.f );
    	rectangle.setPosition({ (m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f+100.f) / 2.f });
    	rectangle.setFillColor(sf::Color::Transparent);
    	sf::RectangleShape temple({900.f , 1100.f });
    	temple.setOutlineColor(sf::Color::Green);
    	temple.setOutlineThickness(6);
    	temple.setOrigin(temple.getSize().x / 2.f, temple.getSize().y / 2.f);
    	temple.setPosition({ (m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f-70) / 2.f });
    	temple.setFillColor(sf::Color::Transparent);


    	OBB obb = go->getBoundingBox();
    	sf::Color col = sf::Color::Green;

    	auto corners = obb.getCorners();

    	std::vector<sf::Vertex> lines;
    	lines.reserve(8);

    	for (size_t i = 0; i < corners.size(); ++i) {
    		size_t nextIdx = (i + 1) % corners.size();
    		lines.push_back(sf::Vertex{ {corners[i].x, corners[i].y}, col });
    		lines.push_back(sf::Vertex{ {corners[nextIdx].x, corners[nextIdx].y}, col });
    	}
    	window.draw(rectangle);
    	window.draw(temple);
    	window.draw(&lines[0], lines.size(), sf::Lines);
		}
    }
}


void Game::handleInputs(const sf::Event& event)
{

    for (auto& go : m_allGameObjects)
        go->handleInputs(event);
}

TextureCache& Game::getTextureCache()
{
    return m_textureCache;
}

