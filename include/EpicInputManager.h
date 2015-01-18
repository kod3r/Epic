#ifndef EPIC_INCLUDE_EPICINPUTMANAGER_H
#define EPIC_INCLUDE_EPICINPUTMANAGER_H

#include "include/EpicPrerequisites.h"
#include <Windows.h>
#include <dinput.h>
#define DIRECTINPUT_VERSION 0x0800

namespace epic {
	class EPIC_EXPORT InputManager {
	public:
		InputManager();
		~InputManager();
		HWND hwnd() const { return hwnd_; }
	protected:
		void Initialize(HWND hwnd);
	private:
		HWND hwnd_; // window handle
		IDirectInput8* directinput_;
	}; // InputManager
} // epic

#endif // EPIC_INCLUDE_EPICINPUTMANAGER_H