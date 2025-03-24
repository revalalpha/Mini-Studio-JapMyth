#include "Game.h"
#include "Scrolling.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "TextureCache.h"
#include "PathFinder.h"
#include <iostream>

Game* Game::m_gameInstance = nullptr;

Game::Game(sf::RenderWindow* window, const float& framerate)
    : SceneBase(window, framerate)
{
    m_gameInstance = this;
    initialize();
}

void Game::setPlayer()
{
    m_player = createPlayer();

	addCameraToPlayer();
    m_gameObjects.push_back(std::static_pointer_cast<ComponentGameObject>(m_player));
}

std::shared_ptr<Hero> Game::createPlayer()
{
    auto player = std::make_shared<Hero>("Player");
    if (!player)
    {
        std::cerr << "Failed to create player" << std::endl;
    }
    else
    {
        std::cout << "Player created successfully" << std::endl;
    }
    player->initialize(sf::Vector2f(1000, 1000.f), 50.f, sf::Color::Transparent, 300.f);
    return player;
}



void Game::setEnemy()
{
}

void Game::initialize()
{
	TextureManager::getInstance().initialize();
    TextureManager::getInstance().loadAllGameTextures();

    Camera::getInstance().initialize(m_renderWindow);
    Camera::getInstance().setZoom(1.f);
    Camera::getInstance().setInterpolationSpeed(4.0f);

    setMap();
    setPlayer();
}

void Game::setMap()
{
    m_map = createMap();
    m_gameObjects.push_back(std::static_pointer_cast<ComponentGameObject>(m_map));
}

std::shared_ptr<Map> Game::createMap()
{
    auto map = std::make_shared<Map>("Sprites\\map\\Map.png");
    std::cout << "map is loaded" << std::endl;
    map->load();
    return map;
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

    if (m_map) {
        std::cout << "Rendering: Map" << std::endl;
        m_map->render(*m_renderWindow);
    }

    for (auto& gameObject : m_gameObjects)
    {
        std::cout << "Rendering: " << gameObject->getName() << std::endl;
        gameObject->render(*m_renderWindow);
    }

    SceneBase::render();
}

Game* Game::getInstance()
{
    return m_gameInstance;
}