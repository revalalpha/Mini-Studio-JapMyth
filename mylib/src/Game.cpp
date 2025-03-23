#include "Game.h"
#include "Scrolling.h"
#include "Enemy.h"
#include "TextureManager.h"
#include <iostream>

Game::Game(sf::RenderWindow* window, const float& framerate, TextureCache* texture)
    : SceneBase(window, framerate, texture)
{
    initialize();
}

void Game::setPlayer()
{
    m_player = createPlayer();

	addCameraToPlayer();
    m_gameObjects.push_back(m_player);
}

std::shared_ptr<Hero> Game::createPlayer()
{
    auto player = std::make_shared<Hero>("Player");
    player->initialize(sf::Vector2f(1000, 1000.f), 50.f, sf::Color::Transparent, 300.f);
    return player;
}

void Game::setEnemy()
{
}

void Game::initialize()
{
    Camera::getInstance().initialize(m_renderWindow);
    Camera::getInstance().setZoom(1.f);
    Camera::getInstance().setInterpolationSpeed(4.0f);

    setMap();
    setPlayer();
}

void Game::setMap()
{
    sf::Texture& mapTexture = m_texture_cache->GetTexture("map\\Map.png");
    m_mapSprite.setTexture(mapTexture);
    m_mapSprite.setPosition(m_renderWindow->getPosition().x, m_renderWindow->getPosition().y);
}

void Game::addCameraToPlayer()
{
    auto cameraTarget = std::make_shared<CameraTarget>(1.0f, true);
    m_player->addComposite(cameraTarget);
}


void Game::processInput(const sf::Event& event)
{
    m_player->processInput(event);

    SceneBase::processInput(event);
}

void Game::update(const float& deltaTime)
{
    SceneBase::update(deltaTime);

    for (auto& gameObject : m_gameObjects)
        gameObject->update(deltaTime);

    m_player->update(deltaTime);

    SquareRenderer* playerRender = nullptr;

    playerRender = dynamic_cast<SquareRenderer*>(m_player->getComposite("SquareRenderer"));
    if (playerRender) {
        sf::Vector2f playerPos = playerRender->getPosition();
        /*IEnemy::updateAllEnemyLOS(m_gameObjects, playerPos);*/
    }

    Camera::getInstance().update(deltaTime);
}

void Game::render()
{
    Camera::getInstance().apply();

    m_renderWindow->draw(m_mapSprite);

    for (auto& gameObject : m_gameObjects)
    {
        std::cout << "Rendering: " << gameObject->getName() << std::endl;
        gameObject->render(*m_renderWindow);
    }

    SceneBase::render();
}
