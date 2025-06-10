#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "TruckEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"

TruckEnemy::TruckEnemy(int x, int y,std::string type) : Enemy("play/big_car.png", x, y, 50, 80, 40, 800,type) {
}

void TruckEnemy::CreateBullet() {
    
}