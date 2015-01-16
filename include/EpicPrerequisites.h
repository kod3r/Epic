#ifndef EPIC_INCLUDE_EPICPREREQUISITES_H
#define EPIC_INCLUDE_EPICPREREQUISITES_H

#include <string>

namespace epic {
	#if defined(EPIC_NONCLIENT_BUILD)
	#	define EPIC_EXPORT __declspec(dllexport)
	#else
	#	define EPIC_EXPORT __declspec(dllimport)
	#endif

	// build-in type define
	typedef unsigned __int64 uint64;
	typedef unsigned int uint32;
	typedef unsigned short uint16;
	typedef unsigned char uint8;
	typedef __int64 int64;
	typedef int int32;
	typedef short int16;
	typedef char int8;
	typedef float float32;
	typedef double float64;
	
	typedef std::string String;

	// forward declarations
	class RenderSystem;
	class Root;

} // epic

#endif // EPIC_INCLUDE_EPICPREREQUISITES_H