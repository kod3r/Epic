#ifndef EPIC_INCLUDE_EPICGLRENDERSYSTEM_H
#define EPIC_INCLUDE_EPICGLRENDERSYSTEM_H

#include "include/EpicRenderSystem.h"
#include "include/EpicResourceManager.h"
#include <GL/glew.h>
#include <GL/wglew.h>

namespace epic {
	class EPIC_EXPORT GLRenderSystem : public RenderSystem {
	public:
		GLRenderSystem(RenderWindow* rwnd);
		virtual ~GLRenderSystem();


		void set_opengl_version(const int major,const int minor)override;

		virtual void InitRender();
		virtual bool Reset();
		virtual void ClearColorBuffer(void);
		virtual void ClearDepthBuffer(void);
		virtual void SwapRenderBuffers(void);
		virtual void RenderFlush(void);
		virtual void RenderFinish(void);
		
		HDC hdc(void)const{return hdc_;}
		HGLRC hrc(void)const{return hrc_;}
		virtual GLResourceManager* resource_manager();

	private:
		HGLRC hrc_;
		HDC hdc_;
		HWND hwnd_;
		HINSTANCE hInstance_;

		int opengl_major_version_;
		int opengl_minor_version_;

		PIXELFORMATDESCRIPTOR pixel_format_descriptor_;

		GLResourceManager* gl_resource_manager_;
	}; // GLRenderSystem
} // epic


#endif // EPIC_INCLUDE_EPICGLRENDERSYSTEM_H
