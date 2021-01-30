#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"

#include <memory>

using namespace std;

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
	inline bool GetIsRunning() { return isRunning; };

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
};

#endif