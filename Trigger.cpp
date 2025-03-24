#include "Trigger.h"
#include <iostream>

class Trigger {
private:
    sf::Vector2f position;
    float range;

public:
    Trigger(sf::Vector2f pos, float r) : position(pos), range(r) {}

    bool isActivated(const sf::Vector2f& enemyPos) const {
        return (enemyPos.x > position.x - range && enemyPos.x < position.x + range &&
            enemyPos.y > position.y - range && enemyPos.y < position.y + range);
    }

    sf::Vector2f getPosition() const {
        return position;
    }
};
