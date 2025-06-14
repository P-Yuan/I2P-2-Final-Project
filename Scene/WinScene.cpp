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
#include "Scene/ScoreboardScene.hpp"

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
    
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW/2 , halfH * 3/2 +30, 450, 80);
    btn->SetOnClickCallback(std::bind(&WinScene::ScoreboardOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("scoreboard", "pirulen.ttf", 36, halfW/2+230, halfH * 3/2 +70 , 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW +200, halfH * 3/2 +30, 450, 80);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("back", "pirulen.ttf", 36, halfW+430, halfH * 3/2 +70 , 0, 0, 0, 255, 0.5, 0.5));

    std::string s0="我們的得分是:"+ std::to_string(wincoin) ;
    std::string s1="謝謝你的幫助!";

    AddNewObject(new Engine::Label(s1, "IMing.ttf", 36, halfW/2 +50, halfH-100, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label(username, "IMing.ttf", 36, halfW/2 +50, halfH-60, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label(s0, "IMing.ttf", 36, halfW/2 +50, halfH-20, 0, 0, 0, 255, 0.5, 0.5));

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

void WinScene::ScoreboardOnClick() {
    // Change to scoreboard scene.
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard-scene");
}

void WinScene::storelives()
{
    wincoin=PlayScene :: Getlives();
    username=PlayScene :: Getusername();

}
