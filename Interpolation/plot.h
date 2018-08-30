#include<vector>
#include<string>

using namespace std;

struct MyRGB{
	float R;
	float G;
	float B;
	MyRGB(float R_, float G_, float B_)
	{
		R=R_;
		G=G_;
		B=B_;
	}	
};

struct Ponto2{
	float x;
	float y;
	Ponto2(float x_, float y_)
	{
		x=  x_;
		y=y_;	
	}
};


typedef float (*TipoFunction)(float);
typedef vector<Ponto2> Pontos;


void myplot(TipoFunction f, float xmin_, float xmax_,MyRGB cor);
void desenha_Eixos(float xmin_, float xmax_, float ymin_, float ymax_, MyRGB cor);
void linha(float x1, float y1, float x2, float y2);
float myfunc(TipoFunction f,float x);
void plotPoints(Pontos P, MyRGB cor);
void myplotaxis(float xmin_, float xmax_,float ymin_, float ymax_, MyRGB cor);
void myText(std:: string mytext, float x,float y);
