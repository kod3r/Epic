#include "include/EpicGLRenderSystem.h"
#include "include/EpicRenderWindow.h"
#include "include/EpicException.h"
namespace epic{
	GLRenderSystem::GLRenderSystem(RenderWindow* rwnd):RenderSystem(rwnd)
	{
		current_render_type_ = RENDERSYSTEMTYPE_OPENGL;
		opengl_major_version_ = 4;
		opengl_minor_version_ = 3;
		gl_resource_manager_ = new GLResourceManager();
	}

	GLRenderSystem::~GLRenderSystem()
	{
		
	}

	void GLRenderSystem::InitRender()
	{
		hwnd_ = render_window_->hwnd();
		hInstance_ = render_window_->hinstance();
		if (!(hdc_ = GetDC(hwnd_)))
			throw(Exception("InitRender() -> GetDC() failed!"));
		PIXELFORMATDESCRIPTOR pixel_format_descriptor = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW|
			PFD_SUPPORT_OPENGL|
			PFD_SWAP_EXCHANGE|
			PFD_DOUBLEBUFFER|
			PFD_DEPTH_DONTCARE,
			PFD_TYPE_RGBA,
			color_bits_,
			0, 0, 0, 0, 0, 0,						// ºöÂÔµÄÉ«²ÊÎ»
			0,								// ÎÞAlpha»º´æ
			0,								// ºöÂÔShift Bit
			0,								// ÎÞÀÛ¼Ó»º´æ
			0, 0, 0, 0,							// ºöÂÔ¾Û¼¯Î»
			depth_bits_,								// 16Î» Z-»º´æ (Éî¶È»º´æ)
			0,								// ÎÞÃÉ°å»º´æ
			0,								// ÎÞ¸¨Öú»º´æ
			PFD_MAIN_PLANE,							// Ö÷»æÍ¼²ã
			0,								// Reserved
			0, 0, 0			
		};

		pixel_format_descriptor_ = pixel_format_descriptor;

		Reset();

		ShowWindow(hwnd_, SW_SHOW);
		//return true;
	}

	bool GLRenderSystem::Reset()
	{
		if (enable_depth_buffer_)
			pixel_format_descriptor_.dwFlags |= PFD_DEPTH_DONTCARE;
		else
			pixel_format_descriptor_.dwFlags &= ~PFD_DEPTH_DONTCARE;
		if (enable_double_buffer_)
			pixel_format_descriptor_.dwFlags |= PFD_DOUBLEBUFFER;
		else
			pixel_format_descriptor_.dwFlags &= ~PFD_DOUBLEBUFFER;
		pixel_format_descriptor_.cColorBits = color_bits_;
		pixel_format_descriptor_.cDepthBits = depth_bits_;

		int pixelformat;
		if (!(pixelformat = ChoosePixelFormat(hdc_, &pixel_format_descriptor_)))
			throw(Exception("Reset() -> ChoosePixelFormat() failed!"));
		if (!SetPixelFormat(hdc_, pixelformat, &pixel_format_descriptor_))
			throw(Exception("Reset() -> SetPixelFormat() failed!"));
		if (!(hrc_ = wglCreateContext(hdc_)))
			throw(Exception("Reset() -> wglCreateContext() failed!"));
		if (!wglMakeCurrent(hdc_, hrc_))
			throw(Exception("Reset() -> wglMakeCurrent() failed!"));
		GLenum err = glewInit();
		if (GLEW_OK != err)
			throw(Exception("Reset() -> glewInit() failed!"));
		
		const GLubyte* OpenGLVersion =glGetString(GL_VERSION);

		if ('0'+opengl_major_version_ > OpenGLVersion[0])
		{
			opengl_major_version_ = OpenGLVersion[0] - '0';
			opengl_minor_version_ = OpenGLVersion[2] - '0';
		}
		else if (('0'+opengl_major_version_ == OpenGLVersion[0]) && '0'+opengl_minor_version_ > OpenGLVersion[2] )
		{
			opengl_minor_version_ = OpenGLVersion[2] - '0';
		}

		if (wglewIsSupported("WGL_ARB_create_context") == 1)
		{
			int attribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, opengl_major_version_,
				WGL_CONTEXT_MINOR_VERSION_ARB, opengl_minor_version_,
				WGL_CONTEXT_FLAGS_ARB, 0,
				0
			};

			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hrc_);

			if (!(hrc_ = wglCreateContextAttribsARB(hdc_, 0, attribs)))
				throw(Exception("Reset() -> wglCreateContextAttribsARB() failed!"));
		}

		if (!wglMakeCurrent(hdc_, hrc_))
			throw(Exception("Reset() -> wglMakeCurrent() failed!"));

		return true;
	}

	void GLRenderSystem::set_opengl_version(const int major,const int minor)
	{
		assert(current_render_type_ == RENDERSYSTEMTYPE_OPENGL);
		opengl_major_version_ = major;
		opengl_minor_version_ = minor;

		Reset();
	}

	void GLRenderSystem::ClearColorBuffer()
	{
		glClearColor(clear_color_.r,
			clear_color_.g,
			clear_color_.b,
			clear_color_.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GLRenderSystem::ClearDepthBuffer()
	{
		glClearDepth(depth_clear_float_);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void GLRenderSystem::SwapRenderBuffers()
	{
		SwapBuffers(hdc_);
	}

	void GLRenderSystem::RenderFlush(void)
	{
		glFlush();
	}

	void GLRenderSystem::RenderFinish(void)
	{
		glFinish();
	}

	GLResourceManager* GLRenderSystem::resource_manager()
	{
		return gl_resource_manager_;
	}
}

