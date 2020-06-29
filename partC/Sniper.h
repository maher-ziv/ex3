#ifndef HW3_SNIPER_H
#define HW3_SNIPER_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <memory>

using mtm::GridPoint;
using mtm::Character;
namespace mtm {
    class Sniper : public Character {
       public:
        Sniper (int health, int ammo, int range, int power, GridPoint coordinate)
            : Character (health, ammo, range, power, coordinate) {}
        ~Sniper() override {}
        Character* clone() const override;
        void move();
        void attack();
        void relode();
    };
}  // namespace mtm

#endif  // HW3_SNIPER_H
