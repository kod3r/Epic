#ifndef EPIC_INCLUDE_EPICGLRESOURCEMANANGER_H
#define EPIC_INCLUDE_EPICGLRESOURCEMANANGER_H
#include <GL/glew.h>
#include <GL/wglew.h>
#include "include/EpicPrerequisites.h"
#include "include/EpicResourceManager.h"

namespace epic
{
	class GLProgram
	{
	public:
		friend class GLVertexData;
	private:
		GLint program_handle_;
		int map_index;
	};

	class GLAttributeBuffer//GL object attribute buffer
	{
	public:
		friend class GLVertexData;
		GLAttributeBuffer(){}
		GLAttributeBuffer(GLenum data_type, GLsizeiptr type_size, int data_count, GLvoid* data_resource);
		virtual ~GLAttributeBuffer();
		int map_index(void){return map_index_;}
		GLenum data_type(void){return data_type_;}

		virtual void PushData(int count, void* data_resource);
		virtual void ClearData(void);
	private:
		GLenum data_type_;
		GLuint buffer_handle_;
		int type_size_;
		int data_count_;
		int referance_count_by_vao_;
		int map_index_;
	};

	class GLVertexData//for packing GL vertex attribute buffers
	{
	public:
		GLVertexData(){}
		GLVertexData(EpicPrimitiveType primitive_type);
		~GLVertexData();
		void AddBuffer(GLAttributeBuffer* buffer, int offset, std::string attribute_name, bool is_indices);
		void DeleteBuffer(std::string attribute_name);
		void UseProgram(GLProgram program);
		void Finish();//write it at the end of the initial GLObject,or when drawing?
	private:
		GLuint vao_handle_;
		GLProgram* shader_program_;
		std::vector<GLAttributeBuffer*> vertex_attribute_buffer_array_;
		bool is_visible_;
		int map_index_;
		GLenum primitive_type_;
		int referance_count_by_object_;
		GLint instance_count_;
		std::vector<GLAttributeBuffer*> instance_attribute_buffer_array_;
	};

	class GLResourceManager
	{
	public:
		friend class GLAttributeBuffer;
		friend class GLVertexData;
		friend class GLProgram;
		GLResourceManager();
		virtual ~GLResourceManager();
	private:
		std::vector<int> visible_data_index_array_;
		std::map<int, GLVertexData*> data_map_;
		std::map<int, GLProgram*> shader_map_;
		std::map<int, GLAttributeBuffer*> buffer_map_;
	};
}

#endif//EPIC_INCLUDE_EPICGLRESOURCEMANANGER_H