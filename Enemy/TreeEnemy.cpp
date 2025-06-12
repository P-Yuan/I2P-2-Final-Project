#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "TreeEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"

TreeEnemy::TreeEnemy(int x, int y,int type) : Enemy("play/tree.png", x, y, 50, 20, 10, 800,type) {
}

void TreeEnemy::CreateBullet() {
    
}