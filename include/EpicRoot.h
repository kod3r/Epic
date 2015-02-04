#ifndef EPIC_INCLUDE_EPICROOT_H
#define EPIC_INCLUDE_EPICROOT_H

#include "include/EpicPrerequisites.h"
#include "include/EpicRenderSystem.h"
#include "include/EpicSingleton.h"
#include "include/EpicResourceManager.h"

namespace epic {
	class EPIC_EXPORT Root : public Singleton<Root>{
	public:
		Root(RenderSystemType type, const char* title = "miaomi~");
		~Root();
		
		void StartRendering(void);
		void RenderOneFrame(void);
		RenderWindow* render_window() const {
			return render_window_;
		}
		RenderSystem* render_system() const {
			return render_system_;
		}
		SceneManager* scene_manager() const {
			return scene_manager_;
		}

		static Root& GetInstance(void);
		static Root* GetInstancePtr(void);
	private:
		void InitSystem(void);
		RenderWindow* render_window_;
		RenderSystem* render_system_;
		SceneManager* scene_manager_;
		ResourceManager* resource_manager_;
	}; // Root
} // epic

#endif // EPIC_INCLUDE_EPICROOT_H