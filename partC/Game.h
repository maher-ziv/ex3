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
#include <string>
#include<cctype>
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
        void isIllegalCell (const GridPoint &coordinates) const;
        
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
        bool isOver(Team* winningTeam = NULL) const;

        friend std::ostream& operator<< (std::ostream& os, const Game& game) {
            std::string delimiter = std::string (2 * game.width + 1, '*');
            os << delimiter << std::endl;
            for (vector<shared_ptr<Character>> i : game.board) {
                for (shared_ptr<Character> j : i) {
                    if (j != nullptr) {
                        os << "|" << (j->letter());
                    } else {
                        os << "|" << (' ');
                    }
                }
                os << "|" << std::endl;
            }
            os << delimiter;
            return os;
        }
    };

    // std::ostream& operator<<(std::ostream& os, const Game& game) {
    //     std::string delimiter = std::string(2 * game.width + 1, '*');
	// 	os << delimiter << std::endl;
    //     for (vector<shared_ptr<Character>> i : game.board) {
    //         for (shared_ptr<Character> j : i) {
    //             if (j != nullptr) {
    //                 os << "|" << (j->letter());
    //             }else { 
    //                 os << "|" << (' ');
    //             }
    //         }
    //         os << "|" << std::endl;
    //     }
    //     os << delimiter;
    //     return os;
    // }

    
/*

http://www.cplusplus.com/reference/cctype/tolower/


function
<cctype>
tolower

int tolower ( int c );

Convert uppercase letter to lowercase
Converts c to its lowercase equivalent if c is an uppercase letter and has a lowercase equivalent. If no such conversion is possible, the value returned is c unchanged.

Notice that what is considered a letter may depend on the locale being used; In the default "C" locale, an uppercase letter is any of: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z, which translate respectively to: a b c d e f g h i j k l m n o p q r s t u v w x y z.

In other locales, if an uppercase character has more than one correspondent lowercase character, this function always returns the same character for the same value of c.

In C++, a locale-specific template version of this function (tolower) exists in header <locale>.
*/


}  // namespace mtm

#endif  // HW3_GAME_H

