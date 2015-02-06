#include <Windows.h>
#include <iostream>
#include "EpicFramework.h"
#include "include/EpicException.h"
#include "include/EpicRoot.h"
#include "include/EpicRenderWindow.h"

int WINAPI
	WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) 
{
	try {
		EpicFramework* app = new EpicFramework(epic::RENDERSYSTEMTYPE_OPENGL);
		//EpicFramework* app = new EpicFramework(epic::RENDERSYSTEMTYPE_D3D9);
		app->StartRenderLoop();
	}
	catch(const epic::Exception& e) {
	//	std::cerr << e.what() << std::endl;
		MessageBox(epic::Root::GetInstancePtr()->render_window()->hwnd(),
				   e.what(), "Error", MB_OKCANCEL | MB_ICONERROR);
		exit(0);
	}
	return 0;
}