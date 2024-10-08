#include "game.hpp"
#include <SFML/System/Vector3.hpp>
#include <algorithm>
#include <cmath>

// Distance
float hallslike::Game::distanceFrom(sf::Vector3f origin, sf::Vector3f other) {
	float dx = other.x - origin.x;
	float dy = other.y - origin.y;
	float dz = other.z - origin.z;

	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

float hallslike::Game::calculateDepthForSorting(const sf::Vector3f cameraPos, const sf::Vector3f planePos, const sf::Vector2f cameraRotation) {
	sf::Vector3f cameraDir(
		std::cos(cameraRotation.y) * std::cos(cameraRotation.x),
		std::sin(cameraRotation.x),
		std::sin(cameraRotation.y) * std::cos(cameraRotation.x)
	);

	sf::Vector3f relativePos = planePos - cameraPos;

	return (relativePos.x * cameraDir.x) +
		   (relativePos.y * cameraDir.y) +
		   (relativePos.z * cameraDir.z);
}

// Projections
sf::Vector2f hallslike::Game::project(sf::Vector3f position, float distance) {
	float aspect = (float) window.getSize().x / window.getSize().y;

	float z = std::max(position.z, camera.near);

	return sf::Vector2f(
		((position.x / (z + distance)) * camera.fov * aspect),
		((position.y / (z + distance)) * camera.fov)
	);
}

sf::Vector2f hallslike::Game::project(sf::Vector3i position, float distance) {
	float aspect = (float) window.getSize().x / window.getSize().y;

	float z = std::max((float) position.z, camera.near);

	return sf::Vector2f(
		((position.x / (z + distance)) * camera.fov * aspect),
		((position.y / (z + distance)) * camera.fov)
	);
}

// Rotations
sf::Vector3f hallslike::Game::rotateWithCamera(sf::Vector3f position) {
	// X Rotation
	float xr1 = (position.x * std::cos(camera.rotation.x)) - (position.z * sin(camera.rotation.x));
	float yr1 = position.y;
	float zr1 = (position.x * std::sin(camera.rotation.x)) + (position.z * cos(camera.rotation.x));

	// Y rotation
	float xr2 = xr1;
	float yr2 = (yr1 * std::cos(camera.rotation.y)) - (zr1 * std::sin(camera.rotation.y));
	float zr2 = (yr1 * std::sin(camera.rotation.y)) + (zr1 * std::cos(camera.rotation.y));

	// Return
	return sf::Vector3f(xr2, yr2, zr2);
}

// Adding Vectors
sf::Vector3f hallslike::Game::addVector3(sf::Vector3f first, sf::Vector3f second) {
	return sf::Vector3f(
		first.x + second.x,
		first.y + second.y,
		first.z + second.z
	);
}

sf::Vector3f hallslike::Game::addVector3(sf::Vector3i first, sf::Vector3f second) {
	return sf::Vector3f(
		first.x + second.x,
		first.y + second.y,
		first.z + second.z
	);
}

sf::Vector3f hallslike::Game::addVector3(sf::Vector3f first, sf::Vector3i second) {
	return sf::Vector3f(
		first.x + second.x,
		first.y + second.y,
		first.z + second.z
	);
}

sf::Vector3f hallslike::Game::addVector3(sf::Vector3i first, sf::Vector3i second) {
	return sf::Vector3f(
		first.x + second.x,
		first.y + second.y,
		first.z + second.z
	);
}

// Multiplying vectors
sf::Vector3f hallslike::Game::mulVector3(sf::Vector3f first, float second) {
	return sf::Vector3f(
		first.x * second,
		first.y * second,
		first.z * second
	);
}

// Vector conversion
sf::Vector3i hallslike::Game::as3i(sf::Vector3f position) {
	return sf::Vector3i(
		(int) position.x,
		(int) position.y,
		(int) position.z
	);
}

// Center of Quad
sf::Vector3f hallslike::Game::centerQuad(sf::Vector3f positions[4]) {
	return sf::Vector3f(
		(positions[0].x + positions[1].x + positions[2].x + positions[3].x) / 4,
		(positions[0].y + positions[1].y + positions[2].y + positions[3].y) / 4,
		(positions[0].z + positions[1].z + positions[2].z + positions[3].z) / 4
	);
}


// Inside Screen
bool hallslike::Game::insideScreen(float x, float y) {
	return 
		x < window.getSize().x && x > 0 &&
		y < window.getSize().y && y > 0;
}