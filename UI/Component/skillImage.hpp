#ifndef TURRETBUTTON_HPP
#define TURRETBUTTON_HPP
#include <string>

#include "Engine/Sprite.hpp"
#include "UI/Component/ImageButton.hpp"

class PlayScene;

class skillImage :public Engine::Sprite {
protected:
    PlayScene *getPlayScene();

public:
    int money;
    // Engine::Sprite Base;
    // Engine::Sprite Turret;
    skillImage(std::string img, float x, float y, float w , float h ,std::string t);
    void Update(float deltaTime) ;
    void Draw() ;//const override;
    static bool useflag;
    std::string type;
};
#endif   // TURRETBUTTON_HPP
