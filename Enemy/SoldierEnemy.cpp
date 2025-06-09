#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "SoldierEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"

// TODO HACKATHON-3 (1/3): You can imitate the 2 files: 'SoldierEnemy.hpp', 'SoldierEnemy.cpp' to create a new enemy.
SoldierEnemy::SoldierEnemy(int x, int y) : Enemy("play/enemy-1.png", x, y, 10, 30, 10, 100) {
}

void SoldierEnemy::CreateBullet() {
    
}