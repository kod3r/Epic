#ifndef EPIC_INCLUDE_EPICROOT_H
#define EPIC_INCLUDE_EPICROOT_H

#include "include/EpicPrerequisites.h"
#include "include/EpicRenderSystem.h"
#include "include/EpicSingleton.h"

namespace epic {
	class EPIC_EXPORT Root : public Singleton<Root>{
	public:
		Root();
		Root(RenderSystemType type);
		~Root();
		
		void StartRendering(void);
		
		static Root& GetInstance(void);
		static Root* GetInstancePtr(void);
	private:
		void InitSystem(void);
		RenderWindow* render_window_;
		RenderSystem* render_system_;
	}; // Root
} // epic

#endif // EPIC_INCLUDE_EPICROOT_H