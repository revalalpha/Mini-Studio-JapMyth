#pragma once

#include "Hero.h"
#include "SceneBase.h"

class Game : public SceneBase
{
public:
	Game(sf::RenderWindow* window, const float& framerate, TextureCache* texture);
	~Game() = default;

	void setPlayer();
	void setEnemy();
	void initialize();

	void processInput(const sf::Event& event) override;
	void update(const float& deltaTime) override;
	void render() override;

private:
	std::shared_ptr<Hero> m_player;
	sf::Sprite m_mapSprite;
	std::vector<std::shared_ptr<ComponentGameObject>> m_gameObjects;
};