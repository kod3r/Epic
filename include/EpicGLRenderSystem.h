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
		void set_opengl_version(const int major,const int minor);

		virtual bool InitRender()override;
		virtual bool Reset()override;
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
