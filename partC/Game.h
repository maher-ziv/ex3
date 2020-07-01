#ifndef HW3_GAME_H
#define HW3_GAME_H

#include "Auxiliaries.h"
#include "Character.h"
#include "Exceptions.h"
#include "Medic.h"
#include "Sniper.h"
#include "Soldier.h"

#include <iostream>
#include <memory>
#include <vector>
using mtm::Character;
using mtm::GridPoint;
using std::array;
using std::shared_ptr;
using std::vector;

namespace mtm {
    class Game {
        private:
        using pCharacter = shared_ptr<Character>;
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
        void attack (const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void reload (const GridPoint& coordinates);
        friend std::ostream& operator<< (std::ostream& os, const Game& game);
        bool isOver(Team* winningTeam = NULL) const;
    };

    std::ostream& operator<<(std::ostream& os, const Game& game) {
        std::string delimiter = std::string(2 * game.width + 1, '*');
		os << delimiter << std::endl;
        for (vector<shared_ptr<Character>> i : game.board) {
            for (shared_ptr<Character> j : i) {
                if (j != nullptr) {
                    os << "|" << (j->letter());
                }else { 
                    os << "|" << (' ');
                }
            }
            os << "|" << std::endl;
        }
        os << delimiter;
        return os;
    }

}  // namespace mtm

#endif  // HW3_GAME_H

