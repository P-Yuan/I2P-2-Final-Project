#ifndef ATTACKENEMY_HPP
#define ATTACKENEMY_HPP
#include "Enemy.hpp"

class AttackEnemy : public Enemy {
public:
    AttackEnemy(int x, int y);
    void CreateBullet() override;
};
#endif   // ATTACKENEMY_HPP
