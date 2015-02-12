#include "include/EpicGLResourceManager.h"

namespace epic{
//----------------------------------------------------------------------------
// GLTexture2D
//----------------------------------------------------------------------------
	GLTexture2D::GLTexture2D(int width, int height, EpicTextureFormat format, EpicDataType data_type, void* data)
	{
		glGenTextures(1, &texture_handle_);
		glBindTexture(GL_TEXTURE_2D, texture_handle_);
		glTexImage2D(GL_TEXTURE_2D, 0, GLTextureInternalFormat[format], width, height, 0, GLTextureFormat[format], GLTypeEnum[data_type], data);
		glBindTexture(GL_TEXTURE_2D, 0);

		ResourceManager::GetInstancePtr()->gl_resource_manager()->texture_2d_map_.insert(std::pair<unsigned int, GLTexture2D*>(texture_handle_, this));
		referance_count_by_vao_ = 0;
	}

//----------------------------------------------------------------------------
// GLAttributeBuffer
//----------------------------------------------------------------------------
	GLAttributeBuffer::GLAttributeBuffer(GLenum data_type, int type_size, int data_count, GLvoid* data_resource)
	{
		name_ = "default";
		data_type_ = data_type;
		glGenBuffers(1, &buffer_handle_);
		data_count_ = data_count;
		glBindBuffer(GL_ARRAY_BUFFER, buffer_handle_);
		if (data_resource)
			glBufferData(GL_ARRAY_BUFFER, type_size * data_count, data_resource, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		ResourceManager::GetInstancePtr()->gl_resource_manager()->buffer_map_.insert(std::pair<unsigned int, GLAttributeBuffer*>(buffer_handle_, this));
		referance_count_by_vao_ = 0;
		type_size_ = type_size;
	}

	GLAttributeBuffer::~GLAttributeBuffer()
	{
		if (buffer_handle_)
			glDeleteBuffers(1, &buffer_handle_);
	}

	void GLAttributeBuffer::set_name(std::string name)
	{
		name_ = name;
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

	void GLAttributeBuffer::FillData(int offset, int count, void* data_resource)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer_handle_);
		if (data_resource)
			glBufferSubData(GL_ARRAY_BUFFER, offset * type_size_, count * type_size_, data_resource);
		int new_count = offset + count;
		if (new_count >= data_count_)
			data_count_ = new_count;
	}

	void GLAttributeBuffer::SetDataType(EpicDataType type)
	{
		data_type_ = GLTypeEnum[type];
		type_size_ = GLTypeSize[type];
	}
//----------------------------------------------------------------------------
// GLVertexData
//----------------------------------------------------------------------------
	GLVertexData::GLVertexData(EpicPrimitiveType primitive_type, GLProgram* shader_program)
	{
		glGenVertexArrays(1, &vao_handle_);

		name_ = "default";
		shader_program_ = shader_program;
		is_visible_ = false;
		
		ResourceManager::GetInstancePtr()->gl_resource_manager()->data_map_.insert(std::pair<unsigned int, GLVertexData*>(vao_handle_, this));

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

		draw_element_ = false;

		//create an instance attribute array for model matrix
		model_matrix_ = new GLAttributeBuffer(GL_FLOAT, sizeof(float), 0, 0);
		glBindVertexArray(vao_handle_);
		//it is important to comment the program, otherwise, the operate to set UNIFROMS does not make sense.
		//glUseProgram(shader_program_->program_handle_);
		glBindBuffer(GL_TEXTURE_BUFFER, model_matrix_->buffer_handle_);
		GLuint model_matrix_location = glGetUniformLocation(shader_program_->program_handle_, "model_matrix");
		GLuint model_texture;
		if (model_matrix_location >= 0)
		{
			glGenTextures(1, &model_texture);
			glBindTexture(GL_TEXTURE_BUFFER, model_texture);
			glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, model_matrix_->buffer_handle_);
			glUniform1i(model_matrix_location, 0);
			glActiveTexture(GL_TEXTURE0);
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
	}

	void GLVertexData::set_name(std::string name)
	{
		name_ = name;
	}

	void GLVertexData::AddBuffer(GLAttributeBuffer* buffer, int component_stride, std::string attribute_name, bool is_indices)
	{
		if(!buffer)
			return;
		std::map<unsigned int, GLAttributeBuffer*>& buffer_map 
			= ResourceManager::GetInstancePtr()->gl_resource_manager()->buffer_map_;
		buffer->referance_count_by_vao_++;
		if (is_indices)
		{
			draw_element_ = true;
			GLint current_index;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &current_index);
			if (current_index > 0)
			{
				std::map<unsigned int, GLAttributeBuffer*>::iterator it = buffer_map.find((unsigned int)current_index);
				if (it != buffer_map.end())
				{
					if ( (it->second->referance_count_by_vao_) <= 1)
					{
						glDeleteBuffers(1, (GLuint*)current_index);
						delete it->second;
						buffer_map.erase(it);
					}
					else
						it->second->referance_count_by_vao_ --;
				}
			}
			glBindVertexArray(vao_handle_);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->buffer_handle_);
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		else
		{
			GLint attribute_location = glGetAttribLocation(shader_program_->program_handle_, attribute_name.c_str());
			if (attribute_location >= 0)
			{
				DeleteAttributeBufferWithName(attribute_name);
				glBindVertexArray(vao_handle_);
				glBindBuffer(GL_ARRAY_BUFFER, buffer->buffer_handle_);
				glEnableVertexAttribArray((GLuint)attribute_location);
				glVertexAttribPointer(attribute_location, component_stride, buffer->data_type(), GL_FALSE, 0, 0);
			}
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	void GLVertexData::AddInstanceBuffer(int component_stride, EpicDataType data_type, std::string attribute_name)
	{
		assert(component_stride < 5 && component_stride > 0);
		std::map<unsigned int, GLAttributeBuffer*>& buffer_map 
			= ResourceManager::GetInstancePtr()->gl_resource_manager()->buffer_map_;
		GLint instance_attribute_loction = glGetAttribLocation(shader_program_->program_handle_, attribute_name.c_str());
		if (instance_attribute_loction >= 0)
		{
			DeleteAttributeBufferWithName(attribute_name);
			GLAttributeBuffer* instance_attribute_buffer = new GLAttributeBuffer(data_type, GLTypeSize[data_type], 0, 0);
			instance_attribute_buffer->referance_count_by_vao_ ++;
			glBindVertexArray(vao_handle_);
			glBindBuffer(GL_ARRAY_BUFFER, instance_attribute_buffer->buffer_handle_);
			glEnableVertexAttribArray(instance_attribute_loction);
			glVertexAttribPointer(instance_attribute_loction, component_stride, GLTypeEnum[data_type], GL_FALSE, 0, 0);
			glVertexAttribDivisor(instance_attribute_loction, 1);
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	GLAttributeBuffer* GLVertexData::GetAttributeBufferPtrWithName(std::string attribute_name)
	{
		std::map<unsigned int, GLAttributeBuffer*>& buffer_map 
			= ResourceManager::GetInstancePtr()->gl_resource_manager()->buffer_map_;

		GLint attribute_loction = glGetAttribLocation(shader_program_->program_handle_, attribute_name.c_str());
		if (attribute_loction >= 0)
		{
			GLint attribute_buffer;
			glGetVertexAttribiv((GLuint)attribute_loction, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &attribute_buffer);
			if (attribute_buffer > 0)
				return buffer_map.find((unsigned int)attribute_buffer)->second;
			else return NULL;
		}
		else return NULL;
	}

	void GLVertexData::DeleteAttributeBufferWithName(std::string attribute_name)
	{
		GLAttributeBuffer* attribute_buffer = GetAttributeBufferPtrWithName(attribute_name);
		std::map<unsigned int, GLAttributeBuffer*>& buffer_map 
			= ResourceManager::GetInstancePtr()->gl_resource_manager()->buffer_map_;

		if (attribute_buffer)
		{
			if (attribute_buffer->referance_count_by_vao_ <= 1)
			{
				glDeleteBuffers(1, (GLuint*)&(attribute_buffer->buffer_handle_));
				std::map<unsigned int, GLAttributeBuffer*>::iterator it 
					= buffer_map.find(attribute_buffer->buffer_handle_);
				if (it != buffer_map.end())
				{
					delete it->second;
					buffer_map.erase(it);
				}
			}
			else
				attribute_buffer->referance_count_by_vao_ --;
		}
	}

	void GLVertexData::UseMaterial(Material* material)
	{

	}

	void GLVertexData::PushBackInstance(float* model_matrix)
	{
		if (model_matrix)
		{
			instance_count_ ++;
			model_matrix_->PushData(16, model_matrix);
		}
	}

	void GLVertexData::PushBackInstanceValueWithName(std::string instance_attribute_name, int count, void* data_resource)
	{
		if (data_resource)
		{
			GLAttributeBuffer* buffer = GetAttributeBufferPtrWithName(instance_attribute_name);
			if (buffer)
				buffer->PushData(count, data_resource);
		}
	}

	void GLVertexData::PushBackToVisibleArray(int render_priority)
	{
		std::map<int, unsigned int>& visible_map
			= ResourceManager::GetInstancePtr()->gl_resource_manager()->visible_data_index_array_;
		visible_map.insert(std::pair<int, unsigned int>(render_priority, (unsigned int)vao_handle_));
	}

	GLVertexData::~GLVertexData()
	{
		if (model_matrix_)
		{
			delete model_matrix_;
		}
		if (vao_handle_)
		{
			glDeleteVertexArrays(1, &vao_handle_);
		}
	}

//----------------------------------------------------------------------------
// GLResourceManager
//----------------------------------------------------------------------------
	GLResourceManager::GLResourceManager()
	{

	}

	GLResourceManager::~GLResourceManager()
	{
		
	}
}