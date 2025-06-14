#ifndef PLOT3SCENE_HPP
#define PLOT3SCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include <string>
#include <set>
#include <fstream>
#include <vector>

#include "Engine/IScene.hpp"

class plot3Scene : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    static int page;
    
    enum place{
        START, Stage1, Stage2, Stage3
    };
public:
    
    explicit plot3Scene()=default;
    void Initialize() override;
    void Terminate() override;
    void NextClick(int choice);
    
};

#endif   // PLOT3SCENE_HPP
