#ifndef HW3_SOLDIER_H
#define HW3_SOLDIER_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <memory>

using mtm::GridPoint;
using mtm::Character;
namespace mtm {
    class Soldier : public Character {
       public:
        Soldier (int health, int ammo, int range, int power, GridPoint coordinate)
            : Character (health, ammo, range, power, coordinate) {}
        ~Soldier() override {}
        Character* clone() const override;
        void move();
        void attack();
        void relode();
    };
}  // namespace mtm

#endif  // HW3_SOLDIER_H
