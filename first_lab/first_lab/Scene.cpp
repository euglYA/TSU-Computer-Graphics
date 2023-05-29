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
	window->clear(sf::Color::Blue);
	sf::RectangleShape ground(sf::Vector2f(800.f, 300.f));
	ground.setFillColor(sf::Color(128, 64, 48));
	ground.setPosition(0.f, 500.f);
	//sf::RectangleShape box;
	//box.setSize(sf::Vector2f(150, 150));
	sf::CircleShape circle(150.f);
	circle.setFillColor(sf::Color(1, 50, 32));
	circle.setPosition(400.f, -50.f);
	window->draw(ground);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->render(*window);

	window->display();
}

void Scene::addObject(Object* obj) {
	objects.push_back(obj);
}