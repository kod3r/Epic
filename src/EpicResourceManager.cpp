#include "include/EpicResourceManager.h"

namespace epic{
	GLAttributeBuffer::GLAttributeBuffer(GLenum data_type, int type_size, int data_count, GLvoid* data_resource)
	{
		data_type_ = data_type;
		glGenBuffers(1, &buffer_handle_);
		data_count_ = data_count;
		glBindBuffer(GL_ARRAY_BUFFER, buffer_handle_);
		glBufferData(GL_ARRAY_BUFFER, type_size * data_count, data_resource, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		int map_index_ = 0;
	}

	GLAttributeBuffer::~GLAttributeBuffer()
	{
		if (buffer_handle_)
			glDeleteBuffers(1, &buffer_handle_);
	}

	template<> GLResourceManager* Singleton<GLResourceManager>::singleton_ = 0;
	GLResourceManager& GLResourceManager::GetInstance(void) {
		assert(singleton_);
		return *singleton_;
	}
	GLResourceManager* GLResourceManager::GetInstancePtr(void) {
		return singleton_;
	}

	void GLResourceManager::InsertBuffer(GLAttributeBuffer& buffer)
	{
		assert((buffer.map_index()) == 0);
		buffer.set_map_index(buffer_map_.size());
		buffer_map_.insert(std::pair<int, GLAttributeBuffer>(buffer.map_index(), buffer));
	}
}