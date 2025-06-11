#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <allegro5/allegro.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "Bullet/Bullet.hpp"
#include "Enemy/Enemy.hpp"
#include "Player.hpp"
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

PlayScene *Player::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Player::OnExplode() {
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


Player::Player(std::string img, float x, float y, float radius, float speed, float hp, int money) :
    Sprite(img, x, y),
    hp(hp),
    money(money) {
    CollisionRadius = radius;
    
    cooldown=0;
    timeTicks=0;
    HitTicks=0;
    MoveTicks=0;
    DyingTicks=0.4;
    WinningTicks=0.8;

    walk_bmps.clear();
    hit_bmps.clear();
    win_bmps.clear();
    for (int i = 1; i <= 6; i++) {
        walk_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/player_walk" + std::to_string(i) + ".png"));
    }
    for (int i = 1; i <= 4; i++) {
        hit_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/player_hit" + std::to_string(i) + ".png"));
    }
    hit_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/player_hit4.png"));
    hit_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/player_hit4.png"));
    for (int i = 1; i <= 8; i++) {
        win_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/player_jump" + std::to_string(i%4 +1) + ".png"));
    }
    Engine::LOG(Engine::INFO)<<"spawn player at"<<x<<","<<y;
}
void Player::Hit(float damage) {
    getPlayScene()->Hit(damage);
}

void Player::Update(float deltaTime){
    //Sprite::Update(deltaTime);
    //Engine::LOG(Engine::INFO)<<"update player ";
    if(HitTicks>0){
        Hitting(deltaTime);
    }
    else{
        Walking(deltaTime);
    }
    if(MoveTicks>0){
        Position.y+=32*move_dir;
        MoveTicks-=0.01;
    }

    if(cooldown<=0){
        //Walking(deltaTime);
        PlayScene *scene = getPlayScene();
        for (auto &it : scene->EnemyGroup->GetObjects()) {
            Enemy *enemy = dynamic_cast<Enemy *>(it);
            if (!enemy->Visible)
                continue;
            if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
                //OnExplode();
                //enemy->Hit(damage);
                //getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
                HitTicks=0.6;
                Hit(enemy->getdamage());
                cooldown=1.5;
                return;
            }
        }
    }
    else{
        cooldown-=deltaTime;
    }
}

void Player::Draw() const {
    if(cooldown>0 && HitTicks<=0){
        al_draw_tinted_scaled_rotated_bitmap(bmp.get(), al_map_rgba(0, 255, 255, 255), Anchor.x * GetBitmapWidth(), Anchor.y * GetBitmapHeight(),
                                             Position.x, Position.y, Size.x / GetBitmapWidth(), Size.y / GetBitmapHeight(), Rotation, 0);
    }
    else if(DyingTicks<0.4f){
        al_draw_tinted_scaled_rotated_bitmap(bmp.get(), al_map_rgba(255, 0, 0, 255), Anchor.x * GetBitmapWidth(), Anchor.y * GetBitmapHeight(),
                                             Position.x, Position.y, Size.x / GetBitmapWidth(), Size.y / GetBitmapHeight(), Rotation, 0);
    }
    else{
        Sprite::Draw();
    }
    
    if (PlayScene::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
    }
}

void Player::Walking(float deltaTime) {
    timeTicks+=deltaTime;
    if(timeTicks>=timeSpan) timeTicks-=timeSpan;
    int phase = floor(timeTicks / timeSpan * walk_bmps.size());
    //Engine::LOG(Engine::INFO)<<"Find walking phase:"<<phase;
    bmp = walk_bmps[phase];
    Sprite::Update(deltaTime);
}

void Player::Hitting(float deltaTime) {
    HitTicks-=deltaTime;
    if(HitTicks<=0){
        //Engine::LOG(Engine::INFO)<<"End hit";
        return;
    }
    int phase = floor((HitSpan*6 - HitTicks) / HitSpan);
    //Engine::LOG(Engine::INFO)<<"Find hitting phase:"<<phase;
    bmp = hit_bmps[phase];
    Sprite::Update(deltaTime);
}

void Player::OnKeyDown(int keyCode){
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    if(cooldown<=0){
        if(keyCode==ALLEGRO_KEY_UP){
            if(Position.y >= halfH / 2 +365){
                MoveTicks=0.04;
                move_dir=UP;
                Engine::LOG(Engine::INFO)<<"player move up";
            }
        }
        else if(keyCode==ALLEGRO_KEY_DOWN){
            if(Position.y <= halfH / 2 +365){
                MoveTicks=0.04;
                move_dir=DOWN;
                Engine::LOG(Engine::INFO)<<"player move down";
            }
        }
    }
}

void Player::Dying(float deltaTime){
    DyingTicks-=deltaTime;
    if(DyingTicks<=0){
        //Engine::LOG(Engine::INFO)<<"End hit";
        return;
    }
    int phase = floor((DyingSpan*4 - DyingTicks) / DyingSpan);
    Engine::LOG(Engine::INFO)<<"Find dying phase:"<<phase;
    bmp = hit_bmps[phase];
    Sprite::Update(deltaTime);
}

void Player::Winning(float deltaTime){
    WinningTicks-=deltaTime;
    if(WinningTicks<=0){
        WinningTicks=0.8;
        return;
    }
    int phase = floor((WinningSpan*4 - WinningTicks) / WinningSpan);
    Engine::LOG(Engine::INFO)<<"Find winning phase:"<<phase;
    bmp = win_bmps[phase];
    Sprite::Update(deltaTime);
}