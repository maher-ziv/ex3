#ifndef HW3_GAME_H
#define HW3_GAME_H

#include <Auxiliaries.h>
#include <Character.h>
#include <Exceptions.h>

#include <iostream>
#include <memory>
#include <vector>

using mtm::Character;
using mtm::GridPoint;
using std::shared_ptr;
using std::vector;

namespace mtm {
    class Game {
       private:
        typedef shared_ptr<Character> pCharacter;
        vector<vector<pCharacter>> board;
        int height, width;

       public:
        Game() = delete;
        Game (int height, int width);
        ~Game() = default;
        Game (const Game& other);
        Game& operator= (const Game& other);
        void addCharacter (const GridPoint& coordinates, shared_ptr<Character> character);
        void move (const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        static std::shared_ptr<Character> makeCharacter (CharacterType type, Team team, units_t health, units_t ammo,
                                                         units_t range, units_t power);
    };

}  // namespace mtm

#endif  // HW3_GAME_H
