//
// Created by Hsuan on 2024/4/10.
//
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "StartScene.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Scene/StartScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

std::map<std::string,std::string> StartScene::arr;
// TODO HACKATHON-2 (1/3): You can imitate the 2 files: 'StartScene.hpp', 'StartScene.cpp' to implement your SettingsScene.
void StartScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    s = "|";
    username="";
    password="";
    ticks = 0;
    Engine::ImageButton *btn;

    AddNewObject(new Engine::Image("city.jpg", halfW, halfH, w, h, 0.5, 0.5));

    AddNewObject(new Engine::Label("Pedestrian’s Inferno", "pirulen.ttf", 80, halfW, halfH / 3 , 25, 25, 112, 255, 0.5, 0.5));
    //loginbutton
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW - 200, halfH / 2 + 150, 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::LoginOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Login", "pirulen.ttf", 48, halfW, halfH / 2 + 200, 0, 0, 0, 255, 0.5, 0.5));
    
    //registerbutton
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW - 200, halfH * 3 / 2 -100, 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::RegisterOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("register", "pirulen.ttf", 48, halfW, halfH * 3 / 2-50, 0, 0, 0, 255, 0.5, 0.5));

    //settingbutton
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW - 200, halfH +280,400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Settings", "pirulen.ttf", 48, halfW, halfH+330, 0, 0, 0, 255, 0.5, 0.5));

    
    
    AddNewObject(LoginGroup = new Group());

    bgmInstance = AudioHelper::PlaySample("happy.ogg", true, AudioHelper::BGMVolume,5);
}

void StartScene::Draw() const {
    IScene::Draw();

}

void StartScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void StartScene::Update(float deltaTime) {
    IScene :: Update(deltaTime);

    ticks += deltaTime;
    //LoginGroup->Update(0);
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        //bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}

void StartScene::backOnClick(int stage) 
{
    popcontrolObject(1);
    popObject(2);
    LoginGroup->Clear();
}

void StartScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}

void StartScene::LoginOnClick(int stage) 
{
    mode=5;
    mode=1;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    LoginGroup->AddNewObject(new Engine::Image("scenes/login.png", 800, 400, 1400, 700, 0.5, 0.5));

    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW-200, halfH +220,400, 80);
    btn->SetOnClickCallback(std::bind(&StartScene::backOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("back", "pirulen.ttf", 48, halfW, halfH+260, 0, 0, 0, 255, 0.5, 0.5));
    LoginGroup->AddNewObject(new Engine::Label(s,"pirulen.ttf", 48, 970, 365, 0, 0, 0, 255, 0.5, 0.5));
   
}

void StartScene::RegisterOnClick(int stage) 
{
    mode=5;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    LoginGroup->AddNewObject(new Engine::Image("scenes/register.png", 800, 400, 1400, 700, 0.5, 0.5));
    btn = new Engine::ImageButton("scenes/buttonup.png", "scenes/buttondown.png", halfW-200, halfH +220,400, 80);
    btn->SetOnClickCallback(std::bind(&StartScene::backOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("back", "pirulen.ttf", 48, halfW, halfH+260, 0, 0, 0, 255, 0.5, 0.5));
    LoginGroup->AddNewObject(new Engine::Label(s,"pirulen.ttf", 48, 970, 365, 0, 0, 0, 255, 0.5, 0.5));
}

// void StartScene::OnMouseDown(int button, int mx, int my) 
// {
//     Group::OnKeyDown(button);
//     LoginGroup->OnMouseDown(button, mx, my);

// }
// void StartScene::OnMouseUp(int button, int mx, int my)
// {
//     Group::OnKeyUp(button);
//     LoginGroup->OnMouseUp(button, mx, my);
// }


void StartScene::OnKeyDown(int keyCode) 
{
    //std::cout << keyCode << std::endl;
    IScene::OnKeyDown(keyCode);
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    
    auto it =keycode_to_char.find(keyCode);
    if(it!=keycode_to_char.end() )
    {
        if(s=="|")
        {
            s=it->second;
        }
        else if(s.size()<12)
        {
            s.push_back(it->second);
        }

        if(mode==1 || mode==5)
        {
            LoginGroup->popObject(1);
            LoginGroup->AddNewObject(new Engine::Label(s,"pirulen.ttf", 48, 970, 365, 0, 0, 0, 255, 0.5, 0.5));
            LoginGroup->Update(0);
        }
        else if(mode==2|| mode==6)
        {
            LoginGroup->popObject(1);
            LoginGroup->AddNewObject(new Engine::Label(s,"pirulen.ttf", 48, 970, 530, 0, 0, 0, 255, 0.5, 0.5));
            LoginGroup->Update(0);
        }
    }
    else if(keyCode==67)
    {
        //typing=false;
        if(mode==1 || mode==5)
        {
            if(mode==1)
            {
                mode=2;
            }
            else
            {
                mode=6;
            }
            
            username=s;
            s="|";
            LoginGroup->popObject(1);
            LoginGroup->AddNewObject(new Engine::Label(username,"pirulen.ttf", 48, 970, 365, 0, 0, 0, 255, 0.5, 0.5));
            LoginGroup->AddNewObject(new Engine::Label(s,"pirulen.ttf", 48, 970, 530, 0, 0, 0, 255, 0.5, 0.5));
            LoginGroup->Update(0);
        }
        else if(mode==2|| mode==6)
        {
            password=s;
            s="|";
            LoginGroup->popObject(1);
            LoginGroup->AddNewObject(new Engine::Label(password,"pirulen.ttf", 48, 970, 530, 0, 0, 0, 255, 0.5, 0.5));
            LoginGroup->Update(0);
            if(mode==6)
            {
                arr.insert({username,password});
                mode=3;
                LoginGroup->AddNewObject(new Engine::Label("Register complete, Press enter to play","pirulen.ttf", 24, 800, 600, 0, 0, 0, 255, 0.5, 0.5));
            }
            else
            {
                auto it=arr.find(username);
                std::cout << arr.begin()->first << std::endl;
                std::cout << username << std::endl;
                if(it!=arr.end())
                {
                    mode=3;
                    LoginGroup->AddNewObject(new Engine::Label("Login complete, Press enter to play","pirulen.ttf", 24, 800, 600, 0, 0, 0, 255, 0.5, 0.5));
                }
                else
                {
                    mode=4;
                    LoginGroup->AddNewObject(new Engine::Label("Wrong username or password. Press the Enter key to re-enter","pirulen.ttf", 24, 800, 600, 0, 0, 0, 255, 0.5, 0.5));
                }
            }
        }
        else if(mode==3)
        {
            outputdata();
            Engine::GameEngine::GetInstance().ChangeScene("plot");
        }
        else if(mode==4)
        {
            LoginGroup->popObject(3);
            LoginGroup->AddNewObject(new Engine::Label(s,"pirulen.ttf", 48, 970, 365, 0, 0, 0, 255, 0.5, 0.5));
            mode=1;
        }
    }
    else if(keyCode==63)
    {
        s.pop_back();
        if(mode==1)
        {
            LoginGroup->popObject(1);
            LoginGroup->AddNewObject(new Engine::Label(s,"pirulen.ttf", 48, 970, 365, 0, 0, 0, 255, 0.5, 0.5));
            LoginGroup->Update(0);
        }
        else if(mode==2)
        {
            LoginGroup->popObject(1);
            LoginGroup->AddNewObject(new Engine::Label(s,"pirulen.ttf", 48, 970, 530, 0, 0, 0, 255, 0.5, 0.5));
            LoginGroup->Update(0);
        }
    }

     
   

}

void StartScene::inputdata()
{
    std::ifstream in("C:\\Users\\user\\OneDrive\\Desktop\\Final Project\\Resource\\account.txt");

    std::string name;
    std::string password;
    while(in >> name >> password)
    {
        arr.insert({name,password});
    }
    in.close();
}

void  StartScene::outputdata()
{
    std::ofstream out("C:\\Users\\user\\OneDrive\\Desktop\\Final Project\\Resource\\account.txt");
    for (auto &p : arr) 
    {
        out << p.first << " " << p.second << "\n"; 
    }
    out.close();
}

