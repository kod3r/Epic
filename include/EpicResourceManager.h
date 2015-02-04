#ifndef EPIC_INCLUDE_EPICRESOURCEMANANGER_H
#define EPIC_INCLUDE_EPICRESOURCEMANANGER_H
#include <GL/glew.h>
#include <GL/wglew.h>
#include "include/EpicObject.h"
#include "include/EpicSingleton.h"
#include <map>

namespace epic
{
	class EPIC_EXPORT ResourceManager
	{
	public:
		//static ResourceManager& GetInstance(void);
		//static ResourceManager* GetInstancePtr(void);
		ResourceManager(){}
		~ResourceManager(){}
	};

	class GLProgram
	{
	private:
		GLint program_handle_;
		int map_index;
	};

	class GLAttributeBuffer//GL object attribute buffer
	{
	public:
		GLAttributeBuffer(GLenum data_type, GLsizeiptr type_size, int data_count, GLvoid* data_resource);
		virtual ~GLAttributeBuffer();
		int map_index(void){return map_index_;}
		void set_map_index(const int index){map_index_ = index;}
		GLenum data_type(void){return data_type_;}
		int data_count(void){return data_count_;}
	private:
		GLenum data_type_;
		GLuint buffer_handle_;
		int data_count_;
		//int referance_count_by_vao_;
		int map_index_;
	};

	class GLVertexData//for packing GL vertex attribute buffers
	{
	public:
		void AddBuffer(GLAttributeBuffer& buffer);
	private:
		GLint vao_handle_;
		GLProgram shader_program_;
		std::vector<GLAttributeBuffer> vertex_attribute_buffer_array_;
		
		//bool is_visible_;
		int map_index_;
		GLenum primitive_type_;
		//int referance_count_by_object_;
		GLint instance_count_;
		std::vector<GLAttributeBuffer> instance_attribute_buffer_array_;
	};

	class EPIC_EXPORT GLResourceManager : public ResourceManager ,public Singleton<GLResourceManager>
	{
	public:
		static GLResourceManager& GetInstance(void);
		static GLResourceManager* GetInstancePtr(void);
		void InsertBuffer(GLAttributeBuffer& buffer);
	private:
		std::vector<int> visible_data_index_array_;
		std::map<int, GLVertexData> data_map_;
		std::map<int, GLProgram> shader_map_;
		std::map<int, GLAttributeBuffer> buffer_map_;
	};
}

#endif//EPIC_INCLUDE_EPICRESOURCEMANANGER_H