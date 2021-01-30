#include "Engine/Core/CoreEngine.h"

int main(int argc, char* argv[])
{
	if (!CoreEngine::GetInstance()->OnCreate("Game 258 Engines", 800, 600))
	{
		cout << "Engine failed to initialize" << endl;
		return 0;
	}

	CoreEngine::GetInstance()->Run();
	return 0;
}