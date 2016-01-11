/* ------------------------------------------------------------------------- */
// File       : GeometricMesh.cpp
// Project    : Long Forgotten Earth
// Author     : David de Lorenzo
/* ------------------------------------------------------------------------- */

#include "macros.h"
#include "GeometricMesh.h"


/* ------------------------------------------------------------------------- */
/// Constructor
/* ------------------------------------------------------------------------- */
GeometricMesh::GeometricMesh(Real radius)
{
	mRadius        = radius;
	mVertexNumber  = 3;        // default value
	mTriangleNumber= 3;        // default value
}

/* ------------------------------------------------------------------------- */
/// Use this function to set the number of triangles of the mesh.
/* ------------------------------------------------------------------------- */
void GeometricMesh::setTriangleNumber(int triangleNumber)
{
	mTriangleNumber = triangleNumber;
}

/* ------------------------------------------------------------------------- */
/// Use this function to set the number of vertices of the mesh.
/* ------------------------------------------------------------------------- */
void GeometricMesh::setVertexNumber(int vertexNumber)
{
	mVertexNumber = vertexNumber;
}

/* ------------------------------------------------------------------------- */
/// This function adds a vertex in the Meshbuffer.
/** 
The vertex is defined by its Position + Normal and UV coordinates.
@param radius  The radius. You can set it to 1, and use real XYZ positions, or set it to a real value
and use XYZ value in the rang [0..1]. 
@param Vx      The X position of the vertex.
@param Vy      The Y position of the vertex.
@param Vz      The Z position of the vertex (vertical axis).
@param U       The U coordinate (optional). If undefined, spherical UV mapping is automaticaly applied.
@param V       The V coordinate (optional). If undefined, spherical UV mapping is automaticaly applied.
@sa addVertex 
*/
/* ------------------------------------------------------------------------- */
void GeometricMesh::addVertexUV(Real radius, Real Vx, Real Vy, Real Vz, Real U, Real V)
{
	// XYZ coordinates of the vertex
	*mpVertex++ = radius*Vx;
	*mpVertex++ = radius*Vy;
	*mpVertex++ = radius*Vz;

	// Normal vector at the vertex position
	Vector3 vNormal = Vector3(Vx, Vy, Vz).normalisedCopy();
	*mpVertex++ = vNormal.x;
	*mpVertex++ = vNormal.y;
	*mpVertex++ = vNormal.z;
	
	// UV coordinates
	if (U==AUTO)
	{
		// U has to be automatically defined
		U = atan2(Vx,Vz)/Math::PI;   // range -1..1
		U = (1+U)/2.0;               // range  0..1
	}
	*mpVertex++ = U;

	if (V==AUTO) 
	{
		// V has to be automatically defined
		V = (1-Vy)/2.0;         // range 0..1
	}
	*mpVertex++ = V;

	DEBUG_LOG("  Point "+ITOA(mVertexIndex)+": X="+ITOA(Vx)+"     \tY="+ITOA(Vy)+"     \tZ="+ITOA(Vz)+"    \tU="+ITOA(U));
//	DEBUG_LOG("V= "+ITOA(V));
	mVertexIndex++;
}

/* ------------------------------------------------------------------------- */
/// This function adds a vertex in the Meshbuffer.
/** 
The vertex is defined by its Position + Normal and UV coordinates. 
Spherical UV mapping is always applied. 
@param radius  The radius. You can set it to 1, and use real XYZ positions, or set it to a real value
and use XYZ value in the rang [0..1]. 
@param Vx      The X position of the vertex.
@param Vy      The Y position of the vertex.
@param Vz      The Z position of the vertex (vertical axis).
*/
/* ------------------------------------------------------------------------- */
void GeometricMesh::addVertex(Real radius, Real Vx, Real Vy, Real Vz)
{
	Real U,V;

	// XYZ coordinates of the vertex
	*mpVertex++ = radius*Vx;
	*mpVertex++ = radius*Vy;
	*mpVertex++ = radius*Vz;

	// Normal vector at the vertex position
	Vector3 vNormal = Vector3(Vx, Vy, Vz).normalisedCopy();
	*mpVertex++ = vNormal.x;
	*mpVertex++ = vNormal.y;
	*mpVertex++ = vNormal.z;
	
	// UV coordinates
	U = atan2(Vx,Vz)/Math::PI;   // range -1..1
	U = (U+1)/2.0;
	*mpVertex++ = U;

	V = (1-Vy)/2.0; 
	*mpVertex++ = V;     // range 0..1

	DEBUG_LOG("  Point "+ITOA(mVertexIndex)+": X="+ITOA(Vx)+"     \tY="+ITOA(Vy)+"     \tZ="+ITOA(Vz)+"    \tU="+ITOA(U));
	mVertexIndex++;
}


/* ------------------------------------------------------------------------- */
/// This function adds 3 vertices in the buffer, making a triangle.
/** 
@param I0      The index of one corner vertex.
@param I1      The index of one corner vertex.
@param I2      The index of one corner vertex.
@param CCW     If FALSE the 3 vertices are inserted in that order: I0, I2, I1. 
This changes the direction of the face normal and the side where the texture will appear.
@param detectborder If TRUE, the function tries to detect of a border of the 
texture is crossing this triangle. If yes the U coordinates are re-ajusted.
*/
/* ------------------------------------------------------------------------- */
void GeometricMesh::addTriangle(int I0, int I1, int I2, bool CCW, bool detectborder)
{
#define UW 0.40

	// special case : the pole.
    /*
    unused variables?
	Real X0 = mpVertex0[I0*8+0];
	Real X1 = mpVertex0[I1*8+0];
	Real X2 = mpVertex0[I2*8+0];
	Real Z0 = mpVertex0[I0*8+2];
	Real Z1 = mpVertex0[I1*8+2];
	Real Z2 = mpVertex0[I2*8+2];
    */
	float U0 = mpVertex0[I0*8+6];
	float U1 = mpVertex0[I1*8+6];
	float U2 = mpVertex0[I2*8+6];

	if (detectborder) 
	{
		// First we check the U coordinate of every corner of the triangle.
		// If some U coordinates are too much wide, we apply a modulo
		// ie: (0.95,0.00,0.05) becomes (-0.05,0.00,0.05)
		TRACE("  U0 U1 U2 =< "+ITOA(U0)+" "+ITOA(U1)+" "+ITOA(U2));
		if (U0<=0)          {/* already modified*/}
		else if (U0-U1>UW) mpVertex0[I0*8+6]=U0-1;
		else if (U0-U2>UW) mpVertex0[I0*8+6]=U0-1;
		if (U1<=0)          {/* already modified*/}
		else if (U1-U0>UW) mpVertex0[I1*8+6]=U1-1;
		else if (U1-U2>UW) mpVertex0[I1*8+6]=U1-1;
		if (U2<=0)          {/* already modified*/}
		else if (U2-U0>UW) mpVertex0[I2*8+6]=U2-1;
		else if (U2-U1>UW) mpVertex0[I2*8+6]=U2-1;
	}
	TRACE("  U0 U1 U2 => "+ITOA(mpVertex0[I0*8+6])+" "+ITOA(mpVertex0[I1*8+6])+" "+ITOA(mpVertex0[I2*8+6]));

	if (CCW)
	{
		mpIndices[mVerticeIndex++] = I0;
		mpIndices[mVerticeIndex++] = I1;
		mpIndices[mVerticeIndex++] = I2;
	}
	else
	{
		mpIndices[mVerticeIndex++] = I0;
		mpIndices[mVerticeIndex++] = I2;
		mpIndices[mVerticeIndex++] = I1;
	}
	TRACE("  Triangle added: P"+ITOA(I0)+" P"+ITOA(I1)+" P"+ITOA(I2));
}


/* ------------------------------------------------------------------------- */
/// This function initialize all the structures and buffers, for creating a manual mesh.
/** 
@param MeshName   The name that will be given to the mesh.
@param vertexNB   The number of vertices needed for the mesh.
@param triangleNB The number of triangles of the mesh.
*/
/* ------------------------------------------------------------------------- */
void GeometricMesh::initializeMesh(String MeshName,int vertexNB, int triangleNB)
{
	mSphere = MeshManager::getSingleton().createManual(MeshName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mSphereVertex = mSphere->createSubMesh();

	mSphere->sharedVertexData = new VertexData();
	mVertexData = mSphere->sharedVertexData;

	// define the vertex format
	mVertexDecl = mVertexData->vertexDeclaration;
	size_t currOffset = 0;
	// positions
	mVertexDecl->addElement(0, currOffset, VET_FLOAT3, VES_POSITION);
	currOffset += VertexElement::getTypeSize(VET_FLOAT3);
	// normals
	mVertexDecl->addElement(0, currOffset, VET_FLOAT3, VES_NORMAL);
	currOffset += VertexElement::getTypeSize(VET_FLOAT3);
	// UV texture coordinates
	mVertexDecl->addElement(0, currOffset, VET_FLOAT2, VES_TEXTURE_COORDINATES, 0);
	currOffset += VertexElement::getTypeSize(VET_FLOAT2);

	// allocate the vertex buffer.
	mVertexData->vertexCount = vertexNB;
	mVertexBuffer = HardwareBufferManager::getSingleton().createVertexBuffer(mVertexDecl->getVertexSize(0), mVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
	VertexBufferBinding* binding = mVertexData->vertexBufferBinding;
	binding->setBinding(0, mVertexBuffer);
	mpVertex = static_cast<float*>(mVertexBuffer->lock(HardwareBuffer::HBL_DISCARD));

	// allocate index buffer
	mSphereVertex->indexData->indexCount = triangleNB*3;
	mSphereVertex->indexData->indexBuffer = HardwareBufferManager::getSingleton().createIndexBuffer(HardwareIndexBuffer::IT_16BIT, mSphereVertex->indexData->indexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
	mIndexBuffer = mSphereVertex->indexData->indexBuffer;
	mpIndices = static_cast<unsigned short*>(mIndexBuffer->lock(HardwareBuffer::HBL_DISCARD));

	// initial status
	mVerticeIndex = 0;
	mVertexIndex  = 0;
	mpVertex0     = mpVertex; 
};



/* ------------------------------------------------------------------------- */
/// This fucntion finalizes the creation of a mesh.
/* ------------------------------------------------------------------------- */
void GeometricMesh::finalizeMesh()
{
	// Unlock the buffers
	mVertexBuffer->unlock();
	mIndexBuffer->unlock();
	// Generate face list
	mSphereVertex->useSharedVertices = true;

	mSphere->_setBounds( AxisAlignedBox( Vector3(-mRadius,-mRadius,-mRadius), Vector3(mRadius,mRadius,mRadius) ), false );
	mSphere->_setBoundingSphereRadius(mRadius);
    // this line makes clear the mesh is loaded (avoids memory leaks)
    mSphere->load();
}


/* ------------------------------------------------------------------------- */
/// This function generates a Manual Ogre Mesh.
/** @param MeshName The name that will be given to the new created mesh. */
/* ------------------------------------------------------------------------- */
void GeometricMesh::createMesh(String MeshName)
{
	this->initializeMesh(MeshName, mVertexNumber, mTriangleNumber); 
	this->fillMesh();
	this->finalizeMesh();
}
