#include <SFML/System/Vector3.hpp>
#include <functional>

namespace hallslike {
	struct Vector3iHash {
		std::size_t operator()(const sf::Vector3i& v) const {
			return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1) ^ (std::hash<int>()(v.z) << 2);
		}
	};
}
