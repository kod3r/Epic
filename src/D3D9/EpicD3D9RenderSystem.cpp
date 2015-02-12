#include "include/d3d9/EpicD3D9RenderSystem.h"
#include "include/EpicRenderWindow.h"
#include "include/EpicException.h"

namespace epic {
	D3D9RenderSystem::D3D9RenderSystem(RenderWindow* render_window):
	RenderSystem(render_window),
	idirect3d9_(NULL),
	idirect3d_device9_(NULL),
	adapter_(D3DADAPTER_DEFAULT),
	device_type_(D3DDEVTYPE_HAL){
	}
	D3D9RenderSystem::~D3D9RenderSystem() {
	}

	void D3D9RenderSystem::InitRender() {
		// 1. Acquiring an IDirect3D9 Interface
		if ( !(idirect3d9_ = Direct3DCreate9(D3D_SDK_VERSION)) )
			throw Exception("D3D9RenderSystem::InitDevice() -> Direct3DCreate9() failed!");
		

		// 2. Verifying HAL support
		D3DDISPLAYMODE mode;
		D3DFORMAT display_format = D3DFMT_X8R8G8B8;
		D3DFORMAT backbuffer_format = D3DFMT_X8R8G8B8;
		idirect3d9_->GetAdapterDisplayMode(adapter_, &mode);
		if ( FAILED(idirect3d9_->CheckDeviceType(adapter_, device_type_,
			mode.Format, mode.Format, true)) )
			throw Exception("D3D9RenderSystem::InitDevice() -> CheckDeviceType() failed!\nFormat not support!");
		if ( FAILED(idirect3d9_->CheckDeviceType(adapter_, device_type_,
			display_format, backbuffer_format, false)) )
			throw Exception("D3D9RenderSystem::InitDevice() -> CheckDeviceType() failed!\nFormat not support!");

		// 3. Checking for Hardware Vertex Processing
		D3DCAPS9 caps;
		if ( FAILED( idirect3d9_->GetDeviceCaps(adapter_, device_type_, &caps) ))
			throw Exception("D3D9RenderSystem::InitDevice() -> GetDeviceCaps() failed!");
		DWORD devBehaviorFlags = 0;
		if ( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) {
			devBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}else {
			devBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}

		if ( caps.DevCaps & D3DDEVCAPS_PUREDEVICE &&
			devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING ) 
		{
			devBehaviorFlags |= D3DCREATE_PUREDEVICE;
		}

		// 4. D3DPRESENT_PARAMETERS	
	//	DWORD qualityLevels;
		/*HR(m_pD3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, 
			m_deviceType, D3DFMT_X8R8G8B8, true, D3DMULTISAMPLE_8_SAMPLES, &qualityLevels));
		HR(m_pD3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, 
			m_deviceType, D3DFMT_D24S8, true, D3DMULTISAMPLE_8_SAMPLES, &qualityLevels));*/
		ZeroMemory(&d3d_pparam_, sizeof(d3d_pparam_));
		d3d_pparam_.BackBufferWidth = 0;
		d3d_pparam_.BackBufferHeight = 0;
		//m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3d_pparam_.BackBufferFormat = backbuffer_format;
		d3d_pparam_.BackBufferCount = 1;
		/*m_d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;*/
		/*m_d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;*/
		d3d_pparam_.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3d_pparam_.MultiSampleQuality = 0;
		d3d_pparam_.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3d_pparam_.hDeviceWindow = render_window_->hwnd();
		d3d_pparam_.Windowed = true;
		d3d_pparam_.EnableAutoDepthStencil = true;
		d3d_pparam_.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3d_pparam_.Flags = 0;
		d3d_pparam_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3d_pparam_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		// 5. Creating the IDirect3DDevice9 Interface
		if( FAILED(idirect3d9_->CreateDevice(adapter_, device_type_, render_window_->hwnd(),
			devBehaviorFlags, &d3d_pparam_, &idirect3d_device9_) ))
			throw Exception("D3D9RenderSystem::InitDevice() -> CreateDevice() failed!");
		ShowWindow(render_window_->hwnd(), SW_SHOW);
	}
	void D3D9RenderSystem::ClearColorBuffer(void){
		if ( FAILED(idirect3d_device9_->Clear(0, 0, D3DCLEAR_TARGET, 
			D3DCOLOR_COLORVALUE(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a),
			depth_clear_float_, 0)) )
			throw Exception("D3D9RenderSystem::ClearColorBuffer() -> Clear failed!");
	}
	void D3D9RenderSystem::ClearDepthBuffer(void){
		if ( FAILED(idirect3d_device9_->Clear(0, 0, D3DCLEAR_ZBUFFER, 
			D3DCOLOR_COLORVALUE(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a),
			depth_clear_float_, 0)) )
			throw Exception("D3D9RenderSystem::ClearDepthBuffer() -> Clear() failed!");
	}
	void D3D9RenderSystem::SwapRenderBuffers(void){
		if ( FAILED(idirect3d_device9_->Present(0, 0, 0, 0)) )
			throw Exception("D3D9RenderSystem::SwapRenderBuffers() -> Present() failed!");
		
	}
	void D3D9RenderSystem::RenderFlush(void){}
	void D3D9RenderSystem::RenderFinish(void){}
} // epic