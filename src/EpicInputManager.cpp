#include "include/EpicInputManager.h"
#include "include/EpicException.h"
namespace epic {
	InputManager::InputManager():
	hwnd_(0),
	directinput_(0)
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
			throw(Exception("DirectInput8Create() failed!"));
		}
	}
} // epic