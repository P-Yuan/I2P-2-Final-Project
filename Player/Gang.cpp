#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <allegro5/allegro.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "Bullet/Bullet.hpp"
#include "Enemy/Enemy.hpp"
#include "Gang.hpp"
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

PlayScene *Gang::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}


Gang::Gang(std::string img, float x, float y, float radius, float speed):Player(img, x, y, radius, speed, 0, 0){
    CollisionRadius = radius;

    nochase=false;

    chasing=1;
    goback=0;

    timeSpan=0.5;
    AttackTicks=0.3;

    walk_bmps.clear();
    hit_bmps.clear();
    for (int i = 1; i <= 4; i++) {
        walk_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/gang_walk" + std::to_string(i) + ".png"));
    }
    for (int i = 1; i <= 3; i++) {
        hit_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/gang_attack" + std::to_string(i) + ".png"));
    }
    Engine::LOG(Engine::INFO)<<"spawn gang at"<<x<<","<<y;
}


void Gang::Update(float deltaTime){
    //Sprite::Update(deltaTime);
    //Engine::LOG(Engine::INFO)<<"update player ";
    if(MoveTicks>0){
        Position.y+=16*move_dir;
        MoveTicks-=0.005;
    }

    if(gochase>0 && !nochase){
        //Engine::LOG(Engine::INFO)<<"Gang go chase";
        Position.x+=0.5;
        gochase-=deltaTime;
        if(gochase<=0){
            gochase=0;
        }
    }
    else if(goback>0){
        //Engine::LOG(Engine::INFO)<<"Gang go back";
        Position.x-=0.5;
        if(Position.x<-15){
            goback=0;
            Position.x=-15;
            Engine::LOG(Engine::INFO)<<"Gang pos.x="<<Position.x;
        }
    }

    if(chasing>0 && cooldown<=0 && !goback){
        PlayScene *scene = getPlayScene();
        Engine:: Point max;
        Engine:: Point min;
        Engine:: Point Emax;
        Engine:: Point Emin;
        min.x=Position.x-(this->GetBitmapWidth()/3);
        min.y=Position.y-(this->GetBitmapHeight()/3);
        max.x=Position.x+(this->GetBitmapWidth()/3);
        max.y=Position.y+(this->GetBitmapHeight()/3);
        Player *player = dynamic_cast<Player *>(getPlayScene()->PlayerGroup->GetObjects().back());
        Emin.x=player->Position.x-(player->GetBitmapWidth()/3);
        Emin.y=player->Position.y-(player->GetBitmapHeight()/3);
        Emax.x=player->Position.x+(player->GetBitmapWidth()/2);
        Emax.y=player->Position.y+(player->GetBitmapHeight()/3);
        if (Engine::Collider::IsRectOverlap(min, max, Emin, Emax)) {
            player->Hit(1000);
            scene->GangHit=true;
            return;
        }
        chasing-=deltaTime;
        if(chasing<=0){
            chasing=0;
            goback=4;
        }
    }
    else{
        cooldown-=deltaTime;
    }
    Walking(deltaTime);
}

void Gang::Draw() const {
    Sprite::Draw();
    
    if (PlayScene::DebugMode) {
        // Draw collision radius.
        //al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
        al_draw_rectangle(Position.x-(this->GetBitmapWidth()/3),Position.y-(this->GetBitmapHeight()/3),
                          Position.x+(this->GetBitmapWidth()/3),Position.y+(this->GetBitmapHeight()/3)
                          , al_map_rgb(255, 0, 0), 2);
    }
}

void Gang::Walking(float deltaTime) {
    if(goback) timeSpan=0.7;
    else if(gochase) timeSpan=0.3;
    else timeSpan=0.5;
    timeTicks+=deltaTime;
    if(timeTicks>=timeSpan) timeTicks-=timeSpan;
    int phase = floor(timeTicks / timeSpan * walk_bmps.size());
    //Engine::LOG(Engine::INFO)<<"Find walking phase:"<<phase;
    bmp = walk_bmps[phase];
    Sprite::Update(deltaTime);
}

void Gang::Dying(float deltaTime) {
    Engine::LOG(Engine::INFO)<<"Gang hit";
    AttackTicks-=deltaTime;
    if(AttackTicks<=0){
        //Engine::LOG(Engine::INFO)<<"End hit";
        return;
    }
    int phase = floor((AttackSpan*3 - AttackTicks) / AttackSpan);
    Engine::LOG(Engine::INFO)<<"Find attack phase:"<<phase;
    bmp = hit_bmps[phase];
    Sprite::Update(deltaTime);
}
