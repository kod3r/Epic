/**
 * @file EpicGLRenderSystem.h
 * @brief 
 * @author Xiao Miaomiao
 * @version 1.0
 * @data 2015
 */
#ifndef EPIC_INCLUDE_OPENGL_EPICGLRENDERSYSTEM_H
#define EPIC_INCLUDE_OPENGL_EPICGLRENDERSYSTEM_H

#include "include/EpicPrerequisites.h"
#include "include/EpicRenderSystem.h"
#include <GL/glew.h>
#include <GL/wglew.h>

namespace epic {
	// @remark
	//   
	class EPIC_EXPORT GLRenderSystem : public RenderSystem {
	public:
		// @brief 
		// @param rwnd, ...
		// @return ,...
		GLRenderSystem(RenderWindow* rwnd);
		virtual ~GLRenderSystem();

		void set_opengl_version(const int major,const int minor)override;
		// 
		virtual void InitRender();
		virtual bool Reset();
		virtual void ClearColorBuffer(void);
		virtual void ClearDepthBuffer(void);
		virtual void SwapRenderBuffers(void);
		virtual void RenderFlush(void);
		virtual void RenderFinish(void);
		
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
} // epic


#endif // EPIC_INCLUDE_OPENGL_EPICGLRENDERSYSTEM_H
