/* ------------------------------------------------------------------------- */
// File       : Mesh_Icosa.h
// Author     : David de Lorenzo
// Project    : Long Forgotten Earth
/* ------------------------------------------------------------------------- */
#ifndef _MESH_ICOSA_H_
#define _MESH_ICOSA_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Ogre.h"
using namespace Ogre;

#include "GeometricMesh.h"

/* ------------------------------------------------------------------------- */
/// This class create an Icosahedron Mesh.
/** This is a simple class, based on the GeometricMesh generic class. */
/* ------------------------------------------------------------------------- */
class Mesh_Icosa : public GeometricMesh
{
public:
	Mesh_Icosa(Real radius);
	virtual ~Mesh_Icosa();

protected:
	void   fillMesh();
};

#endif


