#include "logger.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>

void hallslike::Logger::print(std::string message) {
	std::cout << message;
}

void hallslike::Logger::print(float message) {
	std::cout << message;
}

void hallslike::Logger::print(int message) {
	std::cout << message;
}