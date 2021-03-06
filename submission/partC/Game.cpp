#include "Game.h"

using namespace mtm;
using std::vector;

void Game::isIllegalCell (const GridPoint &coordinates) const {
    if (coordinates.row < 0 || coordinates.row >= height || coordinates.col < 0 || coordinates.col >= width) {
        throw IllegalCell();
    }
}

Game::Game (int height, int width)
    : height (height), width (width), board ((std::abs (height)), vector<pCharacter> (std::abs (width))) {
    if (height <= 0 || width <= 0) {
        throw IllegalArgument();
    }
}

Game::Game (const Game &other)
    : height (other.height), width (other.width), board (other.height, vector<pCharacter> (other.width)) {

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (other.board.at (i).at (j) != nullptr) {
                board.at (i).at (j) = other.board.at (i).at (j)->clone();
            }
        }
    }
}

Game &Game::operator= (const Game &other) {
    Game tmp (other.height, other.width);
    for (int i = 0; i < other.height; i++) {
        for (int j = 0; j < other.width; j++) {
            if (other.board.at (i).at (j) != nullptr) {
                tmp.board.at (i).at (j) = other.board.at (i).at (j)->clone();
            }
        }
    }
    board.empty();
    board = tmp.board;
    height = tmp.height;
    width = tmp.width;
    return *this;
}

shared_ptr<Character> Game::makeCharacter (CharacterType type, Team team, units_t health, units_t ammo, units_t range,
                                           units_t power) {
    if (health <= 0 || ammo < 0 || range < 0 || power < 0) {
        throw IllegalArgument();
    }
    if (type == SOLDIER) {
        return shared_ptr<Character> (new Soldier (health, ammo, range, power, team));
    }
    if (type == MEDIC) {
        return shared_ptr<Character> (new Medic (health, ammo, range, power, team));
    }
    return shared_ptr<Character> (new Sniper (health, ammo, range, power, team));
}

void Game::addCharacter (const GridPoint &coordinates, shared_ptr<Character> character) {
    isIllegalCell (coordinates);
    if (board.at (coordinates.row).at (coordinates.col)) {
        throw CellOccupied();
    }
    board.at (coordinates.row).at (coordinates.col) = character;
}

void Game::move (const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
    isIllegalCell (src_coordinates);
    isIllegalCell (dst_coordinates);

    if (!board.at (src_coordinates.row).at (src_coordinates.col)) {
        throw CellEmpty();
    }
    if (src_coordinates == dst_coordinates) {
        return;
    }

    if (board.at (src_coordinates.row).at (src_coordinates.col)->max_steps() <
        GridPoint::distance (src_coordinates, dst_coordinates)) {
        throw MoveTooFar();
    }
    if (board.at (dst_coordinates.row).at (dst_coordinates.col)) {
        throw CellOccupied();
    }

    board.at (dst_coordinates.row).at (dst_coordinates.col) = board.at (src_coordinates.row).at (src_coordinates.col);
    board.at (src_coordinates.row).at (src_coordinates.col).reset();
}

    void Game::attack (const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {

        isIllegalCell (src_coordinates);
        isIllegalCell (dst_coordinates);

        if (!board.at (src_coordinates.row).at (src_coordinates.col)) {
            throw CellEmpty();
        }
        board.at (src_coordinates.row).at (src_coordinates.col)->attack (board, src_coordinates, dst_coordinates);
    }

    void Game::reload (const GridPoint &coordinates) {

        isIllegalCell (coordinates);

        if (!board.at (coordinates.row).at (coordinates.col)) {
            throw CellEmpty();
        }
        board.at (coordinates.row).at (coordinates.col)->relode();
    }

    bool Game::isOver (Team * winningTeam) const {
        bool cpp = false, python = false;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (board.at (i).at (j)) {
                    board.at (i).at (j)->team == CPP ? cpp = true : python = true;
                    if (cpp && python)
                        return false;
                }
            }
        }
        if (!cpp && !python)
            return false;
        if (winningTeam != nullptr) {
            *winningTeam = cpp ? CPP : PYTHON;
        }
        return true;
    }

    namespace mtm {

        std::ostream &operator<< (std::ostream &os, const Game &game) {
            std::string delimiter = std::string (2 * game.width + 1, '*');
            os << delimiter << std::endl;
            for (vector<shared_ptr<Character>> i : game.board) {
                for (shared_ptr<Character> j : i) {
                    if (j != nullptr) {
                        os << "|" << (j->letter());
                    } else {
                        os << "|" << (' ');
                    }
                }
                os << "|" << std::endl;
            }
            os << delimiter;
            return os;
        }
    }  // namespace mtm
