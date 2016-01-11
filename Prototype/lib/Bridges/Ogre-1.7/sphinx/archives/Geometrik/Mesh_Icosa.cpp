/* ------------------------------------------------------------------------- */
// File       : Mesh_Icosa.cpp
// Author     :
// Project    :
/* ------------------------------------------------------------------------- */
#include "Mesh_Icosa.h"
#include "macros.h"

/* ------------------------------------------------------------------------- */
/// Constructor
/** 
@param radius    The icosahedron's radius.
*/
/* ------------------------------------------------------------------------- */
Mesh_Icosa::Mesh_Icosa(Real radius) : GeometricMesh(radius)
{
	// For an icosahedron, we have: 12 points and 20 triangular faces.
	// 20 triangular faces make 20 triangles.
	// We need 12 more points for the border of the texture. 
	// (4 on the top pole, 4 on the bottom pole, 2 on the side.)
	this->setVertexNumber(12+10);
	this->setTriangleNumber(20);
}

/* ------------------------------------------------------------------------- */
/// Destruction
/* ------------------------------------------------------------------------- */
Mesh_Icosa::~Mesh_Icosa()
{}


/* ------------------------------------------------------------------------- */
/// This function inserts all the vertices of the mesh, and defines all its triangles.
/* ------------------------------------------------------------------------- */
void Mesh_Icosa::fillMesh()
{
	TRACE(">> Mesh_Icosa::fillMesh()");

	// Key values for the icosaedre.
	Real C  = sqrt(5.0)/5;
	Real Bp = (5+sqrt(5.0))/10;
	Real Bm = (5-sqrt(5.0))/10;
	Real Ap = sqrt(Bp);
	Real Am = sqrt(Bm);
	Real r  = mRadius;

	// Generate the 12 vertices of the icosaedre
	// pentagon1 = P1-P5-P4-P3-P2  (CW)
	// pentagon2 = P10-P6-P7-P8-P9 (CW)
	// Do not change this order => it is the index.
	addVertexUV(r, 0,  1,  0, 0.0); // P0  - upper (with U for 1-2-base triangle)

	addVertex (r, Am, C, -Bp); // P1  - penta1 - (Edge : U=0.9)
	addVertex (r,-Am, C, -Bp); // P2  - penta1
	addVertex (r,-Ap, C,  Bm); // P3  - penta1
	addVertex (r, 0,  C, 2*C); // P4  - penta1
	addVertex (r, Ap, C,  Bm); // P5  - penta1
	addVertex (r, Am,-C,  Bp); // P6  - penta2
	addVertex (r,-Am,-C,  Bp); // P7  - penta2
	addVertex (r,-Ap,-C, -Bm); // P8  - penta2
	addVertex (r, 0, -C,-2*C); // P9  - penta2 - (Edge : U=1)
	addVertex (r, Ap,-C, -Bm); // P10 - penta2
	addVertex (r, 0, -1,  0 ); // P11 - lower (7-6-base-triangle)

	// The edge of the texture: we duplicate the vertices
	addVertexUV (r, 0, -C,-2*C, 0.0);  // P12 - border (= P9)
	addVertexUV (r, Am, C,-Bp ,-0.1);  // P13 - border (= P1)

	// The upper vertex has 5 UV coordinates (one is already done = P0)
	addVertexUV (r, 0, 1, 0, 0.2); // P14 = P0 with U for 2-3-base triangle
	addVertexUV (r, 0, 1, 0, 0.4); // P15 = P0 with U for 3-4-base triangle
	addVertexUV (r, 0, 1, 0, 0.6); // P16 = P0 with U for 4-5-base triangle
	addVertexUV (r, 0, 1, 0, 0.8); // P17 = P0 with U for 5-1-base triangle

	// The lower vertex has 5 UV coordinates (one is already done = P11)
	addVertexUV (r, 0,-1, 0, 0.1); // P18 = P11 with U for 12-8-base triangle
	addVertexUV (r, 0,-1, 0, 0.3); // P19 = P11 with U for 8-7-base triangle
	addVertexUV (r, 0,-1, 0, 0.7); // P20 = P11 with U for 6-10-base triangle
	addVertexUV (r, 0,-1, 0, 0.9); // P21 = P11 with U for 10-9-base triangle

	// Central zone (10 triangles)
	addTriangle(10,9,1);
	addTriangle(12,2,13);  // = P1-P2-P9
	addTriangle(12,8,2);   // = P2-P8-P9
	addTriangle(8,3,2);
	addTriangle(8,7,3);
	addTriangle(7,4,3);
	addTriangle(7,6,4);
	addTriangle(6,5,4);
	addTriangle(6,10,5);
	addTriangle(10,1,5);
	// upper zone (5 triangles)
	// upper is P0-14-15-16-17 
	// pentagon1 = P2-P3-P4-P5-P1  (CCW)
	addTriangle(2,0,13); 
	addTriangle(3,14,2); 
	addTriangle(4,15,3); 
	addTriangle(5,16,4); 
	addTriangle(1,17,5); 
	// lower zone (5 triangles) 
	addTriangle(11,6,7);
	addTriangle(18,8,12);
	addTriangle(19,7,8);
	addTriangle(21,9,10);
	addTriangle(20,10,6);


/*	// Central zone (10 triangles)
	mVerticeIndex = 0;
	addTriangle(1,9,10);
	addTriangle(13,2,12);  // = P1-P2-P9
	addTriangle(2,8,12);   // = P2-P8-P9
	addTriangle(2,3,8);
	addTriangle(3,7,8);
	addTriangle(3,4,7);
	addTriangle(4,6,7);
	addTriangle(4,5,6);
	addTriangle(5,10,6);
	addTriangle(5,1,10);
	// upper zone (5 triangles) 
	addTriangle(13,0,2);
	addTriangle(2,14,3);
	addTriangle(3,15,4);
	addTriangle(4,16,5); 
	addTriangle(5,17,1);
	// lower zone (5 triangles) 
	addTriangle(6,10,20);
	addTriangle(7,6,11);
	addTriangle(8,7,19);
	addTriangle(12,8,18);
	addTriangle(10,9,21);
*/
}


