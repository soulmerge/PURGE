/* ------------------------------------------------------------------------- */
// File       : Mesh_Geosphere.h
// Project    : winDome 
// Author     : Richard J. Bono (1995-2002) - GNU licence
// Modified   : D. de Lorenzo (2006)
// Reference : http://mathforum.org/library/view/8321.html
/* ------------------------------------------------------------------------- */
#ifndef _GEOSPHERE_H_
#define _GEOSPHERE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Ogre.h"
using namespace Ogre;

#include "Geodesic.h"
#include "GeometricMesh.h"

/* ------------------------------------------------------------------------- */
/// This class is an instance of the Geodesic generic class, specific to create a geodesic sphere.
/** The geosphere is based on a icosahedron (20 triangle faces), which is a frequency 1 geosphere.
When you increase the frequency, every face of the base-icosahedron is divided into more triangle, 
and the more the shape will be close to a sphere.
Precisely, frequency 2 means that the edges of a face will be divided into 2 segments. So the face will contain 4 triangles.
- frequency 1 = 1 triangles/face -  3 points/face -  20 triangles/sphere -  60 vertex/sphere -  12 points/sphere
- frequency 2 = 4 triangles/face -  6 points/face -  80 triangles/sphere - 240 vertex/sphere -  48 points/sphere
- frequency 3 = 9 triangles/face - 10 points/face - 180 triangles/sphere - 540 vertex/sphere -  ?? points/sphere
...
- frequency 10 = 100 triangles/face - ?? points/face - 2000 triangles/sphere - 6000 vertex/sphere -  ?? points/sphere
- frequency N = N² triangles/face - ?? points/face - 20*N² triangles/sphere - 60*N² vertex/sphere - ?? points/sphere
Note that the number of vertex is much larger than the number of points.
ie, for a freq1 geosphere, it has 12 points, but 60 vertices are generated.
This can surely be optimized, but keep in mind that some points have to contain several vertices,
because of UV mapping. (especially, the vertice near the border of the texture).
*/
/* ------------------------------------------------------------------------- */
class Mesh_Geosphere : public Geodesic, public GeometricMesh
{
public:

	Mesh_Geosphere(Real radius, int frequency=4, bool class_2=false);
	virtual ~Mesh_Geosphere();
	void fillMesh();

protected:
	void   getFacePoints(long facenumber);
	void   getFacePoints_I(long facenumber);
	void   getFacePoints_II(long facenumber);

};

#endif


