#ifndef HW3_MEDIC_H
#define HW3_MEDIC_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <memory>

using mtm::Character;
using mtm::GridPoint;
const int MAX_STEPS = 5;
const int BULLETS = 5;
namespace mtm {
    class Medic : public Character {

        public:
        Medic() = delete;
        Medic (int health, int ammo, int range, int power, Team team) : Character (health, ammo, range, power, team) {}
        Medic (const Medic& medic);
        ~Medic() override {}
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
            return team == CPP ? 'M' : 'm';
        }
    };
}  // namespace mtm

#endif  // HW3_MEDIC_H
