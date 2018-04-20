// Lab3.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <math.h>
#include <iostream>
#include <vector>

#include <string>
#include <time.h>
//#include "supportClass.h"
#include "Mesh.h"


using namespace std;

#define PI			3.141592653589793238
#define	COLORNUM		15


float	ColorArr2[COLORNUM][3] = { { 1.0, 69.0 / 255.0, 0.0 },{ 0.1, 0.9, 0.1 },{ 0.0,  191.0 / 255.0, 1.0 },
{ 0.9, 0.9,  0.1 },{ 0.9, 0.1, 0.9 },{ 0.1, 0.9, 0.9 },
{ 0.3, 0.3, 0.3 },{ 0.5, 0.5, 0.5 },{ 0.9,  0.9, 0.9 },
{ 1.0, 0.5,  0.5 },{ 0.82, 1.0, 0.96 },{ 1.0, 0.82, 0.86 },
{ 0.3, 0.3, 0.3 },{ 1.0, 1.0, 1.0 },{ 153.0 / 255.0,102.0 / 255.0,0.0 } };


string moves = 
"\
e2 e4 e7 e5 \
g1 f3 d7 d6 \
d2 d4 c8 g4	\
d4 e5 g4 f3 \
d1 f3 d6 e5 \
f1 c4 g8 f6 \
f3 b3 d8 e7 \
b1 c3 c7 c6 \
c1 g5 b7 b5 \
c3 b5 c6 b5 \
c4 b5 b8 d7 \
a1 d1 e1 c1 a8 d8 \
d1 d7 d8 d7 \
h1 d1 e7 e6 \
b5 d7 f6 d7 \
b3 b8 d7 b8	\
d1 d8 ";


int		screenWidth = 900;
int		screenHeight= 900;

bool	bWireFrame = false;

float	baseRadius = 0.8;
float	baseHeight = 0.2;
float	baseRotateStep = 2;
int		view = 1;
float moveStep = 0.03;
float cam_step = 0.01;


struct movement {
	movement(int a, int b, int c,int d, int e) {
		src_x = a;
		src_y = b;
		des_x = c;
		des_y = d;
		size = e;
	}
	int src_x;
	int src_y;
	int des_x;
	int des_y;
	int size;
};
vector<movement> v;

float min_angle = 0;
float sec_angle = 0;
float h_angle = 0 ;
float angleG = 0;
float posX, posY, posZ;
float movX, movY, movZ;
float lightX, lightY, lightZ;
float lightR, lightG, lightB;
float lightI;
bool animation = false;
bool playing = false;
bool ultra = false;
bool lightControl = false;
float cam_height = 0;
float cam_distance = 0;


class Shape {
public:
	Mesh * frame;
	Mesh* floor[8][8];
	struct chess {
	public:
		chess() {
		}
		vector<Mesh*> component;
		unsigned int type;
		bool deleted = false;
		float slideX = 0;
		float slideZ = 0;
	};
	chess* pieces[16 + 4 + 4 + 4 + 4];
	chess* pos[8][8];


	int color_black = 12;
	int color_white = 13;
	int frame_color = 14;
	float boardHeight = 0.2;
	float boardSize = 4.0;
	float tileSize = (boardSize / 4.0);    
	float rotateX, rotateY, rotateZ = 0;
	float scale = 1;
	float chessRadius = tileSize * 3 / 8;
	int slices = 50;
	Shape() {
		init();
	}
	void init() {
		scale = 1;
		rotateX= rotateY= rotateZ = 0;
		frame = new Mesh();
		float frameSize = boardSize + 1;
		frame->CreateHoleCuboid(frameSize, boardHeight + 0.2, frameSize, boardSize, boardHeight + 0.3, boardSize );
		frame->SetColor(frame_color);

		createBoard();
		createPawn();
		createBishop();
		createRook();
		createKnight();
		createKing();
		createQueen();
	}

	void createKing() {
		int x_pos = 4;
		int i = 28;
		pieces[i] = new chess();
		Mesh* m1 = new Mesh();
		m1->CreateCylinder(0, 0.1, chessRadius, slices);
		m1->SetColor(color_black);
		m1->slideY = boardHeight + 0.05;
		pieces[i]->component.emplace_back(m1);

		Mesh* m2 = new Mesh();
		m2->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
		m2->SetColor(color_black);
		m2->slideY = boardHeight + 0.1 + 0.05;
		pieces[i]->component.emplace_back(m2);

		Mesh* m3 = new Mesh();
		m3->CreateCylinder(0, 0.8, chessRadius * 2 / 6, 25);
		m3->SetColor(color_black);
		m3->slideY = boardHeight + 0.1 + 0.1 + 0.4;
		pieces[i]->component.emplace_back(m3);

		Mesh* m4 = new Mesh();
		m4->CreateCylinder(0, 0.1, chessRadius * 3 / 5, slices);
		m4->SetColor(color_black);
		m4->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.05;
		pieces[i]->component.emplace_back(m4);

		Mesh* m5 = new Mesh();
		m5->CreateCuboid(0.02, 0.12, 0.02);
		m5->SetColor(color_black);
		m5->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.05 + 0.3 + 0.28;
		m5->rotateZ = 90;
		pieces[i]->component.emplace_back(m5);

		Mesh* m6 = new Mesh();
		m6->CreateCuboid(0.02, 0.22, 0.02);
		m6->SetColor(color_black);
		m6->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.05 + 0.3 + 0.2;
		pieces[i]->component.emplace_back(m6);

		pieces[i]->slideX = floor[0][x_pos]->slideX;
		pieces[i]->slideZ = floor[0][x_pos]->slideZ;

		pos[0][x_pos] = pieces[i];
		//////
		i = 29;
		pieces[i] = new chess();
		Mesh* m11 = new Mesh();
		m11->CreateCylinder(0, 0.1, chessRadius, slices);
		m11->SetColor(color_white);
		m11->slideY = boardHeight + 0.05;
		pieces[i]->component.emplace_back(m11);

		Mesh* m12 = new Mesh();
		m12->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
		m12->SetColor(color_white);
		m12->slideY = boardHeight + 0.1 + 0.05;
		pieces[i]->component.emplace_back(m12);

		Mesh* m13 = new Mesh();
		m13->CreateCylinder(0, 0.8, chessRadius * 2 / 6, 25);
		m13->SetColor(color_white);
		m13->slideY = boardHeight + 0.1 + 0.1 + 0.4;
		pieces[i]->component.emplace_back(m13);

		Mesh* m14 = new Mesh();
		m14->CreateCylinder(0, 0.1, chessRadius * 3 / 5, slices);
		m14->SetColor(color_white);
		m14->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.05;
		pieces[i]->component.emplace_back(m14);

		Mesh* m15 = new Mesh();
		m15->CreateCuboid(0.02, 0.12, 0.02);
		m15->SetColor(color_white);
		m15->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.05 + 0.3 + 0.28;
		m15->rotateZ = 90;
		pieces[i]->component.emplace_back(m15);

		Mesh* m16 = new Mesh();
		m16->CreateCuboid(0.02, 0.22, 0.02);
		m16->SetColor(color_white);
		m16->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.05 + 0.3 + 0.2;
		pieces[i]->component.emplace_back(m16);

		pieces[i]->slideX = floor[7][x_pos]->slideX;
		pieces[i]->slideZ = floor[7][x_pos]->slideZ;
		pos[7][x_pos] = pieces[i];
	}
	void drawKing() {
		int j = 28;
		if (pieces[j]->deleted == false) {
			for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
				draw(*it, pieces[j]->slideX,pieces[j]->slideZ);
			}
			glPushMatrix();
			glScalef(scale, scale, scale);
			glRotatef(rotateY, 0, 1, 0);

			glTranslatef(pieces[j]->component.back()->slideX, pieces[j]->component.back()->slideY - 0.3, pieces[j]->component.back()->slideZ);
			glTranslatef(pieces[j]->slideX, 0, pieces[j]->slideZ);
			glRotatef(-90, 0, 1, 0);
			glColor3f(ColorArr2[color_black][0], ColorArr2[color_black][1], ColorArr2[color_black][2]);
			glutSolidTeapot(0.3);
			glPopMatrix();

		}
		j = 29;
		if (pieces[j]->deleted == false) {
			for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
				draw(*it, pieces[j]->slideX, pieces[j]->slideZ);
			}
			glPushMatrix();
			glScalef(scale, scale, scale);
			glRotatef(rotateY, 0, 1, 0);

			glTranslatef(pieces[j]->component.back()->slideX, pieces[j]->component.back()->slideY - 0.3, pieces[j]->component.back()->slideZ);
			glTranslatef(pieces[j]->slideX, 0, pieces[j]->slideZ);
			glRotatef(90, 0, 1, 0);
			glColor3f(ColorArr2[color_white][0], ColorArr2[color_white][1], ColorArr2[color_white][2]);
			glutSolidTeapot(0.3);
			glPopMatrix();
		}
	}
	void createQueen() {
		int x_pos = 3;
		int i = 30;
		pieces[i] = new chess();
		Mesh* m1 = new Mesh();
		m1->CreateCylinder(0, 0.1, chessRadius, slices);
		m1->SetColor(color_black);
		m1->slideY = boardHeight + 0.05;
		pieces[i]->component.emplace_back(m1);

		Mesh* m2 = new Mesh();
		m2->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
		m2->SetColor(color_black);
		m2->slideY = boardHeight + 0.1 + 0.05;
		pieces[i]->component.emplace_back(m2);

		Mesh* m3 = new Mesh();
		m3->CreateCylinder(0, 0.8, chessRadius * 2 / 6, 25);
		m3->SetColor(color_black);
		m3->slideY = boardHeight + 0.1 + 0.1 + 0.4;
		pieces[i]->component.emplace_back(m3);

		Mesh* m4 = new Mesh();
		m4->CreateCylinder(0, 0.1, chessRadius * 3 / 5, slices);
		m4->SetColor(color_black);
		m4->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.05;
		pieces[i]->component.emplace_back(m4);

		pieces[i]->slideX = floor[0][x_pos]->slideX;
		pieces[i]->slideZ = floor[0][x_pos]->slideZ;
		pos[0][x_pos] = pieces[i];
		//////
		i = 31;
		pieces[i] = new chess();
		Mesh* m11 = new Mesh();
		m11->CreateCylinder(0, 0.1, chessRadius, slices);
		m11->SetColor(color_white);
		m11->slideY = boardHeight + 0.05;
		pieces[i]->component.emplace_back(m11);

		Mesh* m12 = new Mesh();
		m12->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
		m12->SetColor(color_white);
		m12->slideY = boardHeight + 0.1 + 0.05;
		pieces[i]->component.emplace_back(m12);

		Mesh* m13 = new Mesh();
		m13->CreateCylinder(0, 0.8, chessRadius * 2 / 6, 25);
		m13->SetColor(color_white);
		m13->slideY = boardHeight + 0.1 + 0.1 + 0.4;
		pieces[i]->component.emplace_back(m13);

		Mesh* m14 = new Mesh();
		m14->CreateCylinder(0, 0.1, chessRadius * 3 / 5, slices);
		m14->SetColor(color_white);
		m14->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.05;
		pieces[i]->component.emplace_back(m14);

		pieces[i]->slideX = floor[7][x_pos]->slideX;
		pieces[i]->slideZ = floor[7][x_pos]->slideZ;
		pos[7][x_pos] = pieces[i];
	}
	void drawQueen() {
		int j = 30;
		if (pieces[j]->deleted == false) {
			for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
				draw(*it, pieces[j]->slideX, pieces[j]->slideZ);
			}
			int numpot = 7;
			float angle = 360.0f / numpot;
			for (int i = 0; i < numpot; i++) {
				glPushMatrix();
				glScalef(scale, scale, scale);
				glRotatef(rotateY, 0, 1, 0);

				glTranslatef(pieces[j]->component.back()->slideX, pieces[j]->component.back()->slideY + 0.2, pieces[j]->component.back()->slideZ);
				glTranslatef(pieces[j]->slideX, 0, pieces[j]->slideZ);

				glRotatef(i*angle, 0, 1, 0);
				glRotatef(20, 0, 0, 1);
				glColor3f(ColorArr2[color_black][0], ColorArr2[color_black][1], ColorArr2[color_black][2]);
				glutSolidTeapot(0.3);
				glPopMatrix();
			}
		

		}
		j = 31;
		if (pieces[j]->deleted == false) {
			for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
				    draw(*it, pieces[j]->slideX,pieces[j]->slideZ);
			}
			int numpot = 7;
			float angle = 360.0f / numpot;
			for (int i = 0; i < numpot; i++) {
				glPushMatrix();
				glScalef(scale, scale, scale);
				glRotatef(rotateY, 0, 1, 0);

				glTranslatef(pieces[j]->component.back()->slideX, pieces[j]->component.back()->slideY + 0.2, pieces[j]->component.back()->slideZ);
				glTranslatef(pieces[j]->slideX, 0, pieces[j]->slideZ);
				glRotatef(i*angle, 0, 1, 0);
				glRotatef(20, 0, 0, 1);
				glColor3f(ColorArr2[color_white][0], ColorArr2[color_white][1], ColorArr2[color_white][2]);
				glutSolidTeapot(0.3);
				glPopMatrix();
			}
		}


	}
	void createBoard() {
		int color = color_white;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				floor[i][j] = new Mesh();
				floor[i][j]->CreateCuboid(tileSize / 2, boardHeight, tileSize / 2);
				if (i < 4) {
					if (j < 4) {
						floor[i][j]->slideX = -(3-j)  * tileSize - tileSize / 2;
						floor[i][j]->slideY = 0;
						floor[i][j]->slideZ = -(3-i) * tileSize - tileSize / 2;
					}
					else {
						floor[i][j]->slideX = (j-4) * tileSize + tileSize / 2;
						floor[i][j]->slideY = 0;
						floor[i][j]->slideZ = -(3-i)* tileSize - tileSize / 2;
					}	
				}
				else {
					if (j < 4) {
						floor[i][j]->slideX = -(3 - j) * tileSize - tileSize / 2;
						floor[i][j]->slideY = 0;
						floor[i][j]->slideZ = (i - 4) * tileSize + tileSize / 2;
					}
					else {
						floor[i][j]->slideX = (j - 4) * tileSize + tileSize / 2;
						floor[i][j]->slideY = 0;
						floor[i][j]->slideZ = (i - 4) * tileSize + tileSize / 2;
					}
				}
				floor[i][j]->SetColor(color);
				if (color == color_white) {
					color = color_black;
				}
				else color = color_white;
			}
			if (color == color_white) {
				color = color_black;
			}
			else color = color_white;
		
		}
	}
	void drawText() {
		for (int j = 0; j < 8; j++) {
			//draw(floor[i][j]);
			glPushMatrix();
			glScalef(scale , scale, scale);

			glRotatef(rotateY, 0, 1, 0);
			//glScalef(, 1 / 152.38, 1 / 152.38);

			glTranslatef(floor[0][j]->slideX + tileSize/4 + 0.1, boardHeight+ 0.3, floor[0][j]->slideZ - tileSize*2/1.5 );
			glRotatef(180, 0, 1, 0);

			glRotatef(-90, 1, 0, 0);

			glScalef(1 / 160.0, 1 / 160.0, 1 / 160.0);

			glColor3f(1.0, 1.0, 1.0);
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, j + 'A');
			glPopMatrix();
		}
		for (int j = 0; j < 8; j++) {
			//draw(floor[i][j]);
			glPushMatrix();
			glScalef(scale, scale, scale);

			glRotatef(rotateY, 0, 1, 0);
			//glScalef(, 1 / 152.38, 1 / 152.38);

			glTranslatef(floor[7][j]->slideX - tileSize / 4 - 0.1 , boardHeight + 0.3, floor[7][j]->slideZ + tileSize*2 / 1.5);
			glRotatef(-90, 1, 0, 0);
			glScalef(1 / 160.0, 1 / 160.0, 1 / 160.0);

			glColor3f(1.0, 1.0, 1.0);
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, j + 'A');
			glPopMatrix();
		}
		for (int j = 0; j < 8; j++) {
			glPushMatrix();
			glScalef(scale, scale, scale);

			glRotatef(rotateY, 0, 1, 0);

			glTranslatef(floor[j][0]->slideX - tileSize * 2 / 1.5, boardHeight + 0.3, floor[j][0]->slideZ - tileSize / 4 - 0.1);
			glRotatef(-90, 0, 1, 0);

			glRotatef(-90, 1, 0, 0);
			glScalef(1 / 160.0, 1 / 160.0, 1 / 160.0);

			glColor3f(1.0, 1.0, 1.0);
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 7 -j + 1 + '0' );
			glPopMatrix();
		}
		for (int j = 0; j < 8; j++) {
			glPushMatrix();
			glScalef(scale, scale, scale);

			glRotatef(rotateY, 0, 1, 0);

			glTranslatef(floor[j][7]->slideX + tileSize * 2 / 1.5, boardHeight + 0.3, floor[j][7]->slideZ+ tileSize / 4 + 0.1);
			glRotatef(90, 0, 1, 0);

			glRotatef(-90, 1, 0, 0);
			glScalef(1 / 160.0, 1 / 160.0, 1 / 160.0);

			glColor3f(1.0, 1.0, 1.0);
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 7 -j + 1 + '0');
			glPopMatrix();
		}
		
	}
	void createKnight() {
		int x_pos = 1;
		for (int i = 24; i < 26; i++) {
			pieces[i] = new chess();
			Mesh* m1 = new Mesh();
			m1->CreateCylinder(0, 0.1, chessRadius, slices);
			m1->SetColor(color_black);
			m1->slideY = boardHeight + 0.05;
			pieces[i]->component.emplace_back(m1);

			Mesh* m2 = new Mesh();
			m2->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
			m2->SetColor(color_black);
			m2->slideY = boardHeight + 0.1 + 0.05;
			pieces[i]->component.emplace_back(m2);

			Mesh* m3 = new Mesh();
			m3->CreateCylinder(0, 0.2, chessRadius * 2 / 6, 25);
			m3->SetColor(color_black);
			m3->slideY = boardHeight + 0.1 + 0.1 + 0.1;
			pieces[i]->component.emplace_back(m3);

			Mesh* m4 = new Mesh();
			m4->CreateCylinder(0, 0.1, chessRadius * 3 / 3, slices);
			m4->SetColor(color_black);
			m4->slideY = boardHeight + 0.1 + 0.1 + 0.2 + 0.05;
			pieces[i]->component.emplace_back(m4);

			Mesh* m5 = new Mesh();
			m5->CreateCuboid(0.2, 0.4, 0.22);
			m5->SetColor(color_black);
			m5->slideZ = -0.1;// floor[0][x_pos]->slideZ - 0.1;
			m5->slideY = boardHeight + 0.1 + 0.1 + 0.2 + 0.1 + 0.4;
			m5->rotateX = -20;
			pieces[i]->component.emplace_back(m5);

			Mesh* m6 = new Mesh();
			m6->CreateCuboid(0.15, 0.4, 0.17);
			m6->SetColor(color_black);
			m6->slideZ = 0.1;// floor[0][x_pos]->slideZ + 0.1;
			m6->slideY = boardHeight + 0.1 + 0.1 + 0.2 + 0.1 + 0.4 + 0.3;
			m6->rotateX = - 60;
			pieces[i]->component.emplace_back(m6);

			Mesh* m7 = new Mesh();
			m7->CreateCylinder(0,0.1, 0.45, slices);
			m7->SetColor(color_black);
			m7->slideZ = -0.3;// floor[0][x_pos]->slideZ - 0.3 ;
			m7->slideY = boardHeight + 0.1 + 0.1 + 0.2 + 0.1 + 0.4 + 0.2 ;
			m7->rotateZ = 90;

			//m7->rotateY = -55;
			//m7->rotateY = -20;

			pieces[i]->component.emplace_back(m7);

			pieces[i]->slideX = floor[0][x_pos]->slideX;
			pieces[i]->slideZ = floor[0][x_pos]->slideZ;
			pos[0][x_pos] = pieces[i];
			x_pos += 5;
		}
		x_pos = 1;
		for (int i = 26; i < 28; i++) {
			pieces[i] = new chess();
			Mesh* m1 = new Mesh();
			m1->CreateCylinder(0, 0.1, chessRadius, slices);
			m1->SetColor(color_white);
			m1->slideY = boardHeight + 0.05;
			pieces[i]->component.emplace_back(m1);

			Mesh* m2 = new Mesh();
			m2->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
			m2->SetColor(color_white);
			m2->slideY = boardHeight + 0.1 + 0.05;
			pieces[i]->component.emplace_back(m2);

			Mesh* m3 = new Mesh();
			m3->CreateCylinder(0, 0.2, chessRadius * 2 / 6, 25);
			m3->SetColor(color_white);
			m3->slideY = boardHeight + 0.1 + 0.1 + 0.1;
			pieces[i]->component.emplace_back(m3);

			Mesh* m4 = new Mesh();
			m4->CreateCylinder(0, 0.1, chessRadius * 3 / 3, slices);
			m4->SetColor(color_white);
			m4->slideY = boardHeight + 0.1 + 0.1 + 0.2 + 0.05;
			pieces[i]->component.emplace_back(m4);

			Mesh* m5 = new Mesh();
			m5->CreateCuboid(0.2, 0.4, 0.22);
			m5->SetColor(color_white);
			m5->slideZ = 0.1;
			m5->slideY = boardHeight + 0.1 + 0.1 + 0.2 + 0.1 + 0.4;
			m5->rotateX = 20;
			pieces[i]->component.emplace_back(m5);

			Mesh* m6 = new Mesh();
			m6->CreateCuboid(0.15, 0.4, 0.17);
			m6->SetColor(color_white);
			m6->slideZ = -0.1;
			m6->slideY = boardHeight + 0.1 + 0.1 + 0.2 + 0.1 + 0.4 + 0.3;
			m6->rotateX = 60;
			pieces[i]->component.emplace_back(m6);

			Mesh* m7 = new Mesh();
			m7->CreateCylinder(0, 0.1, 0.45, slices);
			m7->SetColor(color_white);
			m7->slideZ = 0.3;
			m7->slideY = boardHeight + 0.1 + 0.1 + 0.2 + 0.1 + 0.4 + 0.2 ;
			m7->rotateZ = 90;
			pieces[i]->component.emplace_back(m7);

			pieces[i]->slideX = floor[7][x_pos]->slideX;
			pieces[i]->slideZ = floor[7][x_pos]->slideZ;
			pos[7][x_pos] = pieces[i];
			x_pos += 5;
		}


	}
	void drawKnight() {
		for (int j = 24; j < 26; j++) {
			if (pieces[j]->deleted == false) {
				for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
					draw(*it,pieces[j]->slideX,pieces[j]->slideZ);
				}
			}
		}
		for (int j = 26; j < 28; j++) {
			if (pieces[j]->deleted == false) {
				for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
					draw(*it,pieces[j]->slideX,pieces[j]->slideZ);
				}

			}

		}
	}
	void createRook() {
		int x_pos = 0;
		for (int i = 20; i < 22; i++) {
			pieces[i] = new chess();
			Mesh* m1 = new Mesh();
			m1->CreateCylinder(0, 0.1, chessRadius, slices);
			m1->SetColor(color_black);
			m1->slideX = 0;// floor[0][x_pos]->slideX;
			m1->slideZ = 0;//floor[0][x_pos]->slideZ;
			m1->slideY = boardHeight + 0.05;
			pieces[i]->component.emplace_back(m1);

			Mesh* m2 = new Mesh();
			m2->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
			m2->SetColor(color_black);
			m2->slideX = 0;// floor[0][x_pos]->slideX;
			m2->slideZ = 0;// floor[0][x_pos]->slideZ;
			m2->slideY = boardHeight + 0.1 + 0.05;
			pieces[i]->component.emplace_back(m2);

			Mesh* m3 = new Mesh();
			m3->CreateCylinder(0, 0.8, chessRadius * 2 / 6, 25);
			m3->SetColor(color_black);
			m3->slideX = 0;// floor[0][x_pos]->slideX;
			m3->slideZ = 0;// floor[0][x_pos]->slideZ;
			m3->slideY = boardHeight + 0.1 + 0.1 + 0.4;
			pieces[i]->component.emplace_back(m3);

			Mesh* m4 = new Mesh();
			m4->CreateCylinder(0, 0.1, chessRadius * 3 / 5, slices);
			m4->SetColor(color_black);
			m4->slideX = 0;// floor[0][x_pos]->slideX;
			m4->slideZ = 0;// floor[0][x_pos]->slideZ;
			m4->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.05;
			pieces[i]->component.emplace_back(m4);

			Mesh* m5 = new Mesh();
			m5->CreateHoleOval(0.15, 0, chessRadius * 3 / 4, chessRadius * 3 / 6, slices);
			m5->SetColor(color_black);
			m5->slideX = 0;// floor[0][x_pos]->slideX;
			m5->slideZ = 0;// floor[0][x_pos]->slideZ;
			m5->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.1 + 0.15 / 2;
			pieces[i]->component.emplace_back(m5);

			pieces[i]->slideX = floor[0][x_pos]->slideX;
			pieces[i]->slideZ = floor[0][x_pos]->slideZ;
			pos[0][x_pos] = pieces[i];
			x_pos += 7;
		}
		x_pos = 0;
		for (int i = 22; i < 24; i++) {
			pieces[i] = new chess();
			Mesh* m1 = new Mesh();
			m1->CreateCylinder(0, 0.1, chessRadius, slices);
			m1->SetColor(color_white);
			m1->slideX = 0;// floor[7][x_pos]->slideX;
			m1->slideZ = 0;// floor[7][x_pos]->slideZ;
			m1->slideY = boardHeight + 0.05;
			pieces[i]->component.emplace_back(m1);

			Mesh* m2 = new Mesh();
			m2->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
			m2->SetColor(color_white);
			m2->slideX = 0;// floor[7][x_pos]->slideX;
			m2->slideZ = 0;// floor[7][x_pos]->slideZ;
			m2->slideY = boardHeight + 0.1 + 0.05;
			pieces[i]->component.emplace_back(m2);

			Mesh* m3 = new Mesh();
			m3->CreateCylinder(0, 0.8, chessRadius * 2 / 6, 25);
			m3->SetColor(color_white);
			m3->slideX = 0;// floor[7][x_pos]->slideX;
			m3->slideZ = 0;// floor[7][x_pos]->slideZ;
			m3->slideY = boardHeight + 0.1 + 0.1 + 0.4;
			pieces[i]->component.emplace_back(m3);

			Mesh* m4 = new Mesh();
			m4->CreateCylinder(0, 0.1, chessRadius * 3 / 5, slices);
			m4->SetColor(color_white);
			m4->slideX = 0;// floor[7][x_pos]->slideX;
			m4->slideZ = 0;// floor[7][x_pos]->slideZ;
			m4->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.05;
			pieces[i]->component.emplace_back(m4);

			Mesh* m5 = new Mesh();
			m5->CreateHoleOval(0.15, 0, chessRadius * 3 / 4, chessRadius * 3 / 6, slices);
			m5->SetColor(color_white);
			m5->slideX = 0;// floor[7][x_pos]->slideX;
			m5->slideZ = 0;// floor[7][x_pos]->slideZ;
			m5->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.1+ 0.15/2;
			pieces[i]->component.emplace_back(m5);

			pieces[i]->slideX = floor[7][x_pos]->slideX;
			pieces[i]->slideZ = floor[7][x_pos]->slideZ;
			pos[7][x_pos] = pieces[i];
			x_pos += 7;
		}


	}
	void drawRook() {
		for (int j = 20; j < 22; j++) {
			if (pieces[j]->deleted == false) {
				for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
					draw(*it,pieces[j]->slideX, pieces[j]->slideZ);
				}
			
			}
		}
		for (int j = 22; j < 24; j++) {
			if (pieces[j]->deleted == false) {
				for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
					draw(*it, pieces[j]->slideX, pieces[j]->slideZ);
				}

			}

		}
	}	
	void createBishop() {
		int x_pos = 2;
		for (int i = 16; i < 18; i++) {
			pieces[i] = new chess();
			Mesh* m1 = new Mesh();
			m1->CreateCylinder(0, 0.1, chessRadius, slices);
			m1->SetColor(color_black);
			m1->slideY = boardHeight + 0.05;
			pieces[i]->component.emplace_back(m1);

			Mesh* m2 = new Mesh();
			m2->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
			m2->SetColor(color_black);
			m2->slideY = boardHeight + 0.1 + 0.05;
			pieces[i]->component.emplace_back(m2);

			Mesh* m3 = new Mesh();
			m3->CreateCylinder(0, 0.8, chessRadius * 2 / 6, 25);
			m3->SetColor(color_black);
			m3->slideY = boardHeight + 0.1 + 0.1 + 0.4;
			pieces[i]->component.emplace_back(m3);

			Mesh* m4 = new Mesh();
			m4->CreateCylinder(0, 0.08, chessRadius * 3 / 5, slices);
			m4->SetColor(color_black);
			m4->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.04;
			pieces[i]->component.emplace_back(m4);

			pieces[i]->slideX = floor[0][x_pos]->slideX;
			pieces[i]->slideZ = floor[0][x_pos]->slideZ;
			pos[0][x_pos] = pieces[i];
			x_pos += 3;	
		}
		x_pos = 2;
		for (int i = 18; i < 20; i++) {
			pieces[i] = new chess();
			Mesh* m1 = new Mesh();
			m1->CreateCylinder(0, 0.1, chessRadius, slices);
			m1->SetColor(color_white);
			m1->slideX =0;
			m1->slideZ =0;
			m1->slideY = boardHeight + 0.05;
			pieces[i]->component.emplace_back(m1);

			Mesh* m2 = new Mesh();
			m2->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
			m2->SetColor(color_white);
			m2->slideY = boardHeight + 0.1 + 0.05;
			pieces[i]->component.emplace_back(m2);

			Mesh* m3 = new Mesh();
			m3->CreateCylinder(0, 0.8, chessRadius * 2 / 6, 25);
			m3->SetColor(color_white);
			m3->slideY = boardHeight + 0.1 + 0.1 + 0.4;
			pieces[i]->component.emplace_back(m3);

			Mesh* m4 = new Mesh();
			m4->CreateCylinder(0, 0.08, chessRadius * 3 / 5, slices);
			m4->SetColor(color_white);
			m4->slideY = boardHeight + 0.1 + 0.1 + 0.8 + 0.04;
			pieces[i]->component.emplace_back(m4);

			pieces[i]->slideX = floor[7][x_pos]->slideX;
			pieces[i]->slideZ = floor[7][x_pos]->slideZ;
			pos[7][x_pos] = pieces[i];
			x_pos += 3;
		}
	}
	void drawBishop() {
		for (int j = 16; j < 18; j++) {
			if (pieces[j]->deleted == false) {
				for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
					draw(*it,pieces[j]->slideX,pieces[j]->slideZ);
				}
				glPushMatrix();
				glScalef(scale, scale, scale);
				glRotatef(rotateY, 0, 1, 0);
				glTranslatef(pieces[j]->component.back()->slideX, pieces[j]->component.back()->slideY + 0.2 , pieces[j]->component.back()->slideZ);
				glTranslatef(pieces[j]->slideX, 0, pieces[j]->slideZ);
				glColor3f(ColorArr2[color_black][0], ColorArr2[color_black][1], ColorArr2[color_black][2]);
				glutSolidSphere(chessRadius * 3 / 5, slices, slices);
				glPopMatrix();

				glPushMatrix();
				glScalef(scale, scale, scale);
				glRotatef(rotateY, 0, 1, 0);
				glTranslatef(pieces[j]->component.back()->slideX, pieces[j]->component.back()->slideY + 0.45, pieces[j]->component.back()->slideZ);
				glTranslatef(pieces[j]->slideX, 0, pieces[j]->slideZ);
				glColor3f(ColorArr2[color_black][0], ColorArr2[color_black][1], ColorArr2[color_black][2]);

				glutSolidSphere(0.05, slices, slices);
				glPopMatrix();
			}
		}
		for (int j = 18; j < 20; j++) {
			if (pieces[j]->deleted == false) {
				for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
					    draw(*it, pieces[j]->slideX,pieces[j]->slideZ);
				}
				glPushMatrix();
				glScalef(scale, scale, scale);
				glRotatef(rotateY, 0, 1, 0);
				glTranslatef(pieces[j]->component.back()->slideX, pieces[j]->component.back()->slideY + 0.2, pieces[j]->component.back()->slideZ);
				glTranslatef(pieces[j]->slideX, 0, pieces[j]->slideZ);
				glColor3f(ColorArr2[color_white][0], ColorArr2[color_white][1], ColorArr2[color_white][2]);
				glutSolidSphere(chessRadius * 3 / 5, slices, slices);
				glPopMatrix();

				glPushMatrix();
				glScalef(scale, scale, scale);
				glRotatef(rotateY, 0, 1, 0);
				glTranslatef(pieces[j]->component.back()->slideX, pieces[j]->component.back()->slideY + 0.45, pieces[j]->component.back()->slideZ);
				glTranslatef(pieces[j]->slideX, 0, pieces[j]->slideZ);
				glColor3f(ColorArr2[color_white][0], ColorArr2[color_white][1], ColorArr2[color_white][2]);
				glutSolidSphere(0.05, slices, slices);
				glPopMatrix();
			}

		}
	}
	void createPawn() {
		for (int i = 0; i < 8; i++) {
			pieces[i] = new chess();
			Mesh* m1 = new Mesh();
			m1->CreateCylinder(0, 0.1, chessRadius, slices);
			m1->SetColor(color_black);
			m1->slideY = boardHeight + 0.05;
			pieces[i]->component.emplace_back(m1);

			Mesh* m2 = new Mesh();
			m2->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
			m2->SetColor(color_black);
			m2->slideY = boardHeight + 0.1 + 0.05;
			pieces[i]->component.emplace_back(m2);

			Mesh* m3 = new Mesh();
			m3->CreateCylinder(0, 0.6, chessRadius * 2 / 6, 25);
			m3->SetColor(color_black);
			m3->slideY = boardHeight + 0.1 + 0.1 + 0.3;
			pieces[i]->component.emplace_back(m3);
			pieces[i]->slideZ = floor[1][i]->slideZ;
			pieces[i]->slideX = floor[1][i]->slideX;
			pos[1][i] = pieces[i];
		}
		for (int i = 8; i < 16; i++) {
			pieces[i] = new chess();
			Mesh* m1 = new Mesh();
			m1->CreateCylinder(0, 0.1, chessRadius, slices);
			m1->SetColor(color_white);
			m1->slideY = boardHeight + 0.05;
			pieces[i]->component.emplace_back(m1);

			Mesh* m2 = new Mesh();
			m2->CreateCylinder(0, 0.1, chessRadius * 3 / 4, slices);
			m2->SetColor(color_white);
			m2->slideY = boardHeight + 0.1 + 0.05;
			pieces[i]->component.emplace_back(m2);


			Mesh* m3 = new Mesh();
			m3->CreateCylinder(0, 0.6, chessRadius * 2 / 6, 25);
			m3->SetColor(color_white);
			m3->slideY = boardHeight + 0.1 + 0.1 + 0.3;
			pieces[i]->component.emplace_back(m3);

			pieces[i]->slideX = floor[6][i - 8]->slideX;
			pieces[i]->slideZ = floor[6][i - 8]->slideZ;
			pos[6][i-8] = pieces[i];
		}
	}		
	void drawPawn() {

		for (int j = 0; j < 8; j++) {
			
			if (pieces[j]->deleted == false) {
				

				for (auto it = pieces[j]->component.begin();it!= pieces[j]->component.end(); ++it) {

					draw(*it, pieces[j]->slideX, pieces[j]->slideZ);

				}
				glPushMatrix();
				glScalef(scale, scale, scale);
				glRotatef(rotateY, 0, 1, 0);
				glTranslatef(pieces[j]->component[2]->slideX, pieces[j]->component[2]->slideY + 0.3, pieces[j]->component[2]->slideZ);
				glTranslatef(pieces[j]->slideX, 0, pieces[j]->slideZ);
				glColor3f(ColorArr2[color_black][0], ColorArr2[color_black][1], ColorArr2[color_black][2]);
				glutSolidSphere(chessRadius * 3 / 5, slices, slices);
				glPopMatrix();



			}

			
		}
		for (int j = 8; j < 16; j++) {
			
			if (pieces[j]->deleted == false) {
				for (auto it = pieces[j]->component.begin(); it != pieces[j]->component.end(); ++it) {
				
					draw(*it, pieces[j]->slideX, pieces[j]->slideZ);
				}
				glPushMatrix();
				glScalef(scale, scale, scale);
				glRotatef(rotateY, 0, 1, 0);
				glTranslatef(pieces[j]->component[2]->slideX, pieces[j]->component[2]->slideY + 0.3, pieces[j]->component[2]->slideZ);
				glTranslatef(pieces[j]->slideX, 0, pieces[j]->slideZ);

				glColor3f(ColorArr2[color_white][0], ColorArr2[color_white][1], ColorArr2[color_white][2]);
				glutSolidSphere(chessRadius * 3 / 5, slices, slices);
				glPopMatrix();


			}
		
		}

		
	}
	void draw(Mesh* object, float slideX, float slideZ) {
		glPushMatrix();
		glScalef(scale, scale, scale);
		glRotatef(rotateY, 0, 1, 0);
		glTranslated(object->slideX, object->slideY, object->slideZ);
		glTranslated(slideX, 0, slideZ);
		glRotatef(object->rotateY, 0, 1, 0);
		glRotatef(object->rotateZ, 0, 0, 1);
		glRotatef(object->rotateX, 1, 0, 0);
		if (bWireFrame)
			object->DrawWireframe();
		else
			object->DrawColor();
		glPopMatrix();
	}
	void draw(Mesh* object) {
		glPushMatrix();
		glScalef(scale, scale, scale);
		glRotatef(rotateY, 0, 1, 0);
		glTranslated(object->slideX, object->slideY, object->slideZ);
		glRotatef(object->rotateY, 0, 1, 0);
		glRotatef(object->rotateZ, 0, 0, 1);
		glRotatef(object->rotateX, 1, 0, 0);
		if (bWireFrame)
			object->DrawWireframe();
		else
			object->DrawColor();
		glPopMatrix();
	}
	void drawBoard() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				draw(floor[i][j]);
				
			}
		}
	}
	bool move(int x, int y, int i, int j, int size) {
		if (pos[x][y] != NULL){
			
			/*for (auto it = pos[x][y]->component.begin(); it != pos[x][y]->component.end();++it) {
				Mesh* m = *it;
				if (m ->slideZ <= floor[i][j]->slideZ) {
					m ->slideZ += moveStep;
				}
				if (m->slideZ >= floor[i][j]->slideZ) {
					m->slideZ -= moveStep;
				}
				if (m->slideX <= floor[i][j]->slideX) {
					m->slideX += moveStep;
				}
				if (m->slideX >= floor[i][j]->slideX) {
					m->slideX -= moveStep;
				}
			}*/
			if (pos[x][y]->slideZ <= floor[i][j]->slideZ) {
				pos[x][y]->slideZ += moveStep;
			}
			if (pos[x][y]->slideZ >= floor[i][j]->slideZ) {
				pos[x][y]->slideZ -= moveStep;
			}
			if (pos[x][y]->slideX <= floor[i][j]->slideX) {
				pos[x][y]->slideX += moveStep;
			}
			if (pos[x][y]->slideX >= floor[i][j]->slideX) {
				pos[x][y]->slideX -= moveStep;
			}
			if (abs(pos[x][y]->slideX - floor[i][j]->slideX) <= moveStep && abs(pos[x][y]->slideZ - floor[i][j]->slideZ) <= moveStep) {

				if (pos[i][j] != NULL) {
					pos[i][j]->deleted = true;
				}
				/*				for (auto it = pos[x][y]->component.begin(); it != pos[x][y]->component.end(); ++it) {
				Mesh* m = *it;
				m->slideX = floor[i][j]->slideX;
				m->slideZ = floor[i][j]->slideZ;
				}*/

				pos[i][j] = pos[x][y];
				pos[x][y] = NULL;
				return true;
			}
			//if (abs(pos[x][y]->component.front()->slideX - floor[i][j]->slideX) <= moveStep && abs(pos[x][y]->component.front()->slideZ - floor[i][j]->slideZ) <= moveStep) {

			//	if (pos[i][j] != NULL) {
			//		pos[i][j]->deleted = true;
			//	}
			//	/*				for (auto it = pos[x][y]->component.begin(); it != pos[x][y]->component.end(); ++it) {
			//	Mesh* m = *it;
			//	m->slideX = floor[i][j]->slideX;
			//	m->slideZ = floor[i][j]->slideZ;
			//	}*/

			//	pos[i][j] = pos[x][y];
			//	pos[x][y] = NULL;
			//	return true;
			//}
			
		}
		else {
			return true;
		}
		

	}
	void drawShape() {

		drawText();
		draw(frame);
		drawBoard();
		drawPawn();
		drawBishop();
		drawRook();
		drawKnight();
		drawKing();
		drawQueen();
	}
	void move(string command)
	{

	}
private:

};

Shape shape;
string i;
//ar i[100];

int charToNum(char c) {
	switch (c) {
	case 'a':
	case 'A':
		return 0;
	case 'b':
	case 'B':
		return 1;
	case 'c':
	case 'C':
		return 2;
	case 'd':
	case 'D':
		return 3;
	case 'e':
	case 'E':
		return 4;
	case 'f':
	case 'F':
		return 5;
	case 'g':
	case 'G':
		return 6;
	case 'h':
	case 'H':
		return 7;
	default: 
		return 0;
	}
}
void parseInput(string in) {
	if (in.length() >= 5) {
		for (int i = 0; i < in.length(); i = i + 6) {
			int src_y = charToNum(in[i]);
			int src_x = in[i + 1] - '0' - 1;
			int des_y = charToNum(in[i + 3]);
			int des_x = in[i + 4] - '0' - 1;
			int size = 3;
			movement m(7 - src_x, src_y, 7 - des_x, des_y, size);

			v.insert(v.begin(), m);


		}
	}
}
void myInit();
void myKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
	case '+':
		cam_distance += cam_step;
		break;
	case '-':
		cam_distance -= cam_step;
		break;

	case'l':
		if (lightControl == false) {
			lightControl = true;
		}
		else lightControl = false;
		break;
	case '1':
		shape.rotateY += baseRotateStep;
		if (shape.rotateY > 360) {
			shape.rotateY -= 360;
		}
		break;
	case '2':
		shape.rotateY -= baseRotateStep;
		if(shape.rotateY < 0)
			shape.rotateY +=360;
		break;
	case '3':
		shape.scale += 0.1;

		break;
	case '4':
		shape.scale -= 0.1;

		break;
	case 'a':
		if (animation == false)
			animation = true;
		else {
			animation = false;
		}
		break;
	case 'm':
		lightI += 0.1;
		break;
	case 'n':
		lightI -= 0.1;
		break;
	case 'u':
		if (ultra == false) {
			ultra = true;
		}
		else {
			ultra = false;
			myInit();
			shape.init();
		}
		break;

	case 'c':
		if (shape.color_black == 12) {
			shape.color_black = 11;
			shape.color_white = 10;
			shape.frame_color = 13;
		}
		else if (shape.color_black == 11) {
			shape.color_black = 0;
			shape.color_white = 3;
			shape.frame_color = 14;

		}
		else if (shape.color_black == 0) {
			shape.color_black = 2;
			shape.color_white = 0;
			shape.frame_color = 13;

		}
		else {
			shape.color_black = 12;
			shape.color_white = 13;
			shape.frame_color = 14;

		}
		//myInit();
		shape.init();
		break;
	case 'r':
		myInit();
		shape.init();
		break;
	case 'v':
		if (view == 1) {
			posX = 1; 
			posY = 9; 
			posZ = 1;
			view = 2;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			float	fHalfSize = 4;
			glScalef(0.8, 0.8, 0.8);
			glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);

			//glFrustum(-1.1, 1.1, -1.1, 1.1, 1.5, 2000.0);
			//glFrustum(-3.0, 3.0, -3.0, 3.0, 10, 2000);
		}
		else {
			posX = 8;
			posY = 4;
			posZ = 8;
			view = 1;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
			glFrustum(-1.1, 1.1, -1.1, 1.1, 1.5, 2000.0);
			//glFrustum(-3.0, 3.0, -3.0, 3.0, 10, 2000);

		}
		break;
	case 'w':
		bWireFrame=!bWireFrame;
		break;
	case'p':
		if (playing == false) {
			playing = true;
			cout << "Playing \"The Most Famous Game of All Time\" \nMorphy vs Duke Karl / Count Isouard, 1858 " << endl;
			parseInput(moves);
		}
		else playing = false;
		break;
	case 'i':
		//scanf(i)
		cout << "Please enter move :";
		getline(cin, i);
		parseInput(i);
		playing = true;
		break;
	case 's':
		angleG += 180;
		if (angleG > 360)
			angleG -= 360;
		break;
	}

    glutPostRedisplay();
}
void mySpecialFunc(int key, int x, int y)
{
	float step = 0.4;
	if (lightControl == true) 
		switch (key)
		{
		case GLUT_KEY_LEFT:
			
			lightX -= moveStep*3;
			break;
		case GLUT_KEY_RIGHT:
			lightX += moveStep * 3;


			break;
		case GLUT_KEY_UP:
			lightZ -= moveStep * 3;

			break;
		case GLUT_KEY_DOWN:
			lightZ += moveStep * 3;


			break;
		}
	
	else
		switch (key)
		{
		case GLUT_KEY_LEFT:
			angleG += baseRotateStep;
			if (angleG > 360) {
				angleG -= 360;
			}
			//movX -= step;
			//angleG += baseRotateStep;

			break;
		case GLUT_KEY_RIGHT:
			angleG -= baseRotateStep;
			if (angleG < 0) {
				angleG += 360;
			}
			//movX += step;

			break;
		case GLUT_KEY_UP:

			cam_height += step;
			//angleG += baseRotateStep;

			break;
		case GLUT_KEY_DOWN:

			cam_height -= step;
			//angleG += baseRotateStep;

			break;
		}
	glutPostRedisplay();
}

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);//r
		glVertex3f(0, 0, 0);//x
		glVertex3f(4, 0, 0);

		glColor3f(0, 1, 0);//g
		glVertex3f(0, 0, 0);//y
		glVertex3f(0, 4, 0);

		glColor3f(0, 0, 1);//b
		glVertex3f(0, 0, 0);//z
		glVertex3f(0, 0, 4);
	glEnd();
}

void processTimer(int i);
void idleFunction() {
	if (ultra == true) {
		myKeyboard('c', 0, 0);
	}
	if (animation == true) {
		posX = 4;
		posY = 2;
		posZ = 4;
		cam_distance += cam_step;
	
		angleG -= 0.8;
		if (angleG < 0)
			angleG += 360;
		if (cam_distance > 2.5 || cam_distance < 0.5)
			cam_step = -cam_step;

		glutPostRedisplay();

	}
	if (playing == true) {

		if (!v.empty()) {
			//glutSwapBuffers();
			if (shape.move(v.back().src_x, v.back().src_y, v.back().des_x, v.back().des_y, v.back().size) == true) {
				v.pop_back();
				//glutTimerFunc(1000, processTimer, 100);

			}
			glutPostRedisplay();
		}
		else playing = false;
	}
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam_distance * posX*sin(angleG*PI/180) , cam_height + posY, cam_distance * posZ * cos(angleG*PI / 180), 0, 1, 0, 0, 1, 0);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);


	float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float mat_ambient_color[] = { 0.8f, 0.8f, 0.2f, 1.0f };
	float mat_diffuse[] = { 0.1f, 0.5f, 0.8f, 1.0f };
	float mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float no_shininess = 0.0f;
	float low_shininess = 5.0f;
	float high_shininess = 100.0f;
	float mat_emission[] = { 0.3f, 0.2f, 0.2f, 0.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	// Create light components for GL_LIGHT0
	float ambientLight0[] = { 0.2f*lightI, 0.2f*lightI, 0.2f*lightI, 1.0f };
	float diffuseLight0[] = { (230.0/255.0)*lightI, (184.0 / 255.0)*lightI, (19.0 / 255.0)*lightI, 1.0f };
	float specularLight0[] = { 0.6f*lightI, 0.6f*lightI, 0.6*lightI, 1.0f };
	float position0[] = { lightX, lightY, lightZ, 1.0f };
	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	//// GL_LIGHT1: the red light emitting light source
	//// Create light components for GL_LIGHT1
	//float ambientLight1[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	//float diffuseLight1[] = { 0.2f, 8.0f, 0.2f, 1.0f };
	//float specularLight1[] = { 0.2f,0.2f, 0.2f, 1.0f };
	//float position1[] = { 3.0f, 3.0f, 3.0f, 1.0f };
	//// Assign created components to GL_LIGHT1
	//glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
	//glLightfv(GL_LIGHT1, GL_POSITION, position1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth, screenHeight);
	//drawAxis();
	shape.drawShape();
	glutSwapBuffers();

	//glFlush();

}

void processTimer(int a) {
	glutPostRedisplay();
	glutTimerFunc(100, processTimer, 100);
}

void myInit()
{
	lightControl = false;
	ultra = false;
	playing = false;
	angleG = 0;
	animation = false;
	float	fHalfSize = 4;
	lightX = lightZ = 0.0f;
	lightY = 2.0f;
	lightI = 1.0f;
	posX = 8;
	posY = 4;
	posZ = 8;
	movX = 0;
	movY = 0;
	movZ = 0;
	cam_distance = 1;
	cam_height = 0;
	v.clear();
	glClearColor(0.7, 0.7, 0.7, 1.8f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
	glFrustum(-1.1, 1.1, -1.1, 1.1, 1.5, 2000.0);
	// glFrustum(-3.0, 3.0, -3.0, 3.0, 10, 2000);

}
void reshape(int w, int h)   // Create The Reshape Function (the viewport)
{
	glViewport(0, 0, w, h);
}
int main(int argc, char* argv[])
{
	
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("3D Chess Visualizer - Kha "); // open the screen window

	cout << "-+-+-+-+-+-+-+-+-3D Chess Visualizer-+-+-+-+-+-+-+-+-"<< endl;

	cout << "--Press r to reset" << endl;

	cout << "+Model control"<<endl;
	cout << "--Press 1/2 to rotate " << endl;
	cout << "--Press 3/4 to zoom in/ zoom out " << endl;
	cout << "--Press c to change color" << endl;
	cout << "--Press u for a suprise" << endl;
	cout << "--Press w to turn on wireframe" << endl;

	cout << "+Lighting control" << endl;
	cout << "--Press l to control light" << endl;
	cout << "--Press m/n to increase/decrease lighting" << endl;

	cout << "+Camera control" << endl;
	cout << "--Press s to switch side" << endl;
	cout << "--Press v to change view" << endl;
	cout << "--Press left/right to move camera around" << endl;
	cout << "--Press up/down to increase/decrease camera height" << endl;
	cout << "--Press +/- to increase/decrease camera distance" << endl;

	cout << "+Animation" << endl;
	cout << "--Press i to insert move(s). Format: [source] [destination] .... Ex: a2 a5 d7 d5" << endl;
	cout << "--Press a to turn on animation" << endl;
	cout << "--Press p to play demo game" << endl;

	cout << "-+-+-+-+-+-+-+-+--+-+-+-+-Kha-+-+--+-+-+-+-+-+-+-+-+-" << endl;

	myInit();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialFunc);
    glutDisplayFunc(myDisplay);
	glutIdleFunc(idleFunction);
	glutTimerFunc(100, processTimer, 100);


		
	glutMainLoop();

	return 0;
}

