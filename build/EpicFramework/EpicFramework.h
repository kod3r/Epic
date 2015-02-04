#ifndef EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H
#define EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H

#include "include/EpicPrerequisites.h"
#include "include/EpicRenderSystem.h"
#include "include/EpicNode.h"

class RootNode : public epic::Node {
public:
	RootNode(){}
	~RootNode(){}
//	virtual void Update(){}
	virtual void OnUpdate();
	
};

class EpicFramework{
public:
	EpicFramework(epic::RenderSystemType render_system_type);
	~EpicFramework();
	// 开始渲染前的初始化
	virtual void InitSystem();
	void StartRenderLoop();

private:
	epic::Root* root_;
	epic::Mesh* test_mesh_;
}; // EpicFramework


#endif // EPIC_BUILD_EPICFRAMEWORK_EPICFRAMEWORK_H