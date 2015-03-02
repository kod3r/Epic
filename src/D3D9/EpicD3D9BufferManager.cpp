#include "include/d3d9/EpicD3D9BufferManager.h"

namespace epic {
	D3D9BufferManager::D3D9BufferManager() {
	}

	D3D9BufferManager::~D3D9BufferManager() {
	}

	VertexBuffer* D3D9BufferManager::CreateVertexBuffer(
		const uint32 buffer_size, 
		const BufferUsage buffer_usage, 
		const uint32 num_vertices, 
		const std::vector<VertexElementStruct>& vertex_declaration,
		const void* buffer_data_) 
	{
		D3D9VertexBuffer* d3d9_vertex_buffer = NULL;
		d3d9_vertex_buffer = new D3D9VertexBuffer(buffer_size, buffer_usage, num_vertices, vertex_declaration, buffer_data_);
		// put the buffer into map
		// ... 
		return d3d9_vertex_buffer;
	}

	IndexBuffer* D3D9BufferManager::CreateIndexBuffer(
		const uint32 buffer_size, 
		const BufferUsage buffer_usage, 
		const uint32 num_indices,
		const IndexType index_type,
		const void* buffer_data_)
	{
		D3D9IndexBuffer* d3d9_index_buffer = NULL;
		d3d9_index_buffer = new D3D9IndexBuffer(buffer_size, buffer_usage, num_indices, index_type, buffer_data_);
		// put the buffer into map
		// ...
		return d3d9_index_buffer;
	}
} // epic