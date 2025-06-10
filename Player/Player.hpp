#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <list>
#include <string>
#include <vector>
#include <allegro5/bitmap.h>
#include <memory>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class PlayScene;
class Enemy;

class Player : public Engine::Sprite {
protected:
    float hp;
    int money;
    float cooldown;
    float timeTicks;
    float timeSpan = 0.7;
    PlayScene *getPlayScene();
    virtual void OnExplode();
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;

public:
    Player(std::string img, float x, float y, float radius, float speed, float hp, int money);
    void Hit(float damage);
    void Update(float deltaTime) override;
    void Draw() const override;
    void Walking(float deltatime);
};
#endif   // PLAYER_HPP