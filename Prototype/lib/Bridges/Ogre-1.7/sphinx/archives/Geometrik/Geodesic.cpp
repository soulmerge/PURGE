/* ------------------------------------------------------------------------- */
// File       : Geodesic.cpp
// Project    : winDome 
// Author     : Richard J. Bono (1995-2002) - GNU licence
// Modified   : D. de Lorenzo (2006)
/* ------------------------------------------------------------------------- */
#include "Geodesic.h"
#include <stdlib.h>

#include <fstream>
using namespace std;

/* ------------------------------------------------------------------------- */
/// Geodesic constructor
/** The constructor handles all calculation when an instance is called.
@param frequency The frequency of subdivision (best values: 1 to 10)
@param class_2   The class (1 or 2) of the geodesic shape
*/
/* ------------------------------------------------------------------------- */
Geodesic::Geodesic(int frequency, bool class_2)
{
	TRACE (">> Geodesic");
	mFrequency = frequency;
	mClass_2   = class_2;

	if (mClass_2)     mFrequency_calc = mFrequency/2;
	else              mFrequency_calc = mFrequency;
	if (mFrequency_calc<1) mFrequency_calc=1;
	if (mFrequency<1)      mFrequency=1;
	
	this->createTopology();

	// Create arrays for the points
	mPoints    = new CPoints[mPointNumber + 1];
	mSphericPoints = new CPoints[mPointNumber + 1];
	mPointLabels   = new CLabels[mPointNumber + 1];
	this->calculateSphericalCoord();

	// Create an array for edges
	mEdges = new CChords[(mChordNumber + 1)];	// edges + 1)]; (modifié par DDL)
	this->chord_factor();

	// Create an array for triangles
	mTriangles = new CFaces[mTriNumber + 1];
	this->face_factor();

	TRACE ("<< Geodesic");
}

/* ------------------------------------------------------------------------- */
/// Geodesic destructor
/* ------------------------------------------------------------------------- */
Geodesic::~Geodesic() 
{
	delete (mEdges);
	delete (mTriangles);
	delete (mSphericPoints);
	delete (mPoints);
	delete (mPointLabels);
}

/* ------------------------------------------------------------------------- */
/// This function calculates the number of vertices & triangles in a face.
/* ------------------------------------------------------------------------- */
void Geodesic::createTopology()
{
	long   vertex;

	for(int i=1; i<=mFrequency_calc; i++)
	{
		if (i==1) vertex = 3;
		else      vertex += (i + 1);
	}

	mPointNumber = vertex;
	mTriNumber   = mFrequency_calc * mFrequency_calc;
	mChordNumber = mPointNumber + mTriNumber - 1;

	TRACE("   Topology per polygon: "
	     +ITOA(mPointNumber)  +" vertex, "
	     +ITOA(mChordNumber)  +" edges, "
	     +ITOA(mTriNumber)    +" triangles");
}

/* ------------------------------------------------------------------------- */
/// This function calculates the spherical coordinates for a geodesic sphere.
/* ------------------------------------------------------------------------- */
void Geodesic::calculateSphericalCoord()
{
	TRACE (">> calculateSphericalCoord");
	TRACE ("   Allocate memory for contructing a Geodesic shape...");

	// Allocate memory for temporary variables (spherical point variable array)
	// vertex coordinates: 0,0,0 equals zenith
	CSphere* pnt_calc = new CSphere[mPointNumber + 1];

	// Initialize vertex labels and coordinates
	long index = 1;
	for (long i=0; i<=mFrequency_calc; i++)
	{
		for (long j=0; j<=i; j++)
		{
			mPointLabels[index].A = i;
			mPointLabels[index].B = j;
			pnt_calc[index].xprime = j;
			pnt_calc[index].yprime = i - j;
			pnt_calc[index].zprime = mFrequency - i;
			index++;
		}
	}

	TRACE ("   Calculating Spherical Coordinates... ");
	for (long i=1; i<=mPointNumber; i++)
	{
		// set-up x,y,z coordinates for spherical calulations
		// See page 75 of Kenner's "Geodesic Math & How to use it" for formulae used below.
		// Icosahedron:
		double X = pnt_calc[i].xprime * sin(72.0 * DEG_TO_RAD);
		double Y = pnt_calc[i].yprime + (pnt_calc[i].xprime * cos(72.0 * DEG_TO_RAD));
		double Z = mFrequency/2.0 + (pnt_calc[i].zprime / (2.0 * cos(36.0 * DEG_TO_RAD)));

		// Calculate PHI while avoiding trig errors
		if (Y == 0 && X == 0)
			mPoints[i].phi = 0.0;
		else if (Y == 0)
			mPoints[i].phi = 90.0;
		else
			mPoints[i].phi = atan(X / Y) * RAD_TO_DEG;

		// Adjust value to correct quadrant
		if (mPoints[i].phi < 0.0)
			mPoints[i].phi += 180.0;

		// Calculate THETA... (this is class dependent)
		if (Z==0)
			mPoints[i].theta = 90.0;
		else if (!mClass_2)
			// theta for class I Icosahedron
			mPoints[i].theta = atan((pow(pow(X, 2.0) + pow(Y, 2.0), 0.5)) / Z) * RAD_TO_DEG;
		else if (mClass_2)
			// theta for class II Icosahedron
			mPoints[i].theta = atan((pow(pow(X, 2.0) + pow(Y, 2.0), 0.5)) / (cos(36.0 * DEG_TO_RAD) * Z)) * RAD_TO_DEG;

		// Make sure the right quadrant is used
		if (mPoints[i].theta < 0.0)
			mPoints[i].theta += 180.0;

		// Set Radius = 1
		mPoints[i].radius = 1.0;
	}
	delete(pnt_calc);
}

/* ------------------------------------------------------------------------- */
/// This function calculates the chord factors.
/** The function cycles through each vertex, and determines the chord connections. */
/* ------------------------------------------------------------------------- */
void Geodesic::chord_factor()
{
	TRACE (">> Calculating Chord Factors... ");
	long index = 1;
	long j;

	for (long i=1; i<mPointNumber; i++)
	{
		if ((mPointLabels[i].A == 0)
		  &&(mPointLabels[i].B == 0))
		{
			//point is the zenith vertex; add 10 & 11
			//line #1 start point definition
			mEdges[index].start = i;
			for (j=i; j<=mPointNumber; j++)
			{
				if ((mPointLabels[j].A == mPointLabels[i].A + 1)
				  &&(mPointLabels[j].B == mPointLabels[i].B))
					break;
			}
			//end point
			mEdges[index].end = j;
			index++;

			//line #2 start point definition
			mEdges[index].start = i;
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 
				 && mPointLabels[j].B == mPointLabels[i].B + 1)
					break;
			}
			//end point
			mEdges[index].end =j;
			index++;

		}
		else if (mPointLabels[i].A == mFrequency_calc && mPointLabels[i].B == 0)
		{
			//point is a left vertex; add 01
			//line #1 start point definition
			mEdges[index].start = i;
			for(j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A 
				 && mPointLabels[j].B == mPointLabels[i].B + 1)
					break;
			}
			//end point
			mEdges[index].end = j;
			index++;
		}
		else if (mPointLabels[i].A == mPointLabels[i].B)
		{
			//point is a right edge; add 10 & 11
			//line #1 start point definition
			mEdges[index].start = i;
			for(j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 
				 && mPointLabels[j].B == mPointLabels[i].B)
					break;
			}
			//end point
			mEdges[index].end = j;
			index++;

			//line #2 start point definition
			mEdges[index].start = i;
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 
				 && mPointLabels[j].B == mPointLabels[i].B + 1)
					break;
			}
			//end point
			mEdges[index].end = j;
			index++;
		}
		else if (mPointLabels[i].A == mFrequency_calc)
		{
			//point is a bottom vertex; add 01
			//line #1 start point definition
			mEdges[index].start = i;
			for (j=i; j<=mPointNumber; j++){
				if (mPointLabels[j].A == mPointLabels[i].A  
				 && mPointLabels[j].B == mPointLabels[i].B + 1)
					break;
			}
			//end point
			mEdges[index].end = j;
			index++;
		}
		else if (mPointLabels[i].B == 0)
		{
			//point is a right edge; add 01, 10 & 11
			//line #1 start point definition
			mEdges[index].start = i;
			for (j=i; j<=mPointNumber; j++){
				if (mPointLabels[j].A == mPointLabels[i].A 
				 && mPointLabels[j].B == mPointLabels[i].B + 1)
					break;
			}
			//end point
			mEdges[index].end = j;
			index++;

			//line #2 start point definition
			mEdges[index].start = i;
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 
				 && mPointLabels[j].B == mPointLabels[i].B)
					break;
			}
			//end point
			mEdges[index].end = j;
			index++;

			//line #3 start point definition
			mEdges[index].start = i;
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 
				 && mPointLabels[j].B == mPointLabels[i].B + 1)
					break;
			}
			//end point
			mEdges[index].end = j;
			index++;
		}
		else 
		{
			//point is an interior vertex; add 01, 10 & 11
			//line #1 start point definition
			mEdges[index].start = i;
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A 
				 && mPointLabels[j].B == mPointLabels[i].B + 1)
					break;
			}
			//end point
			mEdges[index].end = j;
			index++;

			//line #2 start point definition
			mEdges[index].start = i;
			for (j=i; j<=mPointNumber; j++)
				if (mPointLabels[j].A == mPointLabels[i].A + 1 
				 && mPointLabels[j].B == mPointLabels[i].B)
					break;
			//end point
			mEdges[index].end = j;
			index++;

			//line #3 start point definition
			mEdges[index].start = i;
			for(j=i; j<=mPointNumber; j++)
				if (mPointLabels[j].A == mPointLabels[i].A + 1 
				 && mPointLabels[j].B == mPointLabels[i].B + 1)
					break;
			//end point
			mEdges[index].end = j;
			index++;
		}
	}
}

/* ------------------------------------------------------------------------- */
/// This function calculates the face factors.
/** This function cycles through each vertex and determines the face 
definitions essentially going CCW about the face. */
/* ------------------------------------------------------------------------- */
void Geodesic::face_factor()
{
	TRACE (">> Calculating Face Factors... ");
	long index = 1;
	long j, k;
		TRACE("   mPointNumber="+ITOA(mPointNumber));
		TRACE("   mFrequency_calc="+ITOA(mFrequency_calc));

	for (long i=1; i<=mPointNumber-mFrequency_calc-1; i++)
	{
	// The function only interates to the end of line frequency - 1. 
	// This is located at vertex#:vertex_calc-(freq_calc+1)
		if (mPointLabels[i].A == 0 && mPointLabels[i].B == 0)
		{
			//point is the zenith vertex; add 10 & 01;
			//Corner A
			mTriangles[index].cornerA = i;
			TRACE(".  mTriangles["+ITOA(index)+"].cornerA = "+ITOA(i));
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 
				 && mPointLabels[j].B == mPointLabels[i].B)
					break;
			}
			//Corner B
			mTriangles[index].cornerB = j;
			for (k=i; k<=mPointNumber; k++)
			{
				if (mPointLabels[k].A == mPointLabels[j].A && mPointLabels[k].B == mPointLabels[j].B + 1)
					break;
			}
			//Corner C
			mTriangles[index].cornerC = k;
			index++;
		}
		else if (mPointLabels[i].B == 0)
		{
			//point is a left edge; add 10 & 01;
			//                      add 11; subtract 10

			//face #1
			//Corner A
			mTriangles[index].cornerA = i;
			TRACE("..  mTriangles["+ITOA(index)+"].cornerA = "+ITOA(i));
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 && mPointLabels[j].B == mPointLabels[i].B)
					break;
			}
			//corner B
			mTriangles[index].cornerB = j;
			for (k=i; k<=mPointNumber; k++)
			{
				if (mPointLabels[k].A == mPointLabels[j].A && mPointLabels[k].B == mPointLabels[j].B + 1)
					break;
			}
			//corner C
			mTriangles[index].cornerC = k;
			index++;

			//Face #2
			//Corner A
			mTriangles[index].cornerA = i;
			TRACE("...  mTriangles["+ITOA(index)+"].cornerA = "+ITOA(i));
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 && mPointLabels[j].B == mPointLabels[i].B + 1)
					break;
			}
			//Corner B
			mTriangles[index].cornerB = j;
			for (k=i; k<=mPointNumber; k++)
			{
				if (mPointLabels[k].A == mPointLabels[j].A - 1 && mPointLabels[k].B == mPointLabels[j].B)
					break;
			}
			//Corner C
			mTriangles[index].cornerC = k;
			index++;
		}
		else if(mPointLabels[i].A == mPointLabels[i].B)
		{
			//point is a right edge; add 10 & 01; subtract 11
			//line #1 start point definition
			//Corner A
			mTriangles[index].cornerA = i;
			TRACE("....  mTriangles["+ITOA(index)+"].cornerA = "+ITOA(i));
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 && mPointLabels[j].B == mPointLabels[i].B)
					break;
			}
			//Corner B
			mTriangles[index].cornerB = j;
			for (k=i; k<=mPointNumber; k++)
			{
				if (mPointLabels[k].A == mPointLabels[j].A && mPointLabels[k].B == mPointLabels[j].B + 1)
					break;
			}
			//Corner C
			mTriangles[index].cornerC = k;
			index++;
		}
		else 
		{
			//Interior point; add 10 & 01;
			//                add 11; subtract 10

			//face #1
			//Corner A
			mTriangles[index].cornerA = i;
			TRACE(".....  mTriangles["+ITOA(index)+"].cornerA = "+ITOA(i));
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 && mPointLabels[j].B == mPointLabels[i].B)
					break;
			}
			//Corner B
			mTriangles[index].cornerB = j;
			for (k=i; k<=mPointNumber; k++)
			{
				if (mPointLabels[k].A == mPointLabels[j].A && mPointLabels[k].B == mPointLabels[j].B + 1)
					break;
			}
			//Corner C
			mTriangles[index].cornerC = k;

			index++;

			//Face #2
			//Corner A
			mTriangles[index].cornerA = i;
			TRACE("......  mTriangles["+ITOA(index)+"].cornerA = "+ITOA(i));
			for (j=i; j<=mPointNumber; j++)
			{
				if (mPointLabels[j].A == mPointLabels[i].A + 1 && mPointLabels[j].B == mPointLabels[i].B + 1)
					break;
			}
			//Corner B
			mTriangles[index].cornerB = j;
			for (k=i; k<=mPointNumber; k++)
			{
				if (mPointLabels[k].A == mPointLabels[j].A - 1 && mPointLabels[k].B == mPointLabels[j].B)
					break;
			}
			//Corner C
			mTriangles[index].cornerC = k;
			index++;
		}
	}
}

/* ------------------------------------------------------------------------- */
/// This function clean floating point numbers (close to but not quite zero).
/* ------------------------------------------------------------------------- */
double Geodesic::cleanFloat(double fp_number)
{
	if((fp_number>-1e-5) && (fp_number<1e-5)) fp_number = 0.0;
	return fp_number;
}


/* ------------------------------------------------------------------------- */
/// This function returns the number of basic faces per sphere.
/* ------------------------------------------------------------------------- */
long Geodesic::getFaceNumber()
{
	if (mClass_2) return 60;
	else          return 20;
}

/* ------------------------------------------------------------------------- */
/// This function dumps in a log file, all topological data concerning the geodesic shape.
/* ------------------------------------------------------------------------- */
void Geodesic::dumpData()
{
	Real sphi, stheta;
	Real ephi, etheta;

	TRACE("----------------Precision data (floating numbers)-------------");
	TRACE("Real:       " + ITOA(sizeof(Real)*8)        +" bits");
	TRACE("float:      " + ITOA(sizeof(float)*8)       +" bits");;
	TRACE("double:     " + ITOA(sizeof(double)*8)      +" bits");;
	TRACE("long double:" + ITOA(sizeof(long double)*8) +" bits");;

	TRACE("----------------Basic Face: General Data----------------------");
	TRACE("Frequency:  " + ITOA(mFrequency));
	TRACE("Real Freq:  " + ITOA(mFrequency_calc));
	TRACE("Class II:   " + ITOA(mClass_2));
	TRACE("Vertices:   " + ITOA(mPointNumber));
	TRACE("Edges:      " + ITOA(mChordNumber));
	TRACE("Triangle(s):" + ITOA(mTriNumber));

	TRACE("-----------Basic Face: Triangle Spherical Coordinates---------");
	TRACE("Vertex# \t phi \t theta" );
	for(long i=1; i<=mPointNumber; i++)
	{
		TRACE( " "+ITOA(i)              + "   \t " + 
			   ITOA((Real)mPoints[i].phi)+ "   \t " +
			   ITOA((Real)mPoints[i].theta));
	}

	TRACE("----------Basic Face: Edge data (Chords)----------------------" );
	TRACE("Edge");
	TRACE("start/end\t Length" );
	for(long i=1; i<=mChordNumber; i++)
	{
		sphi   = mPoints[mEdges[i].start].phi; 
		stheta = mPoints[mEdges[i].start].theta;
		ephi   = mPoints[mEdges[i].end].phi;
		etheta = mPoints[mEdges[i].end].theta;
		TRACE(" "+ITOA(mEdges[i].start)+"-"+ITOA(mEdges[i].end)+" \t "+
			      ITOA((Real)getChordLength(sphi,stheta,ephi,etheta)));
	}

	TRACE("---------Basic Face: Angle Data-------------------------------");
	TRACE("Edge");
	TRACE("start/end\t Axis #1 \t Axis #2");
	for(long i=1; i<=mChordNumber; i++)
	{
		TRACE( " "+ITOA(mEdges[i].start)   + "-"  +
			   ITOA(mEdges[i].end  )       + " \t " +
		       ITOA((Real)axial_angle_A(i)) + " \t " +
			   ITOA((Real)axial_angle_B(i, axial_angle_A(i))));
	}

	TRACE("---------Basic Face:  Triangle Angles ------------------------");
	TRACE("Triangle \t Angle #1 \t Angle #2 \t Angle #3");
	for(long i=1; i<=mTriNumber; i++)
	{
		TRACE( " "+ITOA(i)                + "   \t " +
		       ITOA((Real)face_angle_A(i))+ " \t\t " +
		       ITOA((Real)face_angle_B(i, face_angle_A(i))) + " \t " +
		       ITOA((Real)face_angle_C(face_angle_A(i), face_angle_B(i, face_angle_A(i)))));
	}

	TRACE("---------Vertex List: Spherical Coordinates-------------------");
	TRACE("vertex \tphi  \ttheta");
	for(long i=1; i<=mPointNumber; i++)
	{
		TRACE(" "+ITOA(i)+"   \t"+ITOA((Real)mPoints[i].phi) + "  \t" + ITOA((Real)mPoints[i].theta));
	}

	TRACE("---------Vertex List: Cartesian Coordinates-------------------");
	TRACE("vertex\tX  \t  Y\t  Z");
	for(long i=1; i<=mPointNumber; i++)
	{
		Vector3 S = this->SphericalToCartesian(&mPoints[i]);
		TRACE(" "+ITOA(i)+" \t"+ITOA(S.x) + " \t" +ITOA(S.y) + " \t" +ITOA(S.z));
	}

	TRACE("----------Chord List: Spherical Coordinates-------------------");
	TRACE(" vertex \tphi,theta \t phi,theta");
	for(long i=1; i<=mChordNumber; i++)
	{
		TRACE (" "+ITOA(i)+" \t"+
            ITOA((Real)mPoints[mEdges[i].start].phi)   + ", " +
		    ITOA((Real)mPoints[mEdges[i].start].theta) + "  \t"+
		    ITOA((Real)mPoints[mEdges[i].end].phi)     + ", " +
		    ITOA((Real)mPoints[mEdges[i].end].theta) );
	}

	TRACE("---------Chord List: Cartesian Coordinates--------------------");
	TRACE(" vertex \tX,Y,Z \t X,Y,Z");
	for(long i=1; i<=mChordNumber; i++)
	{
		//convert spherical to cartesian
		Vector3 StartPoint = this->SphericalToCartesian(&mPoints[mEdges[i].start]);
		Vector3 EndPoint   = this->SphericalToCartesian(&mPoints[mEdges[i].end]);

		TRACE (" "+ITOA(i)+" \t"+
		  ITOA(StartPoint.x)+ ", " +ITOA(StartPoint.y) + ", " +ITOA(StartPoint.z) + "  \t" +
		  ITOA(EndPoint.x)  + ", " +ITOA(EndPoint.y)   + ", " +ITOA(EndPoint.z) );
	}
}


/* ------------------------------------------------------------------------- */
/// Determine Axial Angle A
/* ------------------------------------------------------------------------- */
double Geodesic::axial_angle_A(long index)
{
	//Calculates the first axial angle for chord "index"
	double sphi, stheta, ephi, etheta, length, result;

	sphi   = mPoints[mEdges[index].start].phi;
	stheta = mPoints[mEdges[index].start].theta;
	ephi   = mPoints[mEdges[index].end].phi;
	etheta = mPoints[mEdges[index].end].theta;
	length = this->getChordLength(sphi, stheta, ephi, etheta);

	result = acos((length*length+mPoints[mEdges[index].start].radius*
				mPoints[mEdges[index].start].radius-mPoints[mEdges[index].end].radius*
					mPoints[mEdges[index].end].radius)/(2*length*
						mPoints[mEdges[index].start].radius)) * RAD_TO_DEG;

	return(result);
}

/* ------------------------------------------------------------------------- */
/// Determine Axial Angle B
/* ------------------------------------------------------------------------- */
double Geodesic::axial_angle_B(long index, double angleA)
{
	//calculates second axial angle for chord "index" based on angle A
	double result;
	result = asin((mPoints[mEdges[index].start].radius*
			sin(angleA * DEG_TO_RAD))/
			mPoints[mEdges[index].end].radius) * RAD_TO_DEG;

	return(result);
}

/* ------------------------------------------------------------------------- */
/// Determine Face Angle A
/* ------------------------------------------------------------------------- */
double Geodesic::face_angle_A(long index)
{
	//Calculates first face angle for face "index"
	double sphi, stheta, ephi, etheta, result;
	double l1, l2, l3;

	//get face lengths
	//First A to C
	sphi   = mPoints[mTriangles[index].cornerA].phi;
	stheta = mPoints[mTriangles[index].cornerA].theta;
	ephi   = mPoints[mTriangles[index].cornerC].phi;
	etheta = mPoints[mTriangles[index].cornerC].theta;
	l1 = this->getChordLength(sphi, stheta, ephi, etheta);
	//Next A to B
	sphi   = mPoints[mTriangles[index].cornerA].phi;
	stheta = mPoints[mTriangles[index].cornerA].theta;
	ephi   = mPoints[mTriangles[index].cornerB].phi;
	etheta = mPoints[mTriangles[index].cornerB].theta;
	l2 = this->getChordLength(sphi, stheta, ephi, etheta);
	//Next B to C
	sphi   = mPoints[mTriangles[index].cornerB].phi;
	stheta = mPoints[mTriangles[index].cornerB].theta;
	ephi   = mPoints[mTriangles[index].cornerC].phi;
	etheta = mPoints[mTriangles[index].cornerC].theta;
	l3 = this->getChordLength(sphi, stheta, ephi, etheta);

	result = acos((l1*l1+l2*l2-l3*l3)/(2*l1*l2)) * RAD_TO_DEG;
	return(result);
}

/* ------------------------------------------------------------------------- */
/// Determine Face Angle B
/* ------------------------------------------------------------------------- */
double Geodesic::face_angle_B(long index, double faceA)
{
	//Calculates face angle B for face "index" based on face angle A
	double sphi, stheta, ephi, etheta, result;
	double l1, l3;

	//get face lengths
	//First A to C
	sphi   = mPoints[mTriangles[index].cornerA].phi;
	stheta = mPoints[mTriangles[index].cornerA].theta;
	ephi   = mPoints[mTriangles[index].cornerC].phi;
	etheta = mPoints[mTriangles[index].cornerC].theta;
	l1     = this->getChordLength(sphi, stheta, ephi, etheta);
	//...Then B to C
	sphi   = mPoints[mTriangles[index].cornerB].phi;
	stheta = mPoints[mTriangles[index].cornerB].theta;
	ephi   = mPoints[mTriangles[index].cornerC].phi;
	etheta = mPoints[mTriangles[index].cornerC].theta;
	l3     = this->getChordLength(sphi, stheta, ephi, etheta);

	result = asin((l1*sin(faceA * DEG_TO_RAD)) / l3) * RAD_TO_DEG;
	return(result);
}

/* ------------------------------------------------------------------------- */
/// This function calculates the face angle C from face angles A & B
/* ------------------------------------------------------------------------- */
double Geodesic::face_angle_C(double faceA, double faceB)
{
	double result = 180.0 - faceA - faceB;
	return(result);
}


/* ------------------------------------------------------------------------- */
/// This function returns the distance between two points given their spherical coordinates. 
/** Radius is fixed at 1. 
@param sphi  	Phi-coordinate of the first point (S).
@param stheta	Theta-coordinate of the first point (S).
@param ephi  	Phi-coordinate of the second point (E).
@param etheta	Theta-coordinate of the second point (E).
@return			The distance between S and E.
*/
/* ------------------------------------------------------------------------- */
double Geodesic::getChordLength(double sphi, double stheta, double ephi, double etheta)
{
	double result;

	result = cos(stheta*DEG_TO_RAD) * cos(etheta*DEG_TO_RAD) + 
		     cos((sphi-ephi)*DEG_TO_RAD) * sin(stheta*DEG_TO_RAD) * sin(etheta*DEG_TO_RAD) ;

	result = 2 - 2*result;
	result = pow(result,0.5);
	return result;
}

/* ------------------------------------------------------------------------- */
/// phi rotation function
/* ------------------------------------------------------------------------- */
double Geodesic::rotate_phi(double phi, double phi1, double theta1, double theta2)
{
	//phi half of the rotation formula given in Kenner's "Geodesic Math &
	//How to Use it" Kenner credits this formula to Professor George Owen

	double result;
	result = (sin(theta1 * DEG_TO_RAD)* sin((phi-phi1) * DEG_TO_RAD)) /
				sin(theta2 * DEG_TO_RAD);

	//Apply correction for round-off errors
	if(result > 1.0)
		result = 1.0;
	else if(result < -1.0)
		result = -1.0;

	return asin(result) * RAD_TO_DEG;
}

/* ------------------------------------------------------------------------- */
/// theta rotation function
/* ------------------------------------------------------------------------- */
double Geodesic::rotate_theta(double phi, double phi1, double theta, double theta1)
{
	//theta half of the rotation formula given in Kenner's "Geodesic Math &
	//How to Use it" Kenner credits this formula to Professor George Owen
	double result;
	result = cos(theta1 * DEG_TO_RAD) * cos(theta * DEG_TO_RAD) +
	         sin(theta1 * DEG_TO_RAD) * sin(theta * DEG_TO_RAD) *
	         cos((phi-phi1) * DEG_TO_RAD);

	//Apply correction for round-off errors
	if(result > 1.0)
		result = 1.0;
	else if(result < -1.0)
		result = -1.0;

	return acos(result) * RAD_TO_DEG;
}



/* ------------------------------------------------------------------------- */
/// This function saves the Face data for symmetry triangle to DXF file.
/* ------------------------------------------------------------------------- */
void Geodesic::createDXF(String filename)
{
	long    last_face;
	Vector3 Ac, Bc, Cc;    // cartesian coordinates

	TRACE (">> createDXF("+filename+")");
	ofstream DXF(filename.c_str());

	//output DXF data
	DXF << "0"        << '\n';
	DXF << "SECTION"  << '\n';
	DXF << "2"        << '\n';
	DXF << "ENTITIES" << '\n';
	//Set field widths
	DXF  << setiosflags(ios::fixed) << setw(8) << setprecision(6);

	//determine the number of faces required (first face = 0)
	last_face = this->getFaceNumber()-1;

	for(long j=0; j<=last_face; j++)
	{
		// Get the vertex data for the face in question
		this->getFacePoints(j);

		for(long i=1; i<=mTriNumber; i++)
		{
			// Convert spherical to cartesian.
			Ac = SphericalToCartesian(&mSphericPoints[mTriangles[i].cornerA]);
			Bc = SphericalToCartesian(&mSphericPoints[mTriangles[i].cornerB]);
			Cc = SphericalToCartesian(&mSphericPoints[mTriangles[i].cornerC]);

			DXF << "0"      << '\n';
			DXF << "3DFACE" << '\n';	// Save as a 3D Polyface entity
			DXF << "8"      << '\n';
			DXF << (j + 1)  << '\n';	// Each face is saved on a different level.
			DXF << "62"  << '\n';
			DXF << "3"   << '\n';
			DXF << "10"  << '\n';
			DXF << Ac.x  << '\n';
			DXF << "20"  << '\n';
			DXF << Ac.y  << '\n';
			DXF << "30"  << '\n';
			DXF << Ac.z  << '\n';
			DXF << "11"  << '\n';
			DXF << Bc.x  << '\n';
			DXF << "21"  << '\n';
			DXF << Bc.y  << '\n';
			DXF << "31"  << '\n';
			DXF << Bc.z  << '\n';
			DXF << "12"  << '\n';
			DXF << Cc.x  << '\n';
			DXF << "22"  << '\n';
			DXF << Cc.y  << '\n';
			DXF << "32"  << '\n';
			DXF << Cc.z  << '\n';
			DXF << "13"  << '\n';
			DXF << Cc.x  << '\n';
			DXF << "23"  << '\n';
			DXF << Cc.y  << '\n';
			DXF << "33"  << '\n';
			DXF << Cc.z  << '\n';
		}
	}
	DXF << "0"      << '\n';
	DXF << "ENDSEC" << '\n';
	DXF << "0"      << '\n';
	DXF << "EOF"    << '\n';
	DXF.close();
	TRACE ("<< createDXF");
}


/* ------------------------------------------------------------------------- */
/// This function saves the chord data for symmetry triangle to a DXF file.
/* ------------------------------------------------------------------------- */
void Geodesic::createDXFwireframe(String filename)
{
	long    last_face;
	Vector3 Ac, Bc;

	TRACE (">> createDXFwireframe("+filename+")");
	ofstream DXF(filename.c_str());
  	DXF << "0"        << '\n';
	DXF << "SECTION"  << '\n';
	DXF << "2"        << '\n';
	DXF << "ENTITIES" << '\n';

	//Set field widths
	DXF << setiosflags(ios::fixed) << setw(8) << setprecision(6);

	// Determine the number of faces required (first face = 0)
	last_face = this->getFaceNumber()-1;

	for(long j=0; j<=last_face; j++)
	{
		//Get the vertex data for the face in question
		this->getFacePoints(j);

		for(long i=1; i<=mChordNumber; i++)
		{
			//convert spherical to cartesian.
			Ac = SphericalToCartesian(&mSphericPoints[mEdges[i].start]);
			Bc = SphericalToCartesian(&mSphericPoints[mEdges[i].end]);
			
			DXF << "0"      << '\n';
			DXF << "LINE"   << '\n';	//Save as a 3D Polyface entity
			DXF << "8"      << '\n';
			DXF << (j + 1)  << '\n';	//Each face is saved on a different level.
			DXF << "62"     << '\n';
			DXF << "3"      << '\n';	//color number
			DXF << "10"     << '\n';
			DXF << Ac.x     << '\n';
			DXF << "20"     << '\n';
			DXF << Ac.y     << '\n';
			DXF << "30"     << '\n';
			DXF << Ac.z     << '\n';
			DXF << "11"     << '\n';
			DXF << Bc.x     << '\n';
			DXF << "21"     << '\n';
			DXF << Bc.y     << '\n';
			DXF << "31"     << '\n';
			DXF << Bc.z     << '\n';
		}		
	}
	DXF << "0"      << '\n';
	DXF << "ENDSEC" << '\n';
	DXF << "0"      << '\n';
	DXF << "EOF"    << '\n';
	DXF.close();
	TRACE ("<< createDXFwireframe");
}

/* ------------------------------------------------------------------------- */
/// This function converts Spherical Coordinates to Cartesian Coordinates.
/**
@param PolarPoint A point in polar coordinates
@return The cartesian coordinates of the same point */
/* ------------------------------------------------------------------------- */
Vector3 Geodesic::SphericalToCartesian(CPoints* PolarPoint)
{
	Real X = this->cleanFloat(cos(PolarPoint->phi   *DEG_TO_RAD) * sin(PolarPoint->theta *DEG_TO_RAD));
	Real Y = this->cleanFloat(sin(PolarPoint->phi   *DEG_TO_RAD) * sin(PolarPoint->theta *DEG_TO_RAD));
	Real Z = this->cleanFloat(cos(PolarPoint->theta *DEG_TO_RAD));
	X = PolarPoint->radius * X;
	Y = PolarPoint->radius * Y;
	Z = PolarPoint->radius * Z;

//	return Vector3(X,Y,Z);
	return Vector3(-X,Z,Y);    // Conversion to ogre Axis
}
