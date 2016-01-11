/* ------------------------------------------------------------------------- */
// File       : Mesh_Sphere.h
// Author     : snowblind
// Project    : from www.ogre3d.org/wiki
/* ------------------------------------------------------------------------- */
#ifndef _MESH_SPHERE_H_
#define _MESH_SPHERE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Ogre.h"
using namespace Ogre;

#include "GeometricMesh.h"

/* ------------------------------------------------------------------------- */
/// This class create a Mesh Sphere.
/* ------------------------------------------------------------------------- */
class Mesh_Sphere : public GeometricMesh
{
public:
	Mesh_Sphere(Real radius, int nRings=16, int nSegments=16);
	virtual ~Mesh_Sphere();

protected:
	void   fillMesh();
	int    mRings;
	int    mSegments;
};

#endif


