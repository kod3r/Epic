#include "include/opengl/EpicGLGPUBuffer.h"

namespace epic {
//-------------------------------------------------------------------------
// D3D9VertexBuffer
//-------------------------------------------------------------------------
	GLVertexBuffer::GLVertexBuffer(
		const uint32 buffer_size, 
		const BufferUsage buffer_usage, 
		const uint32 num_vertices, 
		const std::vector<VertexElementStruct>& vertex_declaration,
		const void* buffer_data_) 
		:VertexBuffer(buffer_size, buffer_usage, num_vertices, vertex_declaration)
	{
		// create openGL vertex buffer
	}
	GLVertexBuffer::~GLVertexBuffer() {
	}

//-------------------------------------------------------------------------
// D3D9IndexBuffer
//-------------------------------------------------------------------------
	GLIndexBuffer::GLIndexBuffer(
		const uint32 buffer_size, 
		const BufferUsage buffer_usage, 
		const uint32 num_indices,
		const IndexType index_type,
		const void* buffer_data_)
		:IndexBuffer(buffer_size, buffer_usage, num_indices, index_type)
	{
		// create opengl index buffer
	}
	GLIndexBuffer::~GLIndexBuffer() {
	}
} // epic