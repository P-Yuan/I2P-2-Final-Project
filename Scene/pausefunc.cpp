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

#include "Player/Player.hpp"
#include "Enemy/Enemy.hpp"
#include "Enemy/GrandmaEnemy.hpp"
#include "Enemy/CarEnemy.hpp"
#include "Enemy/GangEnemy.hpp" 
#include "Enemy/HoleEnemy.hpp" 
#include "Enemy/BikeEnemy.hpp"
#include "Enemy/TreeEnemy.hpp"
#include "Enemy/TruckEnemy.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Engine/Sprite.hpp"
#include "PlayScene.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Scene/WinScene.hpp"
#include "Turret/LaserTurret.hpp"
#include "Turret/MachineGunTurret.hpp"
#include "Turret/TurretButton.hpp"
#include "Turret/FireTurret.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/Plane.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/backgroundImage.hpp"
#include "Player/coin.hpp"

void PlayScene::pauseinit()
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    //Engine::GameEngine::GetInstance().ChangeScene("shop");

    Engine::ImageButton *btn;
    PauseGroup->AddNewObject(new Engine::Image("play/shovel-base.png", halfW-100, halfH, 1000, 800, 0.5, 0.5));
    PauseGroup->AddNewObject(new Engine::Label("SHOP", "pirulen.ttf", 48, halfW-100, halfH-350, 0, 0, 0, 255, 0.5, 0.5));
    //laserturret
    PauseGroup->AddNewObject(new Engine::Image("play/floor.png", halfW-400, halfH-200, 150, 150, 0.5, 0.5));
    PauseGroup->AddNewObject(new Engine::Image("play/turret-2.png", halfW-400, halfH-200, 150, 150, 0.5, 0.5));
    //fireturret
    PauseGroup->AddNewObject(new Engine::Image("play/floor.png", halfW-100, halfH-200, 150, 150, 0.5, 0.5));
    PauseGroup->AddNewObject(new Engine::Image("play/turret-fire.png", halfW-100, halfH-200, 150, 150, 0.5, 0.5));
    //plane
    PauseGroup->AddNewObject(new Engine::Image("play/floor.png", halfW+200, halfH-200, 150, 150, 0.5, 0.5));
    PauseGroup->AddNewObject(new Engine::Image("play/plane.png", halfW+200, halfH-200, 150, 150, 0.5, 0.5));
    //laserbutton
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW-500, halfH-100, 200, 90);
    btn->SetOnClickCallback(std::bind(&PlayScene::laserOnClick, this));
    PauseGroup->AddNewControlObject(btn);
    PauseGroup->AddNewObject(new Engine::Label("$500", "pirulen.ttf", 30, halfW-400, halfH-60, 0, 0, 0, 255, 0.5, 0.5));
    //firebutton
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW-200, halfH-100, 200, 90);
    btn->SetOnClickCallback(std::bind(&PlayScene::fireOnClick, this));
    PauseGroup->AddNewControlObject(btn);
    PauseGroup->AddNewObject(new Engine::Label("$1000", "pirulen.ttf", 30, halfW-100, halfH-60, 0, 0, 0, 255, 0.5, 0.5));
    //planebutton
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW+100, halfH-100, 200, 90);
    btn->SetOnClickCallback(std::bind(&PlayScene::planeOnClick, this));
    PauseGroup->AddNewControlObject(btn);
    PauseGroup->AddNewObject(new Engine::Label("$1500", "pirulen.ttf", 30, halfW+200, halfH-60, 0, 0, 0, 255, 0.5, 0.5));
    

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW-300, halfH +250, 400, 100);
    btn->SetOnClickCallback(std::bind(&PlayScene::backOnClick, this));
    PauseGroup->AddNewControlObject(btn);
    PauseGroup->AddNewObject(new Engine::Label("BACK", "pirulen.ttf", 48, halfW-100, halfH+300, 0, 0, 0, 255, 0.5, 0.5));

}

void PlayScene::ShopOnClick()
{
    Engine::GameEngine::GetInstance().resume=true;
    pauseflag=true;
}
void PlayScene::laserOnClick()
{
    if(money-500>=0)
    {
        
        auto it = UIGroup->GetObjects();
        TurretButton* btn=nullptr;
        for(auto itt =it.begin();itt!=it.end();itt++)
        {
            btn = dynamic_cast<TurretButton*>(*itt);
            if(btn!=nullptr && btn->useflag!=true)
            {
                if(btn->type=="laser")
                {
                    EarnMoney(-500);
                    btn->useflag=true;
                    UIGroup->Update(0);
                    break;
                }
            }
        }
    }
    else
    {
        Engine::Sprite *sprite;

        int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
        int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
        int shift = 135 + 25;
        PauseGroup->AddNewObject(sprite = new DirtyEffect("play/nomoney.png", 3, w-shift , h-shift-200 ));
        sprite->Rotation = 0;
    }
}
void PlayScene::fireOnClick()
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    if(money-1000>=0)
    {
        
        auto it = UIGroup->GetObjects();
        TurretButton* btn=nullptr;
        for(auto itt =it.begin();itt!=it.end();itt++)
        {
            btn = dynamic_cast<TurretButton*>(*itt);
            if(btn!=nullptr && btn->useflag!=true)
            {
                if(btn->type=="fire")
                {
                    EarnMoney(-1000);
                    btn->useflag=true;
                    UIGroup->Update(0);
                    break;
                }
            }
        }
    }
    else
    {
       Engine::Sprite *sprite;

        int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
        int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
        int shift = 135 + 25;
        PauseGroup->AddNewObject(sprite = new DirtyEffect("play/nomoney.png", 3, w-shift , h-shift-200 ));
        sprite->Rotation = 0;
    }
}

void PlayScene::planeOnClick()
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    if(money-1500>=0)
    {
        auto it = UIGroup->GetObjects();
        planeflag=true;
        Engine::Sprite* btn=nullptr;
        for(auto itt =it.begin();itt!=it.end();itt++)
        {
            btn = dynamic_cast<Engine::Sprite*>(*itt);
            if(btn!=nullptr && btn->useflag!=2)
            {
                EarnMoney(-1500);
                btn->useflag=2;
                UIGroup->Update(0);
                break;
            }
        }
    }
    else
    {
       Engine::Sprite *sprite;

        int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
        int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
        int shift = 135 + 25;
        PauseGroup->AddNewObject(sprite = new DirtyEffect("play/nomoney.png", 3, w-shift , h-shift-200 ));
        sprite->Rotation = 0;
    }
}
void PlayScene::backOnClick()
{
    PauseGroup->Clear();
    pauseflag=false;
    pauseinitflag=false;
}