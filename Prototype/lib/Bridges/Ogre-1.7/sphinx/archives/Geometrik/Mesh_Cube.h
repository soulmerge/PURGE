/* ------------------------------------------------------------------------- */
// File       : Mesh_Cube.h
// Author     : David de Lorenzo
// Project    : Long Forgotten Earth
/* ------------------------------------------------------------------------- */
#ifndef _MESH_CUBE_H_
#define _MESH_CUBE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Ogre.h"
using namespace Ogre;

#include "GeometricMesh.h"

/* ------------------------------------------------------------------------- */
/// This class is an example of mesh creation using the GeometricMesh surclass.
/* ------------------------------------------------------------------------- */
class Mesh_Cube : public GeometricMesh
{
public:
	Mesh_Cube(Real radius);
	virtual ~Mesh_Cube();

protected:
	void   fillMesh();

};

#endif


