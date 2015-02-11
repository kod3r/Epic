#include "include/EpicMesh.h"
#include "include/EpicException.h"
#include "include/EpicResourceManager.h"
#include "include/EpicMaterial.h"
#include "assimp/include/scene.h"
#include "assimp/include/mesh.h"
#include "assimp/include/material.h"


namespace epic {
	SubMesh::SubMesh():
	num_vertices_(0),
	num_faces_(0),
	vertex_array_(NULL),
	normal_array_(NULL),
	tangent_array_(NULL),
	bitangent_array_(NULL),
	index_array_(NULL)
	{
		for (int i = 0; i < MAX_NUM_COLOR_SETS; ++i) {
			color_array_[i] = NULL;
		}
		for (int i = 0; i < MAX_NUM_TEXTURECOORDS; ++i) {
			texturecoord_2d_array_[i] = NULL;
		}
	}
	SubMesh::~SubMesh() {
		delete [] vertex_array_;
		delete [] normal_array_;
		delete [] tangent_array_;
		delete [] bitangent_array_;
		delete [] index_array_;
		for (int i = 0; i < MAX_NUM_COLOR_SETS; ++i) {
			delete [] color_array_[i];
		}
		for (int i = 0; i < MAX_NUM_TEXTURECOORDS; ++i) {
			delete [] texturecoord_2d_array_[i];
		}
	}
	void SubMesh::InitFromFile(const aiMesh* mesh, VertexData* vertex_data) {
		num_vertices_ = mesh->mNumVertices;
		// 1. load positions
		if (mesh->HasPositions()) {
			vertex_array_ = new Vector3[num_vertices_];
			for (uint32 i = 0; i < num_vertices_; ++i) {
				vertex_array_[i].x = mesh->mVertices[i].x;
				vertex_array_[i].y = mesh->mVertices[i].y;
				vertex_array_[i].z = mesh->mVertices[i].z;
			}
			AttributeBuffer* attribute_buffer = new AttributeBuffer(EPIC_FLOAT, 3 * num_vertices_, static_cast<void*>(vertex_array_));
			vertex_data->AddBuffer(attribute_buffer, 3, "position", false);
		}
		// 2. load normals
		if (mesh->HasNormals()) {
			normal_array_ = new Vector3[num_vertices_];
			for (uint32 i = 0; i < num_vertices_; ++i) {
				normal_array_[i].x = mesh->mNormals[i].x;
				normal_array_[i].y = mesh->mNormals[i].y;
				normal_array_[i].z = mesh->mNormals[i].z;
			}
			AttributeBuffer* attribute_buffer = new AttributeBuffer(EPIC_FLOAT, 3 * num_vertices_, static_cast<void*>(normal_array_));
			vertex_data->AddBuffer(attribute_buffer, 3, "normal", false);
		}
		// 3. load tangents and bitangents
		if (mesh->HasTangentsAndBitangents()) {
			// 3.1 load tangents
			tangent_array_ = new Vector3[num_vertices_];
			for (uint32 i = 0; i < num_vertices_; ++i) {
				tangent_array_[i].x = mesh->mTangents[i].x;
				tangent_array_[i].y = mesh->mTangents[i].y;
				tangent_array_[i].z = mesh->mTangents[i].z;
			}
			AttributeBuffer* attribute_buffer = new AttributeBuffer(EPIC_FLOAT, 3 * num_vertices_, static_cast<void*>(tangent_array_));
			vertex_data->AddBuffer(attribute_buffer, 3, "tangent", false);
			
			// 3.2 load bitangents
			bitangent_array_ = new Vector3[num_vertices_];
			for (uint32 i = 0; i < num_vertices_; ++i) {
				bitangent_array_[i].x = mesh->mBitangents[i].x;
				bitangent_array_[i].y = mesh->mBitangents[i].y;
				bitangent_array_[i].z = mesh->mBitangents[i].z;
			}
			AttributeBuffer* attribute_buffer1 = new AttributeBuffer(EPIC_FLOAT, 3 * num_vertices_, static_cast<void*>(bitangent_array_));
			vertex_data->AddBuffer(attribute_buffer1, 3, "bitangent", false);
		}
		// 4. load color set
		for (int i = 0; i < MAX_NUM_COLOR_SETS; ++i) {
			if (mesh->HasVertexColors(i)) {
				color_array_[i] = new Vector4[num_vertices_];
				for (uint32 j = 0; j < num_vertices_; ++j) {
					color_array_[i][j].r = mesh->mColors[i][j].r;
					color_array_[i][j].g = mesh->mColors[i][j].g;
					color_array_[i][j].b = mesh->mColors[i][j].b;
					color_array_[i][j].a = mesh->mColors[i][j].a;
				}
				AttributeBuffer* attribute_buffer = new AttributeBuffer(EPIC_FLOAT, 4 * num_vertices_, static_cast<void*>(color_array_[i]));
				String attribute_name("color");
				attribute_name += i;
				vertex_data->AddBuffer(attribute_buffer, 4, attribute_name, false);
			}
		}
		// 5. load texture coordinates
		for (int i = 0; i < MAX_NUM_TEXTURECOORDS; ++i) {
			if (mesh->HasTextureCoords(i)) {
				texturecoord_2d_array_[i] = new Vector2[num_vertices_];
				for (uint32 j = 0; j < num_vertices_; ++j) {
					texturecoord_2d_array_[i][j].x = mesh->mTextureCoords[i][j].x;
					texturecoord_2d_array_[i][j].y = mesh->mTextureCoords[i][j].y;
				}
				AttributeBuffer* attribute_buffer = new AttributeBuffer(EPIC_FLOAT, 2 * num_vertices_, static_cast<void*>(texturecoord_2d_array_[i]));
				String attribute_name("texturecoord");
				attribute_name += i;
				vertex_data->AddBuffer(attribute_buffer, 2, attribute_name, false);
			}
		}
		// 6. load indices
		if (mesh->HasFaces()) {
			num_faces_ = mesh->mNumFaces;
			index_array_ = new Face[num_faces_];
			for (uint32 i = 0; i < num_faces_; ++i) {
				index_array_[i].x = mesh->mFaces[i].mIndices[0];
				index_array_[i].y = mesh->mFaces[i].mIndices[1];
				index_array_[i].z = mesh->mFaces[i].mIndices[2];
			}
			AttributeBuffer* attribute_buffer = new AttributeBuffer(EPIC_INT, 3 * num_faces_, static_cast<void*>(index_array_));
			vertex_data->AddBuffer(attribute_buffer, 3, "indices", true);
		}
	}
//----------------------------------------------------------------------------
// Mesh
//----------------------------------------------------------------------------

	Mesh::Mesh(bool is_static):
	is_static_(is_static),
	num_submesh_(0),
	num_material_(0)
	{
	}
	Mesh::~Mesh() {
	}
	void Mesh::InitMeshFromFile(const aiScene* scene) {
		// 1. init meshes
		num_submesh_ = scene->mNumMeshes;
		submesh_array_.clear();
		for (uint32 i = 0; i < num_submesh_; ++i) {
			const aiMesh* mesh = scene->mMeshes[i];
			SubMesh* submesh = new SubMesh();
			VertexData* vertex_data = new VertexData(EPIC_TRIANGLES);
			submesh->InitFromFile(mesh, vertex_data);
			if (is_static_) {
				delete submesh;
			}else {
				submesh_array_.push_back(submesh);
			}
			vertex_data_array_.push_back(vertex_data);
		}
		// 2. init materials
		num_material_ = scene->mNumMaterials;
		material_array_.clear();
		for (uint32 i = 0; i < num_material_; ++i) {
			Material* epic_material = new Material();
			
			const aiMaterial* material = scene->mMaterials[i];
			epic_material->InitMeshFromFile(material);
			material_array_.push_back(epic_material);
			
		}
	}
} // epic