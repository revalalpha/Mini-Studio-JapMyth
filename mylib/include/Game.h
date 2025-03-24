#pragma once

#include "Hero.h"
#include "SceneBase.h"
#include "Map.h"

class Game : public SceneBase
{
public:
	Game(sf::RenderWindow* window, const float& framerate);
	~Game() = default;

	void setPlayer();
	void setMap();
	void setEnemy();
	void initialize();

	void processInput(const sf::Event& event) override;
	void update(const float& deltaTime) override;
	void render() override;

	void addCameraToPlayer();
	std::shared_ptr<Hero> createPlayer();
	std::shared_ptr<Map> createMap();
	Game* getInstance();
private:
	std::shared_ptr<Hero> m_player;
	std::shared_ptr<Map> m_map;
	sf::Sprite m_heroTexture;
	std::vector<std::shared_ptr<ComponentGameObject>> m_gameObjects;
	static Game* m_gameInstance;

};