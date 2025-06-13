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
    if(type=="pause")
    {
        startflag=true;
        for (int i = 3; i >=1 ; i--) 
        {
            start_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/pause_timer (" + std::to_string(i) + ").png"));
        }
        timeSpan=0.75;
    }
    else
    {
        startflag=false;
        for (int i = 1; i <=21 ; i++) 
        {
            start_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/timer (" + std::to_string(i) + ").png"));
        }
        timeSpan = 0.18;
    }
    timeTicks=0;
}
void Timer::Update(float deltatime) {
    Sprite::Update(deltatime);
    PlayScene *scene=getPlayScene();
    if(startflag)
    { 
        timeTicks+=deltatime;
        if(type=="pause")
        {
            phase = floor((timeSpan*start_bmps.size() - timeTicks) / timeSpan);
        }
        else
        {
            phase = floor((timeSpan*start_bmps.size() - timeTicks) / timeSpan)-1;
        }

        if((type=="pause" && 0<=phase && phase<=2) || (type!="pause" && 0<=phase && phase<21))
        {
            bmp = start_bmps[phase];
        }
        else if(type=="pause")
        {
            PlayScene *scene=getPlayScene();
            startflag=false;
            scene->PauseGroup->RemoveObject(objectIterator);
            return;
        }
        else if(type=="double_coin")
        {
            startflag=false;
            scene->doublecoinmode=false;
            auto it=scene->UIGroup->GetObjects();
            skillImage *btn=nullptr;
            for(auto itt=it.begin();itt!=it.end();itt++)
            {
                skillImage *btn=nullptr;
                btn=dynamic_cast<skillImage*>(*itt);
                if(btn!=nullptr && btn->type=="double_coin")
                {
                    btn->useflag=false;
                    break;
                }
            }
            timeTicks=0;
            phase=0;    
            return;
        }
        else
        {
            timeTicks=0;
            phase=0;    
            return;
        }
    }
    else
    {
        bmp=start_bmps[0];
        timeTicks=0;
    }
    return;
}
void Timer::Draw() const{
    Sprite::Draw();
    // Base.Draw();
    // Turret.Draw();
}
