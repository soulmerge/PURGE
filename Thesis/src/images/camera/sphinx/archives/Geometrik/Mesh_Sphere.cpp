/* ------------------------------------------------------------------------- */
// File       : Mesh_Sphere.cpp
// Author     : snowblind
// Source     : from www.ogre3d.org/wiki
/* ------------------------------------------------------------------------- */
#include "Mesh_Sphere.h"
#include "macros.h"

/* ------------------------------------------------------------------------- */
/// Constructor
/** 
@param radius    The sphere's radius.
@param nRings    Number of lines of longitude. Default value is 16.
@param nSegments Number of lines of latitude. Default value is 16.
*/
/* ------------------------------------------------------------------------- */
Mesh_Sphere::Mesh_Sphere(Real radius, int nRings, int nSegments) : GeometricMesh(radius)
{
	mRings    = nRings;
	mSegments = nSegments;

	this->setVertexNumber((mRings + 1) * (mSegments+1));
	this->setTriangleNumber(6 * mRings * (mSegments + 1));
}

/* ------------------------------------------------------------------------- */
/// Destruction
/* ------------------------------------------------------------------------- */
Mesh_Sphere::~Mesh_Sphere()
{}


/* ------------------------------------------------------------------------- */
/// This function inserts all the vertices of the mesh, and defines all its triangles.
/* ------------------------------------------------------------------------- */
void Mesh_Sphere::fillMesh()
{
	TRACE(">> Mesh_Sphere::fillMesh()");

	int wVerticeIndex = 0;

	float fDeltaRingAngle = (Math::PI / mRings);
	float fDeltaSegAngle  = (2 * Math::PI / mSegments);

	// Generate the group of rings for the sphere
	for( int ring=0; ring<=mRings; ring++ ) 
	{
		float r0 = mRadius * sinf (ring * fDeltaRingAngle);
		float y0 = mRadius * cosf (ring * fDeltaRingAngle);

		// Generate the vertices for the current ring
		for(int seg=0; seg<=mSegments; seg++) 
		{
			float x0 = r0 * sinf(seg * fDeltaSegAngle);
			float z0 = r0 * cosf(seg * fDeltaSegAngle);
			Real u0 = (float) seg / (float) mSegments;
			Real v0 = (float) ring / (float) mRings;
			this->addVertexUV(1, x0, y0, z0, u0, v0);
		}
	}

	// Generate the group of rings for the sphere
	for( int ring=0; ring<=mRings; ring++ ) 
	{
		// Generate the triangles for the current ring
		for(int seg=0; seg<=mSegments; seg++)
		{
			if (ring != mRings) 
			{
				// each vertex (except the last) has six indices pointing to it
				int I0 = wVerticeIndex + mSegments;
				int I1 = wVerticeIndex + mSegments + 1;
				int I2 = wVerticeIndex;
				this->addTriangle(I0, I1, I2);

				int I3 = wVerticeIndex + 1;
				this->addTriangle(I2,I1,I3);
				wVerticeIndex ++;
			}
		}
	}
}


