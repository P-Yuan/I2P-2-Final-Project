#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AttackEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"


AttackEnemy::AttackEnemy(int x, int y) : Enemy("play/enemy-6.png", x, y, 10, 60,50, 1000) {
}

void AttackEnemy::CreateBullet() {
    
}