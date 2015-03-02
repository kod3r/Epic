#ifndef EPIC_INCLUDE_D3D9_EPICD3D9BUFFERMANAGER_H
#define EPIC_INCLUDE_D3D9_EPICD3D9BUFFERMANAGER_H

#include "include/EpicPrerequisites.h"
#include "include/EpicBufferManager.h"
#include "include/d3d9/EpicD3D9GPUBuffer.h"

namespace epic {
	class EPIC_EXPORT D3D9BufferManager : public BufferManager {
	public:
		D3D9BufferManager();
		~D3D9BufferManager();
		virtual VertexBuffer* CreateVertexBuffer(
			const uint32 buffer_size, 
			const BufferUsage buffer_usage, 
			const uint32 num_vertices, 
			const std::vector<VertexElementStruct>& vertex_declaration,
			const void* buffer_data_);
		virtual IndexBuffer* CreateIndexBuffer(
			const uint32 buffer_size, 
			const BufferUsage buffer_usage, 
			const uint32 num_indices,
			const IndexType index_type,
			const void* buffer_data_);

	}; // D3D9BufferManager
} // epic

#endif // EPIC_INCLUDE_D3D9_EPICD3D9BUFFERMANAGER_H