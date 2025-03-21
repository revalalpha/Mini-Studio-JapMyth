#include "Game.h"

#include <array>
#include <filesystem>

#include "IGameObject.h"

#include "PlayerShip.h"


#include "Barrier.h"
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
    
	//new Barrier(*this,
 //       Vec2((m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) / 2.f),
 //       Vec2(800.f, 1000.f)
 //   );

    new PlayerShip(*this, {1000.f, 1000.f});
    new Samurai(*this, { (m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.0f- 2000.f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) / 2.0f -200.f});
    new Samurai(*this, { (m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.0f - 1000.f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) / 2.0f + 50 });
    new Samurai(*this, { (m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.0f - 500.f,(m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) / 2.0f + 100});
    new Samurai(*this, { (m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.0f - 1000.f, (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) / 2.0f - 50 });
    new Samurai(*this, { (m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.0f - 500.f,(m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) / 2.0f - 100 });
    new Samurai(*this, { (m_backgroundSprite.getLocalBounds().getSize().x * 1.4f) / 2.0f - 2000.f,(m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) / 2.0f - 200 });

}

Game::~Game()
{
}

Vec2 Game::getWindowSize()const
{
    return { (m_backgroundSprite.getLocalBounds().getSize().x * 1.4f), (m_backgroundSprite.getLocalBounds().getSize().y * 1.2f) };
}

void Game::update(const float& delaTime)
{
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

