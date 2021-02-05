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

	v.pos = vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.pos = vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.pos = vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	// Triagle 2
	Vertex v2;
	vector<Vertex> vertexList2;

	v2.pos = vec3(0.5f, -0.5f, 0.0f);
	vertexList2.push_back(v2);
	v2.pos = vec3(0.5f, 0.5f, 0.0f);
	vertexList2.push_back(v2);
	v2.pos = vec3(-0.5f, -0.5f, 0.0f);
	vertexList2.push_back(v2);

	Model* model = new Model();
	model->AddMesh(new Mesh(vertexList));
	model->AddMesh(new Mesh(vertexList2));
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