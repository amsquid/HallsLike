#include "game.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>

void hallslike::Game::loop() {
	while(window.isOpen()) {
		pollEvents();
		update();
		draw();
	}
}

void hallslike::Game::stopGame() {
	logger.print("Closing game\n");
	
	window.close();
}

void hallslike::Game::startGame() {
	// Creating Logger
	logger = hallslike::Logger();

	// Setting up window
	logger.print("Setting up window\n");
	window.create(sf::VideoMode(1280, 720), "Hallslike", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i());
	window.setMouseCursorVisible(false);

	// Loading font
	logger.print("Loading font\n");
	if(!mainFont.loadFromFile("assets/fonts/main.ttf")) {
		logger.print("Couldn't find main font at: ./assets/fonts/main.ttf\n");

		return;
	}

	// Setting framerate limit
	logger.print("Setting framerate limit to 60\n");
	window.setFramerateLimit(60);

	// Setting up keys vector
	logger.print("Reserving space for keysDown vector");
	for(int i = 0; i < sf::Keyboard::KeyCount; i++) keysDown.push_back(false);

	// Creating player
	logger.print("Creating player\n");
	player = hallslike::Player();

	// Creating test blocks
	logger.print("Creating test block(s)\n");
	//blocks.push_back(Block(0, 0, 0));
	for(int z = -10; z < 10; z++) {
		for (int x = -10; x < 10; x++) {
			int currY = std::sin(x * 3.14f) * 5.0f;

			while(currY < 5) {
				blocks[sf::Vector3i(x, currY, z)] = Block();
				
				currY++;
			}
		}
	}

	// Starting game loop
	logger.print("Starting game loop\n");
	loop();
}