#ifndef HW3_CHARACTER_H
#define HW3_CHARACTER_H

#include <Auxiliaries.h>

#include <iostream>
#include <memory>

using mtm::GridPoint;

namespace mtm {
    class Character {
       private:
        int health, ammo, range, power;
        GridPoint coordinate;

       public:
        Character (int health, int ammo, int range, int power, GridPoint coordinate);
            
        virtual ~Character() {}
        virtual Character* clone() const = 0;
        virtual void move() = 0 ;
        virtual void attack() = 0 ;
        virtual void relode() = 0 ;

    };

}  // namespace mtm

#endif  // HW3_CHARACTER_H
