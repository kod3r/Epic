#ifndef EPIC_INCLUDE_OPENGL_EPICGLBUFFERMANAGER_H
#define EPIC_INCLUDE_OPENGL_EPICGLBUFFERMANAGER_H

#include "include/EpicPrerequisites.h"
#include "include/EpicBufferManager.h"
#include "include/opengl/EpicGLGPUBuffer.h"

namespace epic {
	class EPIC_EXPORT GLBufferManager : public BufferManager {
	public:
		GLBufferManager();
		~GLBufferManager();
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
	}; // GLBufferManager
} // epic

#endif // EPIC_INCLUDE_OPENGL_EPICGLBUFFERMANAGER_H