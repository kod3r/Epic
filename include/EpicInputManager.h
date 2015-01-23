#ifndef EPIC_INCLUDE_EPICINPUTMANAGER_H
#define EPIC_INCLUDE_EPICINPUTMANAGER_H

#include "include/EpicPrerequisites.h"
#include <Windows.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace epic {
	class EPIC_EXPORT InputManager {
	public:
		InputManager();
		~InputManager();
		HWND hwnd() const { return hwnd_; }
	protected:
		void Initialize(HWND hwnd);
		void InitMouse();
	private:
		HWND hwnd_; // window handle
		IDirectInput8* directinput_;
		IDirectInputDevice8* direct_mouse_;
		Mouse* mouse_;
		DWORD mouse_cooperative_level_;
	}; // InputManager
} // epic

#endif // EPIC_INCLUDE_EPICINPUTMANAGER_H