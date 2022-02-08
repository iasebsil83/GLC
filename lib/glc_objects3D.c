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






// ---------------- DECLARATIONS ----------------

//glc shared variables
extern GLC_vars GLC;

#define NB_VERTEX_PER_TRIANGLE 3
#define NB_COORD_PER_VERTEX 3








// ---------------- 3D OBJECTS ----------------


void GLC_3Dshape(
	int nbTriangle,
	unit *vertices,     // vertices tab
	void* tex, char texType // texture
){
	//texture is color & color not null
    GLfloat *colors = (GLfloat*)malloc(sizeof(GLfloat)*nbTriangle*NB_VERTEX_PER_TRIANGLE*NB_COORD_PER_VERTEX);
	if(colors == NULL){
		printf("ERROR -> Malloc colors\n");
		return;
	}

	color* c = (color*)tex;
	for(int i=0; i<nbTriangle*NB_VERTEX_PER_TRIANGLE*NB_COORD_PER_VERTEX; i+=NB_COORD_PER_VERTEX){
		if(!texType && tex){
			colors[i]   = i%2 == 0 ? 0.f : 1.f;
			colors[i+1] = c->g/255;
			colors[i+2] = c->b/255;
		}
		else{
			colors[i]   = 1.f;
			colors[i+1] = 0.f;
			colors[i+2] = 1.f;
		}
	}

	//create normal array for each face (light usage)
	GLfloat *normals = (GLfloat*)malloc(sizeof(GLfloat)*nbTriangle*NB_VERTEX_PER_TRIANGLE*NB_COORD_PER_VERTEX);
	if(normals == NULL){
		printf("ERROR -> Malloc normals\n");
		return;
	}

	for(int i=0; i<nbTriangle; i++){
		
		xyz diff12 = {
			vertices[i*9+3] - vertices[i*9+0], //x2-x1
			vertices[i*9+4] - vertices[i*9+1], //y2-y1
			vertices[i*9+5] - vertices[i*9+2]  //z2-z1
		};
		
		xyz diff13 = {
			vertices[i*9+6] - vertices[i*9+0], //x3-x1
			vertices[i*9+7] - vertices[i*9+1], //y3-y1
			vertices[i*9+8] - vertices[i*9+2]  //z3-z1
		};
		
		normals[i*9]   = diff12.y * diff13.z - diff13.y * diff12.z;
		normals[i*9+1] = diff12.z * diff13.x - diff13.z * diff12.x;
		normals[i*9+2] = diff12.x * diff13.y - diff13.x * diff12.y;
		normals[i*9+3] = normals[i*9];
		normals[i*9+4] = normals[i*9+1];
		normals[i*9+5] = normals[i*9+2];
		normals[i*9+6] = normals[i*9];
		normals[i*9+7] = normals[i*9+1];
		normals[i*9+8] = normals[i*9+2];
		//printf("got : %f / %f / %f\n", normals[i*9], normals[i*9+1], normals[i*9+2]);
	 }

	//texture coord array
	/*GLfloat texCoords[] = {
		1, 0,   0, 0,   0, 1,   1, 1               // v0,v1,v2,v3 (front)
	};*/

	//create index array for glDrawElements for index-vertices linking
	GLuint *indices = (GLuint*)malloc(sizeof(GLuint)*nbTriangle*NB_VERTEX_PER_TRIANGLE);
	if(indices == NULL){
		printf("ERROR -> Malloc indices\n");
		return;
	}

	for(int i=0; i<nbTriangle*NB_VERTEX_PER_TRIANGLE; i++){
		indices[i] = i;
	}

	//create buffers for vertex and index
	GLuint vboId;
	GLuint iboId;
	glGenBuffers(1, &vboId); // vertex buffer
	glGenBuffers(1, &iboId); // index buffer

	//copy vertex attribs data to buffers
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	
	size_t vSize = sizeof(GLfloat)*nbTriangle*NB_VERTEX_PER_TRIANGLE*NB_COORD_PER_VERTEX;
	size_t nSize = sizeof(GLuint)*nbTriangle*NB_VERTEX_PER_TRIANGLE*NB_COORD_PER_VERTEX;
	size_t iSize = sizeof(GLuint)*nbTriangle*NB_VERTEX_PER_TRIANGLE;
	size_t cSize = sizeof(GLfloat)*nbTriangle*NB_VERTEX_PER_TRIANGLE*NB_COORD_PER_VERTEX;
	//size_t tSize = sizeof texCoords;
	
	glBufferData(GL_ARRAY_BUFFER, vSize+nSize+cSize/*+tSize*/, 0, GL_STATIC_DRAW); // reserve space (t_size for texture)
	glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, vertices);                          // copy verts at offset 0
	glBufferSubData(GL_ARRAY_BUFFER, vSize, nSize, normals);               		   // copy norms after verts
	glBufferSubData(GL_ARRAY_BUFFER, vSize+nSize, cSize, colors);                  // copy cols after norms
	//glBufferSubData(GL_ARRAY_BUFFER, vSize+nSize+cSize, tSize, texCoords);       // copy texs after cols
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//copy index data to buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	//bind VBOs before drawing
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);

	//enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	size_t nOffset = vSize;
	size_t cOffset = nOffset + nSize;
	size_t tOffset = cOffset + sizeof colors;

	//specify vertex arrays with their offsets
	glVertexPointer(NB_VERTEX_PER_TRIANGLE, GL_FLOAT, 0, (void*)0);
	glNormalPointer(GL_FLOAT, 0, (void*)nOffset);
	glColorPointer(NB_VERTEX_PER_TRIANGLE, GL_FLOAT, 0, (void*)cOffset);
	//glTexCoordPointer(2, GL_FLOAT, 0, (void*)tOffset);

	//draw plake with glDrawElements
	glDrawElements(GL_TRIANGLES,            		  // primitive type
			       NB_VERTEX_PER_TRIANGLE*nbTriangle, // # of indices
			       GL_UNSIGNED_INT,         		  // data type
			       (void*)0);               		  // offset to indices

	//disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//unbind VBOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	free(colors);
	free(normals);
	free(indices);
}

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

	//shape coordinates
	unit *vertices = malloc(sizeof(unit)*2*NB_VERTEX_PER_TRIANGLE*NB_COORD_PER_VERTEX);
	if(vertices == NULL){
		printf("ERROR -> Malloc vertices is NULL\n");
		return;
	}
	
	vertices[0] = px;
	vertices[1] = py;
	vertices[2] = pz;
	vertices[3] = px+lx;
	vertices[4] = py;
	vertices[5] = pz;
	vertices[6] = px;
	vertices[7] = py+ly;
	vertices[8] = pz;
	
	vertices[9] = px+lx;
	vertices[10] = py;
	vertices[11] = pz;
	vertices[12] = px;
	vertices[13] = py+ly;
	vertices[14] = pz;
	vertices[15] = px+lx;
	vertices[16] = py+ly;
	vertices[17] = pz;
	
	//shape creation
	GLC_3Dshape(
		2,
		vertices,
		tex, texType
	);
	
	free(vertices);
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
	
	//shape coordinates
	unit *vertices = malloc(sizeof(unit)*12*NB_VERTEX_PER_TRIANGLE*NB_COORD_PER_VERTEX);
	if(vertices == NULL){
		printf("ERROR -> Malloc vertices is NULL\n");
		return;
	}
	
	vertices[0] = px;
	vertices[1] = py;
	vertices[2] = pz;
	vertices[3] = px+lx;
	vertices[4] = py+ly;
	vertices[5] = pz;
	vertices[6] = px;
	vertices[7] = py+ly;
	vertices[8] = pz;
	
	vertices[9] = px+lx;
	vertices[10] = py;
	vertices[11] = pz;
	vertices[12] = px;
	vertices[13] = py;
	vertices[14] = pz;
	vertices[15] = px+lx;
	vertices[16] = py+ly;
	vertices[17] = pz;
	
	vertices[18] = px;
	vertices[19] = py;
	vertices[20] = pz+lz;
	vertices[21] = px+lx;
	vertices[22] = py+ly;
	vertices[23] = pz+lz;
	vertices[24] = px;
	vertices[25] = py+ly;
	vertices[26] = pz+lz;
	
	vertices[27] = px+lx;
	vertices[28] = py;
	vertices[29] = pz+lz;
	vertices[30] = px;
	vertices[31] = py;
	vertices[32] = pz+lz;
	vertices[33] = px+lx;
	vertices[34] = py+ly;
	vertices[35] = pz+lz;
	
	vertices[36] = px;
	vertices[37] = py;
	vertices[38] = pz+lz;
	vertices[39] = px+lx;
	vertices[40] = py;
	vertices[41] = pz+lz;
	vertices[42] = px;
	vertices[43] = py;
	vertices[44] = pz;
	
	vertices[45] = px+lx;
	vertices[46] = py;
	vertices[47] = pz;
	vertices[48] = px+lx;
	vertices[49] = py;
	vertices[50] = pz+lz;
	vertices[51] = px;
	vertices[52] = py;
	vertices[53] = pz;

	vertices[54] = px;
	vertices[55] = py+ly;
	vertices[56] = pz+lz;
	vertices[57] = px+lx;
	vertices[58] = py+ly;
	vertices[59] = pz+lz;
	vertices[60] = px;
	vertices[61] = py+ly;
	vertices[62] = pz;
	
	vertices[63] = px+lx;
	vertices[64] = py+ly;
	vertices[65] = pz;
	vertices[66] = px+lx;
	vertices[67] = py+ly;
	vertices[68] = pz+lz;
	vertices[69] = px;
	vertices[70] = py+ly;
	vertices[71] = pz;
	
	vertices[72] = px;
	vertices[73] = py;
	vertices[74] = pz+lz;
	vertices[75] = px;
	vertices[76] = py;
	vertices[77] = pz;
	vertices[78] = px;
	vertices[79] = py+ly;
	vertices[80] = pz+lz;

	vertices[81] = px;
	vertices[82] = py+ly;
	vertices[83] = pz;
	vertices[84] = px;
	vertices[85] = py;
	vertices[86] = pz;
	vertices[87] = px;
	vertices[88] = py+ly;
	vertices[89] = pz+lz;
	
	vertices[90] = px+lx;
	vertices[91] = py;
	vertices[92] = pz+lz;
	vertices[93] = px+lx;
	vertices[94] = py;
	vertices[95] = pz;
	vertices[96] = px+lx;
	vertices[97] = py+ly;
	vertices[98] = pz+lz;
	
	vertices[99] = px+lx;
	vertices[100] = py+ly;
	vertices[101] = pz;
	vertices[102] = px+lx;
	vertices[103] = py;
	vertices[104] = pz;
	vertices[105] = px+lx;
	vertices[106] = py+ly;
	vertices[107] = pz+lz;
	
	//shape creation
	GLC_3Dshape(
		12,
		vertices,
		tex, texType
	);
	
	free(vertices);
}

/*
void GLC_3DSphere(
	unit radius, unsigned int divisions, //division = precision of the sphere
	unit px, unit py, unit pz,           //position
	unit sx, unit sy, unit sz,           //scale
	color* c
){*/

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
	
	/*//position - scale (no rotation because it is a sphere)
	glTranslatef(px, py, pz);
	glScalef(sx, sy, sz);

	//ray
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  *((GLC.currentRay)->a) );
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  *((GLC.currentRay)->d) );
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, *((GLC.currentRay)->s) );

	//shape coordinates
	unit **vertices = malloc(sizeof(unit*)*divisions*divisions);
	if(vertices == NULL){
		printf("ERROR -> Malloc vertices is NULL\n");
		return;
	}
	
	unit step = M_2PI/divisions;
	for(int x=0; x<2*M_PI; step++){
		for(int y=0; y<2*M_PI; step++){
			*vertices[x*step+y] = malloc(sizeof(unit)*NB_VERTEX_PER_TRIANGLE*NB_COORD_PER_VERTEX);
			vertices[x*step+y][0] = 
		}
	}
	
	
	unit step  = M_2PI/divisions;
    unit angle = 0.0;
	for(unsigned int n=0; n < divisions; n++){
		angle += step;

		//sphere fragment
		{
			//TRIANGLE BAS
			px + radius*cos(angle     ), py + radius*sin(angle     ), //A
			px + radius*cos(angle+step), py + radius*sin(angle+step), //D
			px + radius*cos(angle     ), py + radius*sin(angle     )  //C
		}
	}
	
	//shape creation
	GLC_3Dshape(
		12,
		vertices,
		tex, texType
	);


	//sphere
	
}*/
