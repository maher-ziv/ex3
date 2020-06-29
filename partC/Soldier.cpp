#include "Soldier.h"

using mtm::Soldier;

std::shared_ptr<Character> Soldier::clone() const {
    return std::shared_ptr<Character> (new Soldier(*this));
}
