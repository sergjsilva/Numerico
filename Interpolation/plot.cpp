#include<glut.h>
#include<string>

#include"plot.h"

void linha(float x1, float y1, float x2, float y2,MyRGB cor)
{
	glColor3f(cor.R,cor.G,cor.B);
	glLineWidth(3.0);
	glBegin(GL_LINES);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();	
}

void desenha_Eixos(float xmin_,float xmax_, float ymin_, float ymax_, MyRGB cor)
{
	linha(xmin_,0,xmax_,0, cor);
	linha(0,ymin_,0,ymax_, cor);	
}


float myfunc(TipoFunction f,float x)
{
	return f(x);
}

void myplotaxis(float xmin_, float xmax_,float ymin_, float ymax_, MyRGB cor)
{
	glColor3f(cor.R,cor.G,cor.B);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin_,ymin_);
		glVertex2f(xmax_,ymin_);
		glVertex2f(xmax_,ymax_);
		glVertex2f(xmin_,ymax_);
	glEnd();	
}
f=fx;

void myplot(TipoFunction f, float xmin_, float xmax_,MyRGB cor)
{
	int nPts=200;
	int nSubIntervalos=nPts-1;
	float x=xmin_;
	float y=f(x);
	
	float incr=(xmax_-xmin_)/nSubIntervalos;
	
	glColor3f(cor.R,cor.G,cor.B);
	glBegin(GL_LINE_STRIP);		
	for(int i=1; i<=nPts; i++)
		{
			glVertex2f(x,y);
			x+=incr;
			y=f(x);			
		}				
	glEnd();
}

void plotPoints(Pontos P, MyRGB cor)
{
	glColor3f(cor.R,cor.G,cor.B);
	glPointSize(4.0);
	glBegin(GL_POINTS);		
	for(int i=0; i<P.size(); i++)
		{
			glVertex2f(P[i].x,P[i].y);						
		}				
	glEnd();	
}


void myText(std:: string mytext, float x,float y)
{
	
	int n=mytext.length();
	
	char text[n+1];
	strcpy(text,mytext.c_str());
	
	glColor3f(0, 0, 0);	
	// Position of the text to be printer
	glRasterPos2f(x,y);
	for(int i = 0; text[i] != '\0'; i++)
    	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	
}
