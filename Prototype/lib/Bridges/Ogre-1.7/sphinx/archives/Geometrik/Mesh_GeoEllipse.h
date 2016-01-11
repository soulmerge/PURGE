/* ------------------------------------------------------------------------- */
// File       : GeoEllipse.h
// Project    : winDome 
// Author     : Richard J. Bono (1995-2002) - GNU licence
// Modified   : D. de Lorenzo (2006)
/* ------------------------------------------------------------------------- */
#ifndef _GEOELLIPSE_H_
#define _GEOELLIPSE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Ogre.h"
using namespace Ogre;

#include "Geodesic.h"
#include "GeometricMesh.h"

/* ------------------------------------------------------------------------- */
/// This class is an instance of the Geodesic generic class, specific to create a geodesic ellipse.
/** The geoEllipse is a flatten geosphere, looking like a flying saucer or a 
zeppelin (depending on the eccentricity factor). */
/* ------------------------------------------------------------------------- */
class Mesh_GeoEllipse : public Geodesic, public GeometricMesh
{
public:
	Mesh_GeoEllipse(Real radius, double Eccent, int frequency=8, bool class_2=false);
	virtual ~Mesh_GeoEllipse();
	void fillMesh();

protected:
	double mEccent;             // Ellipse eccentricity

	void   getFacePoints(long facenumber);
	void   getFacePoints_I(long facenumber);
	void   getFacePoints_II(long facenumber);
	double getEllipseRadius(double E, double theta);
	double root_E(double E, double theta);

};

#endif


