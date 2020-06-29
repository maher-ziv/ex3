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
        GridPoint coordinates;
        Team team;
        CharacterType type;
        const GridPoint OUT_OF_GAME = {-1,-1};

       public:
        Character() = delete;
        Character (int health, int ammo, int range, int power, Team team);
        virtual ~Character() {}
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual void move() = 0;
        virtual void attack() = 0;
        virtual void relode() = 0;
        void locate(const GridPoint& coor) {
            coordinates = coor;
        }
    };

}  // namespace mtm

#endif  // HW3_CHARACTER_H
