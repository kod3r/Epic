#ifndef EPIC_INCLUDE_EPICMATERIAL_H
#define EPIC_INCLUDE_EPICMATERIAL_H

#include "include/EpicPrerequisites.h"
struct aiMaterial;
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
		//void setName(std::string name);
		Material();
		~Material();
		void InitMeshFromFile(const aiMaterial* material_from_file);
		void LoadTexture(const String& file_name);
	private:
		RenderSystemType current_render_system_;
		String name_;
		int shading_model_;
		Vector3 color_emissive_;
		Vector4 color_diffuse_;
		Vector3 color_specular_;
		Vector4 color_ambient_;
		float shininess_;
		String texture_path_;
	};

} // epic

#endif // EPIC_INCLUDE_EPICMATERIAL_H