#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>

class PlayScene;

class WinScene final : public Engine::IScene {
private:
    float ticks;
    ALLEGRO_SAMPLE_ID bgmId;
    Group *textGroup;
    static int wincoin;
    static std::string username;
    bool typing = true;

public:
    explicit WinScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void BackOnClick(int stage);
    void ScoreboardOnClick(int stage);
    //void OnKeyDown(int keyCode) override;
    void Draw() const override;
    static void storelives();
    
};

#endif   // WINSCENE_HPP
