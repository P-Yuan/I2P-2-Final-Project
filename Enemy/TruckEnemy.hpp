#ifndef TruckEnemy_HPP
#define TruckEnemy_HPP
#include "Enemy.hpp"

class TruckEnemy : public Enemy {
public:
    TruckEnemy(int x, int y,int type);
    void CreateBullet() override;
};
#endif   // CarEnemy_HPP
