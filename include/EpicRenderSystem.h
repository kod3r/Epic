#ifndef EPIC_INCLUDE_EPICRENDERSYSTEM_H
#define EPIC_INCLUDE_EPICRENDERSYSTEM_H

#include "include/EpicPrerequisites.h"
#include "include/EpicSingleton.h"
#include <Windows.h>
#include <glm/glm.hpp>

namespace epic {
	enum RenderSystemType{RENDERSYSTEMTYPE_D3D9 = 0, RENDERSYSTEMTYPE_OPENGL};
	class EPIC_EXPORT RenderSystem : public Singleton<RenderSystem> {
	public:
		RenderSystem(){}
		RenderSystem(RenderWindow* rwnd);
		virtual ~RenderSystem();
		virtual void InitRender(void);
		virtual void set_opengl_version(const int major,const int minor);

		virtual void ClearColorBuffer(void){}
		virtual void ClearDepthBuffer(void){}
		virtual void SwapRenderBuffers(void){}
		virtual void RenderFlush(void){}
		virtual void RenderFinish(void){}

		static RenderSystem& GetInstance(void);
		static RenderSystem* GetInstancePtr(void);
		RenderSystemType current_render_type(void);

		void set_enable_double_buffer(const bool double_buffer);
		bool enable_double_buffer(void)const;

		void set_enable_depth_buffer(const bool depth_buffer);
		bool enable_depth_buffer(void)const;

		void set_color_depth_bits(const int color_bits,const int depth_bits);

		void set_render_window(RenderWindow* rwnd);
		RenderWindow* render_window() const;
		
		void set_clear_color(const float r,const float g,const float b,const float alpha);
		void set_depth_clear_float(const float depth);
	protected:
		RenderSystemType current_render_type_;

		bool enable_double_buffer_;
		bool enable_depth_buffer_;
		int color_bits_;
		int depth_bits_;

		RenderWindow* render_window_;
		virtual bool Reset();

		glm::vec4 clear_color_;
		float depth_clear_float_;
	}; // RenderSystem
} // epic

#endif // EPIC_INCLUDE_EPICRENDERSYSTEM_H