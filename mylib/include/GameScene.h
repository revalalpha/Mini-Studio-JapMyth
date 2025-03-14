#pragma once
#include "IScene.h"
#include "SceneManager.h"
#include "Game.h"

class GameScene : public IScene
{
public:
    GameScene(sf::RenderWindow* window, SceneManager* sceneManager, const float& framerate, const std::string& execPath);
    ~GameScene();

    void setBackground(sf::RenderWindow* window);
    void processInput(const sf::Event& event) override;
    void update(const float& deltaTime) override;
    void render() override;

private:
    SceneManager* m_sceneManager;
    Game* m_game;

    sf::Texture m_background;
    sf::Sprite m_backgroundSprite;
};