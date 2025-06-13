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
    static int winlives;
    bool typing = true;

public:
    explicit WinScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void BackOnClick();
    void OnKeyDown(int keyCode) override;
    void Draw() const override;
    static void storelives();

    std::string s;
    std::string NEWs;
};

#endif   // WINSCENE_HPP
