#include "Geodesic.h"

/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
class CThetaTruncation  
{
public:
	double InitialPeakTheta;
	long   InitialPeakA;
	long   InitialPeakB;
	double PeakTheta;
	long   PeakA;
	long   PeakB;

	CThetaTruncation()
	{
	InitialPeakTheta = 0;
	InitialPeakA = -1;
	InitialPeakB = -1;
	PeakTheta = 0;
	PeakA = -1;
	PeakB = -1;
	};
	virtual ~CThetaTruncation() {};

};

//	long   peakrow;
	CThetaTruncation* Truncation;	//< Pointer to Peak Truncation info
//	double zenith(double, double);			//Calculate zenith height
//	double floor(double, double);			//Calculate floor radius 
	double  FindTruncLimit(double Trunc);
	bool   testChordCrossing(Vector3 &A, Vector3 &B, Vector3 &T);





/* ------------------------------------------------------------------------- */
// This function is used to test whether a truncated chord is crossing an inside vertex.
/** 
@param A	Starting point of the chord.
@param B	Ending point of the chord.
@param T	Vertex to test.
@return		TRUE if the vertex T belongs to the chord A-B.
*/
/* ------------------------------------------------------------------------- */
bool testChordCrossing(Vector3& A, Vector3& B, Vector3& T)
{
	double slope;
	double TestY;
	double DeltaY;
	bool   test_flag = false;

	slope = (B.y - A.y)/(B.x - A.x);					
	TestY = slope * (T.x - A.x) + A.y;
		
	//Calculate the difference in Y
	DeltaY = TestY - T.y;

	if (T.y > 0.0)
	{
		if (DeltaY <= 0.0)  test_flag = true;
	}		
	else
	{
		if (DeltaY >= 0.0)  test_flag = true;
	}
	return (test_flag);
}


///* ------------------------------------------------------------------------- */
///// The zenith altitude function
///* ------------------------------------------------------------------------- */
//double Geodesic::zenith(double radius, double theta)
//{
//	//Calculate the zenith altitude for a given truncation plane specified by theta
//
//	return radius - cos(theta * DEG_TO_RAD);
//}
//
///* ------------------------------------------------------------------------- */
///// This function calculates the floor radius for a given truncation defined by theta
///* ------------------------------------------------------------------------- */
//double Geodesic::floor(double radius, double theta)
//{
//	return radius * sin(theta * DEG_TO_RAD);
//}
//

/* ------------------------------------------------------------------------- */
/// unused function ??????
/* ------------------------------------------------------------------------- */
/*
double FindTruncLimit(double Trunc)
{
	double peak    = 0; // initialized by DDL
	long   indexinc= 5;	// For an icosahedron
	//determine the number of faces required (first face = 0)
	long   last_face = this->getFaceNumber()-1;
	
	//Allocate Peakdata array space
	Truncation = new CThetaTruncation[last_face+1];
	
	for(long j=0; j<=last_face; j+=indexinc)
	{
		this->getFacePoints(j);

		for(long i=1; i<=mPointNumber; i++)
		{
			//Find peak Theta
			if(mSphericPoints[i].theta <= Trunc)
			{
				if(mSphericPoints[i].theta > Truncation[j].InitialPeakTheta)
				{
					Truncation[j].InitialPeakTheta = mSphericPoints[i].theta;
					Truncation[j].InitialPeakA     = mPointLabels[i].A;
					Truncation[j].InitialPeakB     = mPointLabels[i].B;
				}	
			}
		}
		
		if(Truncation[j].InitialPeakTheta > peak)
		{
			peak    = Truncation[j].InitialPeakTheta;
//			peakrow = Truncation[j].InitialPeakA;     // inutile ?
		}

		Truncation[j].PeakTheta = Truncation[j].InitialPeakTheta;
		Truncation[j].PeakA = Truncation[j].InitialPeakA;
		Truncation[j].PeakB = Truncation[j].InitialPeakB;
		long LabelIndex = 0;

		LabelIndex++;
		for(long i=1; i<=mPointNumber; i++)
		{
			//Find peak Theta
			if((mSphericPoints[i].theta > Trunc) && (Truncation[j].InitialPeakA == mPointLabels[i].A + LabelIndex || Truncation[j].InitialPeakA == mPointLabels[i].A - LabelIndex))
			{
				if(mSphericPoints[i].theta <= 90.0)
				{
						Truncation[j].PeakTheta = mSphericPoints[i].theta;
						Truncation[j].PeakA = mPointLabels[i].A;
						Truncation[j].PeakB = mPointLabels[i].B;
				}
			}	
			if(Truncation[j].PeakTheta > peak)
			{
				peak    = Truncation[j].PeakTheta;
//				peakrow = Truncation[j].PeakA;         // inutile ?
			}
		}
	}  
	return peak;
}
*/
