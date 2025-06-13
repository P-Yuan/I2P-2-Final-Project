#include <functional>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "LoseScene.hpp"
#include "PlayScene.hpp"
#include "Engine/LOG.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"


void LoseScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    PlayScene * played = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
    if(played->GangHit){
        AddNewObject(new Engine::Image("lose/lai.png", halfW, halfH, w, h, 0.5, 0.5));
    }
    else{
        AddNewObject(new Engine::Image("lose/lose.png", halfW, halfH, w, h, 0.5, 0.5));
    }
    
    //AddNewObject(new Engine::Image("lose/bonk.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Lose :(", "pirulen.ttf", 56, halfW, halfH / 5 + 10, 25, 25, 112, 255, 0.5, 0.5));
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW *3/2 +40, halfH * 7 / 4 , 300, 80);
    btn->SetOnClickCallback(std::bind(&LoseScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW*3/2 +190, halfH * 7 / 4 +40, 0, 0, 0, 255, 0.5, 0.5));
    //bgmInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, PlayScene::DangerTime);

    if(played->GangHit==true){
        bgmInstance = AudioHelper::PlaySample("lailailai.ogg", false, AudioHelper::BGMVolume, 0);
    }
    else{
        bgmInstance = AudioHelper::PlaySample("tobecontinue.mp3", false, AudioHelper::BGMVolume, 3.755);
    }
}
void LoseScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void LoseScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
