#include "mysystem.h"

void arraycopy(double target[],double source[],int n) //���鿽��
{
 int i;
 for(i=0;i<n;i++)
	 target[i]=source[i];
}

void arraysub(double x[],double y[],double z[],int n)// z=x-y;
{
 int i;
 for(i=0;i<n;i++)
	 z[i]=x[i]-y[i];
} 

double arraymax(double a[], int n) //�������ֵ
{
  double max;
  int i;
  max=a[0];
  for(i=1;i<n;i++)
  {
	if(max<a[i]) max=a[i];
  }
   return max;
}

double arraymin(double a[], int n) //������Сֵ
{
  double min;
  int i;
  min=a[0];
  for(i=1;i<n;i++)
  {
	if(min>a[i]) min=a[i];
  }
   return min;
}

double arrayscale(double a[], int n) // �������ֵ��Χ
{
  return arraymax(a,n)-arraymin(a,n);
}
