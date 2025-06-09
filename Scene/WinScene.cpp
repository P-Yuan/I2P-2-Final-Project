#include <functional>
#include <string>
#include<iostream>
#include <sstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "WinScene.hpp"
#include "Engine/Group.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Scene/PlayScene.hpp"

int WinScene::winlives;
void WinScene::Initialize() {
    
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    s="|";
    NEWs="|";
    textGroup = new Group();
    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW-300, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Image("win/text.png", halfW+300, halfH, 500, 500, 0.5, 0.5));
    textGroup->AddNewObject(new Engine::Label(s, "pirulen.ttf", 48, halfW+300, halfH,  0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Please Enter Your Name", "pirulen.ttf", 24, halfW+300, halfH-100, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW-300, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    // Engine::ImageButton *btn;
    // btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 500, halfH * 7 / 4 - 50, 400, 100);
    // btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    // AddNewControlObject(btn);
    // AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW-300, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("win.wav");
    AddNewObject(textGroup);
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
// void WinScene::BackOnClick(int stage) {
//     // Change to select scene.
//     Engine::GameEngine::GetInstance().ChangeScene("stage-select");
// }

void WinScene::OnKeyDown(int keyCode) 
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    
    
    
    IScene::OnKeyDown(keyCode);
    if(keyCode>=1 && keyCode<=26) 
    {
        if(s=="|")
        {
            s=char(*al_keycode_to_name(keyCode));
        }
        else
        {
            s.push_back(char(*al_keycode_to_name(keyCode)));

        }
    }
    else if(keyCode==67)
    {
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
        ScoreboardScene :: storetovec(winlives,s,date,timee); 
        Engine::GameEngine::GetInstance().ChangeScene("scoreboard-scene");
    }
     textGroup->Clear();
     textGroup->AddNewObject(new Engine::Label(s, "pirulen.ttf", 48, halfW+300, halfH,  0, 0, 0, 255, 0.5, 0.5));
     textGroup->Update(0);
   
    
   


}

void WinScene::storelives()
{
    winlives=PlayScene :: Getlives();

}
