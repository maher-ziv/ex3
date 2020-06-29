#ifndef HW3_SNIPER_H
#define HW3_SNIPER_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <memory>

using mtm::Character;
using mtm::GridPoint;
namespace mtm {
    class Sniper : public Character {
       public:
        Sniper() = delete;
        Sniper (int health, int ammo, int range, int power, Team team)
            : Character (health, ammo, range, power, team) {}
        Sniper (const Sniper& sniper);
        ~Sniper() override {}
        std::shared_ptr<Character> clone() const override;
        void move();
        void attack();
        void relode();
    };
}  // namespace mtm

#endif  // HW3_SNIPER_H
