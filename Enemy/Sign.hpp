#ifndef SIGN_HPP
#define SIGN_HPP
#include "Enemy.hpp"

class Sign : public Enemy {
public:
    float timeTicks;
    float timeSpan = 0.7;    
    Sign(int x, int y,int type, std::string end_place);

    void Draw() const override;
    void Update(float deltaTime) override;

    void CreateBullet() override;
};
#endif   // SIGN_HPP
