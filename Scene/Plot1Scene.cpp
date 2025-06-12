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
#include "Plot1Scene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

int plot1Scene::page;

void plot1Scene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    std::string s;
    Engine::ImageButton *btn1, *btn2;
    page=1;

    AddNewObject(new Engine::Image("scenes/textbox_back.png", halfW, halfH, w, h, 0.5, 0.5));
    AddNewObject(new Engine::Image("play/people1.png", halfW-500, halfH+200, 240, 200, 0.5, 0.5));

    //Next button1
    btn1 = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW /2, halfH/4 , 800, 80);
    btn1->SetOnClickCallback(std::bind(&plot1Scene::NextClick, this, 1));
    AddNewControlObject(btn1);
    
    //next button2
    btn2 = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW /2, halfH/4 + 150 , 800, 80);
    btn2->SetOnClickCallback(std::bind(&plot1Scene::NextClick, this, 2));
    AddNewControlObject(btn2);

    
    AddNewObject(new Engine::Label("新竹的交通狀況如何呢?", "IMing.ttf", 40, halfW +100, halfH* 3/2 -80, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("有什麼要注意的地方嗎? ", "IMing.ttf", 40, halfW +100, halfH* 3/2 -20, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("簡直是行人天堂 !  人行道什麼的根本不需要啦~ ", "IMing.ttf", 30, halfW, halfH/2 -50 -15, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("小心有人會騎貢丸喔 !", "IMing.ttf", 30, halfW , halfH/2 + 100 -15, 0, 0, 0, 255, 0.5, 0.5));

    bgmInstance = AudioHelper::PlaySample("happy.ogg", true, AudioHelper::BGMVolume,5);
}




void plot1Scene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void plot1Scene::NextClick(int choice) {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    page++;
    switch (page)
    {
    case 2:
        popObject(4);
        AddNewObject(new Engine::Label("Let's   go~", "IMing.ttf", 30, halfW, halfH/2 -50 -15, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("走吧 ! 可惜我們沒有貢丸可以騎", "IMing.ttf", 30, halfW, halfH/2 +100 -15, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("真的嗎 !   那我們出發吧 !", "IMing.ttf", 40, halfW +100, halfH* 3/2 -50, 0, 0, 0, 255, 0.5, 0.5));
        break;
    
    default:
        page=0;
        PlayScene *scene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
        scene->MapId = 1;
        Engine::GameEngine::GetInstance().ChangeScene("play");
        break;
    }  
}

void plot1Scene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void plot1Scene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}