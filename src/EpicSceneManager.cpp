#include "include/EpicSceneManager.h"
#include "include/EpicNode.h"

namespace epic {
	SceneManager::SceneManager():
	root_node_(NULL){
		InitSceneManager();
	}
	SceneManager::~SceneManager(){
	}
	void SceneManager::UpdateScene() {
		root_node_->Update();
	}
	void SceneManager::DrawScene() {
	}
	Node* SceneManager::root_node() const {
		return root_node_;
	}
	void SceneManager::InitSceneManager() {
		root_node_ = new Node();
	}

} // epic