#include "include/EpicResourceManager.h"
#include "include/EpicGLResourceManager.h"

namespace epic{
	AttributeBuffer::AttributeBuffer(EpicDataType data_type, int data_count, void* data_resource)
	{
		current_render_system_ = RenderSystem::GetInstancePtr()->current_render_type();
		if (current_render_system_ == RENDERSYSTEMTYPE_OPENGL)
		{
			switch(data_type)
			{
			case EPIC_FLOAT:
				gl_attribute_buffer_ptr_ = new GLAttributeBuffer(GL_FLOAT, sizeof(float), data_count, data_resource);
				break;
			case EPIC_INT:
				gl_attribute_buffer_ptr_ = new GLAttributeBuffer(GL_INT, sizeof(int), data_count, data_resource);
				break;
			case EPIC_UINT:
				gl_attribute_buffer_ptr_ = new GLAttributeBuffer(GL_UNSIGNED_INT, sizeof(unsigned int), data_count, data_resource);
				break;
			case EPIC_BYTE:
				gl_attribute_buffer_ptr_ = new GLAttributeBuffer(GL_BYTE, sizeof(signed char), data_count, data_resource);
				break;
			case EPIC_UBYTE:
				gl_attribute_buffer_ptr_ = new GLAttributeBuffer(GL_UNSIGNED_BYTE, sizeof(unsigned char), data_count, data_resource);
				break;
			case EPIC_USHORT:
				gl_attribute_buffer_ptr_ = new GLAttributeBuffer(GL_UNSIGNED_SHORT, sizeof(unsigned short), data_count, data_resource);
				break;
			case EPIC_SHOT:
				gl_attribute_buffer_ptr_ = new GLAttributeBuffer(GL_SHORT, sizeof(short), data_count, data_resource);
				break;
			default:
				break;
			}
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