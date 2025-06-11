#ifndef CarEnemy_HPP
#define CarEnemy_HPP
#include "Enemy.hpp"

class CarEnemy : public Enemy {
public:
    CarEnemy(int x, int y,int type);
    void CreateBullet() override;
};
#endif   // CarEnemy_HPP
