#include <allegro5/base.h>
#include <cmath>
#include <random>
#include <string>
#include <iostream>

#include "Engine/Point.hpp"
#include "Engine/AudioHelper.hpp"
#include "GangEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Scene/PlayScene.hpp"
//#include "Bullet/TankBullet.hpp"

PlayScene *TankEnemy::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
TankEnemy::TankEnemy(int x, int y,float c,int type)
    : Enemy("play/bikeman.png", x, y, 50, 80, 30, 500,type),
      head("play/enemy-3-head.png", x, y), targetRotation(0),
      coolDown(c) {
}
void TankEnemy::Draw() const {
    Enemy::Draw();
    //head.Draw();
}
void TankEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    head.Position = Position;
    PlayScene *scene = getPlayScene();
    // Choose arbitrary one
    if (!Target) 
    {
        for (auto &it : scene->PlaneGroup->GetObjects()) 
        {
            Target = dynamic_cast<Plane *>(it);
            break;
        }
        if(!Target)
        {
             std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_real_distribution<> dist(0.0f, 4.0f);
            float rnd = dist(rng);
            if (rnd < deltaTime) {
                // Head arbitrary rotation.
                std::uniform_real_distribution<> distRadian(-ALLEGRO_PI, ALLEGRO_PI);
                targetRotation = distRadian(rng);
            }
            head.Rotation = (head.Rotation + deltaTime * targetRotation) / (1 + deltaTime);
        }
    }
    if(Target)
    {
        Engine::Point direction = Target->Position - Position;
        targetRotation=atan2(direction.y, direction.x);    
        head.Rotation = targetRotation;
        reload -= deltaTime;
        if (reload <= 0) {
            // shoot.
            reload = coolDown;

            CreateBullet();
        }
    }
}
void TankEnemy::CreateBullet() {
    
    // Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    // float rotation = atan2(diff.y, diff.x);
    // Engine::Point normalized = diff.Normalize();

    Engine::Point dir = Target->Position - this->Position;
    dir.x += 100;
    Engine::Point forwardDir = dir.Normalize();
    float rotation = atan2(forwardDir.y, forwardDir.x) + ALLEGRO_PI / 2;
    // Change bullet position to the front of the gun barrel.
    //getPlayScene()->BulletGroup->AddNewObject(new TankBullet("play/bullet-4.png", 500, 5, Position , forwardDir, rotation,this));
    AudioHelper::PlayAudio("gun.wav");
}
