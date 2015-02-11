#include "include/EpicResourceManager.h"
#include "include/EpicGLResourceManager.h"
#include "include/EpicD3D9ResourceManager.h"


namespace epic{
	
//----------------------------------------------------------------------------
// AttributeBuffer
//----------------------------------------------------------------------------
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
	VertexData::VertexData(EpicPrimitiveType primitive_type, uint32 vertex_struct_size, uint32 flag)
	{
		current_render_system_ = RenderSystem::GetInstancePtr()->current_render_type();
		if (current_render_system_ == RENDERSYSTEMTYPE_OPENGL)
		{
			
		}else if (current_render_system_ == RENDERSYSTEMTYPE_D3D9) {
			d3d9_vertex_data_ = new D3D9VertexData(vertex_struct_size, flag);
		}
	}
	void VertexData::AddBuffer(const AttributeBuffer* buffer, const int component_stride, const String& attribute_name, bool is_indices) {
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

	ResourceManager::ResourceManager(RenderSystemType render_system_type, const String& resource_file_location)
	{
		if (render_system_type == RENDERSYSTEMTYPE_OPENGL)
		{
			gl_resource_manager_ = new GLResourceManager();
		}
		resource_file_location_ = resource_file_location;
	}

	ResourceManager::~ResourceManager()
	{

	}
}