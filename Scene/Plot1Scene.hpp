#ifndef PLOT1SCENE_HPP
#define PLOT1SCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include <string>
#include <set>
#include <fstream>
#include <vector>

#include "Engine/IScene.hpp"

class plot1Scene : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    static int page;
    
    enum place{
        START, Stage1, Stage2, Stage3
    };
public:
    
    explicit plot1Scene()=default;
    void Initialize() override;
    void Terminate() override;
    void NextClick(int choice);
    
    void BGMSlideOnValueChanged(float value);
    void SFXSlideOnValueChanged(float value);
};

#endif   // PLOT1SCENE_HPP
