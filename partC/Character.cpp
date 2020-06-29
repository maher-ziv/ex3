#include "Character.h"

#include "Exceptions.h"

using namespace mtm;
;

Character::Character (int health, int ammo, int range, int power, Team team)
    : health (health), ammo (ammo), power (power), range (range), team (team) {
    if (health <= 0 || power < 0 || ammo < 0) {
        throw IllegalArgument();

    }  // TODO exception for coordinate
}

Character::Condition Character::health_add (int points) {
    health += points;
    if (health <= 0){
        return DEAD;
    }
    return ALIVE;
}



