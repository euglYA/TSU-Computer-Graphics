#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Scene {
public:
	Scene();
	~Scene();

	void pollEvents(bool& restart);
	bool isOpen();
	void render();
	void addObject(Object* obj);


private:
	std::vector<Object*> objects;

	sf::RenderWindow* window;
};

