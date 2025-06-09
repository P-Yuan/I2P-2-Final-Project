#ifndef GrandmaEnemy_HPP
#define GrandmaEnemy_HPP
#include "Enemy.hpp"

class GrandmaEnemy : public Enemy {
public:
    GrandmaEnemy(int x, int y);
    void CreateBullet() override;
};
#endif   // ATTACKENEMY_HPP
