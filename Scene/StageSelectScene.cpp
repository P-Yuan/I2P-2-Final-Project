#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

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

void StageSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;
    AddNewObject(new Engine::Image("city.jpg", halfW, halfH, w, h, 0.5, 0.5));
    AddNewObject(new Engine::Image("stage-select/vertical.png", halfW/2 +105, halfH, 0, 0, 0.5, 0.5));
    
    //stage1 button
    btn = new Engine::ImageButton("stage-select/right.png", "stage-select/right_down.png", halfW/2 +100, halfH / 3 - 50, 400, 130);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Hsinchu", "pirulen.ttf", 48, halfW/2 +290, halfH / 3 +10, 0, 0, 0, 255, 0.5, 0.5));

    // Scoreboard1 button
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW *3/2 -200 , halfH / 3 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::ScoreboardOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Hsinchu", "pirulen.ttf", 36, halfW *3/2 , halfH / 3 -20, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 36, halfW *3/2 , halfH / 3 +20, 0, 0, 0, 255, 0.5, 0.5));

    //stage2 button
    btn = new Engine::ImageButton("stage-select/left.png", "stage-select/left_down.png", halfW/2 - 240, halfH / 3 + 110, 360, 130);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Taipei", "pirulen.ttf", 48, halfW/2 -40, halfH / 3+170, 0, 0, 0, 255, 0.5, 0.5));

    // Scoreboard2 button
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW *3/2 -200, halfH / 3 + 110, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::ScoreboardOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Taipei", "pirulen.ttf", 36, halfW *3/2 , halfH / 3 + 140, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 36, halfW *3/2 , halfH / 3 + 180, 0, 0, 0, 255, 0.5, 0.5));

    //stage3 button
    btn = new Engine::ImageButton("stage-select/right.png", "stage-select/right_down.png", halfW/2 +100, halfH / 3 + 310, 400, 130);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Taichung", "pirulen.ttf", 48, halfW/2 +290, halfH / 3 + 370, 0, 0, 0, 255, 0.5, 0.5));

    // Scoreboard3 button
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW *3/2 -200, halfH / 3 + 310, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::ScoreboardOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Taichung", "pirulen.ttf", 36, halfW *3/2 , halfH / 3 + 340, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 36, halfW *3/2 , halfH / 3 + 380, 0, 0, 0, 255, 0.5, 0.5));

    //back button
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW *3/2 -200, halfH * 3 / 2 +50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::BackOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW *3/2, halfH * 3 / 2+100, 0, 0, 0, 255, 0.5, 0.5));

    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    //bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
    bgmInstance = AudioHelper::PlaySample("happy.ogg", true, AudioHelper::BGMVolume,5);
}
void StageSelectScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void StageSelectScene::BackOnClick() {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void StageSelectScene::PlayOnClick(int stage) {
    // PlayScene *scene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
    // scene->MapId = stage;
    // Engine::GameEngine::GetInstance().ChangeScene("play");
    std::string place;
    place = std::string("plot") + std::to_string(stage);
    Engine::GameEngine::GetInstance().ChangeScene(place);
}
void StageSelectScene::ScoreboardOnClick(int stage) {
    ScoreboardScene::storetovec(stage);
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard-scene");
}
void StageSelectScene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void StageSelectScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}

