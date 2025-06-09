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

int plotScene::page;

void plotScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    std::string s;
    Engine::ImageButton *btn;
    page=1;

    AddNewObject(new Engine::Image("start_back.jpg", halfW, halfH, 1600, 800, 0.5, 0.5));

    //Next button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW +350, halfH+250, 400, 80);
    btn->SetOnClickCallback(std::bind(&plotScene::NextClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Image("play/people1.png", halfW-550, halfH+200, 300, 200, 0.5, 0.5));
    AddNewObject(new Engine::Label("Welcome to NTHU", "pirulen.ttf", 24, halfW +530, halfH+290, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Image("play/textbox1.png", halfW-50, halfH+250, 780, 180, 0.5, 0.5));

    bgmInstance = AudioHelper::PlaySample("happy.ogg", true, AudioHelper::BGMVolume,5);
}




void plotScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void plotScene::NextClick() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    page++;
    if(page==2)
    {
        popObject(2);
        AddNewObject(new Engine::Label("Of course, but...", "pirulen.ttf", 24, halfW +530, halfH+290, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Image("play/textbox2.png", halfW-50, halfH+250, 780, 180, 0.5, 0.5));
    }
    else if(page==3)
    {
        popObject(2);
        AddNewObject(new Engine::Label("What's in your hand?", "pirulen.ttf", 20, halfW +550, halfH+290, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Image("play/textbox3.png", halfW-50, halfH+250, 780, 180, 0.5, 0.5));
    }
    else if(page==4)
    {
        popObject(2);
        AddNewObject(new Engine::Label("Umh......", "pirulen.ttf", 24, halfW +530, halfH+290, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Image("play/textbox4.png", halfW-50, halfH+250, 780, 180, 0.5, 0.5));
    }
    else if(page==5)
    {
        page=0;
        Engine::GameEngine::GetInstance().ChangeScene("stage-select");
    }
    
    
}

void plotScene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void plotScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}