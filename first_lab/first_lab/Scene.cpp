#include "Scene.h"

Scene::Scene() {
	window = new sf::RenderWindow(sf::VideoMode(800, 800), "spinning box", sf::Style::Default);
}

Scene::~Scene() {
	if (window)
		delete window;
}

void Scene::pollEvents(bool& restart) {
	restart = false;

	sf::Event event;

	while (window->pollEvent(event)) {
		
		if (event.type == sf::Event::Closed)
			window->close();
	
		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::R)
				restart = true;
	}
}

bool Scene::isOpen() {
	return window->isOpen();
}

void Scene::render() {
	window->clear(sf::Color::White);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->render(*window);

	window->display();
}

void Scene::addObject(Object* obj) {
	objects.push_back(obj);
}