#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "coin.hpp"
#include "Scene/PlayScene.hpp"
//#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Player/Player.hpp"
#include "Engine/Collider.hpp"


Coin::Coin(int x, int y,int type) : Enemy("play/coins_1.png", x, y, 50, 30, 20, 1000,type) 
{
    timeTicks=0;
    for (int i = 1; i <= 8; i++) {
        rotate_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/coins_" + std::to_string(i) + ".png"));
    }

     for (int i = 9; i<=16 ; i++) {
        hit_bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/coins_" + std::to_string(i) + ".png"));
    }
}

void Coin::CreateBullet() {
    
}

void Coin::Draw() const
{
     al_draw_tinted_scaled_rotated_bitmap(bmp.get(), Tint, Anchor.x * GetBitmapWidth(), Anchor.y * GetBitmapHeight(),
                                             Position.x, Position.y, Size.x/3 , Size.y/3 , Rotation, 0);
    if (PlayScene::DebugMode) {
        // Draw collision radius.
        //al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
        al_draw_rectangle(Position.x-(this->GetBitmapWidth()),Position.y-(this->GetBitmapHeight()),
                          Position.x+(this->GetBitmapWidth()),Position.y+(this->GetBitmapHeight())
                          , al_map_rgb(255, 0, 0), 2);
    }
    
}

void Coin::Update(float deltatime)
{
    timeTicks+=deltatime;
    if(timeTicks>=timeSpan) timeTicks-=timeSpan;
    int phase = floor(timeTicks / timeSpan * rotate_bmps.size());
    //Engine::LOG(Engine::INFO)<<"Find walking phase:"<<phase;
    bmp = rotate_bmps[phase];
    Enemy::Update(deltatime);

    PlayScene *scene = getPlayScene();
    Engine:: Point max;
    Engine:: Point min;
    Engine:: Point Pmax;
    Engine:: Point Pmin;
    min.x=Position.x-(this->GetBitmapWidth());
    min.y=Position.y-(this->GetBitmapHeight());
    max.x=Position.x+(this->GetBitmapWidth());
    max.y=Position.y+(this->GetBitmapHeight());

    //  for (auto &it : scene->PlayerGroup->GetObjects()) 
    //  {
        auto &it= scene->PlayerGroup->GetObjects().back();
        Player *player = dynamic_cast<Player *>(it);
        Pmin.x=player->Position.x-(player->GetBitmapWidth()/3);
        Pmin.y=player->Position.y-(player->GetBitmapHeight()/3);
        Pmax.x=player->Position.x+(player->GetBitmapWidth()/3);
        Pmax.y=player->Position.y+(player->GetBitmapHeight()/3);
        if (Engine::Collider::IsRectOverlap(min, max, Pmin, Pmax)) 
        {
            OnExplode(deltatime);
            
        }
    // }
}

void Coin::OnExplode(float deltatime)
{
    timeTicks+=deltatime;
    if(timeTicks>=timeSpan) timeTicks-=timeSpan;
    int phase = floor(timeTicks / timeSpan * hit_bmps.size());
    //Engine::LOG(Engine::INFO)<<"Find walking phase:"<<phase;
    bmp = hit_bmps[phase];
    PlayScene *scene = getPlayScene();
    if(phase<4)
    {
        AudioHelper::PlayAudio("coins.wav");
    }
    if(phase==7)
    {
        scene->coinGroup->RemoveObject(objectIterator);
        if(scene->doublecoinmode)
        {
            scene->EarnMoney(20);
        }
        else
        {
            scene->EarnMoney(10);
        }
    }
    //std::cout << phase << std::endl;
}
