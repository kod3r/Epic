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
	/*void SceneManager::DrawScene() {

	}*/
	Node* SceneManager::root_node() const {
		return root_node_;
	}
	void SceneManager::set_root_node(Node* root_node) {
		if (root_node_) {
			delete root_node_;
			root_node_ = NULL;
		}
		root_node_ = root_node;
	}
	void SceneManager::InitSceneManager() {
		
	}

} // epic