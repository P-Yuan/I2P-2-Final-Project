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
#include "Turret/LaserTurret.hpp"
#include "Turret/MachineGunTurret.hpp"
#include "Turret/FireTurret.hpp"
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
    money = 10;
    SpeedMult = 1;
    pauseflag = false;
    pauseinitflag = false;
    WinningAnimation = false;
    DyingAnimation = false;
    WinningTimer = 0;
    DyingTimer = 0;
    GangHit = false;
    
    // Add groups from bottom to top.
    //AddNewObject(TileMapGroup = new Group());
    AddNewObject(backgroundGroup = new Group());
    AddNewObject(GroundEffectGroup = new Group());
    AddNewObject(DebugIndicatorGroup = new Group());
    
    AddNewObject(TowerGroup = new Group());
    AddNewObject(EnemyGroup = new Group());
    AddNewObject(PlayerGroup = new Group());
    AddNewObject(BulletGroup = new Group());
    AddNewObject(EffectGroup = new Group());
    AddNewObject(PlaneGroup = new Group());
    AddNewObject(coinGroup = new Group());
    // Should support buttons.
    AddNewControlObject(UIGroup = new Group());
    AddNewControlObject(PauseGroup = new Group());

    //backgroundGroup->AddNewObject(new Engine::backgroundImage("play/Taichung_color.png",1280,385,1));
    //backgroundGroup->AddNewObject(new Engine::backgroundImage(std::string("play/background") + std::to_string(MapId) + ".png",1280,385,1));
    backgroundGroup->AddNewObject(new Engine::backgroundImage(std::string("play/road") + std::to_string(MapId) + ".png",1385,832,1));

    ReadMap();
    ReadEnemyWave();
    // ReadCoinWave();
    mapDistance = CalculateBFSDistance();
    ConstructUI();
    imgTarget = new Engine::Image("play/target.png", 0, 0);
    imgTarget->Visible = false;
    preview = nullptr;
    UIGroup->AddNewObject(imgTarget);

    //Add player
    //if(MapId==3)
    PlayerGroup->AddNewObject(new Gang("play/gang_walk1.png", 100, halfH / 2 +365, 50,0));
    PlayerGroup->AddNewObject(new Player("play/player_walk1.png", 300, halfH / 2 +365, 50,0,100,110));

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW+500, halfH / 2 +500, 200, 100);
    btn->SetOnClickCallback(std::bind(&PlayScene::ShopOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("SHOP", "pirulen.ttf", 30, halfW+600, halfH / 2 +550, 0, 0, 0, 255, 0.5, 0.5));

    
    // Preload Lose Scene
    deathBGMInstance = Engine::Resources::GetInstance().GetSampleInstance("astronomia.ogg");
    Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
    // Start BGM.
    bgmId = AudioHelper::PlayBGM("play.ogg");
}


void PlayScene::Terminate() {
    AudioHelper::StopBGM(bgmId);
    AudioHelper::StopSample(deathBGMInstance);
    deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void PlayScene::Update(float deltaTime) 
{
    if (DyingAnimation) {
        // Only update player and possibly effect/animation groups
        
        auto &it = PlayerGroup->GetObjects().back();
        Player *player = dynamic_cast<Player *>(it);
        player->Dying(deltaTime);
        if(GangHit){
            it = PlayerGroup->GetObjects().front();
            Gang *gang = dynamic_cast<Gang *>(it);
            gang->Dying(deltaTime);
        }
        
        DyingTimer+=deltaTime;
        if (DyingTimer >= 4.0f) {
            Engine::LOG(Engine::INFO)<<"end dying";
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
        backgroundGroup->Update(deltaTime);
        DyingTimer+=deltaTime;
        if (DyingTimer >= 3.0f) {
            Engine::LOG(Engine::INFO)<<"end winning";
            Engine::GameEngine::GetInstance().ChangeScene("win");           
        }
            
        // Skip updating everything else
        return;
    }

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
        }
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
    // Can use Heap / Priority-Queue instead. But since we won't have too many enemies, sorting is fast enough.
    std::sort(reachEndTimes.begin(), reachEndTimes.end());
    float newDeathCountDown = -1;
    int danger = lives;
    for (auto &it : reachEndTimes) {
        if (it <= DangerTime) {
            danger--;
            if (danger <= 0) {
                // Death Countdown
                float pos = DangerTime - it;
                if (it > deathCountDown) {
                    // Restart Death Count Down BGM.
                    AudioHelper::StopSample(deathBGMInstance);
                    if (SpeedMult != 0)
                        deathBGMInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, pos);
                }
                float alpha = pos / DangerTime;
                alpha = std::max(0, std::min(255, static_cast<int>(alpha * alpha * 255)));
                dangerIndicator->Tint = al_map_rgba(255, 255, 255, alpha);
                newDeathCountDown = it;
                break;
            }
        }   
    }
    deathCountDown = newDeathCountDown;

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
        // ticks_coin+=deltaTime;
        // if (enemyWaveData.empty()) { 
        //     if (EnemyGroup->GetObjects().empty()) {
        //         WinScene :: storelives();
        //         Engine::GameEngine::GetInstance().ChangeScene("win");
        //     }
        //     continue;
        // }
        if (enemyWaveData_new.empty()) { 
            if (EnemyGroup->GetObjects().empty()) {
                Engine::backgroundImage *it;
                backgroundGroup->AddNewObject(it=new Engine::backgroundImage("play/you_win.png",1280,385,2));
                //WinScene :: storelives();
                //Engine::GameEngine::GetInstance().ChangeScene("win");
                WinningAnimation=true;
                SpeedMult = 0; // freeze enemy bullets and movement
                AudioHelper::StopBGM(bgmId);
                // WinScene :: storelives();
                // Engine::GameEngine::GetInstance().ChangeScene("win");
            }
            continue;
        }
        //auto current = enemyWaveData.front();
        // if (ticks < current.second)
        //     continue;
        // ticks -= current.second;
        //enemyWaveData.pop_front();
        //Engine::Point SpawnCoordinate = Engine::Point(SpawnGridPoint.x * BlockSize + BlockSize / 2, SpawnGridPoint.y * BlockSize + BlockSize / 2);
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

    if (preview) {
        preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
        // To keep responding when paused.
        preview->Update(deltaTime);
    }
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
void PlayScene::OnMouseDown(int button, int mx, int my) {
    if ((button & 1) && !imgTarget->Visible && preview) {
        // Cancel turret construct.
        UIGroup->RemoveObject(preview->GetObjectIterator());
        preview = nullptr;
    }
    IScene::OnMouseDown(button, mx, my);
}
void PlayScene::OnMouseMove(int mx, int my) {
    IScene::OnMouseMove(mx, my);
    const int x = mx / BlockSize;
    const int y = my / BlockSize;
    if (!preview || x < 0 || x >= MapWidth || y < 0 || y >= MapHeight) {
        imgTarget->Visible = false;
        return;
    }
    imgTarget->Visible = true;
    imgTarget->Position.x = x * BlockSize;
    imgTarget->Position.y = y * BlockSize;
}
void PlayScene::OnMouseUp(int button, int mx, int my) {
    IScene::OnMouseUp(button, mx, my);
    if (!imgTarget->Visible)
        return;
    const int x = mx / BlockSize;
    const int y = my / BlockSize;
    if (button & 1) {
        if (mapState[y][x] != TILE_OCCUPIED) {
            if (!preview)
                return;
            // Check if valid.

            if(preview->type=="Fire")
            {
                if (CheckSpaceValid(x, y)) 
                {
                    Engine::Sprite *sprite;
                    GroundEffectGroup->AddNewObject(sprite = new DirtyEffect("play/target-invalid.png", 1, x * BlockSize + BlockSize / 2, y * BlockSize + BlockSize / 2));
                    sprite->Rotation = 0;
                    return;
                }

            }
            else
            {
                if (!CheckSpaceValid(x, y)) 
                {
                    Engine::Sprite *sprite;
                    GroundEffectGroup->AddNewObject(sprite = new DirtyEffect("play/target-invalid.png", 1, x * BlockSize + BlockSize / 2, y * BlockSize + BlockSize / 2));
                    sprite->Rotation = 0;
                    return;
                }

            }
            
            
            // Purchase.
            EarnMoney(-preview->GetPrice());
            // Remove Preview.
            preview->GetObjectIterator()->first = false;
            UIGroup->RemoveObject(preview->GetObjectIterator());
            // Construct real turret.
            preview->Position.x = x * BlockSize + BlockSize / 2;
            preview->Position.y = y * BlockSize + BlockSize / 2;
            preview->Enabled = true;
            preview->Preview = false;
            preview->Tint = al_map_rgba(255, 255, 255, 255);
            TowerGroup->AddNewObject(preview);
            // To keep responding when paused.
            preview->Update(0);
            // Remove Preview.
           
            if(preview->type=="Fire")
            {
                mapState[y][x] = TILE_DIRT;
            }
            else
            {
                mapState[y][x] = TILE_OCCUPIED;
            }
             preview = nullptr;
            OnMouseMove(mx, my);
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
        
        // auto it = PlayerGroup->GetObjects().back();
        // Player *player = dynamic_cast<Player *>(it);
        // player->OnKeyDown(keyCode);
        // it = PlayerGroup->GetObjects().front();
        // player = dynamic_cast<Player *>(it);
        // player->OnKeyDown(keyCode);
        for(auto& it:PlayerGroup->GetObjects()){
            Engine::LOG(Engine::INFO)<<"one player up/down";
            Player *player = dynamic_cast<Player *>(it);
            player->OnKeyDown(keyCode);
        }
        
    }
    else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
        // Hotkey for Speed up.
        SpeedMult = keyCode - ALLEGRO_KEY_0;
    }

    // else if(keyCode == ALLEGRO_KEY_A || keyCode == ALLEGRO_KEY_B || keyCode == ALLEGRO_KEY_UP || keyCode == ALLEGRO_KEY_DOWN || keyCode == ALLEGRO_KEY_LEFT || keyCode == ALLEGRO_KEY_RIGHT || keyCode == ALLEGRO_KEY_LSHIFT ||keyCode == ALLEGRO_KEY_ENTER )
    // {
    //     temp.push_back(keyCode);
    // } 
    
    // else if (keyCode == ALLEGRO_KEY_Q) {
    //     // Hotkey for MachineGunTurret.
    //     UIBtnClicked(0);
    // } 
    // else if (keyCode == ALLEGRO_KEY_W) {
    //     // Hotkey for LaserTurret.
    //     UIBtnClicked(1);
    // }
    
    
    // else 
    // {
    //     keyStrokes.push_back(keyCode);
    //     if (keyStrokes.size() > code.size())
    //         keyStrokes.pop_front();
    // }

    // int l =temp.size();
    // int addflag=0;
    // for(int i=0;i<l;i++)
    // {
    //     if(code[i]!=temp[i])
    //     {
    //         temp.clear();
    //         break;
    //     }
    // }
    // if(l==code.size() && planeflag)
    // {
    //     temp.clear();
    //     EarnMoney(10000);
    //     Plane *newplane=new Plane();
    //     PlaneGroup->AddNewObject(newplane);
    // }
    
}
void PlayScene::Hit(int l) {
    lives-=l;
    UILives->Text = std::string("Life ") + std::to_string(lives);
    if (lives <= 0) {
        // When losing
        DyingAnimation = true;
        SpeedMult = 0; // freeze enemy bullets and movement
        AudioHelper::StopBGM(bgmId);
        AudioHelper::PlayAudio("lose.wav");
    }
}
int PlayScene::GetMoney() {
    return money;
}
int PlayScene::Getlives() {
    return lives;
}
void PlayScene::EarnMoney(int money) {
        this->money += money;
        UIMoney->Text = std::string("$") + std::to_string(this->money);
    
}
void PlayScene::ReadMap() {
    std::string filename = std::string("Resource/map") + std::to_string(1) + ".txt";
    // Read map file.
    char c;
    std::vector<bool> mapData;
    std::vector<int> roadData;
    std::ifstream fin(filename);
    while (fin >> c) {
        switch (c) {
            // case '0': mapData.push_back(false); break;
            // case '1': mapData.push_back(true); break;
            case '0': roadData.push_back(0); break;
            case '1': roadData.push_back(1); break;
            case '2': roadData.push_back(2); break;
            case '3': roadData.push_back(3); break;
            case '\n':
            case '\r':
                if (static_cast<int>(mapData.size()) / MapWidth != 0)
                    throw std::ios_base::failure("Map data is corrupted.");
                break;
            default: throw std::ios_base::failure("Map data is corrupted.");
        }
    }
    fin.close();
    // Validate map data.
    // if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
    //     throw std::ios_base::failure("Map data is corrupted.");
    if (static_cast<int>(roadData.size()) != MapWidth * MapHeight)
        throw std::ios_base::failure("Map data is corrupted.");
    // Store map in 2d array.
    mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
    for (int i = 0; i < MapHeight; i++) {
        for (int j = 0; j < MapWidth; j++) {
            // const int num = mapData[i * MapWidth + j];
            // mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
            const int num = roadData[i * MapWidth + j];
            mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
            if (num){
                if(num==1){
                    //TileMapGroup->AddNewObject(new Engine::Image("play/floor.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
                }
                if(num==2){
                    //TileMapGroup->AddNewObject(new Engine::Image("play/floor_line_up.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
                }
                if(num==3){
                    //TileMapGroup->AddNewObject(new Engine::Image("play/floor_line_down.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
                }
            }
            else{}
                //TileMapGroup->AddNewObject(new Engine::Image("play/dirt.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
        }
    }
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
    UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "pirulen.ttf", 32, 1294, 0));
    UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(money), "pirulen.ttf", 24, 1294, 48));
    UIGroup->AddNewObject(UILives = new Engine::Label(std::string("Life ") + std::to_string(lives), "pirulen.ttf", 24, 1294, 88));

    skillImage *btn;
    // Timer *timer;

    //GUN


    UIGroup->AddNewObject(new skillImage("play/gun.png","gun",1480,250,100,100));
    //UIGroup->AddNewObject(new Engine::Sprite("play/gun.png.png",1480,250, 100, 100, 0, 0,0,0,0,0, 0, 0, 160));
    UIGroup->AddNewObject(new Timer("play/timer (1).png", 1480,250, 220,200,"gun"));

    //SUPER
    UIGroup->AddNewObject(new skillImage("play/super.png","super",1480,450,200,100));
    UIGroup->AddNewObject(new Timer("play/timer (1).png", 1480,450, 220,200,"super"));
    // Engine::Sprite("play/tower-base.png", 1294, 136, 100, 100, 0, 0),
    //                        Engine::Sprite(, 1294, 136 - 8, 75, 75, 0, 0), 1294, 136, MachineGunTurret::Price,"machine");
    // Reference: Class Member Function Pointer and std::bind.
    //btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 0));
    //AddNewObject(btn);
    //UIGroup->AddNewObject(new Engine::Label("$50", "pirulen.ttf", 15, 1320, 210, 0, 0, 0, 255, 0.5, 0.5));



    // // Button 2
    // btn = new TurretButton("play/floor.png", "play/dirt.png",
    //                        Engine::Sprite("play/tower-base.png", 1370, 136, 0, 0, 0, 0),
    //                        Engine::Sprite("play/turret-2.png", 1370, 136 - 8, 0, 0, 0, 0), 1370, 136, LaserTurret::Price,"laser");
    // btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 1));
    // UIGroup->AddNewControlObject(btn);
    //  UIGroup->AddNewObject(new Engine::Label("$200", "pirulen.ttf", 15, 1396, 210, 0, 0, 0, 255, 0.5, 0.5));
    // //Button 3
    // btn = new TurretButton("play/floor.png", "play/dirt.png",
    //                        Engine::Sprite("play/tower-base.png", 1446, 136, 0, 0, 0, 0),
    //                        Engine::Sprite("play/turret-fire.png", 1446, 143 - 8, 0, 0, 0, 0), 1446, 136, FireTurret::Price,"fire");
    // btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 2));
    // UIGroup->AddNewControlObject(btn);
    //  UIGroup->AddNewObject(new Engine::Label("$400", "pirulen.ttf", 15, 1472, 210, 0, 0, 0, 255, 0.5, 0.5));
    // //Buttonheart
    // btn = new TurretButton("play/floor.png", "play/dirt.png",
    //                        Engine::Sprite("play/tower-base.png", 1294, 236, 0, 0, 0, 0),
    //                        Engine::Sprite("play/heart.png", 1294, 236, 0, 0, 0, 0), 1294, 236, 0,"heart");
    // btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 3));
    // UIGroup->AddNewControlObject(btn);
    // UIGroup->AddNewObject(new Engine::Label("$50", "pirulen.ttf", 15, 1320, 310, 0, 0, 0, 255, 0.5, 0.5));
    // //Imageplane
    // UIGroup->AddNewObject(new Engine::Sprite("play/plane.png", 1370, 236, 0, 0, 0, 0,0,0,0,0, 0, 0, 160));
    
    // btn = new TurretButton("play/floor.png", "play/dirt.png",
    //                        Engine::Sprite("play/tower-base.png", 1370, 236, 0, 0, 0, 0),
    //                        Engine::Sprite("play/heart.png", 1370, 236, 0, 0, 0, 0), 1370, 236, 0,0);
    // btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 4));
    // UIGroup->AddNewControlObject(btn);
    // UIGroup->AddNewObject(new Engine::Label("$50", "pirulen.ttf", 15, 1320, 310, 0, 0, 0, 255, 0.5, 0.5));


    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int shift = 135 + 25;
    dangerIndicator = new Engine::Sprite("play/benjamin.png", w - shift, h - shift);
    dangerIndicator->Tint.a = 0;
    UIGroup->AddNewObject(dangerIndicator);
}

void PlayScene::UIBtnClicked(int id) {
    if (preview)
        UIGroup->RemoveObject(preview->GetObjectIterator());
    if (id == 0 && money >= MachineGunTurret::Price)
        preview = new MachineGunTurret(0, 0);
    else if (id == 1 && money >= LaserTurret::Price)
        preview = new LaserTurret(0, 0);
    else if (id == 2 && money >= FireTurret::Price)
        preview = new FireTurret(0, 0);
    else if(id==3)
    {
        Hit(-1);
        EarnMoney(-50);
    }
    else
    {
        int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
        int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
        int shift = 135 + 25;
        Engine::Sprite *sprite;
        AddNewObject(sprite = new DirtyEffect("play/nomoney.png", 3,  w - shift, h - shift-200 ));
        sprite->Rotation = 0;

    }
    if (!preview)
        return;
    preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
    preview->Tint = al_map_rgba(255, 255, 255, 200);
    preview->Enabled = false;
    preview->Preview = true;
    UIGroup->AddNewObject(preview);
    OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);
}

bool PlayScene::CheckSpaceValid(int x, int y) {
    if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight)
        return false;
    auto map00 = mapState[y][x];
    mapState[y][x] = TILE_OCCUPIED;
    std::vector<std::vector<int>> map = CalculateBFSDistance();
    mapState[y][x] = map00;
    if (map[0][0] == -1)
        return false;
    for (auto &it : EnemyGroup->GetObjects()) {
        Engine::Point pnt;
        pnt.x = floor(it->Position.x / BlockSize);
        pnt.y = floor(it->Position.y / BlockSize);
        if (pnt.x < 0) pnt.x = 0;
        if (pnt.x >= MapWidth) pnt.x = MapWidth - 1;
        if (pnt.y < 0) pnt.y = 0;
        if (pnt.y >= MapHeight) pnt.y = MapHeight - 1;
        if (map[pnt.y][pnt.x] == -1)
            return false;
    }
    // All enemy have path to exit.
    mapState[y][x] = TILE_OCCUPIED;
    mapDistance = map;
    for (auto &it : EnemyGroup->GetObjects())
        dynamic_cast<Enemy *>(it)->UpdatePath(mapDistance);
    return true;
}
std::vector<std::vector<int>> PlayScene::CalculateBFSDistance() {
    // Reverse BFS to find path.
    std::vector<std::vector<int>> map(MapHeight, std::vector<int>(std::vector<int>(MapWidth, -1)));
    std::queue<Engine::Point> que;
    // Push end point.
    // BFS from end point.
    if (mapState[MapHeight - 1][MapWidth - 1] != TILE_DIRT)
        return map;
    que.push(Engine::Point(MapWidth - 1, MapHeight - 1));
    map[MapHeight - 1][MapWidth - 1] = 0;

    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    while (!que.empty()) {
        Engine::Point p = que.front();
        que.pop();
        // TODO -1 (1/1): Implement a BFS starting from the most right-bottom block in the map.
        //                For each step you should assign the corresponding distance to the most right-bottom block.
        //                mapState[y][x] is TILE_DIRT if it is empty.
        int x = p.x;
        int y = p.y;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < MapWidth && ny >= 0 && ny < MapHeight && mapState[ny][nx] == TILE_DIRT && map[ny][nx] == -1) {
                map[ny][nx] = map[y][x] + 1;
                que.push(Engine::Point(nx, ny));
            }
        }
    }
    return map;
}
