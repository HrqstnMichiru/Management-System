#include "mysystem.h"

void generate_background(void)
{
	int r1[] = { 0,0,1000,300 };
	RECT R1 = { r1[0],r1[1],r1[2],r1[3] };
	setfillcolor(RGB(230, 230, 250));
	solidrectangle(r1[0], r1[1], r1[2], r1[3]);
	setfillcolor(RGB(255, 255, 240));
	solidrectangle(0, 300, 1000, 800);
	LOGFONT f1;
	gettextstyle(&f1);
	_tcscpy(f1.lfFaceName, _T("行楷"));
	f1.lfQuality = ANTIALIASED_QUALITY;
	f1.lfHeight = 60, f1.lfWeight = 60;
	settextstyle(&f1);
	settextcolor(BLUE);
	drawtext("----------------------------------------------", &R1, DT_TOP | DT_CENTER | DT_SINGLELINE);
	drawtext("数据处理与信息管理系统", &R1, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	drawtext("----------------------------------------------", &R1, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);
}

void set_style(void)
{
	LOGFONT f2;
	gettextstyle(&f2);
	_tcscpy(f2.lfFaceName, _T("微软雅黑"));
	f2.lfQuality = ANTIALIASED_QUALITY;
	f2.lfHeight = 30, f2.lfWeight = 30, f2.lfWeight = 30;
	settextstyle(&f2);
	settextcolor(BLACK);
}

void loading()
{ 
	int x = 200;
	int r2[] = { 200,450,800,500 };
	RECT R2 = { r2[0],r2[1],r2[2],r2[3] };
	for (int i = 1; i < 101; i++)
	{
		BeginBatchDraw();
		cleardevice();
		generate_background();
		setfillcolor(RGB(255, 255, 240));
		setlinecolor(BLACK);
		fillrectangle(200, 550, 800, 600);
		set_style();
		char str[50];
		sprintf(str, "加载数据中...%d%%/100%%", i);
		drawtext(str, &R2, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		x +=6;
		setfillcolor(WHITE);
		fillrectangle(200, 550, x, 600);
		Sleep(10);
		EndBatchDraw();
	}
	generate_background();
	set_style();
	setfillcolor(WHITE);
	fillrectangle(200, 550, 800, 600);
	drawtext("数据加载完成...", &R2, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	Sleep(1000);
	cleardevice();
}
