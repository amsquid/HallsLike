#include "entity.hpp"

void hallslike::Entity::move() {
    position.x += velocity.x;
    position.y += velocity.y;
    position.z += velocity.z;
}