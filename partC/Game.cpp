#include "Game.h"

#include "Medic.h"
#include "Sniper.h"
#include "Soldier.h"
#include <array>
using namespace mtm;
using std::vector;
using std::array;

Game::Game (int height, int width) : height (height), width (width), board (height, vector<pCharacter> (width)) ,out(nullptr) {
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
    if (coordinates.row < 0 || coordinates.row >= height || coordinates.col < 0 || coordinates.col >= width) {
        throw IllegalCell();
    }
    if (board.at (coordinates.row).at (coordinates.col)) {
        throw CellOccupied();  // TODO לבדןק שישי null
    }
    board.at (coordinates.row).at (coordinates.col) = character;
}

void Game::move (const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {

    if (src_coordinates.row < 0 || src_coordinates.row >= height || src_coordinates.col < 0 ||
        src_coordinates.col >= width || dst_coordinates.row < 0 || dst_coordinates.row >= height ||
        dst_coordinates.col < 0 || dst_coordinates.col >= width) {
        throw IllegalCell();
    }
    if (!board.at (src_coordinates.row).at (src_coordinates.col)) {
        throw CellEmpty();  // TODO לבדןק לא null
    }
    if (board.at (dst_coordinates.row).at (dst_coordinates.col)) {
        throw CellOccupied();  // TODO לבדןק לא null
    }
    if (board.at (src_coordinates.row).at (src_coordinates.col)->max_steps() <
        GridPoint::distance (src_coordinates, dst_coordinates)) {
        throw MoveTooFar();
    }
    board.at (dst_coordinates.row).at (dst_coordinates.col) = board.at (src_coordinates.row).at (src_coordinates.col);
    board.at (src_coordinates.row)
        .at (src_coordinates.col)
        .reset();  // = nullptr; //TODO לבדוק שזה לא גורם לדילפת זיכרון ,אם כן אולי צרייך לשחרר את הזיכרון
}

void Game::attack (const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
    if (src_coordinates.row < 0 || src_coordinates.row >= height || src_coordinates.col < 0 ||
        src_coordinates.col >= width || dst_coordinates.row < 0 || dst_coordinates.row >= height ||
        dst_coordinates.col < 0 || dst_coordinates.col >= width) {
        throw IllegalCell();
    }
    if (!board.at (src_coordinates.row).at (src_coordinates.col)) {
        throw CellEmpty();  // TODO לבדןק לא null
    }
    board.at (dst_coordinates.row).at (dst_coordinates.col)->attack (board, src_coordinates, dst_coordinates);
}

void Game::reload (const GridPoint &coordinates) {
    if (coordinates.row < 0 || coordinates.row >= height || coordinates.col < 0 || coordinates.col >= width) {
        throw IllegalCell();
    }
    if (!board.at (coordinates.row).at (coordinates.col)) {
        throw CellEmpty();  // TODO לבדןק שישי null
    }
    board.at(coordinates.row).at(coordinates.col)->relode();
}



