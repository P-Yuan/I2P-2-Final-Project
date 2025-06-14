// #include <allegro5/base.h>
// #include <cmath>
// #include <string>

// #include "Bullet/Fireball.hpp"
// #include "Engine/AudioHelper.hpp"
// #include "Engine/Group.hpp"
// #include "Engine/Point.hpp"
// #include "FireTurret.hpp"
// #include "Scene/PlayScene.hpp"
// #include "Enemy/Enemy.hpp"

// const int FireTurret::Price = 400;
// FireTurret::FireTurret(float x, float y) : Turret("play/tower-base.png", "play/turret-fire.png", x, y, 300, Price, 10,"Fire") {
//     // Move center downward, since we the turret head is slightly biased upward.
//     Anchor.y += 8.0f / GetBitmapHeight();
//     attackflag=false;
// }
// void FireTurret::CreateBullet() {
//     Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
//     float rotation = atan2(diff.y, diff.x);
//     Engine::Point normalized = diff.Normalize();
//     Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
//     // Change bullet position to the front of the gun barrel.
//     getPlayScene()->BulletGroup->AddNewObject(new Fireball(Position + normalized * 36, diff, rotation, this));
//     //getPlayScene()->BulletGroup->AddNewObject(new Fireball(Position + normalized * 36 + normal * 6, diff, rotation, this));
//     AudioHelper::PlayAudio("fireball.wav");
// }

// void FireTurret::Update(float deltaTime) {
//     Sprite::Update(deltaTime);
//     PlayScene *scene = getPlayScene();
//     imgBase.Position = Position;
//     imgBase.Tint = Tint;
//     if (!Enabled)
//         return;
//     //偵測敵人是否在攻擊範圍內
//     if (Target) {
//         Engine::Point diff = Target->Position - Position;
//         if (diff.Magnitude() > CollisionRadius) {
//             Target->lockedTurrets.erase(lockedTurretIterator);
//             Target = nullptr;
//             lockedTurretIterator = std::list<Turret *>::iterator();
//         }
//     }
//     //抓取敵人位置
//     if (!Target) {
//         // Lock first seen target.
//         // Can be improved by Spatial Hash, Quad Tree, ...
//         // However simply loop through all enemies is enough for this program.
//         for (auto &it : scene->EnemyGroup->GetObjects()) {
//             Engine::Point diff = it->Position - Position;
//             if (diff.Magnitude() <= CollisionRadius) {
//                 Target = dynamic_cast<Enemy *>(it);
//                 Target->lockedTurrets.push_back(this);
//                 lockedTurretIterator = std::prev(Target->lockedTurrets.end());
//                 break;
//             }
//         }
//     }
//     if (Target) {
//         Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
//         Engine::Point targetRotation = (Target->Position - Position).Normalize();
//         float maxRotateRadian = rotateRadian * deltaTime;
//         float cosTheta = originRotation.Dot(targetRotation);
//         // Might have floating-point precision error.
//         if (cosTheta > 1) cosTheta = 1;
//         else if (cosTheta < -1) cosTheta = -1;
//         float radian = acos(cosTheta);
//         Engine::Point rotation;
//         if (abs(radian) <= maxRotateRadian)
//             rotation = targetRotation;
//         else
//             rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
//         // Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
//         Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
//         // Shoot reload.
//         reload -= deltaTime;
//         if (attackflag==false &&reload <= -1) {
//             // shoot.
//             reload = coolDown;
//             CreateBullet();
//             attackflag=true;
//         }
//         else if(attackflag==true && reload<=10)
//         {
//             Target->lockedTurrets.erase(lockedTurretIterator);
//             getPlayScene()->TowerGroup->RemoveObject(objectIterator);

//         }
        
        
//     }
// }
