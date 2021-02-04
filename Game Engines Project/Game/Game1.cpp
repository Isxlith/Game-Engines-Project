#include "Game1.h"

Game1::Game1() : GameInterface() {}

Game1::~Game1()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate()
{
	// Sets the first scene to the start scene
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0)
	{
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Debug::Error("Engine's scene is not initialized to 0", "Game1.cpp", __LINE__);
	return false;
}

void Game1::Update(const float deltaTime_)
{
	// Calls build scene if the scene number and scene aren't the same
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene())
	{
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render()
{
	currentScene->Render();
}

void Game1::BuildScene()
{
	// Deletes the current scene before creating a new one
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene())
	{
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate())
	{
		Debug::Error("Failed to create scene", "Game1.cpp", __LINE__);
		CoreEngine::GetInstance()->Exit();
	}
}