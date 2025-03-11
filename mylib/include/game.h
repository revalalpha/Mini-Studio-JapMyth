#pragma once

#include "hero.h"
#include "sceneBase.h"

class Boss;

class Game : public SceneBase
{
public:
    Game(sf::RenderWindow* window, const float& framerate);
    ~Game() override = default;

    // PLAYER
    void setPlayer();
    void setBoss();
    Hero& getPlayer();
    Boss* getBoss() const;
    void checkCollision();

    // ENEMIES
    void spawnEnemy(sf::RenderWindow* window);

    // GAME MAP
    void setBackground(sf::RenderWindow* window);
    void setGroundTexture(sf::RenderWindow* window);
    sf::FloatRect getGroundHitbox();
    sf::FloatRect getPlatformHitbox();
    sf::FloatRect GetWindowCollision();

    void processInput(const sf::Event& event) override;
    void update(const float& deltaTime) override;
    void render() override;

    void drawHitboxes();

private:
    int m_enemiesCount;
    Hero m_player;
    /*std::unique_ptr<Boss> m_boss;*/

    // MAP
    sf::RectangleShape m_rectangle_shape;
    sf::Texture m_mapTexture;

    // PLATFORM
    sf::RectangleShape m_platform;
    sf::Texture m_platformTexture;

    // BACKGROUND
    sf::Texture m_backgroundTexture;
    sf::RectangleShape m_backgroundShape;
    sf::Music m_gameMusic;

    // SCORE
    sf::Font m_scoreFont;
    sf::Text m_scoreText;
    int m_score = 0;

    // FPS COUNTER
    sf::Font m_fpsFont;
    sf::Text m_fpsText;
    SceneBase* m_currentScene;
    sf::Clock m_fpsClock;
    int m_fpsCounter = 0;
    float m_fpsStartTime = 0.f;

    // GAME OVER
    void displayGameOver();
    sf::Text m_gameOverText;
    sf::Text m_winText;
    bool m_isGameOver = false;
};