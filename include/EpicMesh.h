#ifndef EPIC_INCLUDE_EPICMESH_H
#define EPIC_INCLUDE_EPICMESH_H

#include "include/EpicPrerequisites.h"

namespace epic {
	class EPIC_EXPORT Mesh {
	public: 
		Mesh(bool is_static);
		virtual ~Mesh();
		virtual void InitMesh(void){}
		virtual void UpdateMesh(void){}
		void Draw(){}
		void LoadMeshFromFile(const String& file_name);
		typedef
	private:
		// If the mesh is static, we should release the data in the system memory after
		// creating buffer.
		bool is_static_;
		float* vertex_array[3];
	};

} // epic

#endif // EPIC_INCLUDE_EPICMESH_H