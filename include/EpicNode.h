#ifndef EPIC_INCLUDE_EPICNODE_H
#define EPIC_INCLUDE_EPICNODE_H

#include "include/EpicPrerequisites.h"
#include "glm/gtc/quaternion.hpp"

namespace epic {
	class EPIC_EXPORT Node {
	public:
		Node();
		virtual ~Node();
		virtual void Update();
		virtual void OnUpdate();
		void AddChild(Node* child);		
		void UpdateMatrix();

		const Vector3& position() const;
		void set_position(const Vector3& pos);
		void set_position(float x, float y, float z);
		const Vector3& scale() const;
		void set_scale(const Vector3& scale);
		void set_scale(float x, float y, float z);
		const Quaternion& orientation() const;
		void set_orientation(const Quaternion& quat);
		void set_orientation(float w, float x, float y, float z);
		void set_orientation(float angle, const Vector3& axis);
		void Translate(const Vector3& trans); // relative to parents
		void Rotate(float angle, const Vector3& axis); // relative to parents
		void Scale(const Vector3& scale);
		void Roll(float angle);
		void Pitch(float angle);
		void Yaw(float angle);
		Node* parents() const;
		void set_parents(const Node* parents);
		bool visible() const;
		void set_visible(bool vis);
		bool need_update() const;
		void set_need_update(bool need_update);
		const Matrix4& local_transform() const;
		const Matrix4& derived_transform() const;
	private:		
		Vector3 position_;
		Vector3 scale_;
		Quaternion orientation_;
		Matrix4 local_transform_;
		Matrix4 derived_transform_;
		Node* parents_;
		std::vector<Node*> children_;
		bool visible_;
		bool need_update_;
	}; // node

	class EPIC_EXPORT Object : public Node
	{
	public:		
		Object(){}
		~Object(){
			// when object deleted, the reference count of vertex data in Mesh should decrease
			//ResourceManager::DeleteVertexData();
		}
		// add reference count of vertexdata in Mesh
		//void BindMesh(Mesh*);
	private:
		Mesh* mesh_;
	};
} // epic

#endif // EPIC_INCLUDE_EPICNODE_H