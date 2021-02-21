#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>

#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"

#include "../Rendering/3D/GameObject.h"
#include "../Graphics/ShaderHandler.h"

using namespace std;
using namespace glm;

class CoreEngine
{
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	static CoreEngine* GetInstance();

	bool OnCreate(string name_, int width_, int height_);
	void Run();
	void Exit();

	inline bool GetIsRunning() const { return isRunning; };
	inline int GetCurrentScene() const { return currentSceneNum; };

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);

private:
	CoreEngine();
	~CoreEngine();

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static unique_ptr<CoreEngine> engineInstance;
	friend default_delete<CoreEngine>;

	Window* window;
	bool isRunning;
	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;
};

#endif