#pragma once
#include <memory>
#include <vector>

#include "IScene.h"

class SceneManager
{
public:
	SceneManager(const int& width, const int& height, const std::string& title, const std::string& execPath);

	void push_back(std::unique_ptr<IScene> scene);
	sf::RenderWindow* getWindow();
	IScene* getCurrentScene();
	void setCurrentScene(const int& index);
	void processInput();
	void exec();

private:
	std::unique_ptr<sf::RenderWindow> m_window;
	std::vector<std::unique_ptr<IScene>> m_scenes;
	IScene* m_currentScene;
};