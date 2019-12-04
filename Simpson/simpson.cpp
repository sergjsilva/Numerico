#include<iostream>
#include<cmath>


using namespace std;

typedef double (*Funcao)(double);

double fx(double x)
{
    return exp(x);   
}

double Simpson(Funcao f, double a, double b, unsigned n)
{
    double h=(b-a)/n;
    double yo=f(a);
    double yn=f(b);
    double xo=a;
    double x,soma;
    soma=yo+yn;

    for(int j=1;j<n;j++)
    {

        if(!(j&1)) // eh par
        {
            x=xo+j*h;
            soma=soma+2*f(x);
        }
        else // ímpar
        {
            x=xo+j*h;
            soma=soma+4*f(x);
        }
    }
    soma=h/3*soma;
    return soma;
}


int main()
{
    double result=Simpson(fx,0,1,10);
    cout.precision(10);
    cout<<result<<endl;
    return 0;
}
