//
// Created by Hsuan on 2024/4/10.
//

#ifndef INC_2025_I2P2_TOWERDEFENSE_WITH_ANSWER_STARTSCENE_H
#define INC_2025_I2P2_TOWERDEFENSE_WITH_ANSWER_STARTSCENE_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>


#include "Engine/IScene.hpp"
class StartScene final : public Engine::IScene {
private:
    std::unordered_map<int, char> keycode_to_char = {
    // A–Z → 'a'–'z'
    {ALLEGRO_KEY_A, 'a'}, {ALLEGRO_KEY_B, 'b'}, {ALLEGRO_KEY_C, 'c'},
    {ALLEGRO_KEY_D, 'd'}, {ALLEGRO_KEY_E, 'e'}, {ALLEGRO_KEY_F, 'f'},
    {ALLEGRO_KEY_G, 'g'}, {ALLEGRO_KEY_H, 'h'}, {ALLEGRO_KEY_I, 'i'},
    {ALLEGRO_KEY_J, 'j'}, {ALLEGRO_KEY_K, 'k'}, {ALLEGRO_KEY_L, 'l'},
    {ALLEGRO_KEY_M, 'm'}, {ALLEGRO_KEY_N, 'n'}, {ALLEGRO_KEY_O, 'o'},
    {ALLEGRO_KEY_P, 'p'}, {ALLEGRO_KEY_Q, 'q'}, {ALLEGRO_KEY_R, 'r'},
    {ALLEGRO_KEY_S, 's'}, {ALLEGRO_KEY_T, 't'}, {ALLEGRO_KEY_U, 'u'},
    {ALLEGRO_KEY_V, 'v'}, {ALLEGRO_KEY_W, 'w'}, {ALLEGRO_KEY_X, 'x'},
    {ALLEGRO_KEY_Y, 'y'}, {ALLEGRO_KEY_Z, 'z'},

    // 主鍵區數字鍵 0–9
    {ALLEGRO_KEY_0, '0'}, {ALLEGRO_KEY_1, '1'}, {ALLEGRO_KEY_2, '2'},
    {ALLEGRO_KEY_3, '3'}, {ALLEGRO_KEY_4, '4'}, {ALLEGRO_KEY_5, '5'},
    {ALLEGRO_KEY_6, '6'}, {ALLEGRO_KEY_7, '7'}, {ALLEGRO_KEY_8, '8'},
    {ALLEGRO_KEY_9, '9'},

    // 數字小鍵盤（NumPad）0–9
    {ALLEGRO_KEY_PAD_0, '0'}, {ALLEGRO_KEY_PAD_1, '1'}, {ALLEGRO_KEY_PAD_2, '2'},
    {ALLEGRO_KEY_PAD_3, '3'}, {ALLEGRO_KEY_PAD_4, '4'}, {ALLEGRO_KEY_PAD_5, '5'},
    {ALLEGRO_KEY_PAD_6, '6'}, {ALLEGRO_KEY_PAD_7, '7'}, {ALLEGRO_KEY_PAD_8, '8'},
    {ALLEGRO_KEY_PAD_9, '9'}
};
    float ticks;
    
public:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    static std::map<std::string,std::string> arr;
    Group *LoginGroup;
    explicit StartScene() = default;
    void Initialize() override;
    void Terminate() override;
    void backOnClick(int stage);
    void SettingsOnClick(int stage);
    void RegisterOnClick(int stage);
    void LoginOnClick(int mode);
    void downOnClick(int stage);
    void OnKeyDown(int keyCode)override;
    void Update(float deltaTime)override;
    void Draw() const override;
    static void inputdata();
    void outputdata();
    std::string s ; 
    std::string username ; 
    std::string password ; 
    int mode=0;
    // void OnMouseDown(int button, int mx, int my) override;
    // void OnMouseUp(int button, int mx, int my) override;
    //void OnMouseMove(int mx, int my) override;
};
#endif   // INC_2025_I2P2_TOWERDEFENSE_WITH_ANSWER_STARTSCENE_H
