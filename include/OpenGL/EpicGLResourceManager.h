/**
 * @file .h EpicGLResourceManager.h
 * @brief OpenGL version for the abstract ResourceManager.
 * @author Xiao Miaomiao
 * @version 1.0
 * @data 2015.2
 */
#ifndef EPIC_INCLUDE_EPICGLRESOURCEMANANGER_H
#define EPIC_INCLUDE_EPICGLRESOURCEMANANGER_H
#include <GL/glew.h>
#include <GL/wglew.h>
#include "include/EpicPrerequisites.h"
#include "include/EpicResourceManager.h"

namespace epic
{
	static const int GLTypeSize[] = 
	{
		sizeof(float),
		sizeof(int),
		sizeof(unsigned int),
		sizeof(char),
		sizeof(unsigned char),
		sizeof(unsigned short),
		sizeof(short)
	};

	static const GLenum GLTypeEnum[] =
	{
		GL_FLOAT,
		GL_INT,
		GL_UNSIGNED_INT,
		GL_BYTE,
		GL_UNSIGNED_BYTE,
		GL_UNSIGNED_SHORT,
		GL_SHORT
	};
	
	static const GLenum GLTextureInternalFormat[] =
	{
		GL_RGBA32F,
		GL_RGBA32I,
		GL_RGBA8,
		GL_RGB32F,
		GL_RGB32I,
		GL_RGB8,
		GL_R32F,
		GL_R32I,
		GL_R8,
	};

	static const GLenum GLTextureFormat[] =
	{
		GL_RGBA,
		GL_RGBA_INTEGER,
		GL_RGBA_INTEGER,
		GL_RGB,
		GL_RGB_INTEGER,
		GL_RGB_INTEGER,
		GL_RED,
		GL_RED_INTEGER,
		GL_RED_INTEGER
	};

	static const GLenum GLTextureFilter[] =
	{
		GL_NEAREST,
		GL_LINEAR
	};

	static const GLenum GLTextureWarp[] =
	{
		GL_CLAMP,
		GL_REPEAT,
		GL_MIRRORED_REPEAT
	};

	class GLProgram
	{
	public:
		friend class GLVertexData;
		
	private:
		GLint program_handle_;
		//int map_index;
	};

	/*class GLTexture2D
	{
	public:
		friend class GLVertexData;
		GLTexture2D(int width, int height, EpicTextureFormat format, EpicDataType data_type, void* data);
	private:
		GLuint texture_handle_;
		int referance_count_by_vao_;
	};*/

	class GLAttributeBuffer//GL object attribute buffer
	{
	public:
		friend class GLVertexData;
		GLAttributeBuffer(){}
		GLAttributeBuffer(GLenum data_type, GLsizeiptr type_size, int data_count, GLvoid* data_resource);
		virtual ~GLAttributeBuffer();
		void set_name(std::string name);

		//int map_index(void){return map_index_;}
		GLenum data_type(void){return data_type_;}

		void PushData(int count, void* data_resource);
		void ClearData(void);
		void FillData(int offset, int count, void* data_resource);
		void SetDataType(EpicDataType type);
	private:
		std::string name_;
		GLenum data_type_;
		GLuint buffer_handle_;
		int type_size_;
		int data_count_;
		int referance_count_by_vao_;
		//int map_index_;
	};

	class GLVertexData//for packing GL vertex attribute buffers
	{
	public:
		GLVertexData(){}
		GLVertexData(EpicPrimitiveType primitive_type, GLProgram* shader_program);
		~GLVertexData();
		void set_name(std::string name);
		void AddBuffer(GLAttributeBuffer* buffer, int component_stride, std::string attribute_name, bool is_indices);
		//void UseProgram(GLProgram* program);
		void AddInstanceBuffer(int component_stride, EpicDataType data_type, std::string attribute_name);
		GLAttributeBuffer* GetAttributeBufferPtrWithName(std::string attribute_name);
		void DeleteAttributeBufferWithName(std::string attribute_name);
		void UseMaterial(Material* material);
		// @brief interface per instance, when traverse Objects in scene
		void PushBackInstance(float* model_matrix);
		void PushBackInstanceValueWithName(std::string instance_attribute_name, int count, void* data_resource);
		void PushBackToVisibleArray(int render_priority);

		void AddTexture2D(GLTexture2D* texture_2d, std::string name, EpicTextureFilter filter, EpicTextureWrap wrap);
		GLTexture2D* GetTexture2DPtrWithName(std::string texture_name_in_shader);
		void DeleteTexture2DWithName(std::string texture_name_in_shader);
	private:
		std::string name_;
		GLuint vao_handle_;
		GLProgram* shader_program_;
		bool draw_element_;
		//std::vector<GLAttributeBuffer*> vertex_attribute_buffer_array_;
		bool is_visible_;
		//int map_index_;
		GLenum primitive_type_;
		int referance_count_by_object_;
		GLint instance_count_;
		GLAttributeBuffer* model_matrix_;
		//std::vector<GLAttributeBuffer*> instance_attribute_buffer_array_;
	};

	class GLResourceManager
	{
	public:
		friend class GLAttributeBuffer;
		friend class GLVertexData;
		friend class GLProgram;
		friend class GLTexture2D;
		GLResourceManager();
		virtual ~GLResourceManager();
	private:
		std::map<int,unsigned int> visible_data_index_array_;
		std::map<unsigned int, GLVertexData*> data_map_;
		std::map<unsigned int, GLProgram*> shader_map_;
		std::map<unsigned int, GLAttributeBuffer*> buffer_map_;
		std::map<unsigned int, GLTexture2D*> texture_2d_map_;
	};
}

#endif//EPIC_INCLUDE_EPICGLRESOURCEMANANGER_H