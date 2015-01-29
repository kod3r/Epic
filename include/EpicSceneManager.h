#ifndef EPIC_INCLUDE_EPICSCENEMANAGER_H
#define EPIC_INCLUDE_EPICSCENEMANAGER_H

#include "include/EpicPrerequisites.h"

namespace epic {
	class Object;
	class EPIC_EXPORT SceneManager {
	public:
		SceneManager();
		~SceneManager();
	private:
		Vector3 position_;
		Vector3 scale_;
	}; // SceneManager
} // epic

#endif // EPIC_INCLUDE_EPICSCENEMANAGER_H