#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;
	
	int		numFaces;
	Face*		face;
	float	slideX, slideY, slideZ;
	float	rotateX, rotateY, rotateZ;
	float	scaleX, scaleY, scaleZ;

public:
	Mesh()
	{
		slideX = 0;
		slideY = 0;
		slideZ = 0;
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		scaleX = 0;
		scaleY = 0;
		scaleZ = 0;
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void Rotate();
	void DrawWireframe();
	void DrawColor();

	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateHoleCuboid(float fSizeX1, float fSizeY1, float fSizeZ1, float fSizeX2, float fSizeY2, float fSizeZ2);
	void CreateCylinder(float fPos, float fHeight, float fRadius, int iSlices);
	void CreateOval(float fHeight,float fLength, float fRadius, int iSlices);
	void CreateHoleOval(float fHeight, float fLength, float fRadius, float fInnerRadius, int iSlices);
	void CreateMoebius(float fRadius, float fThickness, int iPoints);

	void CreateTSlider(float fHeight, float fLength, float fRadius, float fInnerRadius, int iSlices, float fSizeY);
	void CreateHolder(float fSizeX, float fSizeY, float fSizeZ, float fSizeX1, float fSizeY1, float fSizeZ1, float fSizeX2, float fSizeY2, float fSizeZ2);
	void CreateCrank(float fHeight, float fLength, float fRadius,float fInnerRadius,float fInnerHeight, int iSlices);


	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void SetColor(int colorIdx);
	void normal(Face* f, Point3 *normal);


};

#endif