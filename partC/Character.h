#ifndef HW3_CHARACTER_H
#define HW3_CHARACTER_H

#include <math.h>

#include <iostream>
#include <memory>
#include <vector>

#include "Auxiliaries.h"
#include "Exceptions.h"
using mtm::GridPoint;

namespace mtm {
    class Character {

        private:
        protected:
        int range, power, health, ammo;
        enum Condition { DEAD, ALIVE };

        public:
        const Team team;
        Character() = delete;
        Character (int health, int ammo, int range, int power, Team team);
        virtual ~Character() {}
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual void move (const GridPoint& src_coordinates, const GridPoint& dst_coordinates) = 0;
        virtual void attack (std::vector<std::vector<std::shared_ptr<Character>>>& board, const GridPoint& src_coordinates,
                             const GridPoint& dst_coordinates) = 0;
        virtual void relode() = 0;
        virtual int max_steps() = 0;
        virtual Condition health_add (int points);
        virtual char letter() = 0; 

    };

}  // namespace mtm

#endif  // HW3_CHARACTER_H
