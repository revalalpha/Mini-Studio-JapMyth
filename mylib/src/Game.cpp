#include "Game.h"

#include <array>
#include <filesystem>

#include "IGameObject.h"

#include "PlayerShip.h"


#include "Barrier.h"
#include "Boss.h"



Game::Game(sf::RenderWindow& window, const std::string& execPath)
    :// m_window(sf::VideoMode(), "Boss!", sf::Style::Fullscreen)
     m_textureCache(execPath)
	, m_Width(window.getSize().x)
	, m_Height(window.getSize().y)
{
    //m_window.setFramerateLimit(60);
    
    font.loadFromFile(this->getTextureCache().getAbsoluteFilepath("arial.ttf"));
    new Barrier(*this,
        Vec2(m_Width / 2.0f, -15.0f),
        Vec2(m_Width + 40.0f, 30.0f)
    );

    new Barrier(*this,
        Vec2(m_Width / 2.0f, m_Height + 14.0f),
        Vec2(m_Width + 40.0f, 30.0f)
    );

    new Barrier(*this,
        Vec2(-14.0f, m_Height / 2.0f),
        Vec2(30.0f, m_Height + 40.0f)
    );

    new Barrier(*this,
        Vec2(m_Width + 15.0f, m_Height / 2.0f),
        Vec2(30.0f, m_Height + 40.0f)
    );
    

    new PlayerShip(*this, {( m_Width+300) - m_Width, m_Height / 2.0f });
    new Boss(*this, { m_Width / 2.0f, m_Height / 2.0f });
}

Game::~Game()
{
}

Vec2 Game::getWindowSize()const
{
    return { m_Width, m_Height };
}

void Game::update(const float& delaTime)
{
    _deferedAddObjects();

    detectCollision();
    for (auto& gameObject : m_allGameObjects)
        gameObject->update(delaTime);

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

    for (auto& gameObject : m_allGameObjects)
        gameObject->render(window);

    renderBoundingBox(window);

    window.display();
}

void Game::renderBoundingBox(sf::RenderWindow& window)
{
    for (const auto& go : m_allGameObjects)
    {
        sf::RectangleShape rectangle({ m_Width -350.f,m_Height - 250.f });
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setOutlineThickness(5);
        rectangle.setOrigin(rectangle.getSize().x / 2.f, rectangle.getSize().y / 2);
        rectangle.setPosition({ m_Width /2.f, m_Height / 2.f });
        rectangle.setFillColor(sf::Color::Transparent);
    	
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
        window.draw(&lines[0], lines.size(), sf::Lines);
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
