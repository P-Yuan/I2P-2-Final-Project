#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>
#include <iostream>

#include "Sign.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Player/Player.hpp"
#include "Engine/Collider.hpp"

Sign::Sign(int x, int y,int type, std::string end_place) : Enemy(end_place, x, y, 50, 30, 20, 1000,type) {}

void Sign::CreateBullet() {
    
}

void Sign::Draw() const
{
    al_draw_tinted_scaled_rotated_bitmap(bmp.get(), al_map_rgba(255, 255, 255, 255), Anchor.x * GetBitmapWidth(), Anchor.y * GetBitmapHeight(),
                                             Position.x, Position.y, Size.x / GetBitmapWidth(), Size.y / GetBitmapHeight(), Rotation, 0);
    if (PlayScene::DebugMode) {
        // Draw collision radius.
        //al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
        al_draw_rectangle(Position.x-(this->GetBitmapWidth()/2),Position.y-(this->GetBitmapHeight()/2),
                          Position.x+(this->GetBitmapWidth() /2),Position.y+(this->GetBitmapHeight() /2)
                          , al_map_rgb(255, 0, 0), 2);
    }
    
}

void Sign::Update(float deltatime)
{
    Enemy::Update(deltatime);
    //Position.x-=speed*0.1;

    PlayScene *scene = getPlayScene();
    Engine:: Point max;
    Engine:: Point min;
    Engine:: Point Pmax;
    Engine:: Point Pmin;
    min.x=Position.x-(this->GetBitmapWidth() /2);
    min.y=Position.y-(this->GetBitmapHeight() /2);
    max.x=Position.x+(this->GetBitmapWidth() /2);
    max.y=Position.y+(this->GetBitmapHeight() /2);

    auto &it = scene->PlayerGroup->GetObjects().back();
    Player *player = dynamic_cast<Player *>(it);
    Pmin.x=player->Position.x-(player->GetBitmapWidth()/3);
    Pmin.y=player->Position.y-(player->GetBitmapHeight()/3);
    Pmax.x=player->Position.x+(player->GetBitmapWidth()/3);
    Pmax.y=player->Position.y+(player->GetBitmapHeight()/3);
    if (Engine::Collider::IsRectOverlap(min, max, Pmin, Pmax)) 
    {
        scene->WinningAnimation=true;
    }
}
