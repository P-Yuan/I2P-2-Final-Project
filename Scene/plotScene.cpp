#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <iostream>
#include <vector>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "StageSelectScene.hpp"
#include "plotScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"


// std::vector<ScoreboardScene::scorenode> ScoreboardScene::arr;
// int ScoreboardScene::page;
//std::set<ScoreboardScene::scorenode,ScoreboardScene::mycompare> :: iterator ScoreboardScene::it;

void plotScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    std::string s;
    Engine::ImageButton *btn;
    textnum=0;

    AddNewObject(new Engine::Image("start_back.jpg", halfW, halfH, 1600, 800, 0.5, 0.5));

    AddNewObject(new Engine::Image("play/people1.png", halfW, halfH, 400, 200, 0.5, 0.5));

    
    
    // //Next button
    // btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 650, halfH * 3 / 2 - 50, 400, 100);
    // btn->SetOnClickCallback(std::bind(&ScoreboardScene::PrevClick, this));
    // AddNewControlObject(btn);
    // AddNewObject(new Engine::Label("PREV PAGE", "pirulen.ttf", 48, halfW-450, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    // //Prev button
    // btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 250, halfH * 3 / 2 - 50, 400, 100);
    // btn->SetOnClickCallback(std::bind(&ScoreboardScene::NextClick, this));
    // AddNewControlObject(btn);
    // AddNewObject(new Engine::Label("NEXT PAGE", "pirulen.ttf", 48, halfW + 450, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    // //back button
    // btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW-200 , halfH * 3 / 2 - 50, 400, 100);
    // btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this));
    // AddNewControlObject(btn);
    // AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    // std::sort(arr.begin(), arr.end(), mycompare());
    

    // for(int i=0;i<5;i++)
    // {
    //     if(page*5+i>=arr.size())
    //     {
    //         break;
    //     }
    //     textnum++;
    //     s=arr[page*5+i].name + " " + std::to_string(arr[page*5+i].scores) + " " + arr[page*5+i].date + " " + arr[page*5+i].timee;
    //     AddNewObject(new Engine::Label(s, "pirulen.ttf", 30, halfW, halfH / 3+(i*50), 10, 255, 255, 255, 0.5, 0.5));
    // } 

    bgmInstance = AudioHelper::PlaySample("happy.ogg", true, AudioHelper::BGMVolume,5);
}

void plotScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void plotScene::BackOnClick() {
    page=0;
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void plotScene::NextClick() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    int maxpage=arr.size()/5;
    if(arr.size()%5>0)
    {
        maxpage++;
    }
    if(page+1>=maxpage)
    {
        return;
    }
    page++;
    popObject(textnum);
    
    std::string s;
    textnum=0;
    for(int i=0;i<5;i++)
    {
        if(page*5+i>=arr.size())
        {
            break;
        }
        textnum++;
        s=arr[page*5+i].name + " " + std::to_string(arr[page*5+i].scores) + " " + arr[page*5+i].date + " " + arr[page*5+i].timee;
        AddNewObject(new Engine::Label(s, "pirulen.ttf", 30, halfW, halfH / 3+(i*50), 10, 255, 255, 255, 0.5, 0.5));
    } 
}
void plotScene::PrevClick() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
     if(page-1<0)
    {
        return;
    }
    page--;
    popObject(textnum);
   
    std::string s;
    textnum=0;
    for(int i=0;i<5;i++)
    {
        if(page*5+i>=arr.size())
        {
            break;
        }
        textnum++;
        s=arr[page*5+i].name + " " + std::to_string(arr[page*5+i].scores) + " " + arr[page*5+i].date + " " + arr[page*5+i].timee;
        AddNewObject(new Engine::Label(s, "pirulen.ttf", 30, halfW, halfH / 3+(i*50), 10, 255, 255, 255, 0.5, 0.5));
    } 
}
void plotScene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void plotScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}