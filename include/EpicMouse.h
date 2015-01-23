#ifndef EPIC_INCLUDE_EPICMOUSE_H
#define EPIC_INCLUDE_EPICMOUSE_H

#include "include/EpicPrerequisites.h"

namespace epic {
	class EPIC_EXPORT MouseListener {
	public:
		MouseListener(){}
		virtual ~MouseListener(){}
		virtual bool MousePressed() = 0;
	}; // MouseListener

	class EPIC_EXPORT Mouse {
	public:
		Mouse();
		~Mouse();
		MouseListener* mouse_listener() const { return mouse_listener_;	}
		void set_mouse_listener(const MouseListener* listener) {
			mouse_listener_ = listener;
		}
	private:
		MouseListener* mouse_listener_;
	}; // Mouse
} // epic

#endif // EPIC_INCLUDE_EPICMOUSE_H