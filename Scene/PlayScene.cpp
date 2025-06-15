#include <algorithm>
#include <allegro5/allegro.h>
#include <cmath>
#include <fstream>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>

#include "Player/Player.hpp"
#include "Player/Gang.hpp"
#include "Enemy/Enemy.hpp"
#include "Enemy/GrandmaEnemy.hpp"
#include "Enemy/CarEnemy.hpp"
#include "Enemy/GangEnemy.hpp" 
#include "Enemy/HoleEnemy.hpp" 
#include "Enemy/BikeEnemy.hpp"
#include "Enemy/TreeEnemy.hpp"
#include "Enemy/TruckEnemy.hpp"
#include "Enemy/gun.hpp"
#include "Enemy/coin.hpp"
#include "Enemy/Super.hpp"
#include "Enemy/Sign.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Engine/Sprite.hpp"
#include "PlayScene.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Scene/WinScene.hpp"
// #include "Turret/LaserTurret.hpp"
// #include "Turret/MachineGunTurret.hpp"
// #include "Turret/FireTurret.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/Plane.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/backgroundImage.hpp"
#include "UI/Component/skillImage.hpp"
#include "UI/Component/timer.hpp"

bool PlayScene::DebugMode = false;
// int PlayScene::backgroundflag = 1;
int PlayScene :: lives=0;
int PlayScene :: money=0;
float player_y_2=0;
float DyingTimer = 0.0f;
bool PlayScene :: GangHit = false;
std::string PlayScene ::username;

const std::vector<Engine::Point> PlayScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int PlayScene::MapWidth = 20, PlayScene::MapHeight = 13;
const int PlayScene::BlockSize = 64;
const float PlayScene::DangerTime = 7.61;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(1, 9);
const Engine::Point PlayScene::SpawnGridPoint_1 = Engine::Point(22, 7);
const Engine::Point PlayScene::SpawnGridPoint_2 = Engine::Point(22, 9);
const Engine::Point PlayScene::SpawnGridPoint_3 = Engine::Point(22, 11);
const Engine::Point PlayScene::EndGridPoint = Engine::Point(MapWidth, MapHeight - 1);
const std::vector<int> PlayScene::code = {
    ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN,
    ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT,
    ALLEGRO_KEY_B, ALLEGRO_KEY_A, ALLEGRO_KEY_LSHIFT, ALLEGRO_KEY_ENTER
};
Engine::Point PlayScene::GetClientSize() {
    return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}
void PlayScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    mapState.clear();
    keyStrokes.clear();
    planeflag=false;
    ticks = 0;
    ticks_coin=0;
    deathCountDown = -1;
    lives = 100;
    money = 150;
    SpeedMult = 1;
    pauseflag = false;
    pauseinitflag = false;
    WinningAnimation = false;
    DyingAnimation = false;
    WinningTimer = 0;
    DyingTimer = 0;
    //GangHit = false;
    doublecoinmode=false;
    goend=false;
    
    // Add groups from bottom to top.
    //AddNewObject(TileMapGroup = new Group());
    AddNewObject(backgroundGroup = new Group());
    AddNewObject(GroundEffectGroup = new Group());
    AddNewObject(DebugIndicatorGroup = new Group());
    
    //AddNewObject(TowerGroup = new Group());
    AddNewObject(EnemyGroup = new Group());
    AddNewObject(PlayerGroup = new Group());
    AddNewObject(BulletGroup = new Group());
    AddNewObject(EffectGroup = new Group());
    //AddNewObject(PlaneGroup = new Group());
    AddNewObject(coinGroup = new Group());
    // Should support buttons.
    AddNewControlObject(UIGroup = new Group());
    AddNewControlObject(PauseGroup = new Group());

    backgroundGroup->AddNewObject(new Engine::backgroundImage(std::string("play/road") + std::to_string(MapId) + ".png",1385,832,1));

    //ReadMap();
    ReadEnemyWave();
    // ReadCoinWave();
    //mapDistance = CalculateBFSDistance();
    ConstructUI();
    imgTarget = new Engine::Image("play/target.png", 0, 0);
    imgTarget->Visible = false;
    //preview = nullptr;
    UIGroup->AddNewObject(imgTarget);

    //Add player
    if(MapId==3)PlayerGroup->AddNewObject(new Gang("play/gang_walk1.png", 100, halfH / 2 +365, 50,0));
    PlayerGroup->AddNewObject(new Player("play/player_walk1.png", 300, halfH / 2 +365, 50,0,100,110));

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("play/7-11.png", "play/7-11b.png", 1410,710, 140, 80);
    btn->SetOnClickCallback(std::bind(&PlayScene::ShopOnClick, this));
    AddNewControlObject(btn);
   // AddNewObject(new Engine::Label("SHOP", "pirulen.ttf", 20, halfW+685, halfH +350, 0, 0, 0, 255, 0.5, 0.5));

    
    // Preload Lose Scene
    deathBGMInstance = Engine::Resources::GetInstance().GetSampleInstance("tobecontinue.mp3");
    // Start BGM.
    
    switch (MapId)
    {
    case 1:
        bgmId = AudioHelper::PlayBGM("music1.ogg");
        break;
    case 2:
        bgmId = AudioHelper::PlayBGM("music2.ogg");
        break;
    case 3:
        bgmId = AudioHelper::PlayBGM("music3.mp3");
        break;
    
    default:
        bgmId = AudioHelper::PlayBGM("music1.ogg");
        break;
    }    
}


void PlayScene::Terminate() {
    AudioHelper::StopBGM(bgmId);
    AudioHelper::StopSample(deathBGMInstance);
    deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void PlayScene::Update(float deltaTime) 
{
    if(pauseflag)
    {
        if(!pauseinitflag)
        {
            pauseinit();
            pauseinitflag=true;
        }
        else
        {
            PauseGroup->Update(deltaTime);
            if(PauseGroup->GetObjects().size()==0)
            {
                pauseflag=false;
                pauseinitflag=false;
            }
        }
        return;
    }
    
    if (DyingAnimation) {
        // Only update player and possibly effect/animation groups
        
        auto it = PlayerGroup->GetObjects().back();
        Player *player = dynamic_cast<Player *>(it);
        player->Dying(deltaTime);
        if(GangHit){
            it = PlayerGroup->GetObjects().front();
            Gang *gang = dynamic_cast<Gang *>(it);
            gang->Dying(deltaTime);
        }
        
        DyingTimer+=deltaTime;
        if (DyingTimer >= 3.75f) {
            AudioHelper::StopSample(deathBGMInstance);
            Engine::LOG(Engine::INFO)<<"end dying";
            Engine::LOG(Engine::INFO)<<"gang hit at lose:"<<GangHit;
            Engine::GameEngine::GetInstance().ChangeScene("lose");           
        }
            
        // Skip updating everything else
        return;
    }

    if (WinningAnimation) {
        // Only update player and possibly effect/animation groups
        
        auto it = PlayerGroup->GetObjects().back();
        Player *player = dynamic_cast<Player *>(it);
        player->Winning(deltaTime);
        EnemyGroup->Update(deltaTime);
        //backgroundGroup->Update(deltaTime);
        backgroundGroup->GetObjects().back()->Update(deltaTime);
        DyingTimer+=deltaTime;
        if (DyingTimer >= 3.0f) {
            AudioHelper::StopBGM(bgmId);
            Engine::LOG(Engine::INFO)<<"end winning";
            WinScene :: storelives();
            Engine::GameEngine::GetInstance().ChangeScene("win");           
        }
            
        // Skip updating everything else
        return;
    }
    // If we use deltaTime directly, then we might have Bullet-through-paper problem.
    // Reference: Bullet-Through-Paper
    if (SpeedMult == 0)
        deathCountDown = -1;
    else if (deathCountDown != -1)
        SpeedMult = 1;
    // Calculate danger zone.
    std::vector<float> reachEndTimes;
    for (auto &it : EnemyGroup->GetObjects()) {
        reachEndTimes.push_back(dynamic_cast<Enemy *>(it)->reachEndTime);
    }

    if (SpeedMult == 0)
        AudioHelper::StopSample(deathBGMInstance);
    if (deathCountDown == -1 && lives > 0) {
        AudioHelper::StopSample(deathBGMInstance);
        dangerIndicator->Tint.a = 0;
    }
    if (SpeedMult == 0)
        deathCountDown = -1;
    for (int i = 0; i < SpeedMult; i++) {
        IScene::Update(deltaTime);
        // Check if we should create new enemy.
        ticks += deltaTime;

        if (enemyWaveData_new.empty() ) { 
            if (EnemyGroup->GetObjects().empty() && !goend) {
                Engine::backgroundImage *it;
                backgroundGroup->AddNewObject(it=new Engine::backgroundImage("play/you_win.png",1380,385,2));
                goend = true;
                Engine::LOG(Engine::INFO)<<"goend";
                //WinningAnimation=true;
                //SpeedMult = 0; // freeze enemy bullets and movement

                Engine::Point SpawnCoordinate;
                SpawnCoordinate = Engine::Point(SpawnGridPoint_2.x * BlockSize + BlockSize , SpawnGridPoint_2.y * BlockSize );           
                std::string place = std::string("play/end") + std::to_string(MapId) + std::string(".png");
                coinGroup->AddNewObject(new Sign(SpawnCoordinate.x, SpawnCoordinate.y, 11, place));
                
            }
            continue;
        }

        auto current = enemyWaveData_new.front();
        if (ticks < current[1])
            continue;
        ticks -= current[1];

        Engine::Point SpawnCoordinate;
        Engine::Point SpawnCoordinate_coin;
        switch (current[2])
        {
        case 1:
            SpawnCoordinate = Engine::Point(SpawnGridPoint_1.x * BlockSize + BlockSize / 2, SpawnGridPoint_1.y * BlockSize );
            break;
        case 2:
            SpawnCoordinate = Engine::Point(SpawnGridPoint_2.x * BlockSize + BlockSize / 2, SpawnGridPoint_2.y * BlockSize );
            break;
        case 3:
            SpawnCoordinate = Engine::Point(SpawnGridPoint_3.x * BlockSize + BlockSize / 2, SpawnGridPoint_3.y * BlockSize );
            break;
        case 4:
            SpawnCoordinate = Engine::Point(SpawnGridPoint.x * BlockSize + BlockSize / 2, SpawnGridPoint.y * BlockSize );
            break;
        default:
            SpawnCoordinate = Engine::Point(SpawnGridPoint_1.x * BlockSize + BlockSize / 2, SpawnGridPoint_1.y * BlockSize );
            break;
        }
        enemyWaveData_new.erase(enemyWaveData_new.begin());
        
        Enemy *enemy;
        switch (current[0]) {
            case 1:
                EnemyGroup->AddNewObject(enemy = new HoleEnemy(SpawnCoordinate.x, SpawnCoordinate.y,1));
                break;
            case 2:
                EnemyGroup->AddNewObject(enemy = new TreeEnemy(SpawnCoordinate.x, SpawnCoordinate.y,2));
                break;
            case 3:
                EnemyGroup->AddNewObject(enemy = new BikeEnemy(SpawnCoordinate.x, SpawnCoordinate.y,3));
                break;
            case 4:
                EnemyGroup->AddNewObject(enemy = new GrandmaEnemy(SpawnCoordinate.x, SpawnCoordinate.y,4));
                break;
            case 5:
                EnemyGroup->AddNewObject(enemy = new TruckEnemy(SpawnCoordinate.x, SpawnCoordinate.y,5));
                break;
            case 6:
                EnemyGroup->AddNewObject(enemy = new CarEnemy(SpawnCoordinate.x, SpawnCoordinate.y,6));
                break;
            case 7:
                EnemyGroup->AddNewObject(enemy = new TankEnemy(SpawnCoordinate.x, SpawnCoordinate.y,3,7));
                break;
            case 8:
                coinGroup->AddNewObject(enemy = new Coin(SpawnCoordinate.x, SpawnCoordinate.y,8));
                break;
            case 9:
                coinGroup->AddNewObject(enemy = new Gun(SpawnCoordinate.x, SpawnCoordinate.y,9));
                break;
            case 10:
                coinGroup->AddNewObject(enemy = new Super(SpawnCoordinate.x, SpawnCoordinate.y,10));
                break;
            default:
                continue;
        }
        // Compensate the time lost.
        enemy->Update(ticks);
    }

    backgroundGroup->Update(deltaTime);
    BulletGroup->Update(deltaTime);


}
void PlayScene::Draw() const 
{
    IScene::Draw();
    if (DebugMode) {
        // Draw reverse BFS distance on all reachable blocks.
        for (int i = 0; i < MapHeight; i++) {
            for (int j = 0; j < MapWidth; j++) {
                if (mapDistance[i][j] != -1) {
                    // Not elegant nor efficient, but it's quite enough for debugging.
                    Engine::Label label(std::to_string(mapDistance[i][j]), "pirulen.ttf", 32, (j + 0.5) * BlockSize, (i + 0.5) * BlockSize);
                    label.Anchor = Engine::Point(0.5, 0.5);
                    label.Draw();
                }
            }
        }
    }
}

void PlayScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    if (keyCode == ALLEGRO_KEY_TAB) 
    {
        DebugMode = !DebugMode;
    }

    if(keyCode == ALLEGRO_KEY_UP || keyCode == ALLEGRO_KEY_DOWN){
        for(auto& it:PlayerGroup->GetObjects()){
            //Engine::LOG(Engine::INFO)<<"one player up/down";
            Player *player = dynamic_cast<Player *>(it);
            player->OnKeyDown(keyCode);
        }
        
    }
    else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
        // Hotkey for Speed up.
        SpeedMult = keyCode - ALLEGRO_KEY_0;
    }
    
}
void PlayScene::Hit(int l) {
    lives-=l;
    if(lives<=0) lives=0;
    UILives->Text = std::string("Life ") + std::to_string(lives);
    if (lives <= 0) {
        // When losing
        DyingAnimation = true;
        SpeedMult = 0; // freeze enemy bullets and movement
        AudioHelper::StopBGM(bgmId);
        deathBGMInstance = AudioHelper::PlaySample("tobecontinue.mp3", false, AudioHelper::BGMVolume,0);
    }
}
int PlayScene::GetMoney() {
    return money;
}
int PlayScene::Getlives() {
    return lives;
}
std::string PlayScene::Getusername() {
    return username;
}
void PlayScene::EarnMoney(int money) {
        this->money += money;
        UIMoney->Text = std::string("$") + std::to_string(this->money);
    
}

void PlayScene::ReadEnemyWave() {
    std::string filename = std::string("Resource/enemy")+ std::to_string(MapId) + ".txt";
    // Read enemy file.
    float type, wait, repeat, line;
    enemyWaveData.clear();
    enemyWaveData_new.clear();
    std::ifstream fin(filename);
    while (fin >> type && fin >> wait && fin >> repeat && fin>>line) {
        for (int i = 0; i < repeat; i++){
            std::vector<int> oneEnemy;
            oneEnemy.emplace_back(type);
            oneEnemy.emplace_back(wait);
            oneEnemy.emplace_back(line);
            enemyWaveData_new.emplace_back(oneEnemy);
        }
            //enemyWaveData.emplace_back(type, wait);
            
    }
    fin.close();
}

void PlayScene::ConstructUI() {
    // Background
    UIGroup->AddNewObject(new Engine::Image("play/skillboard.png", 1352, 0, 250, 840 ,0,0.01));
    // Text
    switch(MapId)
    {
        case 1:
            UIGroup->AddNewObject(new Engine::Label("Hsinchu", "pirulen.ttf", 25, 1200, 20));
            UIGroup->AddNewObject(new Engine::Image("play/landmark.png", 1072, -10, 200,100 ,0,0.01));
            break;
        case 2:
            UIGroup->AddNewObject(new Engine::Label("Taipei", "pirulen.ttf", 25, 1250, 20));
            UIGroup->AddNewObject(new Engine::Image("play/landmark.png", 1122, -10, 200,100 ,0,0.01));
            break;
        case 3:
            UIGroup->AddNewObject(new Engine::Label("Taichung", "pirulen.ttf", 25, 1180, 20));
            UIGroup->AddNewObject(new Engine::Image("play/landmark.png", 1052, -10, 200,100 ,0,0.01));
            break;
    }

    UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(money), "pirulen.ttf", 24, 1410, 45));
    UIGroup->AddNewObject(UILives = new Engine::Label(std::string("Life ") + std::to_string(lives), "pirulen.ttf", 24, 1410, 80));

    skillImage *btn;
    //GUN

    UIGroup->AddNewObject(new skillImage("play/gun.png","gun",1480,220,100,100));
    //UIGroup->AddNewObject(new Engine::Sprite("play/gun.png.png",1480,250, 100, 100, 0, 0,0,0,0,0, 0, 0, 160));
    UIGroup->AddNewObject(new Timer("play/timer (1).png", 1480,220, 220,200,"gun"));

    //SUPER
    UIGroup->AddNewObject(new skillImage("play/super.png","super",1480,410,200,100));
    UIGroup->AddNewObject(new Timer("play/timer (1).png", 1480,410, 220,200,"super"));

    UIGroup->AddNewObject(new skillImage("play/shop_coin.png","double_coin",1480,600,95,95));
    UIGroup->AddNewObject(new Timer("play/timer (1).png", 1480,600, 220,200,"double_coin"));


    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int shift = 135 + 25;
    dangerIndicator = new Engine::Sprite("play/benjamin.png", w - shift, h - shift);
    dangerIndicator->Tint.a = 0;
    UIGroup->AddNewObject(dangerIndicator);
}

void PlayScene::ShopOnClick()
{
    pauseflag=true;
}
