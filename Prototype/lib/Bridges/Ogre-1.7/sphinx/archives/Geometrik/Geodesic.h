/* ------------------------------------------------------------------------- */
// File       : Geodesic.h
// Project    : winDome 
// Author     : Richard J. Bono (1995-2002) - GNU licence
// Modified   : D. de Lorenzo (2006)
// Reference : http://mathforum.org/library/view/8321.html
/*
	Copyright (C) 1995 - 2002 Richard J. Bono

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License.
	 Please direct inquiries, comments and modifications to:
	 Richard J. Bono
	 44 Augusta Rd.
	 Brownsville, TX 78521
	 email: rjbono@applied-synergetics.com

 Acknowledgements & References:
  The main reference used in the creation of this code was 
  "Geodesic Math & How to Use It" by Hugh Kenner, 1976, University of California Press.
  ISBN 0-520-02924-0; Library of Congress Catalog Card Number: 74-27292. 
  Many thanks to Hugh for putting this data in an accessible format.
  Also, many thanks to:
	J. F. Nystrom
	My wife & Daughters
	Chris Fearnley
	Kirby Urner
	& R. Buckminster Fuller for changing the way I view Universe.
*/
/* ------------------------------------------------------------------------- */

#ifndef _GEODESIC_H_
#define _GEODESIC_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Ogre.h"
#include "macros.h"
using namespace Ogre;

const double RAD_TO_DEG = 57.2957795130824;
const double DEG_TO_RAD = 0.0174532925199433;

/* ------------------------------------------------------------------------- */
/// Geodesic Shape (generic class)
/** Geodesic shapes can be theorically based on an assembly of triangles, of pentagons 
(5 sides) or of hexagons (6 sides). Here, we will use only geodesic shapes based on triangles,
as it is for 'trimesh' creation.
The elementary shape (frequency=1) is the Icosahedron, an assembly of 20 triangles (with 12 points). 
Note that the function getFacePoints()has to be implemented in derived classes.
*/
/* ------------------------------------------------------------------------- */
class Geodesic	
{
protected:
	int    mFrequency;
	bool   mClass_2;
	// Topology per basic Face
	long   mFrequency_calc;
	long   mPointNumber;
	long   mTriNumber;
	long   mChordNumber; 
	

    // typedef?
	/* typedef */ struct CSphere  {long xprime; long yprime; long zprime; }; ///< Structure containing intermediate coordinates
	/* typedef */ struct CLabels {long A; long B; };
	/* typedef */ struct CPoints {double phi; double theta; double radius; }; 
	/* typedef */ struct CChords {long start; long end; };	///< chord start & end points
	/* typedef */ struct CFaces  {long cornerA; long cornerB; long cornerC;};	///< The three points required to define a triangle.
		
	CPoints* mPoints;  			    ///< All the points of a face 
	CPoints* mSphericPoints;		///< All the points of a face 
	CLabels* mPointLabels;			///< Dynamic array for point's labels.
	CChords* mEdges;      		    ///< Dynamic array for all the edges of a face.
	CFaces*  mTriangles;			///< Dynamic array for all triangles of a face.
	
public:
	Geodesic(int frequency, bool class_2);
	~Geodesic();		   						
	void dumpData(); 
	void createDXFwireframe(String filename);
	void createDXF(String filename);


protected:
	virtual void getFacePoints(long facenumber) = 0;
	void   createTopology();
	void   calculateSphericalCoord();
	long   getFaceNumber();
	double getChordLength(double sphi, double stheta, double ephi, double etheta);
	void   chord_factor();
	void   face_factor();
	double cleanFloat(double fp_number);
	double rotate_phi(double, double, double, double);
	double rotate_theta(double, double, double, double);
	double axial_angle_A(long index);
	double axial_angle_B(long index, double angleA);
	double face_angle_A(long index);
	double face_angle_B(long, double);
	double face_angle_C(double, double);
	Vector3 SphericalToCartesian(CPoints* PolarPoint);

};

#endif


