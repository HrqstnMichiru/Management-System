#include "mysystem.h"

void polyfit(int n,double x[],double y[],int poly_n,double p[])
{
	int i,j;
	double *tempx,*tempy,*sumxx,*sumxy,*ata;
	
	tempx = (double *)calloc(n , sizeof(double));
	sumxx = (double *)calloc((poly_n*2+1) , sizeof(double));
	tempy = (double *)calloc(n , sizeof(double));
	sumxy = (double *)calloc((poly_n+1) , sizeof(double));
	ata = (double *)calloc( (poly_n+1)*(poly_n+1) , sizeof(double) );
	
	for (i=0;i<n;i++)
	{
		tempx[i]=1;
		tempy[i]=y[i];
	}


	for (i=0;i<2*poly_n+1;i++)
	{
		for (sumxx[i]=0,j=0;j<n;j++)
		{
			sumxx[i]+=tempx[j];
			tempx[j]*=x[j];
		}
	}
 

	for (i=0;i<poly_n+1;i++)
	{
		for (sumxy[i]=0,j=0;j<n;j++)
		{
			sumxy[i]+=tempy[j];
			tempy[j]*=x[j];
		}
	}


 
	for (i=0;i<poly_n+1;i++)
	{
		for (j=0;j<poly_n+1;j++)
		{
			ata[i*(poly_n+1)+j]=sumxx[i+j];
		}
	}
	
	gauss_solve(poly_n+1,ata,p,sumxy);
	reverseP(p,poly_n);

	//释放动态分配的内存。	
	free(tempx);
	free(sumxx);
	free(tempy);
	free(sumxy);
	free(ata);
}
 
/*============================================================*/
	//高斯消元法计算得到	n 次多项式的系数
	//n: 系数的个数
	//ata: 线性矩阵
	//sumxy: 线性方程组的Y值
//	p: 返回拟合的结果
/*============================================================*/
void gauss_solve(int n,double A[],double x[],double b[])
{
	int i,j,k,r;
	double max;
	for (k=0;k<n-1;k++)
	{
		max=fabs(A[k*n+k]);					// find maxmum 
		r=k;
		for (i=k+1;i<n-1;i++)
		{
			if (max<fabs(A[i*n+i]))
			{
				max=fabs(A[i*n+i]);
				r=i;
			}
		}
		if (r!=k)
		{
			for (i=0;i<n;i++)		//change array:A[k]&A[r]
			{
				max=A[k*n+i];
				A[k*n+i]=A[r*n+i];
				A[r*n+i]=max;
			}
 
			max=b[k];                    //change array:b[k]&b[r]
			b[k]=b[r];
			b[r]=max;
		}                                  //为了使用列主元消去法，在第k步消元前，先找出k行下所有第k列元素最大的非零元素ar,k，将第r行与第k行进行整行交换
		
		for (i=k+1;i<n;i++)
		{
			for (j=k+1;j<n;j++)
				A[i*n+j]-=A[i*n+k]*A[k*n+j]/A[k*n+k];
			b[i]-=A[i*n+k]*b[k]/A[k*n+k];
		}
	} 

	
	for (i=n-1;i>=0;x[i]/=A[i*n+i],i--)
	{
		for (j=i+1,x[i]=b[i];j<n;j++)
			x[i]-=A[i*n+j]*x[j];
	}
}

// 将多项式的系数变为最高次在首位
void reverseP(double arr[],int size) {
	double temp;
	int i;
    for (i=0;i<=size/2; i++) 
		{
        temp=arr[i];arr[i]=arr[size-i];arr[size-i]=temp;
		}
}
