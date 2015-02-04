#ifndef EPIC_INCLUDE_EPICMESH_H
#define EPIC_INCLUDE_EPICMESH_H

#include "include/EpicPrerequisites.h"

namespace epic {
	class EPIC_EXPORT Mesh {
	public: 
		Mesh();
		virtual ~Mesh();
		bool LoadMeshFromFile(const String& file_name);
	};

} // epic

#endif // EPIC_INCLUDE_EPICMESH_H