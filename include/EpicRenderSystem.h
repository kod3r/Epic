#ifndef EPIC_INCLUDE_EPICRENDERSYSTEM_H
#define EPIC_INCLUDE_EPICRENDERSYSTEM_H

#include "include/EpicPrerequisites.h"
#include "include/EpicSingleton.h"

namespace epic {
	enum RenderSystemType{RENDERSYSTEMTYPE_D3D9 = 0, RENDERSYSTEMTYPE_OPENGL};
	class EPIC_EXPORT RenderSystem : public Singleton<RenderSystem> {
	public:
		//RenderSystem();
		virtual ~RenderSystem();

		static RenderSystem& GetInstance(void);
		static RenderSystem* GetInstancePtr(void);
	private:

	}; // RenderSystem
} // epic

#endif // EPIC_INCLUDE_EPICRENDERSYSTEM_H