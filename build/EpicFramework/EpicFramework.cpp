#include "EpicFramework.h"
#include "include/EpicRoot.h"
#include "include/EpicSceneManager.h"
#include "include/EpicNode.h"
#include "include/EpicMesh.h"

static int cc = 0;
void RootNode::OnUpdate() {
	epic::Root::GetInstancePtr()->render_system()->set_clear_color((float)cc/1000.0f, 0.0f, 0.0f, 1.0f);
	epic::Root::GetInstancePtr()->render_system()->ClearColorBuffer();
	epic::Root::GetInstancePtr()->render_system()->SwapRenderBuffers();
	cc ++;
	if (cc>1000)
	{
		cc = 0;
	}
}

EpicFramework::EpicFramework(epic::RenderSystemType render_system_type) {
	root_ = new epic::Root(render_system_type);
	root_->render_system()->set_opengl_version(3, 1);
	root_->resource_manager()->set_resource_file_location("../resource/");
}

EpicFramework::~EpicFramework() {
}


void EpicFramework::InitSystem() {
	RootNode* root_node = new RootNode();
	root_->scene_manager()->set_root_node(root_node);
	test_mesh_ = new epic::Mesh();
	root_->LoadMeshFromFile("../resource/man_walk.x", test_mesh_, NULL);
	
}

void EpicFramework::StartRenderLoop() {
	InitSystem();
	root_->StartRendering();
}

