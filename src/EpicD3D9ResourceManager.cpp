#include "include/EpicD3D9ResourceManager.h"
#include "include/EpicRoot.h"
#include "include/EpicD3D9RenderSystem.h"
#include "include/EpicException.h"

namespace epic {
//-------------------------------------------------------------------------
// D3D9AttributeBuffer
//-------------------------------------------------------------------------	


//-------------------------------------------------------------------------
// D3D9VertexData
//-------------------------------------------------------------------------
	D3D9VertexData::D3D9VertexData(uint32 buffer_size, uint32 usage_flag) {
		IDirect3DDevice9* d3d9_device = (static_cast<D3D9RenderSystem*>(Root::GetInstancePtr()->render_system()))->idirect3d_device9();
		D3DPOOL d3d_pool;
		DWORD d3d_usage = 0;
		if (usage_flag & BUFFER_USAGE_DYNAMIC) {
			d3d_usage |= D3DUSAGE_DYNAMIC;
			d3d_pool = D3DPOOL_DEFAULT;
		}else {
			d3d_pool = D3DPOOL_MANAGED;
		}
		if (usage_flag & BUFFER_USAGE_WRITEONLY) {
			d3d_usage |= D3DUSAGE_WRITEONLY;
		}
		if ( FAILED(d3d9_device->CreateVertexBuffer(buffer_size, d3d_usage, 0, d3d_pool, &vertex_buffer_, 0)) )
			throw Exception("D3D9VertexData::D3D9VertexData() CreateVertexBuffer failed!");
		index_buffer_ = NULL;
	}
	void D3D9VertexData::AddBuffer(const D3D9AttributeBuffer* attribute_buffer,const int component_stride, const String& attribute_name, bool is_indices) {

	}
//-------------------------------------------------------------------------
// D3D9ResourceManager
//-------------------------------------------------------------------------
} // epic