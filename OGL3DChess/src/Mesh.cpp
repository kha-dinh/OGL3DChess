//#include "stdafx.h"
#include "Mesh.h"
#include <math.h>

#define PI			3.141592653589793238
#define	COLORNUM		15


float	ColorArr[COLORNUM][3] = { { 1.0, 69.0/255.0, 0.0 },{ 0.1, 0.9, 0.1 },{ 0.0,  191.0 / 255.0, 1.0 },
{ 0.9, 0.9,  0.1 },{ 0.9, 0.1, 0.9 },{ 0.1, 0.9, 0.9 },
{ 0.3, 0.3, 0.3 },{ 0.5, 0.5, 0.5 },{ 0.9,  0.9, 0.9 },
{ 1.0, 0.5,  0.5 },{ 0.82, 1.0, 0.96 },{ 1.0, 0.82, 0.86 },
{ 0.3, 0.3, 0.3 },{ 1.0, 1.0, 1.0 },{ 153.0 / 255.0,102.0 / 255.0,0.0 } };


void Mesh::SetColor(int colorIdx) {
	for (int f = 0; f < numFaces; f++) {
		for (int v = 0; v < face[f].nVerts; v++) {
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}


void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}


void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}
//Mesh cuboid;
//Mesh holeoval;
void Mesh::CreateTSlider(float fHeight, float fLength, float fRadius, float fInnerRadius, int iSlices, float fSizeY)
{
	//cuboid.CreateCuboid()
	int i, j;
	numVerts = iSlices * 4 + 8;
	pt = new Point3[numVerts];
	float angle = (2 * PI) / iSlices;

	//top out
	for (i = 0; i < iSlices; i++) {
		if (i < iSlices / 4 || i > iSlices * 3 / 4)
			pt[i].set(fLength / 2 + fRadius * cos(i * angle), fHeight / 2, fRadius * sin(i * angle));
		else
			pt[i].set(-fLength / 2 + fRadius * cos(i * angle), fHeight / 2, fRadius * sin(i * angle));
	}
	//top in
	for (i = iSlices * 2; i < iSlices * 3; i++) {
		if (i < iSlices * 9 / 4 || i > iSlices * 11 / 4)
			pt[i].set(fLength / 2 + fInnerRadius * cos(i * angle), fHeight / 2, fInnerRadius * sin(i * angle));
		else
			pt[i].set(-fLength / 2 + fInnerRadius * cos(i * angle), fHeight / 2, fInnerRadius * sin(i * angle));
	}
	//bot out
	for (i = iSlices; i < iSlices * 2; i++) {
		if (i < iSlices * 5 / 4 || i > iSlices * 7 / 4)
			pt[i].set(fLength / 2 + fRadius * cos(i * angle), -fHeight / 2, fRadius * sin(i * angle));
		else
			pt[i].set(-fLength / 2 + fRadius * cos(i * angle), -fHeight / 2, fRadius * sin(i * angle));
	}
	//bot in
	for (i = iSlices * 3; i < iSlices * 4; i++) {
		if (i < iSlices * 13 / 4 || i > iSlices * 15 / 4)
			pt[i].set(fLength / 2 + fInnerRadius * cos(i * angle), -fHeight / 2, fInnerRadius * sin(i * angle));
		else
			pt[i].set(-fLength / 2 + fInnerRadius * cos(i * angle), -fHeight / 2, fInnerRadius * sin(i * angle));
	}

/*
	numFaces = 6;
	face = new Face[numFaces];
*/

	numFaces = iSlices * 4 + 6;
	face = new Face[numFaces];

	//out face
	for (i = 0; i < iSlices; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = i;
		if (i >= iSlices - 1) {
			face[i].vert[1].vertIndex = 0;
			face[i].vert[2].vertIndex = 0 + iSlices;
		}
		else {
			face[i].vert[1].vertIndex = i + 1;
			face[i].vert[2].vertIndex = i + 1 + iSlices;
		}
		face[i].vert[3].vertIndex = i + iSlices;
		for (j = 0; j<face[i].nVerts; j++)
			face[i].vert[j].colorIndex = i;
	}
	//in face
	for (i = iSlices * 2; i < iSlices * 3; i++) {
		int id = i - iSlices;
		face[id].nVerts = 4;
		face[id].vert = new VertexID[face[id].nVerts];
		face[id].vert[0].vertIndex = i;
		if (i >= iSlices * 3 - 1) {
			face[id].vert[1].vertIndex = iSlices * 2;
			face[id].vert[2].vertIndex = iSlices * 2 + iSlices;
		}
		else {
			face[id].vert[1].vertIndex = i + 1;
			face[id].vert[2].vertIndex = i + 1 + iSlices;
		}

		face[id].vert[3].vertIndex = i + iSlices;
		for (j = 0; j<face[id].nVerts; j++)
			face[id].vert[j].colorIndex = id;
	}
	//top
	for (i = 0; i < iSlices; i++) {
		int id = i + 2 * iSlices;
		face[id].nVerts = 4;
		face[id].vert = new VertexID[face[id].nVerts];

		face[id].vert[0].vertIndex = i;
		if (i >= iSlices - 1) {
			face[id].vert[1].vertIndex = 0;
			face[id].vert[2].vertIndex = 0 + 2 * iSlices;
		}
		else {
			face[id].vert[1].vertIndex = i + 1;
			face[id].vert[2].vertIndex = i + 1 + 2 * iSlices;
		}

		face[id].vert[3].vertIndex = i + 2 * iSlices;
		for (j = 0; j<face[id].nVerts; j++)
			face[id].vert[j].colorIndex = id;
	}
	//bot
	for (i = iSlices; i < iSlices * 2; i++) {
		int id = i + 2 * iSlices;
		face[id].nVerts = 4;
		face[id].vert = new VertexID[face[id].nVerts];

		face[id].vert[0].vertIndex = i;
		if (i >= iSlices * 2 - 1) {
			face[id].vert[1].vertIndex = iSlices;
			face[id].vert[2].vertIndex = iSlices + 2 * iSlices;
		}
		else {
			face[id].vert[1].vertIndex = i + 1;
			face[id].vert[2].vertIndex = i + 1 + 2 * iSlices;
		}

		face[id].vert[3].vertIndex = i + 2 * iSlices;
		for (j = 0; j<face[id].nVerts; j++)
			face[id].vert[j].colorIndex = id;
	}



	pt[numVerts-0].set(-fHeight / 2,	 fHeight/2	,fRadius +	fHeight / 2	+ fSizeY);
	pt[numVerts-1].set(fHeight / 2,		fHeight / 2	,fRadius + fHeight / 2	+ fSizeY);
	pt[numVerts-2].set(fHeight / 2,		fHeight / 2	,fRadius + -fHeight / 2	);
	pt[numVerts-3].set(-fHeight / 2,	fHeight / 2	,fRadius + -fHeight / 2	);
	pt[numVerts-4].set(-fHeight / 2,	-fHeight / 2,fRadius + fHeight / 2	+ fSizeY);
	pt[numVerts-5].set(fHeight / 2,		-fHeight / 2,fRadius + fHeight / 2	+ fSizeY);
	pt[numVerts-6].set(fHeight / 2,		-fHeight / 2,fRadius +	-fHeight /2	);
	pt[numVerts-7].set(-fHeight / 2,	-fHeight / 2,fRadius + -fHeight/2	);

	//Left face
	face[numFaces].nVerts = 4;
	face[numFaces].vert = new VertexID[face[0].nVerts];
	face[numFaces].vert[0].vertIndex = numVerts-1;
	face[numFaces].vert[1].vertIndex = numVerts-5;
	face[numFaces].vert[2].vertIndex = numVerts-6;
	face[numFaces].vert[3].vertIndex = numVerts-2;
	for (i = 0; i<face[numFaces].nVerts; i++)
		face[numFaces].vert[i].colorIndex = 0;

	//Right face
	face[numFaces-1].nVerts = 4;
	face[numFaces-1].vert = new VertexID[face[1].nVerts];
	face[numFaces-1].vert[0].vertIndex = numVerts-0;
	face[numFaces-1].vert[1].vertIndex = numVerts-3;
	face[numFaces-1].vert[2].vertIndex = numVerts-7;
	face[numFaces-1].vert[3].vertIndex = numVerts-4;
	for (i = 0; i<face[numFaces-1].nVerts; i++)
		face[numFaces-1].vert[i].colorIndex = 1;

	//top face
	face[numFaces-2].nVerts = 4;
	face[numFaces-2].vert = new VertexID[face[2].nVerts];
	face[numFaces-2].vert[0].vertIndex = numVerts-0;
	face[numFaces-2].vert[1].vertIndex = numVerts-1;
	face[numFaces-2].vert[2].vertIndex = numVerts-2;
	face[numFaces-2].vert[3].vertIndex = numVerts-3;
	for (i = 0; i<face[numFaces-2].nVerts; i++)
		face[numFaces-2].vert[i].colorIndex = 2;

	//bottom face
	face[numFaces-3].nVerts = 4;
	face[numFaces-3].vert = new VertexID[face[3].nVerts];
	face[numFaces-3].vert[0].vertIndex = numVerts-7;
	face[numFaces-3].vert[1].vertIndex = numVerts-6;
	face[numFaces-3].vert[2].vertIndex = numVerts-5;
	face[numFaces-3].vert[3].vertIndex = numVerts-4;
	for (i = 0; i<face[numFaces-3].nVerts; i++)
		face[numFaces-3].vert[i].colorIndex = 3;

	//near face
	face[numFaces-4].nVerts = 4;
	face[numFaces-4].vert = new VertexID[face[4].nVerts];
	face[numFaces-4].vert[0].vertIndex = numVerts-4;
	face[numFaces-4].vert[1].vertIndex = numVerts-5;
	face[numFaces-4].vert[2].vertIndex = numVerts-1;
	face[numFaces-4].vert[3].vertIndex = numVerts-0;
	for (i = 0; i<face[numFaces-4].nVerts; i++)
		face[numFaces-4].vert[i].colorIndex = 4;

	//Far face
	face[numFaces-5].nVerts = 4;
	face[numFaces-5].vert = new VertexID[face[5].nVerts];
	face[numFaces-5].vert[0].vertIndex = numVerts-3;
	face[numFaces-5].vert[1].vertIndex = numVerts-2;
	face[numFaces-5].vert[2].vertIndex = numVerts-6;
	face[numFaces-5].vert[3].vertIndex = numVerts-7;
	for (i = 0; i<face[numFaces-5].nVerts; i++)
		face[numFaces- 5].vert[i].colorIndex = 5;





	
}
Mesh cuboid;
Mesh holecuboid;
void Mesh::CreateHolder(float fSizeX, float fSizeY, float fSizeZ,float fSizeX1, float fSizeY1, float fSizeZ1, float fSizeX2, float fSizeY2, float fSizeZ2) {
	cuboid.CreateCuboid(fSizeX, fSizeY, fSizeZ);
	holecuboid.CreateHoleCuboid(fSizeX1, fSizeY1, fSizeZ1, fSizeX2, fSizeY2, fSizeZ2);

	numVerts = cuboid.numVerts + holecuboid.numVerts;
	numFaces = cuboid.numFaces + holecuboid.numFaces;
	pt = new Point3[numVerts];
	face = new Face[numFaces];
	for (int i = 0; i < cuboid.numVerts; i++) {
		pt[i] = cuboid.pt[i];
		//pt[i].x += fLength / 2;
	}
	for (int i = cuboid.numVerts; i < numVerts; i++) {
		pt[i] = holecuboid.pt[i - cuboid.numVerts];
		pt[i].z += fSizeZ + fSizeZ2;
	}
	for (int i = 0; i < cuboid.numFaces; i++) {
		face[i] = cuboid.face[i];
	}
	for (int i = cuboid.numFaces; i < numFaces; i++) {
		face[i] = holecuboid.face[i - cuboid.numFaces];
		for (int j = 0; j < face[i].nVerts; j++) {
			face[i].vert[j].vertIndex = face[i].vert[j].vertIndex + cuboid.numVerts;
		}
	}
}
Mesh oval;
Mesh cylinder;
void Mesh::CreateCrank(float fHeight, float fLength, float fRadius, float fInnerRadius, float fInnerHeight, int iSlices)
{
	
	oval.CreateOval(fHeight,fLength,fRadius,iSlices);
	cylinder.CreateCylinder(fInnerHeight/2,fInnerHeight,fInnerRadius, iSlices);
	

	numVerts = oval.numVerts +cylinder.numVerts;
	numFaces = oval.numFaces +cylinder.numFaces;
	pt = new Point3[numVerts];
	face = new Face[numFaces];
	for (int i = 0; i < oval.numVerts; i++) {
		pt[i] = oval.pt[i];
		pt[i].x += fLength / 2;
	}
	for (int i = oval.numVerts; i < numVerts; i++) {
		pt[i] = cylinder.pt[i - oval.numVerts];
		pt[i].x += fLength;
	}
	

	for (int i = 0; i < oval.numFaces; i++) {
		face[i] = oval.face[i];
	}
	for (int i = oval.numFaces; i < numFaces; i++) {
		face[i] = cylinder.face[i - oval.numFaces];
		for (int j = 0; j < face[i].nVerts; j++) {
			face[i].vert[j].vertIndex = face[i].vert[j].vertIndex + oval.numVerts;
		}
	}
}
	
void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ) 
{
	int i;
	numVerts = 8;

	pt = new Point3[numVerts];
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(fSizeX, -fSizeY, fSizeZ);
	pt[6].set(fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);

	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;
	
	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}
void Mesh::CreateHoleCuboid(float fSizeX1, float fSizeY1, float fSizeZ1, float fSizeX2, float fSizeY2, float fSizeZ2)
{
	int i;
	numVerts = 16;

	pt = new Point3[numVerts];
	pt[0].set(-fSizeX1, fSizeY1, fSizeZ1);
	pt[1].set(fSizeX1, fSizeY1, fSizeZ1);
	pt[2].set(fSizeX1, fSizeY1, -fSizeZ1);
	pt[3].set(-fSizeX1, fSizeY1, -fSizeZ1);
	pt[4].set(-fSizeX1, -fSizeY1, fSizeZ1);
	pt[5].set(fSizeX1, -fSizeY1, fSizeZ1);
	pt[6].set(fSizeX1, -fSizeY1, -fSizeZ1);
	pt[7].set(-fSizeX1, -fSizeY1, -fSizeZ1);

	pt[8].set(-fSizeX2, fSizeY2, fSizeZ2);
	pt[9].set(fSizeX2, fSizeY2, fSizeZ2);
	pt[10].set(fSizeX2, fSizeY2, -fSizeZ2);
	pt[11].set(-fSizeX2, fSizeY2, -fSizeZ2);
	pt[12].set(-fSizeX2, -fSizeY2, fSizeZ2);
	pt[13].set(fSizeX2, -fSizeY2, fSizeZ2);
	pt[14].set(fSizeX2, -fSizeY2, -fSizeZ2);
	pt[15].set(-fSizeX2, -fSizeY2, -fSizeZ2);

	numFaces = 16;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[3].vertIndex = 1 + 8;
	face[6].vert[2].vertIndex = 5 + 8;
	face[6].vert[1].vertIndex = 6 + 8;
	face[6].vert[0].vertIndex = 2 + 8;
	for (i = 0; i<face[6].nVerts; i++)
		face[6].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[3].vertIndex = 0 + 8;
	face[7].vert[2].vertIndex = 3 + 8;
	face[7].vert[1].vertIndex = 7 + 8;
	face[7].vert[0].vertIndex = 4 + 8;
	for (i = 0; i<face[7].nVerts; i++)
		face[7].vert[i].colorIndex = 7;

	//top face 
	face[10].nVerts = 4;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 0;
	face[10].vert[1].vertIndex = 1;
	face[10].vert[3].vertIndex = 0 + 8;
	face[10].vert[2].vertIndex = 1 + 8;
	for (i = 0; i<face[10].nVerts; i++)
		face[10].vert[i].colorIndex = 10;

	face[11].nVerts = 4;
	face[11].vert = new VertexID[face[11].nVerts];
	face[11].vert[0].vertIndex = 1;
	face[11].vert[1].vertIndex = 2;
	face[11].vert[3].vertIndex = 1 + 8;
	face[11].vert[2].vertIndex = 2 + 8;
	for (i = 0; i<face[11].nVerts; i++)
		face[11].vert[i].colorIndex = 11;

	face[12].nVerts = 4;
	face[12].vert = new VertexID[face[12].nVerts];
	face[12].vert[0].vertIndex = 2;
	face[12].vert[1].vertIndex = 3;
	face[12].vert[3].vertIndex = 2 + 8;
	face[12].vert[2].vertIndex = 3 + 8;
	for (i = 0; i<face[12].nVerts; i++)
		face[12].vert[i].colorIndex = 12;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 3;
	face[2].vert[1].vertIndex = 0;
	face[2].vert[3].vertIndex = 3+ 8;
	face[2].vert[2].vertIndex = 0 + 8;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;




	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[1].vertIndex = 7;
	face[3].vert[0].vertIndex = 6;
	face[3].vert[2].vertIndex = 7 + 8;
	face[3].vert[3].vertIndex = 6 + 8;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[13].nVerts = 4;
	face[13].vert = new VertexID[face[13].nVerts];
	face[13].vert[1].vertIndex = 6;
	face[13].vert[0].vertIndex = 5;
	face[13].vert[2].vertIndex = 6 + 8;
	face[13].vert[3].vertIndex = 5 + 8;
	for (i = 0; i<face[13].nVerts; i++)
		face[13].vert[i].colorIndex = 13;

	face[14].nVerts = 4;
	face[14].vert = new VertexID[face[14].nVerts];
	face[14].vert[1].vertIndex = 5;
	face[14].vert[0].vertIndex = 4;
	face[14].vert[2].vertIndex = 5 + 8;
	face[14].vert[3].vertIndex = 4 + 8;
	for (i = 0; i<face[14].nVerts; i++)
		face[14].vert[i].colorIndex = 14;

	face[15].nVerts = 4;
	face[15].vert = new VertexID[face[15].nVerts];
	face[15].vert[1].vertIndex = 4;
	face[15].vert[0].vertIndex = 7;
	face[15].vert[2].vertIndex = 4 + 8;
	face[15].vert[3].vertIndex = 7 + 8;
	for (i = 0; i<face[15].nVerts; i++)
		face[15].vert[i].colorIndex = 15;



	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	face[8].nVerts = 4;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[3].vertIndex = 4 + 8;
	face[8].vert[2].vertIndex = 5 + 8;
	face[8].vert[1].vertIndex = 1 + 8;
	face[8].vert[0].vertIndex = 0 + 8;
	for (i = 0; i<face[8].nVerts; i++)
		face[8].vert[i].colorIndex = 8;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	face[9].nVerts = 4;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[3].vertIndex = 3 + 8;
	face[9].vert[2].vertIndex = 2 + 8;
	face[9].vert[1].vertIndex = 6 + 8;
	face[9].vert[0].vertIndex = 7 + 8;
	for (i = 0; i<face[9].nVerts; i++)
		face[9].vert[i].colorIndex = 9;
}
void Mesh::CreateCylinder(float fPos, float fHeight, float fRadius, int iSlices)
{
	int i,j,k;
	numVerts = iSlices * 2 + 2;
	pt = new Point3[numVerts];
	pt[numVerts - 1].set(0, fHeight/2 + fPos , 0 );
	pt[numVerts - 2].set(0, -fHeight/ 2 + fPos , 0);
	float angle = (2 * PI) / iSlices;

	numFaces = iSlices * 3;
	face = new Face[numFaces];
	//top
	for (i = 0; i < iSlices; i++) {
		pt[i].set(fRadius * cos(i * angle) , fHeight/2 + fPos , fRadius * sin(i * angle) );
	}
	for (i = 0; i < iSlices ; i ++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = numVerts - 1;
		face[i].vert[2].vertIndex = i;
		if (iSlices - 1 == i) {
			face[i].vert[1].vertIndex = 0;
		}
		else
			face[i].vert[1].vertIndex = i + 1;
		for (j = 0; j<face[i].nVerts; j++)
			face[i].vert[j].colorIndex = i;
	}
	//bot
	for (i = iSlices; i < iSlices * 2; i++) {
		pt[i].set(fRadius * cos(i * angle) , -fHeight / 2 + fPos , fRadius * sin(i * angle) );
	}
	for (i = iSlices; i < iSlices * 2; i++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[1].vertIndex = numVerts - 2;
		face[i].vert[2].vertIndex = i;
		if (iSlices * 2 - 1 == i) {
			face[i].vert[0].vertIndex = iSlices ;
		}
		else
			face[i].vert[0].vertIndex = i + 1;
		for (j = 0; j<face[i].nVerts; j++)
			face[i].vert[j].colorIndex = i;
	}

	//side
	k = 0;
	for (i = iSlices * 2; i < iSlices * 3; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = k;
	
		face[i].vert[3].vertIndex = k + iSlices;
		if (k == iSlices - 1) {
			face[i].vert[1].vertIndex = 0;
			face[i].vert[2].vertIndex = 0 + iSlices;
		}
		else
		{
			face[i].vert[1].vertIndex = k + 1;
			face[i].vert[2].vertIndex = k + 1 + iSlices;
		}
		for (j = 0; j<face[i].nVerts; j++)
			face[i].vert[j].colorIndex = i;
		k++;
	}
}
void Mesh::CreateOval(float fHeight, float fLength, float fRadius, int iSlices)
{
	int i, j;
	numVerts = iSlices*2;
	pt = new Point3[numVerts];
	float angle = (2 * PI) / iSlices;

	//top
	for (i = 0; i < iSlices; i++) {
		if (i < iSlices / 4 || i > iSlices * 3 / 4)
			pt[i].set(fLength/2 + fRadius * cos(i * angle), fHeight / 2, fRadius * sin(i * angle));
		else
			pt[i].set(-fLength/2 + fRadius * cos(i * angle), fHeight / 2, fRadius * sin(i * angle));
	}
	//bot
	for (i = iSlices; i < iSlices * 2; i++) {
		if (i < iSlices*5 / 4 || i > iSlices* 7 / 4)
			pt[i].set(fLength / 2 + fRadius * cos(i * angle), -fHeight / 2, fRadius * sin(i * angle));
		else
			pt[i].set(-fLength / 2 + fRadius * cos(i * angle), -fHeight / 2, fRadius * sin(i * angle));
	}

	numFaces = 2 + iSlices;
	face = new Face[numFaces];
	
	for (i = 0; i < iSlices; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = i;
		if (i >= iSlices - 1) {
			face[i].vert[1].vertIndex = 0;
			face[i].vert[2].vertIndex = 0 + iSlices;
		}
		else {
			face[i].vert[1].vertIndex = i + 1;
			face[i].vert[2].vertIndex = i + 1 + iSlices;
		}
		face[i].vert[3].vertIndex = i + iSlices;
		for (j = 0; j<face[i].nVerts; j++)
			face[i].vert[j].colorIndex = i;
	}

	face[numFaces -2].nVerts = numVerts / 2;
	face[numFaces -2].vert = new VertexID[face[numFaces-2].nVerts];
	
	for (i = iSlices -1; i >= 0; i--) {
		face[numFaces-2].vert[i].vertIndex = i;
		face[numFaces-2].vert[i].colorIndex = numFaces -2;
	}
	face[numFaces-1].nVerts = numVerts / 2;
	face[numFaces-1].vert = new VertexID[face[numFaces-1].nVerts];
	for (i = iSlices; i < iSlices *2; i++) {
		face[numFaces-1].vert[i - iSlices].vertIndex = i;
		face[numFaces-1].vert[i - iSlices].colorIndex = numFaces-1;
	}

}
void Mesh::CreateHoleOval(float fHeight, float fLength, float fRadius, float fInnerRadius, int iSlices)
{
	int i, j;
	numVerts = iSlices * 4;
	pt = new Point3[numVerts];
	float angle = (2 * PI) / iSlices;

	//top out
	for (i = 0; i < iSlices; i++) {
		if (i < iSlices / 4 || i > iSlices * 3 / 4)
			pt[i].set(fLength / 2 + fRadius * cos(i * angle), fHeight / 2, fRadius * sin(i * angle));
		else
			pt[i].set(-fLength / 2 + fRadius * cos(i * angle), fHeight / 2, fRadius * sin(i * angle));
	}
	//top in
	for (i = iSlices*2; i < iSlices*3; i++) {
		if (i < iSlices*9 / 4 || i > iSlices * 11 / 4)
			pt[i].set(fLength / 2 + fInnerRadius * cos(i * angle), fHeight / 2, fInnerRadius * sin(i * angle));
		else
			pt[i].set(-fLength / 2 + fInnerRadius * cos(i * angle), fHeight / 2, fInnerRadius * sin(i * angle));
	}
	//bot out
	for (i = iSlices; i < iSlices * 2; i++) {
		if (i < iSlices * 5 / 4 || i > iSlices * 7 / 4)
			pt[i].set(fLength / 2 + fRadius * cos(i * angle), -fHeight / 2, fRadius * sin(i * angle));
		else
			pt[i].set(-fLength / 2 + fRadius * cos(i * angle), -fHeight / 2, fRadius * sin(i * angle));
	}
	//bot in
	for (i = iSlices*3; i < iSlices * 4; i++) {
		if (i < iSlices * 13 / 4 || i > iSlices * 15 / 4)
			pt[i].set(fLength / 2 + fInnerRadius * cos(i * angle), -fHeight / 2, fInnerRadius * sin(i * angle));
		else
			pt[i].set(-fLength / 2 + fInnerRadius * cos(i * angle), -fHeight / 2, fInnerRadius * sin(i * angle));
	}



	numFaces = iSlices * 4;
	face = new Face[numFaces];

	//out face
	for (i = 0; i < iSlices; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = i;
		if (i >= iSlices - 1) {
			face[i].vert[1].vertIndex = 0 ;
			face[i].vert[2].vertIndex = 0 + iSlices;
		}
		else {
			face[i].vert[1].vertIndex = i + 1;
			face[i].vert[2].vertIndex = i + 1 + iSlices;
		}
		face[i].vert[3].vertIndex = i + iSlices;
		for (j = 0; j<face[i].nVerts; j++)
			face[i].vert[j].colorIndex = i;
	}
	//in face
	for (i = iSlices*2; i < iSlices*3; i++) {
		int id = i - iSlices;
		face[id].nVerts = 4;
		face[id].vert = new VertexID[face[id].nVerts];
		face[id].vert[3].vertIndex = i;
		if (i >= iSlices * 3 -1) {
			face[id].vert[2].vertIndex = iSlices * 2;
			face[id].vert[1].vertIndex = iSlices * 2 + iSlices;
		}
		else {
			face[id].vert[2].vertIndex = i + 1;
			face[id].vert[1].vertIndex = i + 1 + iSlices;
		}

		face[id].vert[0].vertIndex = i + iSlices;
		for (j = 0; j<face[id].nVerts; j++)
			face[id].vert[j].colorIndex = id;
	}
	//top
	for (i = 0; i < iSlices; i++) {
		int id = i + 2*iSlices;
		face[id].nVerts = 4;
		face[id].vert = new VertexID[face[id].nVerts];

		face[id].vert[3].vertIndex = i;
		if (i >= iSlices - 1 ) {
			face[id].vert[2].vertIndex = 0;
			face[id].vert[1].vertIndex = 0 + 2*iSlices;
		}
		else {
			face[id].vert[2].vertIndex = i + 1;
			face[id].vert[1].vertIndex = i + 1 + 2*iSlices;
		}

		face[id].vert[0].vertIndex = i + 2*iSlices;
		for (j = 0; j<face[id].nVerts; j++)
			face[id].vert[j].colorIndex = id;
	}
	//bot
	for (i = iSlices; i < iSlices*2; i++) {
		int id = i + 2 * iSlices;
		face[id].nVerts = 4;
		face[id].vert = new VertexID[face[id].nVerts];

		face[id].vert[0].vertIndex = i;
		if (i >= iSlices*2 - 1) {
			face[id].vert[1].vertIndex = iSlices;
			face[id].vert[2].vertIndex = iSlices + 2 * iSlices;
		}
		else {
			face[id].vert[1].vertIndex = i + 1;
			face[id].vert[2].vertIndex = i + 1 + 2 * iSlices;
		}

		face[id].vert[3].vertIndex = i + 2 * iSlices;
		for (j = 0; j<face[id].nVerts; j++)
			face[id].vert[j].colorIndex = id;
	}
	//face[numFaces - 2].nVerts = numVerts / 2;
	//face[numFaces - 2].vert = new VertexID[face[numFaces - 2].nVerts];

	//for (i = 0; i < iSlices; i++) {
	//	face[numFaces - 2].vert[i].vertIndex = i;
	//	face[numFaces - 2].vert[i].colorIndex = numFaces - 2;
	//}
	//face[numFaces - 1].nVerts = numVerts / 2;
	//face[numFaces - 1].vert = new VertexID[face[numFaces - 1].nVerts];
	//for (i = iSlices; i < iSlices * 2; i++) {
	//	face[numFaces - 1].vert[i - iSlices].vertIndex = i;
	//	face[numFaces - 1].vert[i - iSlices].colorIndex = numFaces - 1;
	//}

}
void Mesh::Rotate() {
	for ( int i = 0; i < numVerts; i++) {
		//pt[i].y = pt[i].y * cos(rotateX) - pt[i].z * sin(rotateX);
		//pt[i].z = pt[i].y * sin(rotateX) - pt[i].z * cos(rotateX);

		pt[i].x = pt[i].x * cos(rotateY) - pt[i].z * sin(rotateY);
		pt[i].z = pt[i].x * sin(rotateY) - pt[i].z * cos(rotateY);

		/*pt[i].x = pt[i].x * cos(rotateZ) - pt[i].y * sin(rotateZ);
		pt[i].y = pt[i].x * sin(rotateZ) - pt[i].y * cos(rotateZ);*/

	}

}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
void normalize(Point3 *v)
{
	// calculate the length of the vector
	float len = (float)(sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));

	// avoid division by 0
	if (len == 0.0f)
		len = 1.0f;

	// reduce to unit size
	v->x /= len;
	v->y /= len;
	v->z /= len;
}
void Mesh::normal(Face* f, Point3 *normal)
{
	Point3 a, b;
	VertexID* v = f->vert;
	// calculate the vectors A and B
	// note that v[3] is defined with counterclockwise winding in mind
	// a
	a.x = pt[v[0].vertIndex].x - pt[v[1].vertIndex].x;
	a.y = pt[v[0].vertIndex].y -  pt[v[1].vertIndex].y;
	a.z = pt[v[0].vertIndex].z -  pt[v[1].vertIndex].z;
	// b
	b.x =  pt[v[1].vertIndex].x -  pt[v[2].vertIndex].x;
	b.y =  pt[v[1].vertIndex].y -  pt[v[2].vertIndex].y;
	b.z =  pt[v[1].vertIndex].z -  pt[v[2].vertIndex].z;

	// calculate the cross product and place the resulting vector
	// into the address specified by vector_t *normal
	normal->x = (a.y * b.z) - (a.z * b.y);
	normal->y = (a.z * b.x) - (a.x * b.z);
	normal->z = (a.x * b.y) - (a.y * b.x);

	// normalize
	normalize(normal);
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Rotate();
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		Point3* n = new Point3;
		normal(&face[f],n);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			//ic = f % COLORNUM;
			glNormal3f(n->x,n->y,n->z);
			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		delete n;
		n = NULL;
		glEnd();
	}
}



