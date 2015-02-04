#ifndef EPIC_INCLUDE_EPICPREREQUISITES_H
#define EPIC_INCLUDE_EPICPREREQUISITES_H

#include <cassert>
#include <string>
#include <vector>

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include "glm/glm.hpp"

#pragma warning(disable:4251)
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

	typedef glm::vec2 Vector2;
	typedef glm::vec3 Vector3;
	typedef glm::vec4 Vector4;
	typedef glm::mat3 Matrix3;
	typedef glm::mat4 Matrix4;
	typedef glm::quat Quaternion;
	// forward declarations
	class D3D9RenderSystem;
	class Exception;
	class GLRenderSystem;
	class InputManager;
	class Mesh;
	class Mouse;
	class MouseListener;
	class Node;
	class RenderSystem;
	class RenderWindow;
	class Root;
	class SceneManager;

} // epic

#endif // EPIC_INCLUDE_EPICPREREQUISITES_H