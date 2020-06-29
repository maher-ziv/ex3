#include "Game.h"

#include "Medic.h"
#include "Sniper.h"
#include "Soldier.h"

using namespace mtm;
using std::vector;

Game::Game (int height, int width) : height (height), width (width), board (height, vector<pCharacter> (width)) {
    if (height <= 0 || width <= 0) {
        throw IllegalArgument();
    }
}

static shared_ptr<Character> makeCharacter (CharacterType type, Team team, units_t health, units_t ammo, units_t range,
                                            units_t power) {

    if (type == SOLDIER) {
        return shared_ptr<Character> (new Soldier (health, ammo, range, power, team));
    }
    if (type == MEDIC) {
        return shared_ptr<Character> (new Medic (health, ammo, range, power, team));
    }
    if (type == SNIPER) {
        return shared_ptr<Character> (new Sniper (health, ammo, range, power, team));
    }
}

void Game::addCharacter (const GridPoint &coordinates, shared_ptr<Character> character) {
    if (coordinates.row < 0 || coordinates.row >= height || coordinates.col < 0 || coordinates.col >= width){
        throw IllegalCell();
    }
    character->locate (coordinates);
    board.at (coordinates.row).at (coordinates.col) = character;
}

void Game::move (const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
    this->
}
