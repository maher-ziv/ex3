#ifndef HW3_GAME_H
#define HW3_GAME_H

#include "Auxiliaries.h"
#include "Character.h"
#include "Exceptions.h"
#include "Medic.h"
#include "Sniper.h"
#include "Soldier.h"

using std::shared_ptr;
using std::vector;

namespace mtm {

    class Game {
       private:
        using pCharacter = shared_ptr<Character>;
        // 2D vectors game board
        int height, width;
        vector<vector<pCharacter>> board;
        // checks if a cell isn't in the board range
        void isIllegalCell (const GridPoint& coordinates) const;

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
        void attack (const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void reload (const GridPoint& coordinates);
        bool isOver (Team* winningTeam = NULL) const;
        // a friend function to print the board
        friend std::ostream& operator<< (std::ostream& os, const Game& game);
        };


}  // namespace mtm

#endif  // HW3_GAME_H
