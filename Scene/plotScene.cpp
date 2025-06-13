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
#include "StartScene.hpp"
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

    //AddNewObject(new Engine::Image("city.jpg", halfW, halfH, w, 1040, 0.5, 0.6));
    AddNewObject(new Engine::Image("city.jpg", halfW, halfH, w, h, 0.5, 0.5));
    AddNewObject(new Engine::Image("scenes/start_board.png", halfW, halfH-100, 800, 400, 0.5, 0.5));

    //text
    AddNewObject(new Engine::Label("前方有位国际美人(X)  國際友人", "IMing.ttf", 36, halfW, halfH /2 , 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("他想要去新竹、台北、台中玩", "IMing.ttf", 36, halfW, halfH /2 +70, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("但是路上遇到了重重障礙", "IMing.ttf", 36, halfW, halfH /2 +140, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("可以請你幫助他嗎?", "IMing.ttf", 36, halfW, halfH /2 +210, 0, 0, 0, 255, 0.5, 0.5));

    //Next button
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW /2 , halfH *3/2 , 800, 80);
    btn->SetOnClickCallback(std::bind(&plotScene::NextClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("可以", "IMing.ttf", 36, halfW, halfH *3/2 +40, 0, 0, 0, 255, 0.5, 0.5));

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
    switch (page)
    {
    case 2:
        popObject(7);
        AddNewObject(new Engine::Image("scenes/textbox_back.png", halfW, halfH, w, h, 0.5, 0.5));
        AddNewObject(new Engine::Image("play/people1.png", halfW-500, halfH+200, 240, 200, 0.5, 0.5));

        Engine::ImageButton *btn;
        btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW /2, halfH/4 +100, 800, 80);
        btn->SetOnClickCallback(std::bind(&plotScene::NextClick, this));
        AddNewControlObject(btn);
        AddNewObject(new Engine::Label("你好，迪亞哥", "IMing.ttf", 36, halfW, halfH /2 +40, 0, 0, 0, 255, 0.5, 0.5));

        AddNewObject(new Engine::Label("你好，我是迪亞哥", "IMing.ttf", 40, halfW +100, halfH* 3/2 -50 , 0, 0, 0, 255, 0.5, 0.5));
        break;
    case 3:
        popObject(2);
        AddNewObject(new Engine::Label("是啊! 非常危險", "IMing.ttf", 36, halfW, halfH /2 +40, 0, 0, 0, 255, 0.5, 0.5));

        AddNewObject(new Engine::Label("路上不僅有障礙物", "IMing.ttf", 40, halfW +100, halfH* 3/2 -80, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("還有機車、電動車以及飆速的轎車", "IMing.ttf", 40, halfW +100, halfH* 3/2 -20, 0, 0, 0, 255, 0.5, 0.5));
        break;
    case 4:
        popObject(3);
        AddNewObject(new Engine::Label("也可以隨時在商店購買喔", "IMing.ttf", 36, halfW, halfH /2 +40, 0, 0, 0, 255, 0.5, 0.5));

        AddNewObject(new Engine::Label("雖然我手上拿著台中朋友的伴手禮", "IMing.ttf", 40, halfW +100, halfH* 3/2 -120, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("但好像只是裝飾的作用", "IMing.ttf", 40, halfW +100, halfH* 3/2 -70, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("如果可以在路上撿到真貨", "IMing.ttf", 40, halfW +100, halfH* 3/2 -20, 0, 0, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label("我就可以展現真正的技術了", "IMing.ttf", 40, halfW +100, halfH* 3/2 +30, 0, 0, 0, 255, 0.5, 0.5));
        break;
    case 5:
        popObject(5);
        AddNewObject(new Engine::Label("話不多說，我們直接出發吧!", "IMing.ttf", 36, halfW, halfH /2 +40, 0, 0, 0, 255, 0.5, 0.5));

        AddNewObject(new Engine::Label("台灣的便利商店真是太方便了!", "IMing.ttf", 40, halfW +100, halfH* 3/2 -50, 0, 0, 0, 255, 0.5, 0.5));
        break;     
    default:
        page=0;
        Engine::GameEngine::GetInstance().ChangeScene("stage-select");
        break;
    }  
    
}

void plotScene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void plotScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}