#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "BikeEnemy.hpp"
#include "Scene/PlayScene.hpp"
//#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"

BikeEnemy::BikeEnemy(int x, int y,int type) : Enemy("play/bikeman.png", x, y, 50, 70, 30, 800,type) {
}

void BikeEnemy::CreateBullet() {
    
}