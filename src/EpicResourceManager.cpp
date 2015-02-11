#include "include/EpicResourceManager.h"
#include "include/EpicGLResourceManager.h"

namespace epic{
//----------------------------------------------------------------------------
// AttributeBuffer
//----------------------------------------------------------------------------
	AttributeBuffer::AttributeBuffer(EpicDataType data_type, int data_count, void* data_resource)
	{
		current_render_system_ = RenderSystem::GetInstancePtr()->current_render_type();
		if (current_render_system_ == RENDERSYSTEMTYPE_OPENGL)
		{
			gl_attribute_buffer_ptr_ = new GLAttributeBuffer(GLTypeEnum[data_type], GLTypeSize[data_type], data_count, data_resource);
		}
	}
	
	AttributeBuffer::~AttributeBuffer()
	{

	}
//----------------------------------------------------------------------------
// VertexData
//----------------------------------------------------------------------------

	VertexData::VertexData(EpicPrimitiveType primitive_type)
	{
		current_render_system_ = RenderSystem::GetInstancePtr()->current_render_type();
		if (current_render_system_ == RENDERSYSTEMTYPE_OPENGL)
		{
			
		}
	}
	void VertexData::AddBuffer(AttributeBuffer* buffer, int component_stride, std::string attribute_name, bool is_indices) {
	}
//----------------------------------------------------------------------------
// ResourceManager
//----------------------------------------------------------------------------

	template<> ResourceManager* Singleton<ResourceManager>::singleton_ = 0;
	ResourceManager& ResourceManager::GetInstance(void) {
		assert(singleton_);
		return *singleton_;
	}
	ResourceManager* ResourceManager::GetInstancePtr(void) {
		return singleton_;
	}

	ResourceManager::ResourceManager(RenderSystemType render_system_type)
	{
		if (render_system_type == RENDERSYSTEMTYPE_OPENGL)
		{
			gl_resource_manager_ = new GLResourceManager();
		}
	}

	ResourceManager::~ResourceManager()
	{

	}
}