#include "include/d3d9/EpicD3D9GPUBuffer.h"

namespace epic {
//-------------------------------------------------------------------------
// D3D9VertexBuffer
//-------------------------------------------------------------------------
	D3D9VertexBuffer::D3D9VertexBuffer(
		const uint32 buffer_size, 
		const BufferUsage buffer_usage, 
		const uint32 num_vertices, 
		const std::vector<VertexElementSemantic>& vertex_declaration,
		const void* buffer_data_) 
	:VertexBuffer(buffer_size, buffer_usage, num_vertices, vertex_declaration)
	{
		// create d3d9 vertex buffer
	}
	D3D9VertexBuffer::~D3D9VertexBuffer() {
	}

//-------------------------------------------------------------------------
// D3D9IndexBuffer
//-------------------------------------------------------------------------
	D3D9IndexBuffer::D3D9IndexBuffer(
		const uint32 buffer_size, 
		const BufferUsage buffer_usage, 
		const uint32 num_indices,
		const IndexType index_type,
		const void* buffer_data_)
	:IndexBuffer(buffer_size, buffer_usage, num_indices, index_type)
	{
		// create d3d9 index buffer
	}
	D3D9IndexBuffer::~D3D9IndexBuffer() {
	}
} // epic