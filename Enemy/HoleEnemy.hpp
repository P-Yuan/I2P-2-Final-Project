#ifndef HoleEnemy_HPP
#define HoleEnemy_HPP
#include "Enemy.hpp"

class HoleEnemy : public Enemy {
public:
    HoleEnemy(int x, int y,int type);
    void CreateBullet() override;
};
#endif   // HoleEnemy_HPP
