#include<iostream>

typedef double(*Funcao)(double);
double myfx(double x)
{
    return x*x*exp(x);
}

double simpson(double a, double b,Funcao f)
{
    unsigned n=11;
    int nSubIntervalos=n-1;
    double h=(b-a)/nSubIntervalos;
    double y[n];
    double x=a;
    y[0]=f(x);
    double FIRST=y[0];
    double somaOdd=0;
    double somaEven=0;
    for(unsigned i=1;i<n-1;i++)
    {
        x+=h;
        y[i]=f(x);
        if(i & 1)// odd
            somaOdd+=y[i];
        else //even
        somaEven+=y[i];
    }
    x+=h;
    double LAST=f(x);
    return h/3*(FIRST+4*somaOdd+2*somaEven+LAST);

}

int main()
{
  Funcao f=myfx;
  std::cout<<simpson(0,1,f)<<std::endl;
}
