#ifndef EPIC_INCLUDE_EPICMATERIAL_H
#define EPIC_INCLUDE_EPICMATERIAL_H

#include "include/EpicPrerequisites.h"

namespace epic {
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