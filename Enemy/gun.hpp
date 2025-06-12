#ifndef gun_HPP
#define gun_HPP
#include "Enemy.hpp"

class Gun : public Enemy {
public:
    float timeTicks;
    float timeSpan = 0.7;    
    Gun(int x, int y,int type);
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> hit_bmps;
    void Draw() const override;
    void Update(float deltaTime) override;
    void OnExplode(float deltatime);

    void CreateBullet() override;
};
#endif   // Coin_HPP
