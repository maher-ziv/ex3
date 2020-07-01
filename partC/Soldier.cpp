#include "Soldier.h"

using namespace mtm;
using std::shared_ptr;
using std::vector;

std::shared_ptr<Character> Soldier::clone() const {
    return std::shared_ptr<Character> (new Soldier (*this));
}

void Soldier::attack (std::vector<std::vector<std::shared_ptr<Character>>>& board, const GridPoint& src_coordinates,
                      const GridPoint& dst_coordinates) {

    if ((src_coordinates.row != dst_coordinates.row && src_coordinates.col != dst_coordinates.col) ||
        GridPoint::distance (src_coordinates, dst_coordinates) > range) {
        throw OutOfRange();
    }

    if (ammo == 0) {
        throw OutOfAmmo();
    }

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board.at (i).size(); ++j) {
            if (board.at (i).at (j) != nullptr) {
                GridPoint square (i, j);
                if ((GridPoint::distance (square, dst_coordinates) <= ceil (double(range)/ 3)) &&
                    board.at (i).at (j)->team != team) {
                    int damage = (i == dst_coordinates.row && j == dst_coordinates.col) ? power : ceil (double(power)/ 2);
                    if (board.at (i).at (j)->health_add (-damage) == DEAD) {
                        board.at (i).at (j).reset();
                    }
                }
            }
        }
    }
    ammo--;
}
