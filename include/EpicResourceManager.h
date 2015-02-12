/**
 * @file .h EpicResourceManager.h
 * @brief Abstract classes to manage GPU buffers.
 * @author Xiao Miaomiao
 * @version 1.0
 * @data 2015.2
 */
#ifndef EPIC_INCLUDE_EPICRESOURCEMANANGER_H
#define EPIC_INCLUDE_EPICRESOURCEMANANGER_H
#include <GL/glew.h>
#include <GL/wglew.h>
#include "include/EpicPrerequisites.h"
#include "include/EpicSingleton.h"
#include "include/EpicRenderSystem.h"
//#include "include/EpicGLResourceManager.h"

struct aiScene;
namespace epic
{
	// @brief enum to describe data type in GPU buffer
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

	// @brief enum to describe primitive type in Class VertexData.
	enum EpicPrimitiveType{
		EPIC_TRIANGLES = 0,
		EPIC_POINTS,
		EPIC_LINES
		//
	};
	
	enum EpicTextureFormat
	{
		EPIC_RGBA_32FLOAT = 0,
		EPIC_RGBA_32INT,
		EPIC_RGBA_8BYTE,
		EPIC_RGB_32FLOAT,
		EPIC_RGB_32INT,
		EPIC_RGB_8BYTE,
		EPIC_R_32F,
		EPIC_R_32INT,
		EPIC_R_8BYTE
	};

	const uint32 BUFFER_USAGE_DYNAMIC = 0x1;
	const uint32 BUFFER_USAGE_STATIC = 0x2;
	const uint32 BUFFER_USAGE_WRITEONLY = 0x4;

	enum EpicTextureFilter
	{
		EPIC_FILTER_NEAREST = 0,
		EPIC_FILTER_LINEAR
	};

	enum EpicTextureWrap
	{
		EPIC_WARP_CLAMP = 0,
		EPIC_WARA_REPEAT,
		EPIC_WARA_MIRRORED_REPEAT
	};
	// @remark abstract shader program class, GLSL shader or HLSL shader depending on the current renderer.
	class EPIC_EXPORT ShaderProgram
	{
	public:
		void SetName(std::string name);
	private:
		RenderSystemType current_render_system_;
		GLProgram* gl_program_ptr_;
	};
	
	class Texture2D
	{
	public:
		Texture2D(int width, int height, int color_stride, EpicDataType type, void* data);
		void SetName(std::string name);
		GLTexture2D* gl_texture_2d_ptr(void){return gl_texture_2d_ptr_;}
	private:
		RenderSystemType current_render_system_;
		GLTexture2D* gl_texture_2d_ptr_;
	};
	// @remark abstract GPU buffer for model vertex attribute, GL or D3D buffer depending on the current renderer.
	class EPIC_EXPORT AttributeBuffer//GL object attribute buffer
	{
	public:
		// @brief construct.
		// @brief create a empty buffer with default param.
		AttributeBuffer();
		// @param data_resource:a void pointer, pointing to a RAM, with continuous data_count data of data_type.
		AttributeBuffer(EpicDataType data_type, uint32 data_count, void* data_resource);
		virtual ~AttributeBuffer();
		void setName(std::string name);
		// @brief add count number of data at the end of the buffer
		// @param data_resource:a void pointer, pointing to a RAM, with continuous count data of the buffer's data_type.
		void PushData(int count, void* data_resource);
		// @brief clear all the data in the buffer,but this buffer is still exist in GPU RAM.
		void ClearData(void);
		// @brief fill count number of data,start at the offset, end at offset + count.
		void FillData(int offset, int count, void* data_resource);
		// @brief set data type in buffer
		void SetDataType(EpicDataType type);
		GLAttributeBuffer* gl_attribute_buffer_ptr(void){return gl_attribute_buffer_ptr_;}
	private:
		RenderSystemType current_render_system_;
		GLAttributeBuffer* gl_attribute_buffer_ptr_;
		D3D9AttributeBuffer* d3d9_attribute_buffer_;
	};
	
	
	// @remark a collection of VertexData and ShaderProgam for one model data
	class EPIC_EXPORT VertexData
	{
	public:
		// @brief construct with primitive type
		VertexData(EpicPrimitiveType primitive_type, uint32 buffer_size = 0, uint32 flag = 0);
		virtual ~VertexData(){}
		void setName(const String& name);
		void UseShaderProgram(ShaderProgram* shader_program);
		// @brief add an AttributeBuffer.
		// @param attribute_name: the name of attribute in shader.
		// @param component_stride: the number of components in shader.
		// @param is_indices: true if the buffer is filling with primitive indices.
		void AddBuffer(const AttributeBuffer* buffer, const int component_stride, const String& attribute_name, bool is_indices);
		// @param struct_byte_size: if the buffer is NOT filling with a single attribute, set the struct size.
		//void AddBuffer(AttributeBuffer* buffer, int component_stride, std::string attribute_name, int struct_byte_size);
		void AddInstanceBuffer(int component_stride, EpicDataType data_type, std::string attribute_name);
		AttributeBuffer* GetAttributeBufferPtrWithName(std::string attribute_name);
		void DeleteAttributeBufferWithName(std::string attribute_name);
		void UseMaterial(Material* material);
		// @brief interface per instance, when traverse Objects in scene
		void PushBackInstance(float* model_matrix);
		
		void PushBackInstanceValueWithName(const String& instance_attribute_name, int count, void* data_resource);
		void PushBackToVisibleArray(int render_priority);
		uint32 ref_count() const { return ref_count_; }
		// @the user should call this
		void AddRef() { ++ref_count_; }
		void Release() { --ref_count_; }
	private:
		RenderSystemType current_render_system_;
		GLVertexData* gl_vertex_data_ptr_;
		D3D9VertexData* d3d9_vertex_data_;
		uint32 ref_count_;
	};

	// @remark GPU resource manager, for renderer
	class EPIC_EXPORT ResourceManager : public Singleton<ResourceManager>
	{
	public:
		static ResourceManager& GetInstance(void);
		static ResourceManager* GetInstancePtr(void);
		ResourceManager(RenderSystemType render_system_type, const String& resource_file_location = "");
		virtual ~ResourceManager();
		GLResourceManager* gl_resource_manager(void){return gl_resource_manager_;}

		void ResetVisibleMap();
		// @brief if draw order is important
		void SortVisibleMap();
		void DrawVisibleMap();
		void DrawVisibleMapInOrder();

		// @brief push back and find interfaces, but NOT recommended.
		void PushBackToAttributeBufferMap(AttributeBuffer* attribute_buffer);
		void PushBackToVertexDataMap(VertexData* vertex_data);
		void PushBackToProgramMap(ShaderProgram* shader_program);
		AttributeBuffer* FindAttributeBuffer(std::string attribute_buffer_name);
		VertexData* FindVertexData(std::string vertex_data_name);
		ShaderProgram* FindShaderProgram(std::string shader_name);
		void set_resource_file_location(const char* location) { 
			resource_file_location_.clear();
			resource_file_location_ = location;
		}
		const char* resource_file_location() const { return resource_file_location_.c_str(); }

		VertexData* CreateVertexData();
		void AddVertexDataToMap(VertexData*);
		void DeleteVertexData(VertexData*);
	private:
		RenderSystemType current_render_system_;
		GLResourceManager* gl_resource_manager_;
		String resource_file_location_;
		//D3DResourceManager* ....
	};
}

#endif//EPIC_INCLUDE_EPICRESOURCEMANANGER_H