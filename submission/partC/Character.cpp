#include "Character.h"

using namespace mtm;

Character::Character (int health, int ammo, int range, int power, Team team)
    : health (health), ammo (ammo), range (range), power (power), team (team) {
    if (health <= 0 || power < 0 || ammo < 0) {
        throw IllegalArgument();
    }
}

Character::Condition Character::health_add (int points) {
    health += points;
    if (health <= 0) {
        return DEAD;
    }
    return ALIVE;
}
