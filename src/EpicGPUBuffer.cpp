#include "include/EpicGPUBuffer.h"

namespace epic {
//-------------------------------------------------------------------------
// GPUBuffer
//-------------------------------------------------------------------------
	GPUBuffer::GPUBuffer(const uint32 buffer_size, const BufferUsage buffer_usage):
	buffer_size_(buffer_size),
	buffer_usage_(buffer_usage){
	}

	GPUBuffer::~GPUBuffer() {
	}

	void GPUBuffer::Lock() {
	}

	void GPUBuffer::UnLock() {
	}

//-------------------------------------------------------------------------
// VertexElementStruct
//-------------------------------------------------------------------------
	VertexElementStruct::VertexElementStruct(VertexElementSemantic semantic, VertexElementType type, int32 component_count)
	{
		vertex_element_semantic_ = semantic;
		vertex_element_type_ = type;
		vertex_element_component_count_ = component_count;
	}
//-------------------------------------------------------------------------
// VertexDeclaration
//-------------------------------------------------------------------------
	VertexDeclaration::VertexDeclaration() {
	}

	VertexDeclaration::~VertexDeclaration() {
		element_group_.clear();
	}

	void VertexDeclaration::AddElement(const VertexElementStruct element) {
		element_group_.push_back(element);
	}
//-------------------------------------------------------------------------
// VertexBuffer
//-------------------------------------------------------------------------
	VertexBuffer::VertexBuffer(const uint32 buffer_size, 
							   const BufferUsage buffer_usage, 
							   const uint32 num_vertices, 
							   const std::vector<VertexElementStruct>& vertex_declaration) 
	:GPUBuffer(buffer_size, buffer_usage),
	num_vertices_(num_vertices_)
	{
		vertex_declaration_ = new VertexDeclaration();
		for (int i = 0; i < vertex_declaration.size(); ++i) {
			vertex_declaration_->AddElement(vertex_declaration[i]);
		}
	}

	VertexBuffer::~VertexBuffer() {
		if (vertex_declaration_) {
			delete vertex_declaration_;
			vertex_declaration_ = 0;
		}
	}
//-------------------------------------------------------------------------
// IndexBuffer
//-------------------------------------------------------------------------
	IndexBuffer::IndexBuffer(const uint32 buffer_size, 
							 const BufferUsage buffer_usage, 
							 const uint32 num_indices, 
							 const IndexType index_type)
	:GPUBuffer(buffer_size, buffer_usage),
	num_indices_(num_indices),
	index_type_(index_type)
	{

	}
	IndexBuffer::~IndexBuffer() {
	}
} // epic