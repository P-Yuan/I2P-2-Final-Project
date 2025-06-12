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
#include "Plot3Scene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

int plot3Scene::page;

void plot3Scene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    std::string s;
    Engine::ImageButton *btn1,*btn2;
    page=1;

    AddNewObject(new Engine::Image("scenes/textbox_back.png", halfW, halfH, w, h, 0.5, 0.5));

    //Next button1
    btn1 = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW /2, halfH/4 , 800, 80);
    btn1->SetOnClickCallback(std::bind(&plot3Scene::NextClick, this, 1));
    AddNewControlObject(btn1);
    
    //next button2
    btn2 = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW /2, halfH/4 + 150 , 800, 80);
    btn2->SetOnClickCallback(std::bind(&plot3Scene::NextClick, this, 2));
    AddNewControlObject(btn2);

    AddNewObject(new Engine::Image("play/people1.png", halfW-500, halfH+200, 240, 200, 0.5, 0.5));
    AddNewObject(new Engine::Image("play/gang_walk3.png", halfW-700, halfH+180, 240, 200, 0.5, 0.5));

    AddNewObject(new Engine::Label("終於到台中了 ，這裡真的很危險嗎?", "IMing.ttf", 40, halfW +100, halfH* 3/2 -50, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("你手上那把比較危險吧......", "IMing.ttf", 30, halfW, halfH/2 -50 -15, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("你擋到後面的人了", "IMing.ttf", 30, halfW , halfH/2 + 100 -15, 0, 0, 0, 255, 0.5, 0.5));
    
    
    bgmInstance = AudioHelper::PlaySample("happy.ogg", true, AudioHelper::BGMVolume,5);
}




void plot3Scene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void plot3Scene::NextClick(int choice) {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    page++;
    switch (page)
    {
    case 2:
        popObject(5);
        AddNewObject(new Engine::Image("play/gang_walk3.png", halfW-500, halfH+200, 260, 240, 0.5, 0.5));
        AddNewObject(new Engine::Label("跨你緣投啦 !", "IMing.ttf", 30, halfW, halfH/2 -50 -15, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("(烙跑) ", "IMing.ttf", 30, halfW, halfH/2 +100 -15, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("跨三小", "IMing.ttf", 40, halfW +100, halfH* 3/2 -50, 0, 0, 0, 255, 0.5, 0.5));
        break;
    case 3:
        popObject(5);
        AddNewObject(new Engine::Image("play/gang_attack3.png", halfW-680, halfH+200, 240, 200, 0.5, 0.5));
        AddNewObject(new Engine::Image("play/player_jump4.png", halfW-500, halfH+200, 240, 200, 0.5, 0.5));
        if(choice==1){
            AddNewObject(new Engine::Label("啊啊啊 ! 快跑!!!", "IMing.ttf", 30, halfW, halfH/2 -50 -15, 0, 0, 0, 255, 0.5, 0.5));
            AddNewObject(new Engine::Label("為什麼還是追上來了!?", "IMing.ttf", 40, halfW +100, halfH* 3/2 -50, 0, 0, 0, 255, 0.5, 0.5));
        }
        else{
            AddNewObject(new Engine::Label("啊啊啊 ! 快跑!!!", "IMing.ttf", 30, halfW, halfH/2 -50 -15, 0, 0, 0, 255, 0.5, 0.5));
            AddNewObject(new Engine::Label("怎麼追上來了!?", "IMing.ttf", 40, halfW +100, halfH* 3/2 -50, 0, 0, 0, 255, 0.5, 0.5));
        }
        break;
    default:
        page=0;
        PlayScene *scene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
        scene->MapId = 3;
        Engine::GameEngine::GetInstance().ChangeScene("play");
        break;
    }  
    
}

void plot3Scene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void plot3Scene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}