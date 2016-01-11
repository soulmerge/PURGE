/* ------------------------------------------------------------------------- */
// File       : GeometricMesh.h
// Project    : Long Forgotten Earth
// Author     : David de Lorenzo
/* ------------------------------------------------------------------------- */
#ifndef _GEOMETRIC_MESH_H_
#define _GEOMETRIC_MESH_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Ogre.h"
using namespace Ogre;

/* ------------------------------------------------------------------------- */
/// Generic class for creating geometric meshes.
/**
This class has to be derived for creating the mesh. 
In your derived class constructor, call the functions setEdgeNumber() and setVertexNumber() 
to set the topology of your mesh.
Then create a function fillMesh() where you will define all the vertices 
and all the triangles of the mesh.
@sa Mesh_Cube  Mesh_Sphere Mesh_Icosa */
/* ------------------------------------------------------------------------- */

class GeometricMesh
{
#define AUTO 255

public:
	GeometricMesh(Real radius);
	virtual ~GeometricMesh() {}
	void createMesh(String MeshName);

protected:
	virtual void fillMesh()=0;
	void setTriangleNumber(int triangleNumber);
	void setVertexNumber(int vertexNumber);
	void addVertexUV(Real radius, Real Vx, Real Vy, Real Vz, Real U=AUTO, Real V=AUTO);
	void addVertex(Real radius, Real Vx, Real Vy, Real Vz);
	void addTriangle(int I0, int I1, int I2, bool CCW=true, bool detectborder=false);
	void initializeMesh(String MeshName, int vertexNB, int edgesNB);
	void finalizeMesh();

	float*                        mpVertex;
	float*                        mpVertex0;
	unsigned short*               mpIndices;
	unsigned short                mVerticeIndex;
	int                           mVertexIndex;
	Real                          mRadius;
	int                           mVertexNumber;
	int                           mTriangleNumber;

	VertexData*                   mVertexData;
	VertexDeclaration*            mVertexDecl;
	HardwareVertexBufferSharedPtr mVertexBuffer;
	HardwareIndexBufferSharedPtr  mIndexBuffer;
	MeshPtr                       mSphere;
	SubMesh*                      mSphereVertex;
};

#endif
