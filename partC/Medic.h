#ifndef HW3_MEDIC_H
#define HW3_MEDIC_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <memory>

using mtm::Character;
using mtm::GridPoint;



namespace mtm {
    class Medic : public Character {
        private:
        static const int MAX_STEPS = 5;
        static const int BULLETS = 5;
        public:
        Medic() = delete;
        Medic (int health, int ammo, int range, int power, Team team) : Character (health, ammo, range, power, team) {}
        Medic (const Medic& medic) = default;
        ~Medic() override {}
        std::shared_ptr<Character> clone() const override;
        void attack (std::vector<std::vector<std::shared_ptr<Character>>>& board, const GridPoint& src_coordinates,
                             const GridPoint& dst_coordinates) override;
        void relode() override{ammo+=BULLETS;}
        int max_steps() override{return MAX_STEPS;}
        char letter() override {return 'M';}
    };
}  // namespace mtm

#endif  // HW3_MEDIC_H
