#include "include/EpicRenderSystem.h"
#include "include/EpicResourceManager.h"

namespace epic {
	template<> RenderSystem* Singleton<RenderSystem>::singleton_ = 0;

	RenderSystem::RenderSystem(RenderWindow* rwnd):
	current_render_type_(RENDERSYSTEMTYPE_OPENGL),
	enable_double_buffer_(true),
	enable_depth_buffer_(true),
	color_bits_(32),
	depth_bits_(32)
	{	
		render_window_ = rwnd;
		depth_clear_float_ = 1.0f;
		clear_color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	RenderSystem& RenderSystem::GetInstance(void) {
		assert(singleton_);
		return *singleton_;
	}
	RenderSystem* RenderSystem::GetInstancePtr(void) {
		return singleton_;
	}

	void RenderSystem::InitRender(void)
	{
		//return true;
	}

	void RenderSystem::set_opengl_version(const int major,const int minor)
	{
		assert(current_render_type_ == RENDERSYSTEMTYPE_OPENGL);
	}

	RenderSystemType RenderSystem::current_render_type()
	{
		return current_render_type_;
	}

	void RenderSystem::set_enable_double_buffer(const bool enable_double_buffer)
	{
		enable_depth_buffer_ = enable_double_buffer;
		//if (enable_double_buffer_)
		//	pixel_format_descriptor_.dwFlags |= PFD_DOUBLEBUFFER;
		//else
		//	pixel_format_descriptor_.dwFlags &= ~PFD_DOUBLEBUFFER;
		Reset();
	}

	bool RenderSystem::enable_double_buffer()const
	{
		return enable_double_buffer_;
	}

	void RenderSystem::set_enable_depth_buffer(const bool depth_buffer)
	{
		enable_depth_buffer_ = depth_buffer;
		//if (enable_depth_buffer_)
		//	pixel_format_descriptor_.dwFlags |= PFD_DEPTH_DONTCARE;
		//else
		//	pixel_format_descriptor_.dwFlags &= ~PFD_DEPTH_DONTCARE;
		Reset();
	}

	bool RenderSystem::enable_depth_buffer()const
	{
		return enable_depth_buffer_;
	}

	void RenderSystem::set_color_depth_bits(const int color_bits,const int depth_bits)
	{
		color_bits_ = color_bits;
		depth_bits_ = depth_bits;
		//pixel_format_descriptor_.cColorBits = color_bits;
		//pixel_format_descriptor_.cDepthBits = depth_bits;
		Reset();
	}

	void RenderSystem::set_render_window(RenderWindow* rwnd)
	{
		render_window_ = rwnd;
	}

	RenderWindow* RenderSystem::render_window()const
	{
		return render_window_;
	}

	RenderSystem::~RenderSystem(){}

	bool RenderSystem::Reset()
	{
		return true;
	}

	void RenderSystem::set_clear_color(const float r,const float g,const float b,const float alpha)
	{
		clear_color_ = glm::vec4(r, g, b, alpha);
	}

	void RenderSystem::set_depth_clear_float(const float depth)
	{
		depth_clear_float_ = depth;
	}
} // epic