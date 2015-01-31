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
	void RenderWindow::SwitchDisplayMode(bool is_fullscreen) {
		//// windowed to full
		//if (enable) {
		//	if (!m_d3dpp.Windowed) {
		//		return ;
		//	}
		//	int width = GetSystemMetrics(SM_CXSCREEN);
		//	int height = GetSystemMetrics(SM_CYSCREEN);
		//	m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		//	m_d3dpp.BackBufferWidth = width;
		//	m_d3dpp.BackBufferHeight = height;
		//	m_d3dpp.Windowed = false;

		//	SetWindowLongPtr(m_hwnd, GWL_STYLE, WS_POPUP);
		//	SetWindowPos(m_hwnd, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
		//}
		//// full to windowed
		//else {
		//	if (m_d3dpp.Windowed) {
		//		return;
		//	}
		//	RECT R = {0, 0, 800, 600};
		//	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		//	m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		//	m_d3dpp.BackBufferWidth = R.right;
		//	m_d3dpp.BackBufferHeight = R.bottom;
		//	m_d3dpp.Windowed = true;

		//	SetWindowLongPtr(m_hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		//	SetWindowPos(m_hwnd, HWND_TOP, 100, 100, R.right, R.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
		//}
		//onLostDevice();
		//HR( g_pDevice9->Reset(&m_d3dpp) );
		//onResetDevice();
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

		//wc.style = CS_HREDRAW | CS_VREDRAW; 
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = MessageProcess;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hinstance_;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		//wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.hbrBackground = NULL;	
		wc.lpszMenuName = NULL;
		wc.lpszClassName = szAppName;
		if ( !RegisterClass(&wc) ) {
			throw(Exception("CreateRenderWindow() -> RegisterClass() failed!"));
		}
		RECT R = {0, 0, width_, height_};
		//AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		AdjustWindowRectEx(&R, WS_OVERLAPPEDWINDOW, false, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
		//hwnd_ = CreateWindow(
		//	szAppName,
		//	title_.c_str(),
		//	WS_OVERLAPPEDWINDOW|
		//	WS_CLIPCHILDREN|
		//	WS_CLIPSIBLINGS,
		//	0, 0,
		//	R.right, R.bottom,
		//	NULL,
		//	NULL,
		//	hinstance_,
		//	NULL);

		hwnd_ = CreateWindowEx(
			WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
			szAppName,
			title_.c_str(),
			WS_OVERLAPPEDWINDOW|
			WS_CLIPCHILDREN|
			WS_CLIPSIBLINGS,
			0, 0,
			R.right, R.bottom,
			NULL,
			NULL,
			hinstance_,
			NULL);

		if ( !hwnd_ ) {
			throw(Exception("CreateRenderWindow() -> CreateWindow() failed!"));
		}

	//	ShowWindow(hwnd_, SW_SHOW);
	//	UpdateWindow(hwnd_);		
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