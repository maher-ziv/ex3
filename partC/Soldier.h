#ifndef HW3_SOLDIER_H
#define HW3_SOLDIER_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <memory>

using mtm::Character;
using mtm::GridPoint;
namespace mtm {
    class Soldier : public Character {

       public:
        Soldier() = delete;
        Soldier (int health, int ammo, int range, int power, Team team)
            : Character (health, ammo, range, power, team) {}
        Soldier (const Soldier& soldier);
        ~Soldier() override {}
        std::shared_ptr<Character> clone() const override;
        void move();
        void attack();
        void relode();
    };
}  // namespace mtm

#endif  // HW3_SOLDIER_H
