#ifndef EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H
#define EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H

#include "include/EpicPrerequisites.h"
#include "include/EpicRenderSystem.h"

class EpicFramework{
public:
	EpicFramework(epic::RenderSystemType render_system_type);
	~EpicFramework();
	void StartRenderLoop();
private:
	epic::Root* root_;
}; // EpicFramework


#endif // EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H