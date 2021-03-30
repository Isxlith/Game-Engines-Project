#include "GameScene.h"

GameScene::GameScene() : shape(nullptr) {}

GameScene::~GameScene()
{
	model = nullptr;

	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	Debug::Info("Creating GameScene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPos(vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->addLightSource(vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, vec3(1.0f, 1.0f, 1.0f));
	
	//TextureHandler::GetInstance()->CreateTexture("CheckerboardTexture", "./Resources/Textures/CheckerboardTexture.png");

	model = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	//model->SetScale(vec3(0.5));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	shape->Update(deltaTime_);
}

void GameScene::Render()
{
	shape->Render(CoreEngine::GetInstance()->GetCamera());
}