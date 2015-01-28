#include "include/EpicRoot.h"

#include <Windows.h>
#include "include/EpicRenderWindow.h"
#include "include/EpicRenderSystem.h"
#include "include/EpicGLRenderSystem.h"

namespace epic {
	Root::Root():
	render_window_(NULL)
	{
		InitSystem();
	}
	Root::~Root(){
	}
	Root::Root(RenderSystemType type) {
		if (type == RenderSystemType::D3D9Render) {

		}else if (type == RenderSystemType::OpenGLRender) {
			//render_system_ = new GLRenderSystem();
		}
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