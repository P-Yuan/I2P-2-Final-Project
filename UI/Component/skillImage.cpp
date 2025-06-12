#include <allegro5/color.h>
#include <iostream>
#include <string>
#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Sprite.hpp"
#include "Scene/PlayScene.hpp"
#include "skillImage.hpp"

PlayScene *skillImage::getPlayScene() 
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
skillImage::skillImage(std::string img, std::string t,float x, float y, float w, float h ):Sprite(img,x,y,w,h)
{
    type=t;
    useflag=false;
}

void skillImage::Update(float deltaTime) {
    if (useflag) 
    {
        //Enabled = true;
        Tint = al_map_rgba(255, 255, 255, 255);
    } 
    else 
    {
        //Enabled = false;
        Tint = al_map_rgba(0, 0, 0, 160);
    }
}
void skillImage::Draw()const 
{
    Engine::Sprite::Draw();
    // al_draw_tinted_scaled_rotated_bitmap(bmp.get(), Tint, Anchor.x * GetBitmapWidth(), Anchor.y * GetBitmapHeight(),
    //                                          Position.x, Position.y, Size.x / GetBitmapWidth(), Size.y / GetBitmapHeight(), Rotation, 0);
    // // Base.Draw();
    // Turret.Draw();
}
