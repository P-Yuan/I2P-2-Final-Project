#ifndef BikeEnemy_HPP
#define BikeEnemy_HPP
#include "Enemy.hpp"

class BikeEnemy : public Enemy {
public:
    BikeEnemy(int x, int y);
    void CreateBullet() override;
};
#endif   // BikeEnemy_HPP
