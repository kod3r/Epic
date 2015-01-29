#include "include/EpicNode.h"
#include "include/EpicException.h"
#include "glm/gtc/matrix_transform.hpp"

namespace epic {
	Node::Node():
	position_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f),
	orientation_(),
	parents_(NULL),
	visible_(true),
	need_update_(true)
	{
	}
	Node::~Node() {
	}

	void Node::Update() {
		if (need_update_) {
			OnUpdate();
			UpdateMatrix();		
			need_update_ = false;
		}
		std::vector<Node*>::iterator it = children_.begin();
		while (it != children_.end()) {
			(*it)->Update();
			++it;
		}

	}
	void Node::OnUpdate() {
	}
	void Node::AddChild(Node* child) {
		if (child) {
			if (child->parents()){
				throw(Exception("AddChild() failed!\nThe child already has a parents!"));
			}
			child->set_parents(this);
			children_.push_back(child);
		}
	}

	void Node::UpdateMatrix() {
		Matrix4 scale_mat;
		Matrix4 rotate_mat;
		Matrix4 translate_mat;
		glm::scale(scale_mat, scale_);
		glm::rotate(rotate_mat, orientation_.w, 
			Vector3(orientation_.x, orientation_.y, orientation_.z));
		glm::translate(translate_mat, position_);
		local_transform_ = translate_mat * rotate_mat * scale_mat;
		if (parents_) {
			derived_transform_ = local_transform_ * (parents_->derived_transform());
		}else {
			derived_transform_ = local_transform_;
		}
		
	}

	const Vector3& Node::position() const {
		return position_; 
	}
	void Node::set_position(const Vector3& pos) {
		position_ = pos; 
		need_update_ = true;
	}
	void Node::set_position(float x, float y, float z) {
		position_.x = x;
		position_.y = y;
		position_.z = z;
		need_update_ = true;
	}
	const Vector3& Node::scale() const {
		return scale_; 
	}
	void Node::set_scale(const Vector3& scale) {
		scale_ = scale; 
		need_update_ = true;
	}
	void Node::set_scale(float x, float y, float z) {
		scale_.x = x;
		scale_.y = y;
		scale_.z = z;
		need_update_ = true;
	}
	const Quaternion& Node::orientation() const {
		return orientation_; 
	}
	void Node::set_orientation(const Quaternion& quat) {
		orientation_ = quat; 
		need_update_ = true;
	}
	void Node::set_orientation(float w, float x, float y, float z) {
		orientation_.w = w;
		orientation_.x = x;
		orientation_.y = y;
		orientation_.z = z;
		glm::normalize(orientation_);
		need_update_ = true;
	}
	void Node::set_orientation(float angle, const Vector3& axis) {
		orientation_ = Quaternion(angle, axis);
		glm::normalize(orientation_);
		need_update_ = true;
	}
	void Node::Translate(const Vector3& trans) {
		position_ += trans;
		need_update_ = true;
	}
	void Node::Rotate(float angle, const Vector3& axis) {
		glm::rotate(orientation_, angle, axis);
		need_update_ = true;
	}
	void Node::Roll(float angle) {
		glm::rotate(orientation_, angle, Vector3(0, 0, 1));
		need_update_ = true;
	}
	void Node::Pitch(float angle) {
		glm::rotate(orientation_, angle, Vector3(1, 0, 0));
		need_update_ = true;
	}
	void Node::Yaw(float angle) {
		glm::rotate(orientation_, angle, Vector3(0, 1, 0));
		need_update_ = true;
	}
	Node* Node::parents() const {
		return parents_;
	}
	void Node::set_parents(const Node* parents) {
		parents_ = parents_;
	}
	bool Node::visible() const {
		return visible_;
	}
	void Node::set_visible(bool vis) {
		visible_ = vis;
	}
	bool Node::need_update() const {
		return need_update_;
	}
	void Node::set_need_update(bool need_update) {
		need_update_ = need_update;
	}


	const Matrix4& Node::local_transform() const {
		return local_transform_;
	}
	const Matrix4& Node::derived_transform() const {
		return derived_transform_;
	}
} // epic