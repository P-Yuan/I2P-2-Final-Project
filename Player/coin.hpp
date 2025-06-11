#ifndef Coin_HPP
#define Coin_HPP
#include "Enemy/Enemy.hpp"

class Coin : public Enemy {
public:
    float timeTicks;
    float timeSpan = 0.7;
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> rotate_bmps;
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> hit_bmps;
    Coin(int x, int y,std::string type);

    void Draw() const override;
    void Update(float deltaTime) override;
    void OnExplode(float deltatime);

    void CreateBullet() override;
};
#endif   // Coin_HPP
