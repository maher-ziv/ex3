#ifndef HW3_CHARACTER_H
#define HW3_CHARACTER_H

#include <math.h>

#include <iostream>
#include <memory>
#include <vector>

#include "Auxiliaries.h"
#include "Exceptions.h"

namespace mtm {
    class Character {

       private:
       protected:
        int health, ammo, range, power;
        enum Condition { DEAD, ALIVE };

       public:
        const Team team;
        Character() = delete;
        Character (int health, int ammo, int range, int power, Team team);
        Character (const Character& character) = default;

        virtual ~Character() {}
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual void attack (std::vector<std::vector<std::shared_ptr<Character>>>& board,
                             const GridPoint& src_coordinates, const GridPoint& dst_coordinates) = 0;
        virtual void relode() = 0;
        // returns the steps range of a character
        virtual int max_steps() = 0;
        // adding damage points or healing point to the character and returns his vitals
        virtual Condition health_add (int points);
        // returns the first letter of the character type (capital or small) depending on his team
        virtual char letter() = 0;
    };

}  // namespace mtm

#endif  // HW3_CHARACTER_H
