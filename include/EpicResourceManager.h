/**
 * @file .h EpicResourceManager.h
 * @brief Abstract classes to manage GPU buffers.
 * @author Xiao Miaomiao
 * @version 1.0
 * @data 2015
 */
#ifndef EPIC_INCLUDE_EPICRESOURCEMANANGER_H
#define EPIC_INCLUDE_EPICRESOURCEMANANGER_H
#include <GL/glew.h>
#include <GL/wglew.h>
#include "include/EpicPrerequisites.h"
#include "include/EpicSingleton.h"
#include "include/EpicRenderSystem.h"
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

	

	// @remark abstract GPU buffer for model vertex attribute, GL or D3D buffer depending on the current renderer.
	class EPIC_EXPORT AttributeBuffer//GL object attribute buffer
	{
	public:
		// @brief construct.
		// @brief create a empty buffer with default param.
		AttributeBuffer();
		// @param data_resource:a void pointer, pointing to a RAM, with continuous data_count data of data_type.
		AttributeBuffer(EpicDataType data_type, int data_count, void* data_resource);
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
	private:
		RenderSystemType current_render_system_;
		GLAttributeBuffer* gl_attribute_buffer_ptr_;
	};
	
	
	// @remark a collection of VertexData and ShaderProgam for one model data
	class EPIC_EXPORT VertexData
	{
	public:
		// @brief construct with primitive type
		VertexData(EpicPrimitiveType primitive_type);
		virtual ~VertexData(){}
		void setName(std::string name);
		void UseShaderProgram(ShaderProgram shader_program);
		// @brief add an AttributeBuffer.
		// @param attribute_name: the name of attribute in shader.
		// @param component_stride: the number of components in shader.
		// @param is_indices: true if the buffer is filling with primitive indices.
		void AddBuffer(AttributeBuffer* buffer, int component_stride, std::string attribute_name, bool is_indices);
		void AddInstanceBuffer(int component_stride, EpicDataType data_type, std::string attribute_name);
		AttributeBuffer* GetAttributeBufferPtrWithName(std::string attribute_name);
		void DeleteAttributeBufferWithName(std::string attribute_name);
		void UseMaterial(Material* material);
		// @brief interface per instance, when traverse Objects in scene
		void PushBackInstance(float* model_matrix);
		void PushBackInstanceValueWithName(std::string instance_attribute_name, int count, void* data_resource);
	private:
		RenderSystemType current_render_system_;
		GLVertexData* gl_vertex_data_ptr_;
		//D3DVertexData* .....
	};

	// @remark GPU resource manager, for renderer
	class EPIC_EXPORT ResourceManager : public Singleton<ResourceManager>
	{
	public:
		static ResourceManager& GetInstance(void);
		static ResourceManager* GetInstancePtr(void);
		ResourceManager(RenderSystemType render_system_type);
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
	private:
		RenderSystemType current_render_system_;
		GLResourceManager* gl_resource_manager_;
		//D3DResourceManager* ....
	};
}

#endif//EPIC_INCLUDE_EPICRESOURCEMANANGER_H