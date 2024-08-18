#include "game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <cmath>
#include <cstdlib>
#include <functional>
#include <map>
#include <string>
#include <vector>

void hallslike::Game::draw() {
	// Drawing planes
	sf::VertexArray vertices(sf::Quads, planes.size() * 4);

	std::vector<hallslike::Quad>::iterator planeIt;
	std::map<float, hallslike::Quad, std::less<float>> quadsSorted;

	window.clear(sf::Color::Black);

	int i = 0;

	std::map<float, Quad, std::greater<float>> offQuads;

	for(planeIt = planes.begin(); planeIt != planes.end(); planeIt++) {
		
	}

	std::map<float, Quad>::iterator it;

	for(it = offQuads.begin(); it != offQuads.end(); it++) {
		// Rotation coordinates
		sf::Vector3f rot1 = rotateWithCamera(it->second.position[0]);
		sf::Vector3f rot2 = rotateWithCamera(it->second.position[1]);
		sf::Vector3f rot3 = rotateWithCamera(it->second.position[2]);
		sf::Vector3f rot4 = rotateWithCamera(it->second.position[3]);

		// Projection coordinates
		sf::Vector2f proj1 = project(rot1, 0.0f);
		sf::Vector2f proj2 = project(rot2, 0.0f);
		sf::Vector2f proj3 = project(rot3, 0.0f);
		sf::Vector2f proj4 = project(rot4, 0.0f);

		// Drawing coordinates
		float x1Draw = ((float)  window.getSize().x / 2) + (proj1.x * 100.0f);
		float y1Draw = ((float) window.getSize().y / 2) + (proj1.y * 100.0f);

		float x2Draw = ((float) window.getSize().x / 2) + (proj2.x * 100.0f);
		float y2Draw = ((float) window.getSize().y / 2) + (proj2.y * 100.0f);

		float x3Draw = ((float) window.getSize().x / 2) + (proj3.x * 100.0f);
		float y3Draw = ((float) window.getSize().y / 2) + (proj3.y * 100.0f);

		float x4Draw = ((float) window.getSize().x / 2) + (proj4.x * 100.0f);
		float y4Draw = ((float) window.getSize().y / 2) + (proj4.y * 100.0f);

		if(
			(
				!insideScreen(x1Draw, y1Draw) &&
				!insideScreen(x2Draw, y2Draw) &&
				!insideScreen(x3Draw, y3Draw) &&
				!insideScreen(x4Draw, y4Draw)
			) ||
			(
				rot1.z < 0 &&
				rot2.z < 0 &&
				rot3.z < 0 &&
				rot4.z < 0
			)
		) {
			continue;
		}

		// Adding to vertecies
		vertices[(i + 0) * 4 + 0].position = sf::Vector2f(x1Draw, y1Draw);
		vertices[(i + 0) * 4 + 1].position = sf::Vector2f(x2Draw, y2Draw);
		vertices[(i + 0) * 4 + 2].position = sf::Vector2f(x3Draw, y3Draw);
		vertices[(i + 0) * 4 + 3].position = sf::Vector2f(x4Draw, y4Draw);

		vertices[(i + 0) * 4 + 0].color = sf::Color::Magenta;
		vertices[(i + 0) * 4 + 1].color = sf::Color::Green;
		vertices[(i + 0) * 4 + 2].color = sf::Color::White;
		vertices[(i + 0) * 4 + 3].color = sf::Color::Yellow;

		// Adding index
		i++;
	}

	window.draw(vertices);

	// Drawing debug info
	sf::Text quadsText;
	sf::Text posText;
	sf::Text rotationText;

	quadsText.setFont(mainFont);
	posText.setFont(mainFont);
	rotationText.setFont(mainFont);

	quadsText.setString(std::to_string(i) + " quad(s) drawn");
	posText.setString("POSITION X:" + std::to_string(player.position.x) + " Y:" + std::to_string(player.position.y) + " Z:" + std::to_string(player.position.z));
	rotationText.setString("ROTATION X:" + std::to_string(camera.rotation.x) + " Y:" + std::to_string(camera.rotation.y));

	quadsText.setFillColor(sf::Color::White);
	posText.setFillColor(sf::Color::White);
	rotationText.setFillColor(sf::Color::White);

	posText.setPosition(sf::Vector2f(0, 30.0f));
	rotationText.setPosition(sf::Vector2f(0, 60.0f));

	window.draw(quadsText);
	window.draw(posText);
	window.draw(rotationText);

	window.display();
}