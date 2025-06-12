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
#include "Plot2Scene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

int plot2Scene::page;

void plot2Scene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    std::string s;
    Engine::ImageButton *btn1,*btn2;
    page=1;

    AddNewObject(new Engine::Image("scenes/textbox_back.png", halfW, halfH, w, h, 0.5, 0.5));
    AddNewObject(new Engine::Image("play/people1.png", halfW-500, halfH+200, 240, 200, 0.5, 0.5));

    //Next button1
    btn1 = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW /2, halfH/4 , 800, 80);
    btn1->SetOnClickCallback(std::bind(&plot2Scene::NextClick, this, 1));
    AddNewControlObject(btn1);
    
    //next button2
    btn2 = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW /2, halfH/4 + 150 , 800, 80);
    btn2->SetOnClickCallback(std::bind(&plot2Scene::NextClick, this, 2));
    AddNewControlObject(btn2);

    
    AddNewObject(new Engine::Label("台北的街道真是繁忙呢 !", "IMing.ttf", 40, halfW +100, halfH* 3/2 -80, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("車子好多喔 !", "IMing.ttf", 40, halfW +100, halfH* 3/2 -20, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("是啊 ! 無時無刻都要小心車子喔 !", "IMing.ttf", 30, halfW, halfH/2 -50 -15, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("你有看到新聞嗎? 一定要注意車子喔 !", "IMing.ttf", 30, halfW , halfH/2 + 100 -15, 0, 0, 0, 255, 0.5, 0.5));

    bgmInstance = AudioHelper::PlaySample("happy.ogg", true, AudioHelper::BGMVolume,5);
}




void plot2Scene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void plot2Scene::NextClick(int choice) {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    page++;
    switch (page)
    {
    case 2:
        popObject(4);
        AddNewObject(new Engine::Label("沒問題 ! 我們趕緊出發吧 !", "IMing.ttf", 40, halfW +100, halfH* 3/2 -80, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("我已經迫不急待要走九遍忠孝東路了", "IMing.ttf", 40, halfW +100, halfH* 3/2 -20, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("哈哈哈~  那我們出發吧 !", "IMing.ttf", 30, halfW, halfH/2 -50 -15, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("你剛失戀喔?", "IMing.ttf", 30, halfW, halfH/2 +100 -15, 0, 0, 0, 255, 0.5, 0.5));
        break;
    case 3:
        if(choice==1){
            page=0;
            PlayScene *scene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
            scene->MapId = 2;
            Engine::GameEngine::GetInstance().ChangeScene("play");
        }
        else{
            popObject(5);
            AddNewObject(new Engine::Label("......", "IMing.ttf", 40, halfW +100, halfH* 3/2 -50, 0, 0, 0, 255, 0.5, 0.5));
            AddNewObject(new Engine::Label("哈哈哈~  那我們出發吧 !", "IMing.ttf", 30, halfW, halfH/2 -50 -15, 0, 0, 0, 255, 0.5, 0.5));
        }
        break;
    default:
        page=0;
        PlayScene *scene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
        scene->MapId = 2;
        Engine::GameEngine::GetInstance().ChangeScene("play");
        break;
    }  
    
}

void plot2Scene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void plot2Scene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}