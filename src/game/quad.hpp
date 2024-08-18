#include <SFML/System/Vector3.hpp>
namespace hallslike {
	class Quad {
		public:
			sf::Vector3f position[4];

			Quad() = default;

			Quad(sf::Vector3f corner1, sf::Vector3f corner2, sf::Vector3f corner3, sf::Vector3f corner4) {
				position[0] = corner1;
				position[1] = corner2;
				position[2] = corner3;
				position[3] = corner4;
			}
	};
}