#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "TreeEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"

TreeEnemy::TreeEnemy(int x, int y,std::string type) : Enemy("play/tree.png", x, y, 50, 30, 20, 800,type) {
}

void TreeEnemy::CreateBullet() {
    
}