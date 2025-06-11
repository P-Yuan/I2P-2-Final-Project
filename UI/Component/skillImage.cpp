#include <allegro5/color.h>
#include <iostream>
#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "skillImage.hpp"

bool skillImage :: useflag=false;

PlayScene *skillImage::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
skillImage::skillImage(std::string img, float x, float y, float w, float h ,std::string t):Sprite(img,x,y,w,h),type(t)
{
    useflag=false;
    
    // if(type=="heart" || type=="machine")
    // {
    //     useflag=true;
    // }
    // else
    // {
    //     useflag=false;
    // }
    
}
void skillImage::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    if (useflag) {
        //Enabled = true;
        Tint = al_map_rgba(255, 255, 255, 255);
    } else {
        //Enabled = false;
        Tint = al_map_rgba(0, 0, 0, 160);
    }
}
void skillImage::Draw() {
    Sprite::Draw();
    // Base.Draw();
    // Turret.Draw();
}
