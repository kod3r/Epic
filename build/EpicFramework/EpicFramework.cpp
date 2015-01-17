#include "EpicFramework.h"

template<> EpicFramework* epic::Singleton<EpicFramework>::singleton_ = 0;
EpicFramework& EpicFramework::GetInstance(void) {
	assert(singleton_);
	return *singleton_;
}
EpicFramework* EpicFramework::GetInstancePtr(void) {
	return singleton_;
}