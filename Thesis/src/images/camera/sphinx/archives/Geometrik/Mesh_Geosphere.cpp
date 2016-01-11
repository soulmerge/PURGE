/* ------------------------------------------------------------------------- */
// File       : Mesh_Geosphere.cpp
// Project    : winDome 
// Author     : Richard J. Bono (1995-2002) - GNU licence
// Modified   : D. de Lorenzo (2006)
/* ------------------------------------------------------------------------- */
#include "Mesh_Geosphere.h"
#include "macros.h"

/* ------------------------------------------------------------------------- */
/// Constructor
/** 
@param radius    The radius of the sphere.
@param frequency The frequency of subdivision. Best values: 1 to 10.
@param class_2   The class of the geosphere(1 or 2)
*/
/* ------------------------------------------------------------------------- */
Mesh_Geosphere::Mesh_Geosphere(Real radius, int frequency, bool class_2) : Geodesic(frequency, class_2), GeometricMesh(radius)
{
	int N = this->getFaceNumber()*mFrequency*mFrequency; 
	this->setTriangleNumber(N);
	this->setVertexNumber(3*N);
}

/* ------------------------------------------------------------------------- */
/// Destruction
/* ------------------------------------------------------------------------- */
Mesh_Geosphere::~Mesh_Geosphere()
{
}


/* ------------------------------------------------------------------------- */
/// This function fills the mSphericPoints array with all the points of the face.
/** The points are repositionned, to be on a spheric surface. 
@param facenumber	The number of the face to analyze.
*/
/* ------------------------------------------------------------------------- */
void Mesh_Geosphere::getFacePoints(long facenumber)
{
	TRACE(">> getFacePoints("+ITOA(facenumber)+")");

	if (mClass_2)  this->getFacePoints_II(facenumber);
	else           this->getFacePoints_I(facenumber);
}

/* ------------------------------------------------------------------------- */
/// This function fills the mSphericPoints array with all the points of the face.
/** Given the polyhedron face number, this function calculate the Icosa face points 
and store them in an array. For Class I geospheres. */
/* ------------------------------------------------------------------------- */
void Mesh_Geosphere::getFacePoints_I(long facenumber)
{
	long   k;

	if(facenumber >=0 && facenumber <=4)
	{
		//do a 72 degree "cap" rotation
		for (long i=1; i<=mPointNumber; i++)
		{
			mSphericPoints[i].phi   = mPoints[i].phi + 72.0 * facenumber;
			mSphericPoints[i].theta = mPoints[i].theta;
			mSphericPoints[i].radius= 1.0;
		}
	}
	else if (facenumber >= 5 && facenumber <=9)
	{
		//do a downward  rotation then rotate appropriate angle
		k = facenumber - 5;		//phi rotation factor
		for (long i=1; i<=mPointNumber; i++)
		{
			mSphericPoints[i].theta = rotate_theta(36.0, mPoints[i].phi, (180.0 - (atan(2.0) * RAD_TO_DEG)), mPoints[i].theta);
			mSphericPoints[i].phi   = 36.0 + 72.0*k + rotate_phi(36.0, mPoints[i].phi, mPoints[i].theta, mSphericPoints[i].theta);
			mSphericPoints[i].radius= 1.0;
		}
	}
	else if (facenumber >= 10 && facenumber <=14)
	{
		//do a downward rotation then rotate 72° x k phi and 180° theta
		k = facenumber - 10;		//phi rotation factor
		for (long i=1; i<=mPointNumber; i++)
		{
			mSphericPoints[i].theta = 180.0 - rotate_theta(36.0, mPoints[i].phi, (180.0 - (atan(2.0) * RAD_TO_DEG)), mPoints[i].theta);
			mSphericPoints[i].phi   = ((rotate_phi(36.0, mPoints[i].phi, mPoints[i].theta, mSphericPoints[i].theta) + 36.0) + 72.0 * k) + 36.0;
			mSphericPoints[i].radius= 1.0;
		}
	}
	else
	{
		//rotate bottom cap into place and the sphere is done!
		k = facenumber - 15;
		for (long i=1; i<=mPointNumber; i++)
		{
			mSphericPoints[i].phi   = (mPoints[i].phi + 72.0*k) + 36.0;
			mSphericPoints[i].theta = 180.0 - mPoints[i].theta;
			mSphericPoints[i].radius= 1.0;
		}
	}
}


/* ------------------------------------------------------------------------- */
/// This function fills the mSphericPoints array with all the points of the face.
/** Given the polyhedron face number, this function calculate the Icosa face points 
and store them in an array. For Class II geospheres. */
/* ------------------------------------------------------------------------- */
void Mesh_Geosphere::getFacePoints_II(long facenumber)
{
	double x_phi, x_theta, rot_factor;
	long   k;

	if (facenumber >=0 && facenumber <=4)
	{
		//do a 72 degree "cap" rotation
		for (long i=1; i<=mPointNumber; i++)
		{
			mSphericPoints[i].phi   = mPoints[i].phi + 72.0 * facenumber;
			mSphericPoints[i].theta = mPoints[i].theta;
			mSphericPoints[i].radius= 1.0;
		}
	}
	else if (facenumber >= 5 && facenumber <= 29)
	{
		if (facenumber >= 5 && facenumber <= 9)
		{
			k = facenumber - 5;
			rot_factor = 0;
		}
		else if (facenumber >= 10 && facenumber <= 14)
		{
			k = facenumber - 10;
			rot_factor = 1;
		}
		else if(facenumber >= 15 && facenumber <= 19)
		{
			k = facenumber - 15;
			rot_factor = 2;
		}
		else if(facenumber >= 20 && facenumber <= 24)
		{
			k = facenumber - 20;
			rot_factor = 3;
		}
		else if(facenumber >= 25 && facenumber <= 29)
		{
			k = facenumber - 25;
			rot_factor = 4;
		}
		//do a 72 degree cap rotation then rotate appropriate angle
		for (long i=1; i<=mPointNumber; i++)
		{
			x_phi   = mPoints[i].phi + 72.0 * k;
			x_theta = mPoints[i].theta;
			mSphericPoints[i].theta = rotate_theta(36.0 + (72.0 * rot_factor), x_phi, (atan(2.0) * RAD_TO_DEG),x_theta);
			mSphericPoints[i].phi   = (rotate_phi(36.0 + (72.0 * rot_factor), x_phi, x_theta,mSphericPoints[i].theta) + 36.0) + 72.0 * k;
			mSphericPoints[i].radius= 1.0;
		}
	}
	else if (facenumber >=30 && facenumber <=34)
	{
		//do a 72 degree "cap" rotation
		k = facenumber - 30;
		for (long i=1; i<=mPointNumber; i++)
		{
			mSphericPoints[i].phi   = 36.0 + mPoints[i].phi + 72.0 * k;
			mSphericPoints[i].theta = 180.0 - mPoints[i].theta;
			mSphericPoints[i].radius= 1.0;
		}
	}
	else if (facenumber >= 35 && facenumber <= 59)
	{
		if (facenumber >= 35 && facenumber <= 39)
		{
			k = facenumber - 35;
			rot_factor = 0;
		}
		else if (facenumber >= 40 && facenumber <= 44)
		{
			k = facenumber - 40;
			rot_factor = 1;
		}
		else if (facenumber >= 45 && facenumber <= 49)
		{
			k = facenumber - 45;
			rot_factor = 2;
		}
		else if (facenumber >= 50 && facenumber <= 54)
		{
			k = facenumber - 50;
			rot_factor = 3;
		}
		else if (facenumber >= 55 && facenumber <= 59)
		{
			k = facenumber - 55;
			rot_factor = 4;
		}
		//do a 72 degree cap rotation then rotate appropriate angle
		for (long i=1; i<=mPointNumber; i++)
		{
			x_phi = mPoints[i].phi + 72.0 * k;
			x_theta = mPoints[i].theta;
			mSphericPoints[i].theta = 180.0 - rotate_theta(36.0 + (72.0 * rot_factor), x_phi, (atan(2.0) * RAD_TO_DEG),x_theta);
			mSphericPoints[i].phi   = 36.0 + (rotate_phi(36.0 + (72.0 * rot_factor), x_phi, x_theta,mSphericPoints[i].theta) + 36.0) + 72.0 * k;
			mSphericPoints[i].radius= 1.0;
		}
	}
}


/* ------------------------------------------------------------------------- */
/// This function defines the Vertices list (with position, normal and UV mapping).
/* ------------------------------------------------------------------------- */
void Mesh_Geosphere::fillMesh()
{
	TRACE(">> Mesh_Geosphere::fillMesh()");
	int last_face = this->getFaceNumber()-1;

	for(int faceindex=0; faceindex<=last_face; faceindex++)
	{
		TRACE(" Analysing face "+ITOA(faceindex)+"/"+ITOA(last_face));
		//Get the vertex-data for the face in question
		this->getFacePoints(faceindex);   // this updates mSphericPoints

		for (int t=1; t<=mTriNumber; t++)
		{
			// For every triangle of the face, we add the 3 corners of the triangle in the vertex list.
			Vector3 Ac,Bc,Cc;		// cartesian coordinates
//		TRACE(" *A:"+ITOA(mTriangles[t].cornerA));
			Ac = SphericalToCartesian(&mSphericPoints[mTriangles[t].cornerA]);
//		TRACE(" *B:"+ITOA(mTriangles[t].cornerB));
			Bc = SphericalToCartesian(&mSphericPoints[mTriangles[t].cornerB]);
//		TRACE(" *C:"+ITOA(mTriangles[t].cornerC));
			Cc = SphericalToCartesian(&mSphericPoints[mTriangles[t].cornerC]);
	
			// We calculate here the UV coordinates of every vertex
			Real AcU = (mSphericPoints[mTriangles[t].cornerA].phi)/360;
			Real BcU = (mSphericPoints[mTriangles[t].cornerB].phi)/360;
			Real CcU = (mSphericPoints[mTriangles[t].cornerC].phi)/360;

			// If one vertex is at the pole of the sphere, 
			// we have to calculate its U value (= the mean value of the 2 other corners).
			if (abs(Ac.y)==1)    
				this->addVertexUV(mRadius, Ac.x, Ac.y, Ac.z,(BcU+CcU)/2); 
			else
				this->addVertexUV(mRadius, Ac.x, Ac.y, Ac.z,AcU); 

			if (abs(Bc.y)==1)    
				this->addVertexUV(mRadius, Bc.x, Bc.y, Bc.z, (AcU+CcU)/2); 
			else
				this->addVertexUV(mRadius, Bc.x, Bc.y, Bc.z, BcU); 

			if (abs(Cc.y)==1)    
				this->addVertexUV(mRadius, Cc.x, Cc.y, Cc.z, (AcU+BcU)/2); 
			else
				this->addVertexUV(mRadius, Cc.x, Cc.y, Cc.z,CcU); 

			bool CCW =  (faceindex >= 0 && faceindex <=9)
			         || (faceindex >= 10 && faceindex <=19 && mClass_2)
					 || (faceindex >= 20 && faceindex <=29) ;


			this->addTriangle(mVertexIndex-2,mVertexIndex-1,mVertexIndex-3, CCW);


		}
	}
 	TRACE("<< Mesh_Geosphere::fillMesh");
}

