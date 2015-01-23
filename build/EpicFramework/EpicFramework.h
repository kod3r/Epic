#ifndef EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H
#define EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H

#include "include/EpicPrerequisites.h"

class EpicFramework{
public:
	EpicFramework();
	~EpicFramework();
	void StartRenderLoop();
private:
	epic::Root* root_;
}; // EpicFramework


#endif // EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H