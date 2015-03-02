#ifndef EPIC_INCLUDE_EPICGPUBUFFER_H
#define EPIC_INCLUDE_EPICGPUBUFFER_H

#include "include/EpicPrerequisites.h"

namespace epic {
	enum BufferUsage{
		BUFFER_USAGE_STATIC = 1,
		BUFFER_USAGE_DYNAMIC = 2,
		BUFFER_USAGE_WRITEONLY = 4,
		BUFFER_USAGE_DYNAMIC_WRITEONLY = 6
	};

	enum VertexElementSemantic{
		VERTEX_ELEMENT_SEMANTIC_POSITION = 1,
		VERTEX_ELEMENT_SEMANTIC_NORMAL = 2,
		VERTEX_ELEMENT_SEMANTIC_BINORMAL = 3,
		VERTEX_ELEMENT_SEMANTIC_TANGENT = 4,
		VERTEX_ELEMENT_SEMANTIC_TEXTURE_COORDINATES = 5,
		VERTEX_ELEMENT_SEMANTIC_BLEND_WEIGHTS = 6,
		VERTEX_ELEMENT_SEMANTIC_BLEND_INDICES = 7,
		VERTEX_ELEMENT_SEMANTIC_COUNT = 7
	};

	enum VertexElementType{
		VERTEX_ELEMENT_TYPE_FLOAT = 1,
		VERTEX_ELEMENT_TYPE_DOUBLE = 2,
		VERTEX_ELEMENT_TYPE_INT = 3,
		VERTEX_ELEMENT_TYPE_BYTE = 4,
		VERTEX_ELEMENT_TYPE_SHORT = 5,
		VERTEX_ELEMENT_TYPE_UNSIGNED_INT = 6,
		VERTEX_ELEMENT_TYPE_UNSIGNED_SHORT = 7,
		VERTEX_ELEMENT_TYPE_COUNT = 7
	};

	struct  VertexElementStruct
	{
		VertexElementStruct(VertexElementSemantic semantic, VertexElementType type, int32 component_count);
		VertexElementSemantic vertex_element_semantic_;
		VertexElementType vertex_element_type_;
		int32 vertex_element_component_count_;
	};

	enum IndexType {
		INT_16,
		INT_32
	};

	class EPIC_EXPORT GPUBuffer {
	public:
		
		GPUBuffer(const uint32 buffer_size, const BufferUsage buffer_usage);
		virtual ~GPUBuffer();
		virtual void Lock();
		virtual void UnLock();

		uint32 buffer_size() const { return buffer_size_; }
		BufferUsage buffer_usage() const { return buffer_usage_; }
	private:
		// count in bytes
		uint32 buffer_size_;
		BufferUsage buffer_usage_;
	};

	class EPIC_EXPORT VertexDeclaration {
	public:
		VertexDeclaration();
		~VertexDeclaration();
		void AddElement(const VertexElementStruct element);
		uint32 GetNumElements() const { return element_group_.size(); }
	private:
		std::vector<VertexElementStruct> element_group_;
	};

	class EPIC_EXPORT VertexBuffer : public GPUBuffer {
	public:
		
		VertexBuffer(const uint32 buffer_size, 
					 const BufferUsage buffer_usage, 
					 const uint32 num_vertices, 
					 const std::vector<VertexElementStruct>& vertex_declaration);
		virtual ~VertexBuffer();

	private:
		uint32 num_vertices_;
		VertexDeclaration* vertex_declaration_;
	};

	class EPIC_EXPORT IndexBuffer : public GPUBuffer {
	public:
		IndexBuffer(const uint32 buffer_size, 
					const BufferUsage buffer_usage, 
					const uint32 num_indices,
					const IndexType index_type);
		virtual ~IndexBuffer();
	private:
		uint32 num_indices_;
		IndexType index_type_;
	};
} // epic

#endif // EPIC_INCLUDE_EPICGPUBUFFER_H