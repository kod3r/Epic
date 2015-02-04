#include "include/EpicRoot.h"

#include <Windows.h>
#include "include/EpicRenderWindow.h"
#include "include/EpicRenderSystem.h"
#include "include/EpicGLRenderSystem.h"
#include "include/EpicD3D9RenderSystem.h"
#include "include/EpicSceneManager.h"

namespace epic {
	//Root::Root():
	//render_window_(NULL)
	//{
	//	InitSystem();
	//}
	Root::~Root(){
		if (render_window_) {
			delete render_window_;
			render_window_ = 0;
		}
		if (render_system_) {
			delete render_system_;
			render_system_ = 0;
		}
		if (scene_manager_) {
			delete scene_manager_;
			scene_manager_ = 0;
		}
	}
	Root::Root(RenderSystemType type, const char* title) {
		// 1. create render window
		render_window_ = new RenderWindow(GetModuleHandle(NULL));
		render_window_->CreateRenderWindow(title);
		//2. init render system
		if (type == RENDERSYSTEMTYPE_D3D9) {
			render_system_ = new D3D9RenderSystem();

		}else if (type == RENDERSYSTEMTYPE_OPENGL) {
			render_system_ = new GLRenderSystem(render_window_);
			resource_manager_ = render_system_->resource_manager();
		}
		render_system_->InitRender();
		// 3. init scene manager
		scene_manager_ = new SceneManager();
	}
	void Root::InitSystem(void) {
		
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
				scene_manager_->UpdateScene();
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