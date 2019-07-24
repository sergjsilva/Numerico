#include<iostream>
using namespace std;

const int linha=3;
const int coluna=4;


//double a[linha][coluna]={{1,2,1,2},{3,8,1,12},{0,4,1,2}};
double a[linha][coluna]={{1,1,0,2},{2,-1,3,4},{-1,0,1,0}};
double x[linha];

void imprime()
{
	cout<<"---"<<endl;	
	for(int i=0;i<linha;i++)
	{
		for(int j=0;j<coluna;j++)
			cout<<a[i][j]<<" ";
		cout<<endl;
	}	
	
	cout<<"---"<<endl;	
}

void escalona()
{
	for(int k=0;k<coluna-2;k++)
	{
		for(int i=k+1;i<linha;i++)
		{
			double m=-a[i][k]/a[k][k];
			a[i][k]=0;
			for(int j=k+1;j<coluna;j++)
				a[i][j]+=m*a[k][j];
		}
		
	}
}


void solve()
{
	int n=linha-1;
	x[n]=a[n][coluna-1]/a[n][n];
	
	for(int j=n-1;j>=0;j--)
	{
		double soma=0.0;
		for(int i=j+1;i<coluna-1;i++)
		{
			soma+=a[j][i]*x[i];			
		}
			
		cout<<"j="<<j<<endl;
		x[j]=(a[j][coluna-1]-soma)/a[j][j];
	}
	
	for(int k=0;k<linha;k++)
		cout<<x[k]<<endl;
}

int main()
{
	imprime();
	escalona();
	imprime();
	solve();
	return 0;
}
