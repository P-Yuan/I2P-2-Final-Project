#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "HoleEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"

HoleEnemy::HoleEnemy(int x, int y) : Enemy("play/hole.png", x, y, 50, 30, 10, 100) {
}

void HoleEnemy::CreateBullet() {
    
}