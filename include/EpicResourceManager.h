#ifndef EPIC_INCLUDE_EPICRESOURCEMANANGER_H
#define EPIC_INCLUDE_EPICRESOURCEMANANGER_H
#include <GL/glew.h>
#include <GL/wglew.h>
#include "include/EpicPrerequisites.h"
#include "include/EpicSingleton.h"
#include "include/EpicRenderSystem.h"

namespace epic
{
	enum EpicDataType{
		EPIC_FLOAT = 0,
		EPIC_INT,
		EPIC_UINT,
		EPIC_BYTE,
		EPIC_UBYTE,
		EPIC_USHORT,
		EPIC_SHOT
		//add other types
	};

	enum EpicPrimitiveType{
		EPIC_TRIANGLES = 0,
		EPIC_POINTS,
		EPIC_LINES
		//
	};

	class EPIC_EXPORT ShaderProgram
	{
	private:
		RenderSystemType current_render_system_;
		GLProgram* gl_program_ptr_;
	};

	class EPIC_EXPORT AttributeBuffer//GL object attribute buffer
	{
	public:
		AttributeBuffer(EpicDataType data_type, int data_count, void* data_resource);
		virtual ~AttributeBuffer();
	private:
		RenderSystemType current_render_system_;
		GLAttributeBuffer* gl_attribute_buffer_ptr_;
	};

	class EPIC_EXPORT VertexData//for packing GL vertex attribute buffers
	{
	public:
		VertexData(EpicPrimitiveType primitive_type);
		void AddBuffer(AttributeBuffer* buffer, int offset, std::string attribute_name, bool is_indices);
		void UseShaderProgram(ShaderProgram shader_program);
	private:
		RenderSystemType current_render_system_;
		GLVertexData* gl_vertex_data_ptr_;
		//D3DVertexData* .....
	};

	class EPIC_EXPORT ResourceManager : public Singleton<ResourceManager>
	{
	public:
		static ResourceManager& GetInstance(void);
		static ResourceManager* GetInstancePtr(void);
		ResourceManager(RenderSystemType render_system_type);
		virtual ~ResourceManager();
		GLResourceManager* gl_resource_manager(void){return gl_resource_manager_;}
	private:
		RenderSystemType current_render_system_;
		GLResourceManager* gl_resource_manager_;
		//D3DResourceManager* ....
	};
}

#endif//EPIC_INCLUDE_EPICRESOURCEMANANGER_H