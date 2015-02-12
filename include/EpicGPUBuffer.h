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
		VERTEX_ELEMENT_TYPE_POSITION = 1,
		VERTEX_ELEMENT_TYPE_NORMAL = 2,
		VERTEX_ELEMENT_TYPE_BINORMAL = 3,
		VERTEX_ELEMENT_TYPE_TANGENT = 4,
		VERTEX_ELEMENT_TYPE_TEXTURE_COORDINATES = 5,
		VERTEX_ELEMENT_TYPE_BLEND_WEIGHTS = 6,
		VERTEX_ELEMENT_TYPE_BLEND_INDICES = 7,
		VERTEX_ELEMENT_TYPE_COUNT = 7
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
		void AddElement(const VertexElementSemantic element);
		uint32 GetNumElements() const { return element_group_.size(); }
	private:
		std::vector<VertexElementSemantic> element_group_;
	};

	class EPIC_EXPORT VertexBuffer : public GPUBuffer {
	public:
		
		VertexBuffer(const uint32 buffer_size, 
					 const BufferUsage buffer_usage, 
					 const uint32 num_vertices, 
					 const std::vector<VertexElementSemantic>& vertex_declaration);
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