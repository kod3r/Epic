#include "include/EpicRoot.h"

#include <Windows.h>
#include "include/EpicRenderWindow.h"

namespace epic {
	Root::Root():
	render_window_(NULL)
	{
		InitSystem();
	}
	Root::~Root(){
	}
	void Root::InitSystem(void) {
		render_window_ = new RenderWindow(GetModuleHandle(NULL));
		render_window_->CreateRenderWindow("Miaomi~");
	}
	void Root::StartRendering(void) {
		MSG msg;
		msg.message = WM_NULL;		
		while ( msg.message != WM_QUIT ) {
			while ( PeekMessage(&msg, 0, 0, 0, PM_REMOVE) ) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			{
			//	GameLogic();
			//	OnRendering();
			}
		}
	}
	template<> Root* Singleton<Root>::singleton_ = 0;
	Root& Root::GetInstance(void) {
		assert(singleton_);
		return *singleton_;
	}
	Root* Root::GetInstancePtr(void) {
		return singleton_;
	}
} // epic