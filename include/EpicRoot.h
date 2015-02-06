/**
 * @file EpicRoot.h
 * @brief Root is the manager of the whole engine, by which
 *     user can access other modules safely.
 * @author Shi Jiabin
 * @version 1.0
 * @data 2015
 */
#ifndef EPIC_INCLUDE_EPICROOT_H
#define EPIC_INCLUDE_EPICROOT_H

#include "include/EpicPrerequisites.h"
#include "include/EpicRenderSystem.h"
#include "include/EpicSingleton.h"
#include "include/EpicResourceManager.h"

namespace epic {
	// @remark 
	//    Root is used to initialize the engine, start render loop, and some
	//    other manager's works.
	class EPIC_EXPORT Root : public Singleton<Root>{
	public:
		// @param type, whether to use OpenGL or D3D9 to initialize the render system.
		// @param title, the title of the render window.
		Root(RenderSystemType type, const char* title = "miaomi~");
		~Root();
		// start rendering loop
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