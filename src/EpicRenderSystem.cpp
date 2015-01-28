#include "include/EpicRenderSystem.h"

namespace epic {
	template<> RenderSystem* Singleton<RenderSystem>::singleton_ = 0;

	RenderSystem& RenderSystem::GetInstance(void) {
		assert(singleton_);
		return *singleton_;
	}
	RenderSystem* RenderSystem::GetInstancePtr(void) {
		return singleton_;
	}

	RenderSystem::~RenderSystem(){}
} // epic