#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <list>
#include <string>
#include <vector>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class PlayScene;
class Enemy;

class Player : public Engine::Sprite {
protected:
    float hp;
    int money;
    float cooldown;
    PlayScene *getPlayScene();
    virtual void OnExplode();

public:
    Player(std::string img, float x, float y, float radius, float speed, float hp, int money);
    void Hit(float damage);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif   // PLAYER_HPP