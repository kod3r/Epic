#include "include/EpicBufferManager.h"

namespace epic {
	BufferManager::BufferManager() {
	}

	BufferManager::~BufferManager() {
	}


	template<> BufferManager* Singleton<BufferManager>::singleton_ = 0;
	BufferManager& BufferManager::GetInstance(void) {
		assert(singleton_);
		return *singleton_;
	}
	BufferManager* BufferManager::GetInstancePtr(void) {
		return singleton_;
	}
} // epic
