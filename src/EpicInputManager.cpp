#include "include/EpicInputManager.h"
#include "include/EpicException.h"
namespace epic {
	InputManager::InputManager():
	hwnd_(0),
	directinput_(0),
	direct_mouse_(0),
	mouse_(0),
	mouse_cooperative_level_(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
	{
	}
	InputManager::~InputManager() {
		if (directinput_) {
			directinput_->Release();
			directinput_ = 0;
		}
	}
	void InputManager::Initialize(HWND hwnd) {
		HINSTANCE hinstance;
		HRESULT hresult;
		hwnd_ = hwnd;
		hinstance = GetModuleHandle(0);
		hresult = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, 
			IID_IDirectInput8, (void**)directinput_, NULL);
		if (FAILED(hresult)) {
			throw(Exception("Initialize() -> DirectInput8Create() failed!"));
		}
		InitMouse();
	}

	
	// Four basic steps to initializing Mouse :
	// 1. Create the device.
	// 2. Set the data format.
	// 3. Set the cooperative level.
	//   DISCL_FOREGROUND:运行设备接收前台数据，当窗口转变为时后台时，设备停止接收数据。
	//   DISCL_NONEXCLUSIVE:设备接收数据与其他应用程序不冲突。
	// 4. Acquire the device.
	//
	void InputManager::InitMouse() {
		if (FAILED(directinput_->CreateDevice(GUID_SysMouse, &direct_mouse_, NULL))) {
			throw(Exception("InitMouse() -> CreateDevice() failed!"));
		}
		if (FAILED(direct_mouse_->SetDataFormat(&c_dfDIMouse2))) {
			throw(Exception("InitMouse() -> SetDataFormat() failed!"));
		}
		if (FAILED(direct_mouse_->SetCooperativeLevel(hwnd_, mouse_cooperative_level_))) {
			throw(Exception("InitMouse() -> SetCooperativeLevel() failed!"));
		}
		if (FAILED(direct_mouse_->Acquire())) {
			throw(Exception("InitMouse() -> Acquire() failed!"));
		}
	}
} // epic