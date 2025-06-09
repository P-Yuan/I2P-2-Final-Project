#ifndef PLOTSCENE_HPP
#define PLOTSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include <string>
#include <set>
#include <fstream>
#include <vector>

#include "Engine/IScene.hpp"

class plotScene : public Engine::IScene {
private:
    struct scorenode
    {
        std::string name;
        std::string date;
        std::string timee;
        int scores;
        scorenode(){};
        scorenode(int lives,std::string name,std::string date,std::string timee)
        {
            this->scores=lives;
            this->name=name;
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
    
    explicit plotScene()=default;
    void Initialize() override;
    void Terminate() override;
    void NextClick();
    void PrevClick();
    void BackOnClick();
    void printscore();
    static void storetovec(int lives,std::string name,std::string date,std::string timee);
    static void storetotxt();
    static void inputtoset();
    
    

    void BGMSlideOnValueChanged(float value);
    void SFXSlideOnValueChanged(float value);
};

#endif   // PLOTSCENE_HPP
