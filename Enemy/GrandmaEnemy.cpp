#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "GrandmaEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"


GrandmaEnemy::GrandmaEnemy(int x, int y,int type) : Enemy("play/grandma.png", x, y, 50, 50, 20, 1000,type) {
}

void GrandmaEnemy::CreateBullet() {
    
}