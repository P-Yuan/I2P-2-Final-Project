// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/StartScene.hpp"
#include "Scene/SettingsScene.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Scene/plotScene.hpp"
#include "Scene/Plot1Scene.hpp"
#include "Scene/Plot2Scene.hpp"
#include "Scene/Plot3Scene.hpp"

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

    // TODO HACKATHON-2 (2/3): Register Scenes here
    game.AddNewScene("stage-select", new StageSelectScene());
	game.AddNewScene("start", new StartScene());
	game.AddNewScene("settings", new SettingsScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());
	game.AddNewScene("scoreboard-scene", new ScoreboardScene());
	game.AddNewScene("plot", new plotScene());
	game.AddNewScene("plot1", new plot1Scene());
	game.AddNewScene("plot2", new plot2Scene());
	game.AddNewScene("plot3", new plot3Scene());

	ScoreboardScene :: inputtoset();

    // TODO HACKATHON-1 (1/1): Change the start scene
	game.Start("start", 60, 1600, 832);
	return 0;
}
