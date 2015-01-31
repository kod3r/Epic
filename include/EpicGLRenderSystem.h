#ifndef EPIC_INCLUDE_EPICGLRENDERSYSTEM_H
#define EPIC_INCLUDE_EPICGLRENDERSYSTEM_H

#include "include/EpicRenderSystem.h"

#include <GL/glew.h>
#include <GL/wglew.h>

namespace epic {
	class EPIC_EXPORT GLRenderSystem : public RenderSystem {
	public:
		GLRenderSystem(RenderWindow* rwnd);
		virtual ~GLRenderSystem();

		static GLRenderSystem& GetInstance(void);
		static GLRenderSystem* GetInstancePtr(void);
		void set_opengl_version(const int major,const int minor)override;

		virtual bool InitRender()override;
		virtual bool Reset()override;
		virtual void ClearColorBuffer(void)override;
		virtual void ClearDepthBuffer(void)override;
		virtual void SwapRenderBuffers(void)override;
		virtual void RenderFlush(void)override;
		virtual void RenderFinish(void)override;
		
		HDC hdc(void)const{return hdc_;}
		HGLRC hrc(void)const{return hrc_;}

	private:
		HGLRC hrc_;
		HDC hdc_;
		HWND hwnd_;
		HINSTANCE hInstance_;

		int opengl_major_version_;
		int opengl_minor_version_;

		PIXELFORMATDESCRIPTOR pixel_format_descriptor_;
	}; // GLRenderSystem

	class GLMaterial
	{
	public:
	private:
	};

	class GLTexture
	{
	public:
	private:
	};
} // epic


#endif // EPIC_INCLUDE_EPICGLRENDERSYSTEM_H
