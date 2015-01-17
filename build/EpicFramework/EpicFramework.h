#ifndef EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H
#define EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H

#include "include/EpicPrerequisites.h"
#include "include/EpicSingleton.h"

class EpicFramework : public epic::Singleton<EpicFramework> {
public:
	EpicFramework();
	~EpicFramework();
	static EpicFramework& GetInstance(void);
	static EpicFramework* GetInstancePtr(void);
}; // EpicFramework


#endif // EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H