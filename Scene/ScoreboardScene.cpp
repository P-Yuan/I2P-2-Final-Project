#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "StageSelectScene.hpp"
#include "ScoreboardScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"


std::vector<ScoreboardScene::scorenode> ScoreboardScene::arr;
int ScoreboardScene::page;
//std::set<ScoreboardScene::scorenode,ScoreboardScene::mycompare> :: iterator ScoreboardScene::it;

void ScoreboardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    std::string s;
    Engine::ImageButton *btn;
    textnum=0;

    AddNewObject(new Engine::Image("leaderboard.png", halfW, halfH, w, h, 0.5, 0.5));
    //Scoreboard text
    AddNewObject(new Engine::Label("ScoreBoard", "pirulen.ttf", 48, halfW, halfH / 3, 47, 79, 79, 255, 0.5, 0.5));
    
    //Next button
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW - 650, halfH * 7/4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::PrevClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("PREV PAGE", "pirulen.ttf", 48, halfW-450, halfH * 7/4, 0, 0, 0, 255, 0.5, 0.5));

    //Prev button
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW + 250, halfH * 7/4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::NextClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("NEXT PAGE", "pirulen.ttf", 48, halfW + 450, halfH * 7/4, 0, 0, 0, 255, 0.5, 0.5));
    //back button
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW-200 , halfH * 7/4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7/4, 0, 0, 0, 255, 0.5, 0.5));

    std::sort(arr.begin(), arr.end(), mycompare());
    

    for(int i=0;i<5;i++)
    {
        if(page*5+i>=arr.size())
        {
            break;
        }
        textnum++;
        s=arr[page*5+i].name + " " + std::to_string(arr[page*5+i].scores) + " " + arr[page*5+i].date + " " + arr[page*5+i].timee;
        AddNewObject(new Engine::Label(s, "pirulen.ttf", 30, halfW, halfH / 2+(i*50), 10, 255, 255, 255, 0.5, 0.5));
    } 
    

    //Slider *sliderBGM, *sliderSFX;  
    //sliderBGM = new Slider(40 + halfW - 95, halfH - 50 - 2, 190, 4);
    //sliderBGM->SetOnValueChangedCallback(std::bind(&StageSelectScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    //AddNewControlObject(sliderBGM);
    //AddNewObject(new Engine::Label("BGM: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH - 50, 255, 255, 255, 255, 0.5, 0.5));
    //sliderSFX = new Slider(40 + halfW - 95, halfH + 50 - 2, 190, 4);
    //sliderSFX->SetOnValueChangedCallback(std::bind(&StageSelectScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    //AddNewControlObject(sliderSFX);
    //AddNewObject(new Engine::Label("SFX: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH + 50, 255, 255, 255, 255, 0.5, 0.5));
    //Not safe if release resource while playing, however we only free while change scene, so it's fine.
    //bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
    //sliderBGM->SetValue(AudioHelper::BGMVolume);
    //sliderSFX->SetValue(AudioHelper::SFXVolume);

    // Not safe if release resource while playing, however we only free while change scene, so it's fine.

    bgmInstance = AudioHelper::PlaySample("happy.ogg", true, AudioHelper::BGMVolume,5);
}

void ScoreboardScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void ScoreboardScene::BackOnClick() {
    page=0;
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void ScoreboardScene::NextClick() {
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
void ScoreboardScene::PrevClick() {
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
void ScoreboardScene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void ScoreboardScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}

void ScoreboardScene::storetovec(int lives,std::string name,std::string date,std::string timee)
{
    arr.push_back(scorenode(lives,name,date,timee));
}

void ScoreboardScene::storetotxt()
{
    
    std::ofstream out("C:\\Users\\user\\OneDrive\\Desktop\\Introduction to Programing-2\\Mini_Project 2\\2025_I2P2_TowerDefense-main\\Resource\\scoreboard.txt");
    for (auto &p : arr) 
    {
        out << p.name << " " << p.scores << " " << p.date << " " << p.timee << "\n"; 
    }
    out.close();
}

void ScoreboardScene::inputtoset()
{
    std::ifstream in("C:\\Users\\user\\OneDrive\\Desktop\\Introduction to Programing-2\\Mini_Project 2\\2025_I2P2_TowerDefense-main\\Resource\\scoreboard.txt");

    std::string name;
    std::string date;
    std::string timee;
    std::string score;
    while(in >> name >> score >> date >> timee)
    {
        arr.push_back(scorenode(std::stoi(score),name,date,timee));
    }
    in.close();
}