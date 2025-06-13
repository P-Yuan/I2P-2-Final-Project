#ifndef TIMER_HPP
#define TIMER_HPP
#include <string>

#include "Engine/Sprite.hpp"
#include "UI/Component/ImageButton.hpp"

class PlayScene;

class Timer :public Engine::Sprite {
protected:
    PlayScene *getPlayScene();

public: 
    float timeTicks;
    float timeSpan;
    // Engine::Sprite Base;
    // Engine::Sprite Turret;
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> start_bmps;
    Timer(std::string img, float x, float y, float w , float h ,std::string t);
    void Update(float deltaTime)override ;
    void Draw() const override;
    bool startflag;
    std::string type;
    int phase;
};
#endif   // TIMER_HPP
