#ifndef HW3_MEDIC_H
#define HW3_MEDIC_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <memory>

using mtm::GridPoint;
using mtm::Character;
namespace mtm {
    class Medic : public Character {
       public:
        Medic (int health, int ammo, int range, int power, GridPoint coordinate)
            : Character (health, ammo, range, power, coordinate) {}
        ~Medic() override  {}
        Character* clone() const override;
        void move();
        void attack();
        void relode();
    };
}  // namespace mtm

#endif  // HW3_MEDIC_H
