#include "CoordinateSystem.h"

#include "../Math/Vector3.h"

namespace PURGE
{

	const CoordinateSystem
	CoordinateSystem::PX_PY_PZ(Vector3( 1,  0,  0), Vector3( 0,  1,  0), Vector3( 0,  0,  1), true);

	const CoordinateSystem
	CoordinateSystem::PX_PY_NZ(Vector3( 1,  0,  0), Vector3( 0,  1,  0), Vector3( 0,  0, -1), false);

	const CoordinateSystem
	CoordinateSystem::PX_NY_PZ(Vector3( 1,  0,  0), Vector3( 0, -1,  0), Vector3( 0,  0,  1), false);

	const CoordinateSystem
	CoordinateSystem::PX_NY_NZ(Vector3( 1,  0,  0), Vector3( 0, -1,  0), Vector3( 0,  0, -1), true);

	const CoordinateSystem
	CoordinateSystem::NX_PY_PZ(Vector3(-1,  0,  0), Vector3( 0,  1,  0), Vector3( 0,  0,  1), false);

	const CoordinateSystem
	CoordinateSystem::NX_PY_NZ(Vector3(-1,  0,  0), Vector3( 0,  1,  0), Vector3( 0,  0, -1), true);

	const CoordinateSystem
	CoordinateSystem::NX_NY_PZ(Vector3(-1,  0,  0), Vector3( 0, -1,  0), Vector3( 0,  0,  1), true);

	const CoordinateSystem
	CoordinateSystem::NX_NY_NZ(Vector3(-1,  0,  0), Vector3( 0, -1,  0), Vector3( 0,  0, -1), false);

	const CoordinateSystem
	CoordinateSystem::PX_PZ_PY(Vector3( 1,  0,  0), Vector3( 0,  0,  1), Vector3( 0,  1,  0), false);

	const CoordinateSystem
	CoordinateSystem::PX_PZ_NY(Vector3( 1,  0,  0), Vector3( 0,  0,  1), Vector3( 0, -1,  0), true);

	const CoordinateSystem
	CoordinateSystem::PX_NZ_PY(Vector3( 1,  0,  0), Vector3( 0,  0, -1), Vector3( 0,  1,  0), true);

	const CoordinateSystem
	CoordinateSystem::PX_NZ_NY(Vector3( 1,  0,  0), Vector3( 0,  0, -1), Vector3( 0, -1,  0), false);

	const CoordinateSystem
	CoordinateSystem::NX_PZ_PY(Vector3(-1,  0,  0), Vector3( 0,  0,  1), Vector3( 0,  1,  0), true);

	const CoordinateSystem
	CoordinateSystem::NX_PZ_NY(Vector3(-1,  0,  0), Vector3( 0,  0,  1), Vector3( 0, -1,  0), false);

	const CoordinateSystem
	CoordinateSystem::NX_NZ_PY(Vector3(-1,  0,  0), Vector3( 0,  0, -1), Vector3( 0,  1,  0), false);

	const CoordinateSystem
	CoordinateSystem::NX_NZ_NY(Vector3(-1,  0,  0), Vector3( 0,  0, -1), Vector3( 0, -1,  0), true);

	const CoordinateSystem
	CoordinateSystem::PY_PX_PZ(Vector3( 0,  1,  0), Vector3( 1,  0,  0), Vector3( 0,  0,  1), false);

	const CoordinateSystem
	CoordinateSystem::PY_PX_NZ(Vector3( 0,  1,  0), Vector3( 1,  0,  0), Vector3( 0,  0, -1), true);

	const CoordinateSystem
	CoordinateSystem::PY_NX_PZ(Vector3( 0,  1,  0), Vector3(-1,  0,  0), Vector3( 0,  0,  1), true);

	const CoordinateSystem
	CoordinateSystem::PY_NX_NZ(Vector3( 0,  1,  0), Vector3(-1,  0,  0), Vector3( 0,  0, -1), false);

	const CoordinateSystem
	CoordinateSystem::NY_PX_PZ(Vector3( 0, -1,  0), Vector3( 1,  0,  0), Vector3( 0,  0,  1), true);

	const CoordinateSystem
	CoordinateSystem::NY_PX_NZ(Vector3( 0, -1,  0), Vector3( 1,  0,  0), Vector3( 0,  0, -1), false);

	const CoordinateSystem
	CoordinateSystem::NY_NX_PZ(Vector3( 0, -1,  0), Vector3(-1,  0,  0), Vector3( 0,  0,  1), false);

	const CoordinateSystem
	CoordinateSystem::NY_NX_NZ(Vector3( 0, -1,  0), Vector3(-1,  0,  0), Vector3( 0,  0, -1), true);

	const CoordinateSystem
	CoordinateSystem::PY_PZ_PX(Vector3( 0,  1,  0), Vector3( 0,  0,  1), Vector3( 1,  0,  0), true);

	const CoordinateSystem
	CoordinateSystem::PY_PZ_NX(Vector3( 0,  1,  0), Vector3( 0,  0,  1), Vector3(-1,  0,  0), false);

	const CoordinateSystem
	CoordinateSystem::PY_NZ_PX(Vector3( 0,  1,  0), Vector3( 0,  0, -1), Vector3( 1,  0,  0), false);

	const CoordinateSystem
	CoordinateSystem::PY_NZ_NX(Vector3( 0,  1,  0), Vector3( 0,  0, -1), Vector3(-1,  0,  0), true);

	const CoordinateSystem
	CoordinateSystem::NY_PZ_PX(Vector3( 0, -1,  0), Vector3( 0,  0,  1), Vector3( 1,  0,  0), false);

	const CoordinateSystem
	CoordinateSystem::NY_PZ_NX(Vector3( 0, -1,  0), Vector3( 0,  0,  1), Vector3(-1,  0,  0), true);

	const CoordinateSystem
	CoordinateSystem::NY_NZ_PX(Vector3( 0, -1,  0), Vector3( 0,  0, -1), Vector3( 1,  0,  0), true);

	const CoordinateSystem
	CoordinateSystem::NY_NZ_NX(Vector3( 0, -1,  0), Vector3( 0,  0, -1), Vector3(-1,  0,  0), false);

	const CoordinateSystem
	CoordinateSystem::PZ_PX_PY(Vector3( 0,  0,  1), Vector3( 1,  0,  0), Vector3( 0,  1,  0), true);

	const CoordinateSystem
	CoordinateSystem::PZ_PX_NY(Vector3( 0,  0,  1), Vector3( 1,  0,  0), Vector3( 0, -1,  0), false);

	const CoordinateSystem
	CoordinateSystem::PZ_NX_PY(Vector3( 0,  0,  1), Vector3(-1,  0,  0), Vector3( 0,  1,  0), false);

	const CoordinateSystem
	CoordinateSystem::PZ_NX_NY(Vector3( 0,  0,  1), Vector3(-1,  0,  0), Vector3( 0, -1,  0), true);

	const CoordinateSystem
	CoordinateSystem::NZ_PX_PY(Vector3( 0,  0, -1), Vector3( 1,  0,  0), Vector3( 0,  1,  0), false);

	const CoordinateSystem
	CoordinateSystem::NZ_PX_NY(Vector3( 0,  0, -1), Vector3( 1,  0,  0), Vector3( 0, -1,  0), true);

	const CoordinateSystem
	CoordinateSystem::NZ_NX_PY(Vector3( 0,  0, -1), Vector3(-1,  0,  0), Vector3( 0,  1,  0), true);

	const CoordinateSystem
	CoordinateSystem::NZ_NX_NY(Vector3( 0,  0, -1), Vector3(-1,  0,  0), Vector3( 0, -1,  0), false);

	const CoordinateSystem
	CoordinateSystem::PZ_PY_PX(Vector3( 0,  0,  1), Vector3( 0,  1,  0), Vector3( 1,  0,  0), false);

	const CoordinateSystem
	CoordinateSystem::PZ_PY_NX(Vector3( 0,  0,  1), Vector3( 0,  1,  0), Vector3(-1,  0,  0), true);

	const CoordinateSystem
	CoordinateSystem::PZ_NY_PX(Vector3( 0,  0,  1), Vector3( 0, -1,  0), Vector3( 1,  0,  0), true);

	const CoordinateSystem
	CoordinateSystem::PZ_NY_NX(Vector3( 0,  0,  1), Vector3( 0, -1,  0), Vector3(-1,  0,  0), false);

	const CoordinateSystem
	CoordinateSystem::NZ_PY_PX(Vector3( 0,  0, -1), Vector3( 0,  1,  0), Vector3( 1,  0,  0), true);

	const CoordinateSystem
	CoordinateSystem::NZ_PY_NX(Vector3( 0,  0, -1), Vector3( 0,  1,  0), Vector3(-1,  0,  0), false);

	const CoordinateSystem
	CoordinateSystem::NZ_NY_PX(Vector3( 0,  0, -1), Vector3( 0, -1,  0), Vector3( 1,  0,  0), false);

	const CoordinateSystem
	CoordinateSystem::NZ_NY_NX(Vector3( 0,  0, -1), Vector3( 0, -1,  0), Vector3(-1,  0,  0), true);

	const CoordinateSystem&
	CoordinateSystem::OpenGL(CoordinateSystem::NZ_PX_PY);

	const CoordinateSystem&
	CoordinateSystem::DirectX(CoordinateSystem::PZ_PX_PY);

	const CoordinateSystem*
	CoordinateSystem::_current(&CoordinateSystem::OpenGL);

}

