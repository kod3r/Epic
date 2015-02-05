#include "include/EpicMesh.h"
#include "include/EpicException.h"
#include "assimp/include/Importer.hpp"
#include "assimp/include/scene.h"
#include "assimp/include/postprocess.h"

namespace epic {
	Mesh::Mesh(){
	}
	Mesh::~Mesh() {
	}
	void Mesh::LoadMeshFromFile(const String& file_name) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(file_name, 
			aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
		if (!scene) {
			//throw(Exception("LoadMeshFromFile() -> ReadFile() failed!"));
			String error_message("LoadMeshFromFile() -> ReadFile() failed!\n");
			error_message += importer.GetErrorString();
			throw Exception(error_message);
			
		}
	}
} // epic