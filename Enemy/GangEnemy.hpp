#ifndef GangEnemy_HPP
#define GangEnemy_HPP
#include "Enemy.hpp"
#include "Engine/Sprite.hpp"
#include "UI/Animation/Plane.hpp"

class TankEnemy : public Enemy {
private:
    Sprite head;
    float targetRotation;
    float reload = 0;
    float coolDown;
    PlayScene *getPlayScene();
    int flag=0;

public:
    TankEnemy(int x, int y,float coolDown,std::string type);
    Plane *Target=nullptr;
    void Draw() const override;
    void Update(float deltaTime) override;
    void attack(Plane * plane,float deltaTime);
    void CreateBullet() override;
};
#endif   // GangEnemy_HPP
