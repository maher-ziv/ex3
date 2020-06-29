#include "Medic.h"

using mtm::Medic;

std::shared_ptr<Character> Medic::clone() const {
    return std::shared_ptr<Character>(new Medic(*this));
}
