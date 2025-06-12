#ifndef TURRETBUTTON_HPP
#define TURRETBUTTON_HPP
#include <string>

#include "Engine/IControl.hpp"
#include "Image.hpp"
#include "Engine/Sprite.hpp"

class PlayScene;

class skillImage :public Engine::Sprite {
protected:
    PlayScene *getPlayScene();

public:

    int money;
    // Engine::Sprite Base;
    // Engine::Sprite Turret;
    skillImage(std::string img, std::string t,float x, float y, float w , float h );
    void Update(float deltaTime) override;
    void Draw() const override;
    bool useflag;
    std::string type;
};
#endif   // TURRETBUTTON_HPP
