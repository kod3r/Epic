#include "EpicFramework.h"
#include "include/EpicRoot.h"

EpicFramework::EpicFramework() {
	root_ = new epic::Root();
}

EpicFramework::~EpicFramework() {
}

void EpicFramework::StartRenderLoop() {
	root_->StartRendering();
}