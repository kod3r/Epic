#ifndef EPIC_INCLUDE_EPICRENDERWINDOW_H
#define EPIC_INCLUDE_EPICRENDERWINDOW_H

#include "include/EpicPrerequisites.h"
#include "windows.h"
namespace epic {
	class EPIC_EXPORT RenderWindow {
	public:
		RenderWindow(HINSTANCE hinstance);
		~RenderWindow();
		void CreateRenderWindow(const String& title, 
						  bool is_fullscreen = false,
						  uint32 width = 800, 
						  uint32 height = 600);  
		static LRESULT CALLBACK
			MessageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		HWND hwnd() const { return hwnd_; }
	private:
		HINSTANCE hinstance_;
		HWND hwnd_;
		String title_;
		bool is_fullscreen_;
		uint32 width_;
		uint32 height_;
	}; // RenderWindow
} // epic

#endif // EPIC_INCLUDE_EPICRENDERWINDOW_H