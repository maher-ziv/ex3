#include "Medic.h"

using namespace mtm;
using std::shared_ptr;
using std::vector;

std::shared_ptr<Character> Medic::clone() const {
    return std::shared_ptr<Character> (new Medic (*this)); 
}

void Medic::attack (vector<vector<shared_ptr<Character>>>& board, const GridPoint& src_coordinates,
                    const GridPoint& dst_coordinates) {

    if (GridPoint::distance (src_coordinates, dst_coordinates) > range) {
        throw OutOfRange();
    }
    if (!board.at (dst_coordinates.row).at (dst_coordinates.col)) {
        throw CellEmpty();  // TODO לבדןק לא null
    }

    if (GridPoint::distance (src_coordinates, dst_coordinates) == 0) {
        throw IllegalTarget();
    }

    if (board.at (dst_coordinates.row).at (dst_coordinates.col)->team == team) {

        board.at (dst_coordinates.row).at (dst_coordinates.col)->health_add(power);
    } 
    else {
        if (ammo == 0) {
            throw OutOfAmmo();
        }
         board.at (dst_coordinates.row).at (dst_coordinates.col)->health_add(-power);
         ammo--;
    }
 
}

