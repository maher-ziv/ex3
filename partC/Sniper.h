#ifndef HW3_SNIPER_H
#define HW3_SNIPER_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <memory>

using mtm::Character;
using mtm::GridPoint;
const int MAX_STEPS = 4;
const int BULLETS = 2;

namespace mtm {
    class Sniper : public Character {
        private:
        int attack_counter;

        public:
        Sniper() = delete;
        Sniper (int health, int ammo, int range, int power, Team team)
            : Character (health, ammo, range, power, team), attack_counter (0) {}
        Sniper (const Sniper& sniper);
        ~Sniper() override {}
        std::shared_ptr<Character> clone() const override;
        void move (const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;
        void attack (vector<vector<shared_ptr<Character>>>& board, const GridPoint& src_coordinates,
                     const GridPoint& dst_coordinates) override;
        void relode() override {
            ammo += BULLETS;
        }
        int max_steps() override {
            return MAX_STEPS;
        }
        char letter() override {
            return team == CPP ? 'N' : 'n';
        }
    };
}  // namespace mtm

#endif  // HW3_SNIPER_H
