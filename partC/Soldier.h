#ifndef HW3_SOLDIER_H
#define HW3_SOLDIER_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <memory>

using mtm::Character;
using mtm::GridPoint;

const int MAX_STEPS = 3;
const int BULLETS = 3;

namespace mtm {
    class Soldier : public Character {
        friend class Game;

        public:
        Soldier() = delete;
        Soldier (int health, int ammo, int range, int power, Team team)
            : Character (health, ammo, range, power, team) {}
        Soldier (const Soldier& soldier);
        ~Soldier() override {}
        std::shared_ptr<Character> clone() const override;
        void move (const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;
        void attack (std::vector<std::vector<std::shared_ptr<Character>>>& board, const GridPoint& src_coordinates,
                     const GridPoint& dst_coordinates) override;

        void relode() override {
            ammo += BULLETS;
        }
        int max_steps() override {
            return MAX_STEPS;
        }
        char letter() override {
            return team == CPP ? 'S' : 's';
        }
    };
}  // namespace mtm

#endif  // HW3_SOLDIER_H
