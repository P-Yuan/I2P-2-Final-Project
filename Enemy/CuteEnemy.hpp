#ifndef CUTEENEMY_HPP
#define CUTEENEMY_HPP
#include "Enemy.hpp"

class CuteEnemy : public Enemy {
public:
    CuteEnemy(int x, int y);
    void CreateBullet() override;
};
#endif   // CUTEENEMY_HPP
