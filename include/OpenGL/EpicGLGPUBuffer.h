#ifndef EPIC_INCLUDE_OPENGL_EPICGLGPUBUFFER_H
#define EPIC_INCLUDE_OPENGL_EPICGLGPUBUFFER_H

#include "include/EpicPrerequisites.h"
#include "include/EpicGPUBuffer.h"

namespace epic {
	class EPIC_EXPORT GLVertexBuffer : public VertexBuffer {
	public:
		GLVertexBuffer(const uint32 buffer_size, 
			const BufferUsage buffer_usage, 
			const uint32 num_vertices, 
			const std::vector<VertexElementStruct>& vertex_declaration,
			const void* buffer_data_);
		~GLVertexBuffer();
	}; // GLVertexBuffer

	class EPIC_EXPORT GLIndexBuffer : public IndexBuffer{
	public:
		GLIndexBuffer(const uint32 buffer_size, 
			const BufferUsage buffer_usage, 
			const uint32 num_indices,
			const IndexType index_type,
			const void* buffer_data_);
		~GLIndexBuffer();
	}; // D3D9IndexBuffer
} // epic

#endif // EPIC_INCLUDE_OPENGL_EPICGLGPUBUFFER_H