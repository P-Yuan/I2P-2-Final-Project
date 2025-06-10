#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <allegro5/allegro.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "Bullet/Bullet.hpp"
#include "Enemy/Enemy.hpp"
#include "coin.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Allegro5Exception.hpp"
#include "Scene/PlayScene.hpp"
#include "Turret/Turret.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/ExplosionEffect.hpp"
#include "Engine/Resources.hpp"
#include "Engine/LOG.hpp"

PlayScene *coin::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void coin::OnExplode() {
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


coin::coin(std::string img, float x, float y, float radius, float speed, float hp, int money) :
    Sprite(img, x, y),
    hp(hp),
    money(money) {
    CollisionRadius = radius;
    cooldown=0;
    timeTicks=0;
    for (int i = 1; i <= 6; i++) {
        bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/player_walk" + std::to_string(i) + ".png"));
    }
    Engine::LOG(Engine::INFO)<<"bmps size:"<<bmps.size();
}
void coin::Hit(float damage) {
    hp -= damage;
    getPlayScene()->Hit(damage);
}

void coin::Update(float deltaTime){
    //Sprite::Update(deltaTime);
    rotate(deltaTime);
    if(cooldown<=0){
        PlayScene *scene = getPlayScene();
        for (auto &it : scene->EnemyGroup->GetObjects()) {
            Enemy *enemy = dynamic_cast<Enemy *>(it);
            if (!enemy->Visible)
                continue;
            if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
                OnExplode();
                //enemy->Hit(damage);
                //getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
                Hit(1);
                cooldown=2;
                return;
            }
        }
    }
    else{
        cooldown-=deltaTime;
    }
}

void coin::Draw() const {
    Sprite::Draw();
    if (PlayScene::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
    }
}

void coin::rotate(float deltaTime) {
    timeTicks+=deltaTime;
    if(timeTicks>=timeSpan) timeTicks-=timeSpan;
    int phase = floor(timeTicks / timeSpan * bmps.size());
    //Engine::LOG(Engine::INFO)<<"Find walking phase:"<<phase;
    bmp = bmps[phase];
    Sprite::Update(deltaTime);
}