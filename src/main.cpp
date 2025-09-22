#include "CoreSystem.hpp"

using namespace std;

int main(int argc, char* args[])
{
	CoreSystem::Instance()->Init();
	
	while (CoreSystem::Instance()->running)
	{
		CoreSystem::Instance()->Update();
		CoreSystem::Instance()->Render();
		CoreSystem::Instance()->CheckEvents();
	}
	
	CoreSystem::Instance()->Quit();
	
	return 0;
}