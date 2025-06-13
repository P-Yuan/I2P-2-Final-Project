#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "UI/Component/backgroundImage.hpp"
#include "UI/Component/skillImage.hpp"

class Turret;
namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
}   // namespace Engine

class PlayScene final : public Engine::IScene {
private:
    enum TileType {
        TILE_DIRT,
        TILE_FLOOR,
        TILE_OCCUPIED,
    };
    ALLEGRO_SAMPLE_ID bgmId;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;


protected:
    static int lives;
    static int money;
    int SpeedMult;

public:
    static bool DebugMode;
    static int backgroundflag;
    static const std::vector<Engine::Point> directions;
    static const int MapWidth, MapHeight;
    static const int BlockSize;
    static const float DangerTime;
    static const Engine::Point SpawnGridPoint;
    static const Engine::Point SpawnGridPoint_1;
    static const Engine::Point SpawnGridPoint_2;
    static const Engine::Point SpawnGridPoint_3;
    static const Engine::Point EndGridPoint;
    static const std::vector<int> code;
    std::vector<int> temp;
    bool planeflag;
    int MapId;
    float ticks;
    float ticks_coin;
    float deathCountDown;
    Engine::backgroundImage *back1;
    Engine::backgroundImage *back2;
    // Map tiles.
    Group *TileMapGroup;
    Group *GroundEffectGroup;
    Group *DebugIndicatorGroup;
    Group *BulletGroup;
    Group *TowerGroup;
    Group *EnemyGroup;
    Group *PlaneGroup;
    Group *backgroundGroup;
    Group *EffectGroup;
    Group *UIGroup;
    Group *PauseGroup;
    Group *PlayerGroup;
    Group *coinGroup;
    Group *timerGroup;
    // Group *coinGroup;
    Engine::Label *UIMoney;
    Engine::Label *UILives;
    Engine::Image *imgTarget;
    Engine::Sprite *dangerIndicator;
    Turret *preview;
    std::vector<std::vector<TileType>> mapState;
    std::vector<std::vector<int>> mapDistance;
    std::list<std::pair<int, float>> enemyWaveData;
    std::vector<std::vector<int>> enemyWaveData_new;
    std::list<std::pair<int, float>> coinWaveData;
    std::vector<std::vector<int>> coinWaveData_new;
    std::list<int> keyStrokes;
    static Engine::Point GetClientSize();
    explicit PlayScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnMouseDown(int button, int mx, int my) override;
    void OnMouseMove(int mx, int my) override;
    void OnMouseUp(int button, int mx, int my) override;
    void OnKeyDown(int keyCode) override;
    void Hit(int l);
    void full_lives(int l);
    static int GetMoney();
    static int Getlives();
    void EarnMoney(int money);
    void ReadMap();
    void ReadEnemyWave();
    // void ReadCoinWave();
    void ConstructUI();
    void UIBtnClicked(int id);
    bool CheckSpaceValid(int x, int y);
    void ShopOnClick();
    void coinOnClick();
    void hpOnClick();
    void gunOnClick();
    void superOnClick();
    void backOnClick();
    void nomoney();
    void pauseinit();
    std::vector<std::vector<int>> CalculateBFSDistance();
    bool pauseflag;
    bool pauseinitflag;
    bool doublecoinmode;
    bool DyingAnimation = false; // True when dying or winning animation is playing
    float DyingTimer;
    bool WinningAnimation = false; // True when dying or winning animation is playing
    float WinningTimer;
    static bool GangHit;
    bool goend = false;
};
#endif   // PLAYSCENE_HPP
 