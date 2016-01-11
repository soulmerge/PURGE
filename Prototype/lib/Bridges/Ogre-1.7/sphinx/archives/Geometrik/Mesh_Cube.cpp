/* ------------------------------------------------------------------------- */
// File       : Mesh_Cube.cpp
// Author     : David de Lorenzo
// Project    : Long Forgotten Earth
/* ------------------------------------------------------------------------- */
#include "Mesh_Cube.h"
#include "macros.h"

/* ------------------------------------------------------------------------- */
/// Constructor
/** 
@param radius    The radius of the cube (= half-side).
*/
/* ------------------------------------------------------------------------- */
Mesh_Cube::Mesh_Cube(Real radius) : GeometricMesh(radius)
{
	// For a cube, we have 8 corners and 6 faces
	// 6 square faces make 12 triangles
	// We need 2 more points for the border of teh texture. 
	this->setVertexNumber(8+2);
	this->setTriangleNumber(12);
}

/* ------------------------------------------------------------------------- */
/// Destruction
/* ------------------------------------------------------------------------- */
Mesh_Cube::~Mesh_Cube()
{}


/* ------------------------------------------------------------------------- */
/// This function inserts all the vertices of the mesh, and defines all its triangles.
/* ------------------------------------------------------------------------- */
void Mesh_Cube::fillMesh()
{
	TRACE(">> Mesh_Cube::fillMesh()");
	// Define the vertices list 
	this->addVertex (mRadius, 1, 1, 1); // P0
	this->addVertex (mRadius, 1, 1,-1); // P1
	this->addVertex (mRadius,-1, 1,-1); // P2
	this->addVertex (mRadius,-1, 1, 1); // P3
	this->addVertex (mRadius, 1,-1, 1); // P4
	this->addVertex (mRadius, 1,-1,-1); // P5
	this->addVertex (mRadius,-1,-1,-1); // P6
	this->addVertex (mRadius,-1,-1, 1); // P7
	// Texture border: we need to extra vertices.
	// P1 has U=0.875 - P8 has U=-0.125
	this->addVertex (mRadius, 1, 1,-1);	// P8 = P1
	// P5 has U=0.875 - P9 has U=-0.125
	this->addVertex (mRadius, 1,-1,-1); // P9 = P5

	// Define the triangles (6 faces = 12 triangles)
	// Top
	this->addTriangle(1,2,0);
	this->addTriangle(3,0,2);
	// Sides
	this->addTriangle(4,5,0);    //405-045-054-(450)-540-(504)
	this->addTriangle(5,1,0);
	this->addTriangle(9,6,8, true, true);
	this->addTriangle(6,2,8, true, true);
	this->addTriangle(6,7,2);
	this->addTriangle(7,3,2);
	this->addTriangle(7,4,3);
	this->addTriangle(4,0,3);
	// Bottom
	this->addTriangle(6,5,4);
	this->addTriangle(4,7,6);



	//this->addTriangle(0,2,1);
	//this->addTriangle(2,0,3);
	//// Sides
	//this->addTriangle(0,5,4);
	//this->addTriangle(0,1,5);
	//this->addTriangle(8,6,9, true);
	//this->addTriangle(8,2,6, true);
	//this->addTriangle(2,7,6);
	//this->addTriangle(2,3,7);
	//this->addTriangle(3,4,7);
	//this->addTriangle(3,0,4);
	//// Bottom
	//this->addTriangle(4,5,6);
	//this->addTriangle(6,7,4);
}


