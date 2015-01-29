#include "EpicFramework.h"
#include <Windows.h>

int WINAPI
	WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) 
{
	EpicFramework* app = new EpicFramework(epic::RENDERSYSTEMTYPE_OPENGL);
	app->StartRenderLoop();
	return 0;
}