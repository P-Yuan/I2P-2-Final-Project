#include <functional>
#include <string>
#include<iostream>
#include <sstream>
#include <iomanip>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "WinScene.hpp"
#include "Engine/Group.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Scene/PlayScene.hpp"

int WinScene::wincoin;
std::string WinScene::username;
void WinScene::Initialize() {
    typing = true;
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    std::string winplace;
    PlayScene *scene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
    winplace = std::string("win/win") + std::to_string(scene->MapId) + std::string(".png");
    AddNewObject(new Engine::Image(winplace, halfW, halfH, w, h, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 64, halfW, halfH / 4 , 0, 0, 0, 255, 0.5, 0.5));

    //std::string s="你的分數是:"+ std::to_string(wincoin);
    //textGroup = new Group();
    //AddNewObject(new Engine::Image("win/doge.png", halfW-300, halfH, 0, 0, 0.5, 0.5));
    //AddNewObject(new Engine::Image("win/text.png", halfW+300, halfH, 500, 500, 0.5, 0.5));
    //textGroup->AddNewObject(new Engine::Label(s, "pirulen.ttf", 48, halfW * 3/2 -115, halfH * 3/2 +65,  0, 0, 0, 255, 0.5, 0.5));
    //AddNewObject(new Engine::Label(s, "pirulen.ttf", 48, halfW/2 +90, halfH * 3/2 +65, 0, 0, 0, 255, 0.5, 0.5));
    
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW -200, halfH * 7/4 +10, 450, 80);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this,scene->MapId));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("next level", "pirulen.ttf", 48, halfW+30, halfH * 7 / 4 +50 , 0, 0, 0, 255, 0.5, 0.5));

    std::string s="你的分數是:"+ std::to_string(wincoin);
    std::string s1="謝謝" + username + "的幫助!";

    AddNewObject(new Engine::Label(s1, "IMing.ttf", 36, halfW/2 +50, halfH-80, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label(s, "IMing.ttf", 36, halfW/2 +50, halfH-30, 0, 0, 0, 255, 0.5, 0.5));

    bgmId = AudioHelper::PlayAudio("win.wav");
    //AddNewObject(textGroup);
}
void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Draw() const {
    IScene::Draw();
}
void WinScene::Update(float deltaTime) {
    IScene :: Update(deltaTime);
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}
void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    time_t now=time(0);
    tm* ltm = localtime(&now);
    std::ostringstream dateStream, timeStream;

    dateStream << std::setw(4) << std::setfill('0') << (ltm->tm_year + 1900) << "-"
            << std::setw(2) << std::setfill('0') << (ltm->tm_mon + 1) << "-"  // 注意：tm_mon 是從 0 開始
            << std::setw(2) << std::setfill('0') << ltm->tm_mday;

    timeStream << std::setw(2) << std::setfill('0') << ltm->tm_hour << ":"
            << std::setw(2) << std::setfill('0') << ltm->tm_min << ":"
            << std::setw(2) << std::setfill('0') << ltm->tm_sec;

    std::string date = dateStream.str();
    std::string timee = timeStream.str();

    ScoreboardScene :: storetovec(stage); 
    ScoreboardScene :: inputnewdata(wincoin,username,date,timee,stage); 
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

// void WinScene::OnKeyDown(int keyCode) 
// {
//     int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
//     int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
//     int halfW = w / 2;
//     int halfH = h / 2;
    
//     IScene::OnKeyDown(keyCode);
//     if(keyCode>=1 && keyCode<=26 && typing) 
//     {
//         if(s=="|")
//         {
//             s=char(*al_keycode_to_name(keyCode));
//         }
//         else if(s.size()<12)
//         {
//             s.push_back(char(*al_keycode_to_name(keyCode)));
//         }
//     }
//     else if(keyCode==67 && typing)
//     {
//         typing=false;

//         popObject(4);
//         AddNewObject(new Engine::Label("Bye", "pirulen.ttf", 48, halfW, halfH * 7 / 4 +50, 0, 0, 0, 255, 0.5, 0.5));

//         AddNewObject(new Engine::Label("謝謝你", "IMing.ttf", 36, halfW/2 +50, halfH-80, 0, 0, 0, 255, 0.5, 0.5));
//         AddNewObject(new Engine::Label(s, "IMing.ttf", 36, halfW/2 +50, halfH-30, 0, 0, 0, 255, 0.5, 0.5));

//         AddNewObject(new Engine::Label(s, "pirulen.ttf", 48, halfW * 3/2 -115, halfH * 3/2 +65, 25, 25, 112, 255, 0.5, 0.5));

//         time_t now=time(0);
//         tm* ltm = localtime(&now);
//         std::ostringstream dateStream, timeStream;

//         dateStream << std::setw(4) << std::setfill('0') << (ltm->tm_year + 1900) << "-"
//                 << std::setw(2) << std::setfill('0') << (ltm->tm_mon + 1) << "-"  // 注意：tm_mon 是從 0 開始
//                 << std::setw(2) << std::setfill('0') << ltm->tm_mday;

//         timeStream << std::setw(2) << std::setfill('0') << ltm->tm_hour << ":"
//                 << std::setw(2) << std::setfill('0') << ltm->tm_min << ":"
//                 << std::setw(2) << std::setfill('0') << ltm->tm_sec;

//         std::string date = dateStream.str();
//         std::string timee = timeStream.str();
//         ScoreboardScene :: storetovec(winlives,s,date,timee); 
//         //Engine::GameEngine::GetInstance().ChangeScene("scoreboard-scene");
//     }
//      textGroup->Clear();
//      textGroup->AddNewObject(new Engine::Label(s, "pirulen.ttf", 48, halfW * 3/2 -115, halfH* 3/2 +65,  0, 0, 0, 255, 0.5, 0.5));
//      textGroup->Update(0);
   
    
   


// }

void WinScene::storelives()
{
    wincoin=PlayScene :: Getlives();
    username=PlayScene :: Getusername();

}
