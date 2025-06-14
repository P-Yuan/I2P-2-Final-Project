#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <string>
#include <vector>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class Bullet;
class PlayScene;
//class Turret;

class Enemy : public Engine::Sprite {
protected:
    std::vector<Engine::Point> path;
    float speed;
    int damage;
    int money;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    int type;
    std::list<Enemy*>::iterator lockedEnemyIterator;
    PlayScene *getPlayScene();
    virtual void OnExplode();
    virtual void CreateBullet() = 0;
public:
    bool Enabled = true;
    bool Preview = false;
    float reachEndTime;
    //std::list<Turret *> lockedTurrets;
    std::list<Bullet *> lockedBullets;
    Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money,int type);
    void Hit();
    void FireHit();
    void UpdatePath(const std::vector<std::vector<int>> &mapDistance);
    void Update(float deltaTime) override;
    void Draw() const override;
    int getdamage();
};
#endif   // ENEMY_HPP
