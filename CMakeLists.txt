cmake_minimum_required(VERSION 3.27)
project(2025_I2P2_TowerDefense)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Resource)

file(COPY Resource/audios DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY allegro_monolith-5.2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(2025_I2P2_TowerDefense
    Bullet/Bullet.cpp
    Bullet/Bullet.hpp
    Bullet/Fireball.cpp
    Bullet/Fireball.hpp
    Bullet/FireBullet.cpp
    Bullet/FireBullet.hpp
    Bullet/LaserBullet.cpp
    Bullet/LaserBullet.hpp
    Bullet/TankBullet.cpp
    Bullet/TankBullet.hpp

    # TODO HACKATHON-3 (3/3): Add the new enemy source files here
    Enemy/Enemy.cpp
    Enemy/Enemy.hpp
    Enemy/GrandmaEnemy.cpp
    Enemy/GrandmaEnemy.hpp
    Enemy/CarEnemy.cpp
    Enemy/CarEnemy.hpp
    Enemy/GangEnemy.cpp
    Enemy/GangEnemy.hpp
    Enemy/HoleEnemy.cpp
    Enemy/HoleEnemy.hpp
    Enemy/BikeEnemy.cpp
    Enemy/BikeEnemy.hpp
    Enemy/TreeEnemy.cpp
    Enemy/TreeEnemy.hpp
    Enemy/TruckEnemy.cpp
    Enemy/TruckEnemy.hpp
    Enemy/gun.cpp
    Enemy/gun.hpp
    Enemy/coin.cpp
    Enemy/coin.hpp
    Enemy/Super.cpp
    Enemy/Super.hpp
    Enemy/Sign.cpp
    Enemy/Sign.hpp

    Engine/Allegro5Exception.cpp
    Engine/Allegro5Exception.hpp
    Engine/AudioHelper.cpp
    Engine/AudioHelper.hpp
    Engine/Collider.cpp
    Engine/Collider.hpp
    Engine/GameEngine.cpp
    Engine/GameEngine.hpp
    Engine/Group.cpp
    Engine/Group.hpp
    Engine/IControl.cpp
    Engine/IControl.hpp
    Engine/IObject.cpp
    Engine/IObject.hpp
    Engine/IScene.cpp
    Engine/IScene.hpp
    Engine/LOG.cpp
    Engine/LOG.hpp
    Engine/Point.cpp
    Engine/Point.hpp
    Engine/Resources.cpp
    Engine/Resources.hpp
    Engine/Sprite.cpp
    Engine/Sprite.hpp
    
    Player/Player.cpp
    Player/Player.hpp
    Player/Gang.cpp
    Player/Gang.hpp

    Scene/LoseScene.cpp
    Scene/LoseScene.hpp
    Scene/PlayScene.cpp
    Scene/PlayScene.hpp
    Scene/StageSelectScene.cpp
    Scene/StageSelectScene.hpp
    Scene/StartScene.cpp
    Scene/StartScene.hpp
    Scene/ScoreboardScene.cpp
    Scene/ScoreboardScene.hpp
    Scene/SettingsScene.cpp
    Scene/SettingsScene.hpp
    Scene/WinScene.cpp
    Scene/WinScene.hpp
    Scene/plotScene.cpp
    Scene/plotScene.hpp
    Scene/Plot1Scene.cpp
    Scene/Plot1Scene.hpp
    Scene/Plot2Scene.cpp
    Scene/Plot2Scene.hpp
    Scene/Plot3Scene.cpp
    Scene/Plot3Scene.hpp
    Scene/pausefunc.cpp

    UI/Animation/DirtyEffect.cpp
    UI/Animation/DirtyEffect.hpp
    UI/Animation/ExplosionEffect.cpp
    UI/Animation/ExplosionEffect.hpp
    UI/Animation/Plane.cpp
    UI/Animation/Plane.hpp

    UI/Component/backgroundImage.cpp
    UI/Component/backgroundImage.hpp
    UI/Component/Image.cpp
    UI/Component/Image.hpp
    UI/Component/ImageButton.cpp
    UI/Component/ImageButton.hpp
    UI/Component/Label.cpp
    UI/Component/Label.hpp
    UI/Component/Slider.cpp
    UI/Component/Slider.hpp
    UI/Component/skillImage.cpp
    UI/Component/skillImage.hpp
    UI/Component/timer.cpp
    UI/Component/timer.hpp
    
    main.cpp
)

IF (WIN32)
    target_include_directories(2025_I2P2_TowerDefense PUBLIC C:/allegro/include)
    target_link_directories(2025_I2P2_TowerDefense PUBLIC C:/allegro/lib)
    target_compile_options(2025_I2P2_TowerDefense PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2025_I2P2_TowerDefense liballegro_monolith)
ELSE()
    find_package(PkgConfig)
    pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
    target_include_directories(2025_I2P2_TowerDefense PUBLIC lib)
    target_include_directories(2025_I2P2_TowerDefense PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
    target_compile_options(2025_I2P2_TowerDefense PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2025_I2P2_TowerDefense ${ALLEGRO5_LIBRARIES})
    target_link_directories(2025_I2P2_TowerDefense PUBLIC ${ALLEGRO5_LIBRARY_DIRS})
ENDIF()