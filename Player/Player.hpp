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
    float attackcooldown;
    float timeTicks;
    float timeSpan = 0.7;
    float HitTicks;
    float HitSpan = 0.1;
    float MoveTicks;
    float MoveSpan = 0.05;
    float DyingTicks;
    float DyingSpan = 0.1;
    float WinningTicks;
    float WinningSpan = 0.2;
    int attackingcnt=0;
    
    float gochase;
    float chasing;
    float goback;
    PlayScene *getPlayScene();
    virtual void OnExplode();
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> walk_bmps;
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> hit_bmps;
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> win_bmps;
    enum dir{
        UP=-1, DOWN=1
    };
    dir move_dir;
public:
    
    Player(std::string img, float x, float y, float radius, float speed, float hp, int money);
    void Hit(float damage);
    void Update(float deltaTime) override;
    void Draw() const override;
    virtual void Walking(float deltatime);
    void Hitting(float deltatime);
    void OnKeyDown(int keyCode);
    virtual void Dying(float deltaTime);
    void Winning(float deltaTime);
    void attacking(float deltaTime);
    static bool attackingmode;
};
#endif   // PLAYER_HPP