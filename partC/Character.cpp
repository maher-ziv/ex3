#include "Character.h"

#include "Exceptions.h"

using mtm::Character;

Character::Character (int health, int ammo, int range, int power, Team team)
    : health (health), ammo (ammo), power (power) , range(range) , team(team) , coordinates(OUT_OF_GAME) {
    if (health <= 0 || power < 0 || ammo < 0) {
        throw IllegalArgument();

    
} //TODO exception for coordinate
