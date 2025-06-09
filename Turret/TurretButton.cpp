#include <allegro5/color.h>

#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "TurretButton.hpp"

PlayScene *TurretButton::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
TurretButton::TurretButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Turret, float x, float y, int money,std::string type) : ImageButton(img, imgIn, x, y), money(money), Base(Base), Turret(Turret),type(type) {
    if(type=="heart" || type=="machine")
    {
        useflag=true;
    }
    else
    {
        useflag=false;
    }
    
}
void TurretButton::Update(float deltaTime) {
    ImageButton::Update(deltaTime);
    if (useflag) {
        Enabled = true;
        Base.Tint = Turret.Tint = al_map_rgba(255, 255, 255, 255);
    } else {
        Enabled = false;
        Base.Tint = Turret.Tint = al_map_rgba(0, 0, 0, 160);
    }
}
void TurretButton::Draw() const {
    ImageButton::Draw();
    Base.Draw();
    Turret.Draw();
}
