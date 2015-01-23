#include "include/EpicRenderWindow.h"
#include "include/EpicException.h"

namespace epic {
	RenderWindow::RenderWindow(HINSTANCE hinstance):
	hinstance_(hinstance),
	hwnd_(0),
	is_fullscreen_(false),
	width_(800),
	height_(600)
	{
	}

	RenderWindow::~RenderWindow() {
	}

	void RenderWindow::CreateRenderWindow(
		const String& title, 
		bool is_fullscreen,
		uint32 width, 
		uint32 height)
	{
		/* 1. 初始化参数 */
		is_fullscreen_ = is_fullscreen;
		width_ = width;
		height_ = height;
		title_ = title;
		/* 2. 初始化窗口类 */
		WNDCLASS wc;
		char szAppName[] = "EpicEngine";

		wc.style = CS_HREDRAW | CS_VREDRAW; 
		wc.lpfnWndProc = MessageProcess;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hinstance_;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = szAppName;
		if ( !RegisterClass(&wc) ) {
			throw(Exception("CreateRenderWindow() -> RegisterClass() failed!"));
		}
		RECT R = {0, 0, width_, height_};
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		hwnd_ = CreateWindow(
			szAppName,
			title_.c_str(),
			WS_OVERLAPPEDWINDOW,
			0, 0,
			R.right, R.bottom,
			NULL,
			NULL,
			hinstance_,
			NULL);

		if ( !hwnd_ ) {
			throw(Exception("CreateRenderWindow() -> CreateWindow() failed!"));
		}

		ShowWindow(hwnd_, SW_SHOW);
		UpdateWindow(hwnd_);		
	}

	LRESULT CALLBACK
		RenderWindow::MessageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg) {
		case WM_ACTIVATE:
			return 0;
		case WM_SIZE:
			return 0;
		case WM_EXITSIZEMOVE:
			return 0;
		case WM_KEYDOWN:
			return 0;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

} // epic