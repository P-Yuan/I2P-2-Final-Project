#include <allegro5/base.h>
#include <allegro5/color.h>
#include <random>

#include "DirtyEffect.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"

PlayScene *DirtyEffect::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
DirtyEffect::DirtyEffect(std::string img, float timeSpan, float x, float y) : Sprite(img, x, y), timeSpan(timeSpan*0.1), alpha(1) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(-ALLEGRO_PI, ALLEGRO_PI);
    Rotation = dist(rng);
}
void DirtyEffect::Update(float deltaTime) {
    alpha -= deltaTime / timeSpan;
    if (alpha <= 0) {
        getPlayScene()->GroundEffectGroup->RemoveObject(objectIterator);
        return;
    }
    unsigned char r, g, b, a = alpha * 255;
    al_unmap_rgb(Tint, &r, &g, &b);
    Tint = al_map_rgba(r, g, b, a);
    Sprite::Update(deltaTime);
}
