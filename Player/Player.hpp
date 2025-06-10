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
    float HitTicks;
    float HitSpan = 0.1;
    float MoveTicks;
    float MoveSpan = 0.05;
    PlayScene *getPlayScene();
    virtual void OnExplode();
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> walk_bmps;
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> hit_bmps;
    enum dir{
        UP=-1, DOWN=1
    };
    dir move_dir;
public:
    Player(std::string img, float x, float y, float radius, float speed, float hp, int money);
    void Hit(float damage);
    void Update(float deltaTime) override;
    void Draw() const override;
    void Walking(float deltatime);
    void Hitting(float deltatime);
    void OnKeyDown(int keyCode);
};
#endif   // PLAYER_HPP