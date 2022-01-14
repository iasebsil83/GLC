// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//maths
#include <math.h>

//glc
#include "glc.h"

//own header
#include "glc_objects3D.h"








// ---------------- DECLARATIONS ----------------

//glc shared variables
extern GLC_vars GLC;








// ---------------- 3D OBJECTS ----------------

//shapes
void GLC_3DPlane(
	unit lx, unit ly,          //length (width, height)
	unit px, unit py, unit pz, //position
	unit rx, unit ry, unit rz, //rotation
	unit sx, unit sy, unit sz, //scale
	void* tex, char texType    //texture
){

/* ------------------------------------------------
                   Coordinates plan
                   ----------------

          A--------B    --> ^
          |        |     z   \
          |        |          \        -->
          C--------D           X------> x
                               |
        A(0, 0, 0)             |
        B(w, 0, 0)             | -->
        C(0, h, 0)             v  y
        D(w, h, 0)
------------------------------------------------ */

	//texture is a color
	if(!texType && tex){
		color* c = (color*)tex;
		glColor4f(c->r, c->g, c->b, c->a);
	}

	//start drawing
	glDisable(GL_LIGHTING);
	glPushMatrix();

		//position - rotation - scale
		glTranslatef(px, py, pz);
		glRotatef(rx, 1.0, 0.0, 0.0);
		glRotatef(ry, 0.0, 1.0, 0.0);
		glRotatef(rz, 0.0, 0.0, 1.0);
		glScalef(sx, sy, sz);

		//ray
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  *((GLC.currentRay)->a) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  *((GLC.currentRay)->d) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, *((GLC.currentRay)->s) );

		//shape

		//plane
		glBegin(GL_QUADS);
			glVertex3f(px,    py,    pz); //A
			glVertex3f(px+lx, py,    pz); //B
			glVertex3f(px+lx, py+ly, pz); //D
			glVertex3f(px,    py+ly, pz); //C
		glEnd();

	//end drawing
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void GLC_3DHexaedron(
	unit lx, unit ly, unit lz, //length (width, height, depth)
	unit px, unit py, unit pz, //position
	unit rx, unit ry, unit rz, //rotation
	unit sx, unit sy, unit sz, //scale
	void* tex, char texType    //texture
){

/* ------------------------------------------------
                   Coordinates plan
                   ----------------
              w
         <-------->
      ^   E--------F   ^
    h |   |\       |\   \
      |   | \      | \   \
      v   G--\-----H  \   \ d
           \  \     \  \   \
            \  \     \  \   \      -->
             \  \     \  \   \      z
              \  A--------B   v     ^
               \ |      \ |          \
                \|       \|           \        -->
                 C--------D            X------> x
                                       |
        A(0, 0, 0)                     |
        B(w, 0, 0)                     | -->
        C(0, h, 0)                     v  y
        D(w, h, 0)
        E(0, 0, d)
        F(w, 0, d)
        G(0, h, d)
        H(w, h, d)
------------------------------------------------ */

	//texture is a color
	if(!texType && tex){
		color* c = (color*)tex;
		glColor4f(c->r, c->g, c->b, c->a);
	}

	//start drawing
	glDisable(GL_LIGHTING);
	glPushMatrix();

		//position - rotation - scale
		glTranslatef(px, py, pz);
		glRotatef(rx, 1.0, 0.0, 0.0);
		glRotatef(ry, 0.0, 1.0, 0.0);
		glRotatef(rz, 0.0, 0.0, 1.0);
		glScalef(sx, sy, sz);

		//ray
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  *((GLC.currentRay)->a) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  *((GLC.currentRay)->d) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, *((GLC.currentRay)->s) );

		//shape

		//front face
		glBegin(GL_QUADS);
			glVertex3f(px,    py,    pz   ); //A
			glVertex3f(px+lx, py,    pz   ); //B
			glVertex3f(px+lx, py+ly, pz   ); //D
			glVertex3f(px,    py+ly, pz   ); //C
		glEnd();

		//back face
		glBegin(GL_QUADS);
			glVertex3f(px,    py,    pz+lz); //E
			glVertex3f(px+lx, py,    pz+lz); //F
			glVertex3f(px+lx, py+ly, pz+lz); //H
			glVertex3f(px,    py+ly, pz+lz); //G
		glEnd();

		//up face
		glBegin(GL_QUADS);
			glVertex3f(px,    py,    pz+lz); //E
			glVertex3f(px+lx, py,    pz+lz); //F
			glVertex3f(px+lx, py,    pz   ); //B
			glVertex3f(px,    py,    pz   ); //A
		glEnd();

		//down face
		glBegin(GL_QUADS);
			glVertex3f(px,    py+ly, pz+lz); //G
			glVertex3f(px+lx, py+ly, pz+lz); //H
			glVertex3f(px+lx, py+ly, pz   ); //D
			glVertex3f(px,    py+ly, pz   ); //C
		glEnd();

		//left face
		glBegin(GL_QUADS);
			glVertex3f(px,    py,    pz+lz); //E
			glVertex3f(px,    py,    pz   ); //A
			glVertex3f(px,    py+ly, pz   ); //C
			glVertex3f(px,    py+ly, pz+lz); //G
		glEnd();

		//right face
		glBegin(GL_QUADS);
			glVertex3f(px+lx, py,    pz+lz); //F
			glVertex3f(px+lx, py,    pz   ); //B
			glVertex3f(px+lx, py+ly, pz   ); //D
			glVertex3f(px+lx, py+ly, pz+lz); //H
		glEnd();

	//end drawing
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void GLC_3DSphere(
	unit radius, unsigned int divisions, //division = precision of the sphere
	unit px, unit py, unit pz,           //position
	unit sx, unit sy, unit sz,           //scale
	color* c
){

/* ------------------------------------------------
                   Coordinates plan
                   ----------------
               B
                _X-°°°°°--_         -->
              /   \         \        z
             '     \ R       '       ^
            '   a ( \         '       \
            '--------X A      '        \        -->
            '                 '         X------> x
             '               '          |
              ' _         _ '           |
                 --.....--              v

           A(       0,             0,              0)
           B( Rcos(a), Rsin(a)cos(b), Rsin(a)sin(b) )

------------------------------------------------ */

	//color
	if(c){
		glColor4f(c->r, c->g, c->b, c->a);
	}

	//start drawing
	glDisable(GL_LIGHTING);
	glPushMatrix();

		//position - scale (no rotation because it is a sphere)
		glTranslatef(px, py, pz);
		glScalef(sx, sy, sz);

		//ray
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  *((GLC.currentRay)->a) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  *((GLC.currentRay)->d) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, *((GLC.currentRay)->s) );

		//shape

		//sphere
		unit step  = M_2PI/divisions;
        unit angle = 0.0;
		for(unsigned int n=0; n < divisions; n++){
			angle += step;

			//sphere fragment
			glBegin(GL_QUADS);
				glVertex3f(px + radius*cos(angle     ), py + radius*sin(angle     ), 0);
				glVertex3f(px + radius*cos(angle+step), py + radius*sin(angle+step), 0);
				glVertex3f(px + radius*cos(angle     ), py + radius*sin(angle     ), 0);
				glVertex3f(px + radius*cos(angle+step), py + radius*sin(angle+step), 0);
			glEnd();
		}

	//end drawing
	glPopMatrix();
	glEnable(GL_LIGHTING);
}
