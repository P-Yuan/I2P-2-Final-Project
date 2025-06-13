//
// Created by Hsuan on 2024/4/10.
//

#include "StartScene.hpp"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Scene/StartScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

// TODO HACKATHON-2 (1/3): You can imitate the 2 files: 'StartScene.hpp', 'StartScene.cpp' to implement your SettingsScene.
void StartScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    AddNewObject(new Engine::Image("city.jpg", halfW, halfH, w, h, 0.5, 0.5));

    AddNewObject(new Engine::Label("Pedestrian’s Inferno", "pirulen.ttf", 80, halfW, halfH / 3 + 50, 25, 25, 112, 255, 0.5, 0.5));
    //playbutton
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW - 200, halfH / 2 + 200, 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Play", "pirulen.ttf", 48, halfW, halfH / 2 + 250, 0, 0, 0, 255, 0.5, 0.5));
    //settingbutton
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Settings", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    //loginbutton
    // btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW-400, halfH / 2 + 250, 400, 100);
    // btn->SetOnClickCallback(std::bind(&StartScene::LoginOnClick, this, 1));
    // AddNewControlObject(btn);
    // AddNewObject(new Engine::Label("Login", "pirulen.ttf", 48, halfW-400, halfH / 2 + 250, 0, 0, 0, 255, 0.5, 0.5));
    // //registerbutton
    // btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    // btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 2));
    // AddNewControlObject(btn);
    // AddNewObject(new Engine::Label("Settings", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    // //guestlogin
}
void StartScene::Terminate() {
    IScene::Terminate();
}
void StartScene::PlayOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("plot");
}
void StartScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}

void StartScene::LoginOnClick(int stage) {
    AddNewObject(new Engine::Image("scenes/login.png", 500, 500, 1200, 800, 0.5, 0.5));
}