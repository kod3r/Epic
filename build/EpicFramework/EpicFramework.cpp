#include "EpicFramework.h"
#include "include/EpicRoot.h"
#include "include/EpicSceneManager.h"
#include "include/EpicNode.h"

void RootNode::OnUpdate() {
	//epic::Root::GetInstancePtr()->render_system()->ClearColorBuffer();
}


EpicFramework::EpicFramework(epic::RenderSystemType render_system_type) {
	root_ = new epic::Root(render_system_type);
}

EpicFramework::~EpicFramework() {
}


void EpicFramework::InitSystem() {
	RootNode* root_node = new RootNode();
	root_->scene_manager()->set_root_node(root_node);
}

void EpicFramework::StartRenderLoop() {
	InitSystem();
	root_->StartRendering();
}

