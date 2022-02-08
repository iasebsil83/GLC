// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//maths
#include <math.h>

//glc
#include "glc.h"
#include <GLES3/gl3.h>

//own header
#include "glc_objects3D.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))








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
		/*glBegin(GL_QUADS);
			glVertex3f(px,    py,    pz); //A
			glVertex3f(px+lx, py,    pz); //B
			glVertex3f(px+lx, py+ly, pz); //D
			glVertex3f(px,    py+ly, pz); //C
		glEnd();*/
		
		
		
		// unit square      
		// A face has 1 side and has 4 vertices, therefore, the total number
		// of vertices is 4 (1 sides * 4 verts), and 12 floats in the vertex array
		// since each vertex has 3 components (x,y,z) (= 4 * 3)  
		//  v1------v0   
		//  |        |    
		//  |        |  
		//  |        |    
		//  v2------v3    
		
		//1) Create vertex position array
		GLfloat vertices[] = {
			 .5f, .5f, .5f,  -.5f, .5f, .5f,  -.5f,-.5f, .5f,  .5f,-.5f, .5f // v0,v1,v2,v3 (front)
		};

		// normal array
		GLfloat normals[] = {
			 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1  // v0,v1,v2,v3 (front)
		};

		// colour array
		GLfloat colors[] = {
			 1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1  // v0,v1,v2,v3 (front)
		};

		// texture coord array
		GLfloat texCoords[] = {
			1, 0,   0, 0,   0, 1,   1, 1               // v0,v1,v2,v3 (front)
		};

		// index array for glDrawElements()
		// A square requires 6 indices = 1 sides * 2 tris * 3 verts
		GLuint indices[] = {
			 0, 1, 2,   2, 3, 0    // v0-v1-v2, v2-v3-v0 (front)
		};

		
		
		// create VBOs
		GLuint vboId;
		GLuint iboId;
		glGenBuffers(1, &vboId);    // for vertex buffer
		glGenBuffers(1, &iboId);    // for index buffer

		size_t vSize = sizeof vertices;
		size_t nSize = sizeof normals;
		size_t cSize = sizeof colors;
		size_t tSize = sizeof texCoords;

		// copy vertex attribs data to VBO
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, vSize+nSize+cSize+tSize, 0, GL_STATIC_DRAW); // reserve space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, vertices);                  // copy verts at offset 0
		glBufferSubData(GL_ARRAY_BUFFER, vSize, nSize, normals);               // copy norms after verts
		glBufferSubData(GL_ARRAY_BUFFER, vSize+nSize, cSize, colors);          // copy cols after norms
		glBufferSubData(GL_ARRAY_BUFFER, vSize+nSize+cSize, tSize, texCoords); // copy texs after cols
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// copy index data to VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		
		
		
		
		// bind VBOs before drawing
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);

		// enable vertex arrays
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		size_t nOffset = sizeof vertices;
		size_t cOffset = nOffset + sizeof normals;
		size_t tOffset = cOffset + sizeof colors;

		// specify vertex arrays with their offsets
		glVertexPointer(3, GL_FLOAT, 0, (void*)0);
		glNormalPointer(GL_FLOAT, 0, (void*)nOffset);
		glColorPointer(3, GL_FLOAT, 0, (void*)cOffset);
		glTexCoordPointer(2, GL_FLOAT, 0, (void*)tOffset);

		// finally draw a cube with glDrawElements()
		glDrawElements(GL_TRIANGLES,            // primitive type
				       6,                       // # of indices
				       GL_UNSIGNED_INT,         // data type
				       (void*)0);               // offset to indices

		// disable vertex arrays
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		// unbind VBOs
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//end drawing
	glPopMatrix();
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
