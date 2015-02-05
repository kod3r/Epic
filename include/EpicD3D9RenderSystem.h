#ifndef EPIC_INCLUDE_EPICD3D9RENDERSYSTEM_H
#define EPIC_INCLUDE_EPICD3D9RENDERSYSTEM_H

#include "include/EpicPrerequisites.h"
#include "include/EpicRenderSystem.h"
#include <d3d9.h>

namespace epic {
	class D3D9RenderSystem : public RenderSystem{
	public:
		D3D9RenderSystem(RenderWindow* render_window);
		virtual ~D3D9RenderSystem();
		virtual void InitRender(void);
		

		virtual void ClearColorBuffer(void);
		virtual void ClearDepthBuffer(void);
		virtual void SwapRenderBuffers(void);
		virtual void RenderFlush(void);
		virtual void RenderFinish(void);
	private:
		
		IDirect3D9* idirect3d9_;
		IDirect3DDevice9* idirect3d_device9_;
		UINT adapter_;
		D3DDEVTYPE device_type_;
		D3DPRESENT_PARAMETERS d3d_pparam_;
	};
} // EPIC_INCLUDE_EPICD3D9RENDERSYSTEM_H

#endif // EPIC_INCLUDE_EPICD3D9RENDERSYSTEM_H