#ifndef EPIC_INCLUDE_EPICBUFFERMANAGER_H
#define EPIC_INCLUDE_EPICBUFFERMANAGER_H

#include "include/EpicPrerequisites.h"
#include "include/EpicSingleton.h"
#include "include/EpicGPUBuffer.h"

namespace epic {
	class EPIC_EXPORT BufferManager : public Singleton<BufferManager>{
	public:
		BufferManager();
		virtual ~BufferManager();
		virtual VertexBuffer* CreateVertexBuffer(
					 const uint32 buffer_size, 
					 const BufferUsage buffer_usage, 
					 const uint32 num_vertices, 
					 const std::vector<VertexElementSemantic>& vertex_declaration,
					 const void* buffer_data_)=0;
		virtual IndexBuffer* CreateIndexBuffer(
					const uint32 buffer_size, 
					const BufferUsage buffer_usage, 
					const uint32 num_indices,
					const IndexType index_type,
					const void* buffer_data_)=0;
		static BufferManager& GetInstance(void);
		static BufferManager* GetInstancePtr(void);
	private:
		std::map<VertexBuffer*, uint32> vertex_buffer_sets_;
		std::map<IndexBuffer*, uint32> index_buffer_sets_;
	};
} // epic

#endif // EPIC_INCLUDE_EPICBUFFERMANAGER_H