#include "include/EpicRoot.h"

namespace epic {
	template<> Root* Singleton<Root>::singleton_ = 0;
	Root& Root::GetInstance(void) {
		assert(singleton_);
		return *singleton_;
	}
	Root* Root::GetInstancePtr(void) {
		return singleton_;
	}
} // epic