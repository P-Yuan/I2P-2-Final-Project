#include "TankBullet.hpp"
#include "Enemy/Enemy.hpp"
#include "Enemy/GangEnemy.hpp"
#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include "Scene/PlayScene.hpp"
#include "UI/Animation/Plane.hpp"
#include "UI/Animation/DirtyEffect.hpp"

#include <random>
#include <iostream>

PlayScene *TankBullet::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void TankBullet::OnExplode(Plane *plane) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), plane->Position.x, plane->Position.y));
}

TankBullet::TankBullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, TankEnemy *parent) : Sprite(img, position.x, position.y), speed(speed), damage(damage), parent(parent) 
{

    Velocity = forwardDirection.Normalize() * speed;
    Rotation = rotation;
    CollisionRadius = 4;
}

void TankBullet::Update(float deltaTime) {
    //Sprite::Update(deltaTime);
    Position.x += Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;
       // 飛機碰撞判定
    for (auto& it : getPlayScene()->PlaneGroup->GetObjects()) {
        Plane* plane = dynamic_cast<Plane*>(it);
        if (!plane || !plane->Visible) continue;

        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, plane->Position, plane->CollisionRadius)) {
            OnExplode(plane);
            getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            return;
        }
    }

    // 飛出畫面就移除
    if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2,
        Engine::Point(0, 0), PlayScene::GetClientSize())) {
        getPlayScene()->BulletGroup->RemoveObject(objectIterator);
    }
}
