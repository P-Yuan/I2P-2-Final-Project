#ifndef TreeEnemy_HPP
#define TreeEnemy_HPP
#include "Enemy.hpp"

class TreeEnemy : public Enemy {
public:
    TreeEnemy(int x, int y,int type);
    void CreateBullet() override;
};
#endif   // CarEnemy_HPP
