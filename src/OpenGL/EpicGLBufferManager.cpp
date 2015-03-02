#include "include/opengl/EpicGLBufferManager.h"

namespace epic {
	GLBufferManager::GLBufferManager() {
	}

	GLBufferManager::~GLBufferManager() {
	}

	VertexBuffer* GLBufferManager::CreateVertexBuffer(
		const uint32 buffer_size, 
		const BufferUsage buffer_usage, 
		const uint32 num_vertices, 
		const std::vector<VertexElementStruct>& vertex_declaration,
		const void* buffer_data_) 
	{
		GLVertexBuffer* gl_vertex_buffer = NULL;
		gl_vertex_buffer = new GLVertexBuffer(buffer_size, buffer_usage, num_vertices, vertex_declaration, buffer_data_);
		// put the buffer into map
		// ... 
		return gl_vertex_buffer;
	}

	IndexBuffer* GLBufferManager::CreateIndexBuffer(
		const uint32 buffer_size, 
		const BufferUsage buffer_usage, 
		const uint32 num_indices,
		const IndexType index_type,
		const void* buffer_data_)
	{
		GLIndexBuffer* gl_index_buffer = NULL;
		gl_index_buffer = new GLIndexBuffer(buffer_size, buffer_usage, num_indices, index_type, buffer_data_);
		// put the buffer into map
		// ...
		return gl_index_buffer;
	}
} // epic