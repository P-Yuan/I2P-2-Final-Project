#include <algorithm>
#include <allegro5/allegro.h>
#include <cmath>
#include <fstream>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>

#include "PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/timer.hpp"
#include "Player/Player.hpp"


void PlayScene::pauseinit()
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    //Engine::GameEngine::GetInstance().ChangeScene("shop");

    Engine::ImageButton *btn;
    PauseGroup->AddNewObject(new Engine::Image("play/shop.png", halfW-100, halfH-50, 1200, 800, 0.5, 0.5));
    PauseGroup->AddNewObject(new Engine::Label("SHOP", "pirulen.ttf", 48, halfW-100, halfH-250, 0, 0, 0, 255, 0.5, 0.5));

    PauseGroup->AddNewObject(new Engine::Image("play/shop_coin.png", halfW-450, halfH-100, 150, 150, 0.5, 0.5));

    PauseGroup->AddNewObject(new Engine::Image("play/medicine.png", halfW-220, halfH-100, 150, 150, 0.5, 0.5));

    PauseGroup->AddNewObject(new Engine::Image("play/gun.png", halfW, halfH-100, 200, 200, 0.5, 0.5));

    PauseGroup->AddNewObject(new Engine::Image("play/super.png", halfW+225, halfH-100, 300, 150, 0.5, 0.5));
    //coinbutton
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW-530, halfH, 150, 80);
    btn->SetOnClickCallback(std::bind(&PlayScene::coinOnClick, this));
    PauseGroup->AddNewControlObject(btn);
    PauseGroup->AddNewObject(new Engine::Label("$500", "pirulen.ttf", 30, halfW-460, halfH+40, 0, 0, 0, 255, 0.5, 0.5));
    // //hpbutton
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW-295, halfH, 150, 80);
    btn->SetOnClickCallback(std::bind(&PlayScene::hpOnClick, this));
    PauseGroup->AddNewControlObject(btn);
    PauseGroup->AddNewObject(new Engine::Label("$1000", "pirulen.ttf", 30, halfW-225, halfH+40, 0, 0, 0, 255, 0.5, 0.5));
    //gunbutton
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW-70, halfH, 150, 80);
    btn->SetOnClickCallback(std::bind(&PlayScene::gunOnClick, this));
    PauseGroup->AddNewControlObject(btn);
    PauseGroup->AddNewObject(new Engine::Label("$1500", "pirulen.ttf", 30, halfW, halfH+40, 0, 0, 0, 255, 0.5, 0.5));

    //superbutton
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW+150, halfH, 150, 80);
    btn->SetOnClickCallback(std::bind(&PlayScene::superOnClick, this));
    PauseGroup->AddNewControlObject(btn);
    PauseGroup->AddNewObject(new Engine::Label("$1500", "pirulen.ttf", 30, halfW+220, halfH+40, 0, 0, 0, 255, 0.5, 0.5));
    
    //back button
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW-260, halfH +150, 350, 80);
    btn->SetOnClickCallback(std::bind(&PlayScene::backOnClick, this));
    PauseGroup->AddNewControlObject(btn);
    PauseGroup->AddNewObject(new Engine::Label("BACK", "pirulen.ttf", 48, halfW-90, halfH+190, 0, 0, 0, 255, 0.5, 0.5));

}

void PlayScene::coinOnClick()
{
    if(money-500>=0)
    {
        doublecoinmode=true;
        auto it = UIGroup->GetObjects();
        skillImage* skill=nullptr;
        Timer* timer=nullptr;
        for(auto itt =it.begin();itt!=it.end();itt++)
        {
            skill = dynamic_cast<skillImage*>(*itt);
            timer= dynamic_cast<Timer*>(*itt);
            if(skill!=nullptr && skill->type=="double_coin")
            {
                EarnMoney(-500);
                skill->useflag=true;
            }
            if(timer!=nullptr && timer->type=="double_coin")
            {
                timer->startflag=true;
                timer->bmp=timer->start_bmps[20];
            }
        }
        UIGroup->Update(0);
    }
    else
    {
        nomoney();
    }
}
void PlayScene::hpOnClick()
{
    if(money-500>=0)
    {
        lives=100;
        UILives->Text = std::string("Life ") + std::to_string(lives);
        UIGroup->Update(0);
    }
    else
    {
        nomoney();
    }

}
void PlayScene::gunOnClick()
{
    if(money-500>=0)
    {
        auto &pit = PlayerGroup->GetObjects().back();
        Player *player=dynamic_cast<Player*>(pit);
        player->attackingmode=true;

        auto it = UIGroup->GetObjects();
        skillImage* skill=nullptr;
        Timer* timer=nullptr;
        for(auto itt =it.begin();itt!=it.end();itt++)
        {
            skill = dynamic_cast<skillImage*>(*itt);
            timer= dynamic_cast<Timer*>(*itt);
            if(skill!=nullptr && skill->type=="gun")
            {
                EarnMoney(-500);
                skill->useflag=true;
            }
            if(timer!=nullptr && timer->type=="gun")
            {
                
                timer->startflag=true;
                timer->bmp=timer->start_bmps[20];
                
            }
        }
    }
    else
    {
        nomoney();
    }
    UIGroup->Update(0);
}
void PlayScene::superOnClick()
{
    if(money-500>=0)
    {
       auto &pit = PlayerGroup->GetObjects().back();
        Player *player=dynamic_cast<Player*>(pit);
        player->superingmode=true;

        auto it = UIGroup->GetObjects();
        skillImage* skill=nullptr;
        Timer* timer=nullptr;
        for(auto itt =it.begin();itt!=it.end();itt++)
        {
            skill = dynamic_cast<skillImage*>(*itt);
            timer= dynamic_cast<Timer*>(*itt);
            if(skill!=nullptr && skill->type=="super")
            {
                EarnMoney(-500);
                skill->useflag=true;
                UIGroup->Update(0);
            }
            if(timer!=nullptr && timer->type=="super")
            {
                timer->startflag=true;
                timer->bmp=timer->start_bmps[20];
                timer->Update(0);
            }
        }
    }
    else
    {
        nomoney();
    }

}
void PlayScene::backOnClick()
{
    PauseGroup->Clear();
    PauseGroup->AddNewObject(new Timer("play/pause_timer (3).png",700,500, 600,400,"pause"));
}
void PlayScene::nomoney()
{
    Engine::Sprite *sprite;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int shift = 135 + 25;
    PauseGroup->AddNewObject(sprite = new DirtyEffect("play/nomoney.png", 3, w-500 , h-shift ));
    sprite->Rotation = 0;
}

