#ifndef HW3_SNIPER_H
#define HW3_SNIPER_H

#include "Character.h"


namespace mtm {
    class Sniper : public Character {
        private:
        static const int MAX_STEPS = 4;
        static const int BULLETS = 2;
        //counter to double the damage of his third attack
        int attack_counter; 
        public:
        Sniper() = delete;
        Sniper (int health, int ammo, int range, int power, Team team)
            : Character (health, ammo, range, power, team), attack_counter (0) {}
        Sniper (const Sniper& sniper) = default;
        ~Sniper() override {}
        std::shared_ptr<Character> clone() const override;
        void attack (std::vector<std::vector<std::shared_ptr<Character>>>& board, const GridPoint& src_coordinates,
                             const GridPoint& dst_coordinates) override;
        void relode() override{ammo+=BULLETS;}
        int max_steps() override{return MAX_STEPS;}                  
        char letter() override;
    };
}  // namespace mtm

#endif  // HW3_SNIPER_H
