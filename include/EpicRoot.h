#ifndef EPIC_INCLUDE_EPICROOT_H
#define EPIC_INCLUDE_EPICROOT_H

#include "include/EpicPrerequisites.h"
#include "include/EpicSingleton.h"

namespace epic {
	class EPIC_EXPORT Root : public Singleton<Root>{
	public:
		Root();
		~Root();
		static Root& GetInstance(void);
		static Root* GetInstancePtr(void);
	}; // Root
} // epic

#endif // EPIC_INCLUDE_EPICROOT_H