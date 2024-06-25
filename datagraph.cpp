#include "mysystem.h"

void showdata(double dataX[],double dataY[],int n, long color, PLOTAREA p)
{
  	int i;
	int x0,y1,height,width;
	double minX,scaleX, minY, scaleY;

	//  find the min and scale of the input array
	minX=arraymin(dataX,n);
	scaleX=arrayscale(dataX,n);

	minY=arraymin(dataY,n);
	scaleY=arrayscale(dataY,n);
	  
	// Set the plot area;
	x0=p.x0; 
	y1=p.y1;
	height=p.y1-p.y0;
	width=p.x1-p.x0;

	// Plot the graph
	setlinecolor(color);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	for(i=0;i<n-1;i++)
	{
		line(x0+(dataX[i]-minX)/scaleX*width,y1-(dataY[i]-minY)/scaleY*height, x0+(dataX[i+1]-minX)/scaleX*width, y1-(dataY[i+1]-minY)/scaleY*height);
	}
}


//»æÖÆÖù×´Í¼
void showhisto(double result[],int n, PLOTAREA area)
{
	int i;
	double max;
	float xscale,yscale;
	char number[20] = { 0 };
	char number2[20] = { 0 };
	max=result[1]; 
	for(i=1;i<n;i++)
		if(max<result[i]) max=result[i];
	xscale=(area.x1-area.x0)/(float)n;
	yscale=(area.y1-area.y0)/(float)max;
	for(i=1;i<=n;i++)
	{ 
		setfillcolor(COLOR[i+1]);
		solidrectangle(area.x0+i*xscale,area.y1,area.x0+(i+1)*xscale,area.y1-result[i]*yscale);

		settextstyle(0, 0, "ºÚÌå");
		sprintf(number, "%.2lf", result[i]);
		outtextxy(i*xscale+area.x0+15, area.y1 - result[i] * yscale-40, number);

		settextstyle(0, 0, "ºÚÌå");
		sprintf(number2, "%d", i);
		outtextxy(i*xscale+area.x0+25,area.y1 +30,number2);
	}
}

void showpinfo(POLYFITINFO pinfo,PLOTAREA farea)
{
// need to set the project properties to MBCS	
 char s[100];
 sprintf(s,"Filename: %s",pinfo.filename);
 outtextxy(farea.x0,farea.y0,s);
 sprintf(s,"Row of Data %d",pinfo.row);
 outtextxy(farea.x0,farea.y0+30,s);
 sprintf(s,"OptiOrder is %d",pinfo.OptiOrder);
 outtextxy(farea.x0,farea.y0+60,s);
 sprintf(s,"Overall fiterror is %.2lf",pinfo.fitError[pinfo.OptiOrder]);
 outtextxy(farea.x0,farea.y0+90,s);
 sprintf(s, "Mean of data is %.2lf", pinfo.mean);
 outtextxy(farea.x0, farea.y0 + 120, s);
 sprintf(s, "Var of data is %.2lf", pinfo.var);
 outtextxy(farea.x0, farea.y0 + 150, s);
 sprintf(s, "Mean of fiterror is %.2lf", pinfo.error_mean);
 outtextxy(farea.x0, farea.y0 + 180, s);
 sprintf(s, "Var of fiterror is %.2lf", pinfo.error_var);
 outtextxy(farea.x0, farea.y0 + 210, s);
}
