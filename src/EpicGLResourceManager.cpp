#include "include/EpicGLResourceManager.h"

namespace epic{
	GLAttributeBuffer::GLAttributeBuffer(GLenum data_type, int type_size, int data_count, GLvoid* data_resource)
	{
		data_type_ = data_type;
		glGenBuffers(1, &buffer_handle_);
		data_count_ = data_count;
		glBindBuffer(GL_ARRAY_BUFFER, buffer_handle_);
		if (data_resource)
			glBufferData(GL_ARRAY_BUFFER, type_size * data_count, data_resource, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		int map_index_ = ResourceManager::GetInstancePtr()->gl_resource_manager()->buffer_map_.size();
		ResourceManager::GetInstancePtr()->gl_resource_manager()->buffer_map_.insert(std::pair<int, GLAttributeBuffer*>(map_index_, this));
		referance_count_by_vao_ = 0;
		type_size_ = type_size;
	}

	GLAttributeBuffer::~GLAttributeBuffer()
	{
		if (buffer_handle_)
			glDeleteBuffers(1, &buffer_handle_);
	}

	void GLAttributeBuffer::PushData(int count, void* data_resource)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer_handle_);
		if (data_resource)
			glBufferSubData(GL_ARRAY_BUFFER, data_type_*type_size_, count*type_size_, data_resource);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		data_count_ += count;
	}

	void GLAttributeBuffer::ClearData()
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer_handle_);
		int i = 0;
		glBufferData(GL_ARRAY_BUFFER, sizeof(int), (GLvoid*)&i, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		data_count_ = 0;
	}

	GLVertexData::GLVertexData(EpicPrimitiveType primitive_type)
	{
		glGenVertexArrays(1, &vao_handle_);
		//the default program is the first.UseProgram(GLprogram) to set another one.
		shader_program_ = ResourceManager::GetInstancePtr()->gl_resource_manager()->shader_map_.find(0)->second;
		is_visible_ = false;
		map_index_ = ResourceManager::GetInstancePtr()->gl_resource_manager()->data_map_.size();
		
		ResourceManager::GetInstancePtr()->gl_resource_manager()->data_map_.insert(std::pair<int, GLVertexData*>(map_index_, this));
		//a GL_ELEMENT_ARRAY_BUFFER is always at the beginning of the attribute buffer array.
		//if not drawing as indices, it is null
		vertex_attribute_buffer_array_.push_back(NULL);
		switch(primitive_type)
		{
		case EPIC_TRIANGLES:
			primitive_type_ = GL_TRIANGLES;
			break;
		case EPIC_POINTS:
			primitive_type_ = GL_POINTS;
			break;
		case EPIC_LINES:
			primitive_type_ = GL_LINES;
			break;
		default:
			primitive_type_ = GL_POINTS;
		}
		referance_count_by_object_ = 0;
		instance_count_ = 0;

		//a model matrix(for each instance) is always at the beginning of the instance attribute array.
		GLAttributeBuffer* model_matrix_buffer = new GLAttributeBuffer(GL_FLOAT, sizeof(float), 0, 0);
		instance_attribute_buffer_array_.push_back(model_matrix_buffer);
	}

	void GLVertexData::AddBuffer(GLAttributeBuffer* buffer, int offset, std::string attribute_name, bool is_indices)
	{
		//if(!buffer)
		//	return;
		//buffer->referance_count_by_vao_++;
		//if (is_indices)
		//{
		//	glBindVertexArray(vao_handle_);
		//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->buffer_handle_);
		//	glBindVertexArray(0);
		//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//	if (vertex_attribute_buffer_array_.front())
		//	{
		//		GLAttributeBuffer* del_buffer = vertex_attribute_buffer_array_.front();
		//		//delete
		//		del_buffer->referance_count_by_vao_--;
		//		if (del_buffer->referance_count_by_vao_ <= 0)
		//		{
		//			glDeleteBuffers(1, del_buffer->buffer_handle_);
		//			std::map<int, GLAttributeBuffer*>::iterator it = ResourceManager::GetInstancePtr()->gl_resource_manager()->buffer_map_.find(del_buffer->map_index_);
		//			if (it != (ResourceManager::GetInstancePtr()->gl_resource_manager().buffer_map_.begin()))
		//			{
		//				(ResourceManager::GetInstancePtr()->gl_resource_manager().buffer_map_).erase(it);
		//			}
		//		}
		//	}
		//	vertex_attribute_buffer_array_.front() = buffer;
		//}

		//GLint attribute_location = glGetAttribLocation(shader_program_->program_handle_, attribute_name.c_str());
		//
	}

	GLVertexData::~GLVertexData()
	{

	}

	GLResourceManager::GLResourceManager()
	{

	}

	GLResourceManager::~GLResourceManager()
	{

	}
}