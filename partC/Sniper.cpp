#include "Sniper.h"

using namespace mtm;
using std::shared_ptr;
using std::vector;

std::shared_ptr<Character> Sniper::clone() const {
    return std::shared_ptr<Character> (new Sniper (*this));
}

void Sniper::attack (vector<vector<shared_ptr<Character>>>& board, const GridPoint& src_coordinates,
                     const GridPoint& dst_coordinates) {

    if (GridPoint::distance (src_coordinates, dst_coordinates) > range ||
        GridPoint::distance (src_coordinates, dst_coordinates) < ceil (double(range) / 2)) {
        throw OutOfRange();
    }
    if (!board.at (dst_coordinates.row).at (dst_coordinates.col)) {
        throw CellEmpty();  // TODO לבדןק לא null
    }
    if (ammo == 0) {
        throw OutOfAmmo();
    }
    if (board.at(dst_coordinates.row).at(dst_coordinates.col)->team == team) {
        throw IllegalTarget();
    }

    int damage = attack_counter == 2 ? 2 * power : power;
    if (board.at (dst_coordinates.row).at (dst_coordinates.col)->health_add (-damage) == DEAD) {
        board.at (dst_coordinates.row).at (dst_coordinates.col).reset();
    }
    ammo--;
    ++attack_counter %= 3;  // TODO test
}
