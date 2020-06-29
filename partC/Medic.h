#ifndef HW3_MEDIC_H
#define HW3_MEDIC_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <memory>

using mtm::Character;
using mtm::GridPoint;
namespace mtm {
    class Medic : public Character {
       public:
        Medic() = delete;
        Medic (int health, int ammo, int range, int power, Team team)
            : Character (health, ammo, range, power, team) {}
        Medic (const Medic& medic);
        ~Medic() override {}
       std::shared_ptr<Character> clone() const override;
        void move();
        void attack();
        void relode();
    };
}  // namespace mtm

#endif  // HW3_MEDIC_H
