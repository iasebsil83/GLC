// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//maths
#include <math.h>

//own header
#include "glc_objects2D.h"








// ---------------- 2D UTILITIES ----------------

//forms
void GLC_2DPoint(unit x, unit y, color* c){
	if(c){
		glColor4f(c->r, c->g, c->b, c->a);
	}

	//point
	glBegin(GL_POINTS);
		glVertex2f(x,y);
	glEnd();
}

void GLC_2DLine(unit x1, unit y1, unit x2, unit y2, color* c){
	if(c){
		glColor4f(c->r, c->g, c->b, c->a);
	}

	//line
	glBegin(GL_LINES);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();
}

void GLC_2DTriangle(
	unit x1, unit y1,
	unit x2, unit y2,
	unit x3, unit y3,
	color* c, char filled
){
	if(c){
		glColor4f(c->r, c->g, c->b, c->a);
	}

	//full triangle
	if(filled){
		glBegin(GL_TRIANGLES);
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
	}

	//empty triangle
	else{
		GLC_2DLine(x1,y1, x2,y2, NULL);
		GLC_2DLine(x2,y2, x3,y3, NULL);
		GLC_2DLine(x3,y3, x1,y1, NULL);
	}
}

void GLC_2DRectangle(
	unit x1, unit y1,
	unit x2, unit y2,
	color* c, char filled
){
	if(c){
		glColor4f(c->r, c->g, c->b, c->a);
	}

	//full rectangle
	if(filled){
		glBegin(GL_QUADS);
			glVertex2f(x1,y1);
			glVertex2f(x2,y1);
			glVertex2f(x2,y2);
			glVertex2f(x1,y2);
		glEnd();

		//GPU weakness : remove diagonals
		unit thickness;
		glGetFloatv(GL_LINE_WIDTH, &thickness);
		glLineWidth(1.f);
		GLC_2DLine(x1,y1, x2,y2, NULL);
		glLineWidth(thickness);
	}

	//empty rectangle
	else{
		GLC_2DLine(x1,y1, x2,y1, NULL);
		GLC_2DLine(x2,y1, x2,y2, NULL);
		GLC_2DLine(x2,y2, x1,y2, NULL);
		GLC_2DLine(x1,y2, x1,y1, NULL);
	}
}

void GLC__2DQuad(
	unit x1, unit y1,
	unit x2, unit y2,
	unit x3, unit y3,
	unit x4, unit y4,
	color* c, char filled
){
	if(c){
		glColor4f(c->r, c->g, c->b, c->a);
	}

	//full quad
	if(filled){
		glBegin(GL_QUADS);
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
			glVertex2f(x4,y4);
		glEnd();

		//GPU weakness : remove diagonals
		unit thickness;
		glGetFloatv(GL_LINE_WIDTH, &thickness);
		glLineWidth(1.f);
		GLC_2DLine(x1,y1, x3,y3, NULL);
		glLineWidth(thickness);
	}

	//empty quad
	else{
		GLC_2DLine(x1,y1, x2,y2, NULL);
		GLC_2DLine(x2,y2, x3,y3, NULL);
		GLC_2DLine(x3,y3, x4,y4, NULL);
		GLC_2DLine(x4,y4, x1,y1, NULL);
	}
}

void GLC_2DCircle(
	unit x,      unit y,
	unit radius, unsigned int divisions,
	color* c, char filled
){
	if(c){
		glColor4f(c->r, c->g, c->b, c->a);
	}

	//disk
	if(filled){
		unit step  = M_2PI/divisions;
		unit angle = 0.0;
		for(unsigned int n=0; n < divisions; n++){
			angle += step;
			GLC_2DTriangle(
				x                         , y,
				x + radius*cos(angle     ), y + radius*sin(angle     ),
				x + radius*cos(angle+step), y + radius*sin(angle+step),
				NULL, GLC_FILLED
			);
		}
	}

	//empty circle
	else{
		unit step  = M_2PI/divisions;
		unit angle = 0.0;
		for(unsigned int n=0; n < divisions; n++){
			angle += step;
			GLC_2DLine(
				x + radius*cos(angle     ), y + radius*sin(angle     ),
				x + radius*cos(angle+step), y + radius*sin(angle+step),
				NULL
			);
		}
	}
}
