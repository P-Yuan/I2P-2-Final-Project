#include <allegro5/color.h>
#include <iostream>
#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "timer.hpp"
#include "Engine/Resources.hpp"

PlayScene *Timer::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Timer::Timer(std::string img, float x, float y, float w, float h ,std::string t):Sprite(img,x,y,w,h),type(t)
{
    startflag=false;
    for (int i = 1; i <=21 ; i++) {
        start_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/timer (" + std::to_string(i) + ").png"));
    }
    timeTicks=0;
}
void Timer::Update(float deltatime) {
    Sprite::Update(deltatime);
    if(startflag)
    {
         timeTicks+=deltatime;
         
        //if(timeTicks>=timeSpan) timeTicks-=timeSpan;
        int phase = floor((timeSpan*20 - timeTicks) / timeSpan);
        if(phase<0){
        //Engine::LOG(Engine::INFO)<<"End hit";
        return;
        }
        bmp = start_bmps[phase];
    }
    else
    {
        bmp=start_bmps[0];
        timeTicks=0;
    }
    
}
void Timer::Draw() const{
    Sprite::Draw();
    // Base.Draw();
    // Turret.Draw();
}
