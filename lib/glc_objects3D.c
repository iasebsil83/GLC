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

//rays
extern ray  GLC_defaultRay;
static ray* GLC_currentRay = &GLC_defaultRay;








// ---------------- 3D OBJECTS ----------------

//shapes
void GLC_3DHexaedron(
	unit px, unit py, unit pz,
	unit rx, unit ry, unit rz,
	unit lx, unit ly, unit lz,
	color* c
){
	if(c){
		glColor4f(c->r, c->g, c->b, c->a);
	}

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

	//start drawing
	glDisable(GL_LIGHTING);
	glPushMatrix();

		//ray
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  *(GLC_currentRay->a) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  *(GLC_currentRay->d) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, *(GLC_currentRay->s) );

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

		//position & rotation
		glTranslatef(px,py,pz);
		glRotatef(rx, 1.0, 0.0, 0.0);
		glRotatef(ry, 0.0, 1.0, 0.0);
		glRotatef(rz, 0.0, 0.0, 1.0);

	//end drawing
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void GLC_3DSphere(
	unit px, unit py, unit pz,
	unit radius, unsigned int divisions,
	color* c
){
	if(c){
		glColor4f(c->r, c->g, c->b, c->a);
	}

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

	//start drawing
	glDisable(GL_LIGHTING);
	glPushMatrix();

		//ray
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  *(GLC_currentRay->a) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  *(GLC_currentRay->d) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, *(GLC_currentRay->s) );

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

		//position (no rotation because it is a sphere)
		glTranslatef(px,py,pz);

	//end drawing
	glPopMatrix();
	glEnable(GL_LIGHTING);
}
