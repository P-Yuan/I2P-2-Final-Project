#ifndef GANG_HPP
#define GANG_HPP
#include <list>
#include <string>
#include <vector>
#include <allegro5/bitmap.h>
#include <memory>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include "Player.hpp"

class PlayScene;
class Enemy;
class Player;

class Gang: public Player{
protected:
    
    float AttackSpan=0.1;
    float AttackTicks;
    PlayScene *getPlayScene();
public:
    Gang(std::string img, float x, float y, float radius, float speedint);
    void Update(float deltaTime) override;
    void Draw() const override;
    void Walking(float deltatime) override;
    void Dying(float deltatime) override;
    bool nochase;
};
#endif   // GANG_HPP