#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "CarEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"

CarEnemy::CarEnemy(int x, int y,int type) : Enemy("play/small_car.png", x, y, 50, 150, 50, 800,type) {
}

void CarEnemy::CreateBullet() 
{
    
}