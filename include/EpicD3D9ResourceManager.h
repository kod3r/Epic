/**
 * @file EpicD3D9ResourceManager.h
 * @brief the definition of class D3D9VertexData, D3D9ResourceManager
 * @author Shi Jiabin
 * @version 1.0
 * @data 2015
 */

#ifndef EPIC_INCLUDE_EPICD3D9RESOURCEMANAGER_H
#define EPIC_INCLUDE_EPICD3D9RESOURCEMANAGER_H

#include "include/EpicPrerequisites.h"
#include "include/EpicResourceManager.h"
#include <d3d9.h>

namespace epic {
	// @remark the class just keep a pointer of the data
	class D3D9AttributeBuffer {
	public:
		D3D9AttributeBuffer(EpicDataType data_type, int data_count, void* data_resource);
		~D3D9AttributeBuffer();
	private:
		EpicDataType data_type_;

	}; // D3D9AttributeBuffer

	// @remark the abstract of IDirect3DVertexBuffer9 and IDirect3DIndexBuffer9
	class D3D9VertexData {
	public:
		// constructor
		// @brief create vertex buffer in this constructor, the index buffer is created when
		//    VertexData::AddBuffer() is called, and the last param is true
		D3D9VertexData(uint32 buffer_size, uint32 usage_flag);		
		~D3D9VertexData();
		void AddBuffer(const D3D9AttributeBuffer* attribute_buffer,const int component_stride, const String& attribute_name, bool is_indices);
	private:
		// the size of vertex struct in byte
		// uint32 vertex_struct_size_;
		IDirect3DVertexBuffer9* vertex_buffer_;
		IDirect3DIndexBuffer9* index_buffer_;
	}; // D3D9VertexData

	class D3D9ResourceManager {
	}; // D3D9ResourceManager
} // epic

#endif // EPIC_INCLUDE_EPICD3D9RESOURCEMANAGER_H