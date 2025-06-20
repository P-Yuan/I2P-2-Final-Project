#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "Bullet/Bullet.hpp"
#include "Enemy.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Collider.hpp"
#include "Scene/PlayScene.hpp"
//#include "Turret/Turret.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/ExplosionEffect.hpp"

PlayScene *Enemy::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
    getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
    for (int i = 0; i < 10; i++) {
        // Random add 10 dirty effects.
        getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
    }
}


Enemy::Enemy(std::string img, float x, float y, float radius, float speed, float damage, int money, int type) :
    Sprite(img, x, y),
    speed(speed),
    damage(damage),
    money(money),
    type(type){
    CollisionRadius = radius;
    reachEndTime = 10;

}
void Enemy::Hit() {
    OnExplode();
    // Remove all turret's reference to target.
    // for (auto &it : lockedTurrets)
    //     it->Target = nullptr;
    // for (auto &it : lockedBullets)
    //     it->Target = nullptr;
    getPlayScene()->EarnMoney(money);
    getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
    AudioHelper::PlayAudio("explosion.wav");
}
void Enemy::FireHit()
{
    OnExplode();
    // for (auto &it : lockedTurrets)
    //         it->Target = nullptr;
    //     for (auto &it : lockedBullets)
    //         it->Target = nullptr;
    getPlayScene()->EarnMoney(money);
    getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
    AudioHelper::PlayAudio("explosion.wav");
}
void Enemy::UpdatePath(const std::vector<std::vector<int>> &mapDistance) {
    int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
    if (x < 0) x = 0;
    if (x >= PlayScene::MapWidth) x = PlayScene::MapWidth - 1;
    if (y < 0) y = 0;
    if (y >= PlayScene::MapHeight) y = PlayScene::MapHeight - 1;
    Engine::Point pos(x, y);
    int num = mapDistance[y][x];
    if (num == -1) {
        num = 0;
        Engine::LOG(Engine::ERROR) << "Enemy path finding error";
    }
    path = std::vector<Engine::Point>(num + 1);
    while (num != 0) {
        std::vector<Engine::Point> nextHops;
        for (auto &dir : PlayScene::directions) {
            int x = pos.x + dir.x;
            int y = pos.y + dir.y;
            if (x < 0 || x >= PlayScene::MapWidth || y < 0 || y >= PlayScene::MapHeight || mapDistance[y][x] != num - 1)
                continue;
            nextHops.emplace_back(x, y);
        }
        // Choose arbitrary one.
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, nextHops.size() - 1);
        pos = nextHops[dist(rng)];
        path[num] = pos;
        num--;
    }
    path[0] = PlayScene::EndGridPoint;
}
void Enemy::Update(float deltaTime) {
    // Pre-calculate the velocity.
    // float remainSpeed = speed * deltaTime;
    // while (remainSpeed != 0) {
    //     if (path.empty()) {
    //         // Reach end point.
    //         Hit(hp);
    //         getPlayScene()->Hit(1);
    //         reachEndTime = 0;
    //         return;
    //     }
    //     Engine::Point target = path.back() * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
    //     Engine::Point vec = target - Position;
    //     // Add up the distances:
    //     // 1. to path.back()
    //     // 2. path.back() to border
    //     // 3. All intermediate block size
    //     // 4. to end point
    //     reachEndTime = (vec.Magnitude() + (path.size() - 1) * PlayScene::BlockSize - remainSpeed) / speed;
    //     Engine::Point normalized = vec.Normalize();
    //     if (remainSpeed - vec.Magnitude() > 0) {
    //         Position = target;
    //         path.pop_back();
    //         remainSpeed -= vec.Magnitude();
    //     } else {
    //         Velocity = normalized * remainSpeed / deltaTime;
    //         remainSpeed = 0;
    //     }
    // }
    // Rotation = atan2(Velocity.y, Velocity.x);
    if(type!=7 && !((type==1 || type==2) && (getPlayScene()->DyingAnimation || getPlayScene()->WinningAnimation))) Position.x-=speed*0.1;
    Sprite::Update(deltaTime);

    PlayScene *scene = getPlayScene();
    Engine:: Point max;
    Engine:: Point min;
    Engine:: Point Emax;
    Engine:: Point Emin;
    min.x=Position.x-(this->GetBitmapWidth()/3);
    min.y=Position.y-(this->GetBitmapHeight()/3);
    max.x=Position.x+(this->GetBitmapWidth()/3);
    max.y=Position.y+(this->GetBitmapHeight()/3);

    for (auto &it : scene->EnemyGroup->GetObjects()) {
        Enemy *enemy = dynamic_cast<Enemy *>(it);
        Emin.x=enemy->Position.x-(enemy->GetBitmapWidth()/3);
        Emin.y=enemy->Position.y-(enemy->GetBitmapHeight()/3);
        Emax.x=enemy->Position.x+(enemy->GetBitmapWidth()/3);
        Emax.y=enemy->Position.y+(enemy->GetBitmapHeight()/3);
        if (this->type==8 || !enemy->Visible || enemy==this || enemy->type!=6||(enemy->type==6 && this->type==1))
        {
            continue;
        }
        if (Engine::Collider::IsRectOverlap(min, max, Emin, Emax)) 
        {
            Hit();
            //getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            return;
        }
    }
    if (max.x<0){
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
    }
}
void Enemy::Draw() const {
    Sprite::Draw();
    if (PlayScene::DebugMode) {
        // Draw collision radius.
        //al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
        al_draw_rectangle(Position.x-(this->GetBitmapWidth()/3),Position.y-(this->GetBitmapHeight()/3),
                          Position.x+(this->GetBitmapWidth()/3),Position.y+(this->GetBitmapHeight()/3)
                          , al_map_rgb(255, 0, 0), 2);
    }
}


int Enemy::getdamage()
{
    return damage;
}
