#ifndef EPIC_INCLUDE_EPICSCENEMANAGER_H
#define EPIC_INCLUDE_EPICSCENEMANAGER_H

#include "include/EpicPrerequisites.h"

namespace epic {
	class Object;
	class EPIC_EXPORT SceneManager {
	public:
		SceneManager();
		virtual ~SceneManager();
		virtual void UpdateScene();
		virtual void DrawScene();

		Node* root_node() const;
	private:
		void InitSceneManager();

		Node* root_node_;
	}; // SceneManager
} // epic

#endif // EPIC_INCLUDE_EPICSCENEMANAGER_H