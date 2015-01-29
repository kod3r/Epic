#include "EpicFramework.h"
#include "include/EpicRoot.h"

EpicFramework::EpicFramework(epic::RenderSystemType render_system_type) {
	root_ = new epic::Root(render_system_type);
}

EpicFramework::~EpicFramework() {
}

void EpicFramework::StartRenderLoop() {
	root_->StartRendering();
}