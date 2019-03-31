#include "Mat.h"
#include<iomanip>
#include<iostream>
#include<cstdlib>
#include<cmath>

using std::cout;
using std::endl;



bool std::areEqual(double a, double b)
{
    double precision = 1.0e-8;
	return abs(a - b)<precision;
}


Mat std::soma(Mat A, Mat B)
{
    Mat result=Mat(A.row,A.col,0);

	if (A.row == B.row && A.col ==B.col) // mesma dimensao
	{
		for (unsigned i = 0; i<A.row; i++)
			for (unsigned j = 0; j<A.col; j++)
				result.mat[i][j] = A.mat[i][j] + B.mat[i][j];
	}
	else
	{
		cout << "Erro!!! A soma deve ser realizada com matrizes de mesma dimensao!!\n";
		exit(EXIT_FAILURE);

	}
	return result;
}

Mat std::mult(Mat A, Mat B)
{
    if(A.col!=B.row)
    {
        cout<<"Erro!!! Dimensao Errada!!\n";
        exit(EXIT_FAILURE);
    }


    Mat result=Mat(A.row,B.col,0);

    for(unsigned i=0;i<A.row;i++)
        for(unsigned j=0;j<B.col;j++)
            for(unsigned k=0;k<A.col;k++)
                result.mat[i][j]+=A.mat[i][k]*B.mat[k][j];

    return result;
}

Mat std::rotation(double theta)
{
    Mat result=Mat(2,2,1);
    double angle=theta*PI/180;// converte para radianos
    result.mat[0][0]=cos(angle);
    result.mat[0][1]=-sin(angle);
    result.mat[1][0]=sin(angle);
    result.mat[1][1]=cos(angle);

    return result;
}


Mat std::idMat(unsigned n)
{
    Mat I=Mat(n,n,0);
	for (unsigned i = 0; i<I.row; i++)
		for (unsigned j = 0; j<I.col; j++)
			if (i == j)
				I.mat[i][j] = 1.0;


	return I;
}

Mat std::mergeMat(Mat A, Mat B)
{
	Mat temp=Mat(A.row,A.col+B.col,0);
	if (A.row == B.row)
	{
		// Block 1
		for (unsigned i = 0; i < A.row; i++)
			for (unsigned j = 0; j < A.col;j++)
				temp.mat[i][j] = A.mat[i][j];
		// Block 2
		for (unsigned i = 0; i < B.row; i++)
			for (unsigned j = 0; j < B.col; j++)
            temp.mat[i][A.col+j] = B.mat[i][j];

	}
	else
	{
		cout << "\n Error!!! We can only merge matrices with the same number of rows!!\n";
		exit(EXIT_FAILURE);
	}
	return temp;
}


Mat std::rref(Mat M)
{
    int lead = 0;
	int rowCount = M.row;
	int columnCount = M.col;

	for (int r = 0; r<rowCount; r++)
	{
		if (columnCount <= lead)
			break;
		int i = r;
		while (areEqual(M.mat[i][lead], 0.0))
		{
			i++;
			if (i == rowCount)
			{
				i = r;
				lead++;
				if (lead == columnCount)
					return M;
			}
		}//while

		M.changeRow(i,r);
		double pivo = M.mat[r][lead];
		M.divRowby(r,pivo);
		//divideMatriz(r, pivo, M);
		for (unsigned k = 0; k<M.row; k++)
		{
			if (k != r)
			{
				pivo = -M.mat[k][lead];
				for (unsigned j = 0; j<M.col; j++)
					M.mat[k][j] += pivo * M.mat[r][j];
			}
		}
		lead++;
	}//prox r

	return M;
}


Mat std::inv(Mat M)
{
    Mat I = std::idMat(M.row);
	Mat P = std::mergeMat(M, I);
	Mat Escada = std::rref(P);
	Mat Aux1=Mat(M.row,M.col,0);
	Mat Aux2=Mat(M.row,M.col,0);
	Escada.splitMat(Aux1, Aux2);
	if (Aux1.isIdentity())
		return Aux2;
	else
	{
		M.print();
		cout << "\n Not invertible! \n";
		system("pause");
		exit(EXIT_FAILURE);
	}
}


Mat::Mat(unsigned _row, unsigned _col, double inicial)
{
    mat.resize(_row);
    for (unsigned i=0; i<mat.size(); i++)
    {
        mat[i].resize(_col, inicial);
    }
    row = _row;
    col = _col;
}

Mat::Mat(const Mat& rhs)
{
    mat = rhs.mat;
    row = rhs.row;
    col = rhs.col;
}

Mat::Mat(unsigned _row, unsigned _col)
{
    mat.resize(_row);
    for (unsigned i=0; i<mat.size(); i++)
    {
        mat[i].resize(_col, 1);
    }
    row = _row;
    col = _col;
    for(unsigned i=0;i<row;i++)
        for(unsigned j=0;j<col;j++)
            mat[i][j]*=RandomDouble();
}

Mat::Mat(unsigned _row, unsigned _col, double a, double b)
{
        mat.resize(_row);
    for (unsigned i=0; i<mat.size(); i++)
    {
        mat[i].resize(_col, 1);
    }
    row = _row;
    col = _col;
    for(unsigned i=0;i<row;i++)
        for(unsigned j=0;j<col;j++)
            mat[i][j]*=RandomDouble(a,b);
}


void Mat::print()
{
    using std::setprecision;

    for (unsigned i = 0; i<row; i++)
	{
		for (unsigned j = 0; j<col; j++)
		{
			cout<<setprecision(3)<< std::fixed<< mat[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Mat::byUser()
{
    using std::cin;

    cout<<"\t...Creating "<<row<<"x"<<col<<" matrix (row by row, separating by space)...\n";
    for(unsigned i=0;i<row;i++)
        {

            cout<<"[ Linha "<<i+1<<"]=";
            for(unsigned j=0;j<col;j++)
                cin>>mat[i][j];
        }
    cout<<endl;
}

Mat Mat::transp()
{
	Mat temp=Mat(col,row,0);

	for (unsigned i = 0; i<temp.row; i++)
		for (unsigned j = 0; j<temp.col; j++)
			temp.mat[i][j] = mat[j][i];

	return temp;
}


void Mat::soma(Mat M)
{
	Mat result=Mat(row,col,0);

	if (M.row == row && M.col ==col) // mesma dimensao
	{
		for (unsigned i = 0; i<M.row; i++)
			for (unsigned j = 0; j<M.col; j++)
				mat[i][j] += M.mat[i][j];
	}
	else
	{
		cout << "Erro!!! A soma deve ser realizada com matrizes de mesma dimensao!!\n";
		exit(EXIT_FAILURE);

	}
}

void Mat::sub(Mat M)
{
	if (M.row == row && M.col ==col) // mesma dimensao
	{
		for (unsigned i = 0; i<M.row; i++)
			for (unsigned j = 0; j<M.col; j++)
				mat[i][j] -=M.mat[i][j];
	}
	else
	{
		cout << "Erro!!! A soma deve ser realizada com matrizes de mesma dimensao!!\n";
		exit(EXIT_FAILURE);

	}

}


Mat Mat::mult(Mat M)
{
    if(M.row!=col)
    {
        cout<<"Erro!!! Dimensao Errada!!\n";
        exit(EXIT_FAILURE);
    }
    Mat result=Mat(row,M.col,0);


    for(unsigned i=0;i<result.row;i++)
        for(unsigned j=0;j<result.col;j++)
            for(unsigned k=0;k<col;k++)
                result.mat[i][j]+=mat[i][k]*M.mat[k][j];

    return result;
}

void Mat::multby(Mat M)
{
    if(M.col!=row)
    {
        cout<<"Erro!!! Dimensao Errada!!\n";
        exit(EXIT_FAILURE);
    }

    Mat result=Mat(M.row,col,0);
    for(unsigned i=0;i<result.row;i++)
        for(unsigned j=0;j<result.col;j++)
            for(unsigned k=0;k<M.col;k++)
                result.mat[i][j]+=M.mat[i][k]*mat[k][j];

    row=result.row;
    mat=result.mat;
}


void Mat::multN(double n)
{
    for(unsigned i=0;i<row;i++)
        for(unsigned j=0;j<col;j++)
            mat[i][j]*=n;
}

void Mat::divRowby(unsigned row_, double num)
{
	for (unsigned j = 0; j<col; j++)
		mat[row_][j] /= num;
}


void Mat::changeRow(unsigned i, unsigned j)
{
	double temp;
	for (unsigned k = 0; k<col; k++)
	{
		temp = mat[i][k];
		mat[i][k] = mat[j][k];
		mat[j][k] = temp;
	}

}

void Mat::changeCol(unsigned i, unsigned j)
{
	double temp;
	for (unsigned k = 0; k<row; k++)
	{
		temp = mat[k][i];
		mat[k][i] = mat[k][j];
		mat[k][j] = temp;
	}

}

void Mat::splitMat(Mat& A, Mat& B)
{
    // Block 1
	for (unsigned i = 0; i < A.row; i++)
		for (unsigned j = 0; j < A.col; j++)
			A.mat[i][j] = mat[i][j];
	// Block 2
	for (unsigned i = 0; i < B.row; i++)
		for (unsigned j = 0; j < B.col; j++)
			B.mat[i][j] = mat[i][j+A.col];
}

bool Mat::isIdentity()
{
   for (unsigned i = 0; i < row; i++)
		for (unsigned j = 0; j < col; j++)
		{
			if (i == j & !std::areEqual(mat[i][j], 1.0))
				return false;
			else if (i != j & !std::areEqual(mat[i][j], 0))
				return false;
		}
	return true;
}


/*
Mat Mat::inv()
{
    Mat I = idMat(row);
    Mat
	Mat P = std::mergeMat(M, I);
	Matriz Escada = rref(P);
	Matriz Aux1, Aux2;
	int n = M.linha;
	SplitMatriz(Escada, n, n, n, n, Aux1, Aux2);
	if (ehIdentidade(Aux1))
		return Aux2;
	else
	{
		cout << "\n Matriz nao eh inversivel \n";
		system("pause");
		exit(EXIT_FAILURE);
	}
}*/

double Mat::RandomDouble()
{
    double random=(double)rand()/(double)RAND_MAX;
    return random;
}

double Mat::RandomDouble(double a, double b)
{
    double random=(double)rand()/(double)RAND_MAX;
    double dif=b-a;
    double h=random*dif;
    double valor=a+h;
    return valor;
}
