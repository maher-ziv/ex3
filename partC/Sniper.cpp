#include "Sniper.h"

using mtm::Sniper;

std::shared_ptr<Character> Sniper::clone() const {
    return std::shared_ptr<Character>(new Sniper(*this));
}
