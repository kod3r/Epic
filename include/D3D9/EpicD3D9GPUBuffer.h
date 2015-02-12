#ifndef EPIC_INCLUDE_D3D9_EPICD3D9GPUBUFFER_H
#define EPIC_INCLUDE_D3D9_EPICD3D9GPUBUFFER_H

#include "include/EpicPrerequisites.h"
#include "include/EpicGPUBuffer.h"

namespace epic {
	class EPIC_EXPORT D3D9VertexBuffer : public VertexBuffer{
	public:
		D3D9VertexBuffer(const uint32 buffer_size, 
						 const BufferUsage buffer_usage, 
						 const uint32 num_vertices, 
						 const std::vector<VertexElementSemantic>& vertex_declaration,
						 const void* buffer_data_);
		~D3D9VertexBuffer();

	}; // D3D9VertexBuffer

	class EPIC_EXPORT D3D9IndexBuffer : public IndexBuffer{
	public:
		D3D9IndexBuffer(const uint32 buffer_size, 
						const BufferUsage buffer_usage, 
						const uint32 num_indices,
						const IndexType index_type,
						const void* buffer_data_);
		~D3D9IndexBuffer();
	}; // D3D9IndexBuffer
} // epic

#endif // EPIC_INCLUDE_D3D9_EPICD3D9GPUBUFFER_H