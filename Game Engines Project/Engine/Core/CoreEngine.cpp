#include "CoreEngine.h"

unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), isRunning(false) {}

CoreEngine::~CoreEngine() {}

CoreEngine* CoreEngine::GetInstance()
{
	if (engineInstance.get() == nullptr)
	{
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

bool CoreEngine::OnCreate(string name_, int width_, int height_)
{
	window = new Window();
	if (!window->OnCreate(name_, width_, height_))
	{
		cout << "Failed to initialize window" << endl;
		OnDestroy();
		return isRunning = false;
	}
	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning)
	{
		Update(0.016f);
		Render();
	}
	OnDestroy();
}

void CoreEngine::Update(const float deltaTime_)
{

}

void CoreEngine::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()
{
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}