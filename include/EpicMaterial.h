#ifndef EPIC_INCLUDE_EPICMATERIAL_H
#define EPIC_INCLUDE_EPICMATERIAL_H

#include "include/EpicPrerequisites.h"

namespace epic {
	// @remark abstract shader program class, GLSL shader or HLSL shader depending on the current renderer.
	class EPIC_EXPORT ShaderProgram
	{
	public:
		void SetName(std::string name);
	private:
		RenderSystemType current_render_system_;
		GLProgram* gl_program_ptr_;
	};

	class EPIC_EXPORT Material
	{
	public:
		void setName(std::string name);
		void InitMeshFromFile(const aiScene* scene);
	private:
		RenderSystemType current_render_system_;
		//....
	};

} // epic

#endif // EPIC_INCLUDE_EPICMATERIAL_H