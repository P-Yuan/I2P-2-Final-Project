#ifndef TANKBULLET_HPP
#define TANKBULLET_HPP
#include <string>

#include "Engine/Sprite.hpp"

class TankEnemy;
class PlayScene;
class TankBullet;
class Plane;
namespace Engine {
    struct Point;
}   // namespace Engine

class TankBullet : public Engine::Sprite {
protected:
    float speed;
    float damage;
    TankEnemy *parent;
    Engine::Point Velocity;
    PlayScene* getPlayScene();

public:
    Plane *Target = nullptr;
    explicit TankBullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, TankEnemy *parent);
    void Update(float deltaTime) override;
    void OnExplode(Plane *plane);
};
#endif   // TANKBULLET_HPP

