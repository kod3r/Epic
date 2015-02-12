#ifndef EPIC_INCLUDE_EPICMESH_H
#define EPIC_INCLUDE_EPICMESH_H

#include "include/EpicPrerequisites.h"
struct aiScene;
struct aiMesh;
namespace epic {
	struct Face {
		Face():x(0),y(0),z(0){}
		~Face(){}
		int x;
		int y;
		int z;
	};
	class SubMesh {
	public:
		SubMesh();
		~SubMesh();
		// @brief init submesh from aiMesh, which was loaded by assimp library
		// @param [in] mesh, the mesh data from file
		// @param [out] vertex_data, the buffer to be created
		void InitFromFile(const aiMesh* mesh, VertexData* vertex_data);
	private:
		uint32 num_vertices_;
		uint32 num_faces_;
		Vector3* vertex_array_;
		Vector3* normal_array_;
		Vector3* tangent_array_;
		Vector3* bitangent_array_;
		Vector4* color_array_[MAX_NUM_COLOR_SETS];
		Vector2* texturecoord_2d_array_[MAX_NUM_TEXTURECOORDS];
		Face* index_array_;
		// the GPU buffer of the mesh(VAO in OpenGL)
		VertexData* vertex_data_buffer_;
	};
	
	class EPIC_EXPORT Mesh {
	public: 
		Mesh(bool is_static = false);
		virtual ~Mesh();
		virtual void InitMesh(void){}
		virtual void UpdateMesh(void){}
		void Draw(){}
		void InitMeshFromFile(const aiScene* scene);
		void InitMeshFromMemory();
		uint32 num_submesh() const { return num_submesh_; }
	private:
		// If the mesh is static(is_static_ == true), we should release the data in the system memory after
		// creating buffer.
		bool is_static_;
		uint32 num_submesh_;
		uint32 num_material_;
		std::vector<SubMesh*> submesh_array_;
		
		//std::vector<VertexData*> vertex_data_array_;
		std::vector<Material*> material_array_;
	};

} // epic

#endif // EPIC_INCLUDE_EPICMESH_H