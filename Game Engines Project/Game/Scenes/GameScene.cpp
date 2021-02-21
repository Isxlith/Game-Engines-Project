#include "GameScene.h"

GameScene::GameScene() : shape(nullptr) {}

GameScene::~GameScene()
{
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	Debug::Info("Creating GameScene", "GameScene.cpp", __LINE__);

	// Triangle 1
	Vertex v;
	vector<Vertex> vertexList;
	vertexList.reserve(3);

	v.pos = vec3(-0.5f, 0.5f, 0.0f);
	v.colour = vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);
	v.pos = vec3(0.5f, 0.5f, 0.0f);
	v.colour = vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);
	v.pos = vec3(-0.5f, -0.5f, 0.0f);
	v.colour = vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);

	Model* model = new Model(ShaderHandler::GetInstance()->GetShader("colourShader"));
	model->AddMesh(new Mesh(vertexList));

	// Triagle 2
	v.pos = vec3(0.5f, -0.5f, 0.0f);
	v.colour = vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);
	v.pos = vec3(0.5f, 0.5f, 0.0f);
	v.colour = vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);
	v.pos = vec3(-0.5f, -0.5f, 0.0f);
	v.colour = vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);

	model->AddMesh(new Mesh(vertexList));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{

}

void GameScene::Render()
{
	shape->Render();
}