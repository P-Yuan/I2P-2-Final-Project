#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include <string>
#include <set>
#include <fstream>
#include <vector>

#include "Engine/IScene.hpp"

class ScoreboardScene : public Engine::IScene {
private:
    struct scorenode
    {
        std::string name;
        std::string date;
        std::string timee;
        int scores;
        scorenode(){};
        scorenode(int c,std::string n,std::string date,std::string timee)
        {
            this->scores=c;
            this->name=n;
            this->date=date;
            this->timee=timee;
        }
    };
    struct mycompare
    {
        bool operator()(const scorenode &r,const scorenode &l)const
        {
            return r.scores>l.scores;
        }
    };
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    static std::vector<scorenode> arr;
    static int page;
    int textnum;
public:
    
    explicit ScoreboardScene()=default;
    void Initialize() override;
    void Terminate() override;
    void NextClick();
    void PrevClick();
    void BackOnClick();
    void printscore();
    static void storetovec(int stage);
    static void inputnewdata(int coin,std::string name,std::string date,std::string timee,int stage);
    // static void storetotxt();
    // static void inputtoset();
    
    

    void BGMSlideOnValueChanged(float value);
    void SFXSlideOnValueChanged(float value);
};

#endif   // SCOREBOARDSCENE_HPP
