#include "mysystem.h"
#define N 1000
int COLOR[16] = { BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE };


void bk_draw1()
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
	f1.lfHeight = 40, f1.lfWeight = 40;
	settextstyle(&f1);
	settextcolor(BLUE);
	drawtext("--------------------------------------------------", &R1, DT_TOP | DT_CENTER | DT_SINGLELINE);
	drawtext("欢迎来到数据处理系统", &R1, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	drawtext("请选择你要处理的数据文件", &R1, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);
}

int Menu3(void)
{
    int option;
    button button1(200, 400, 200, 50, "1.txt"), button2(600, 400, 200, 50, "2.txt"),
        button3(200, 600, 200, 50, "3.txt"), button4(600, 600, 200, 50, "4.txt"),
		button5(400,500,200,50,"返回");
    while (true)
    {
        BeginBatchDraw();
        cleardevice();
		bk_draw1();
        ExMessage msg;
        msg = getmessage(EM_MOUSE);
        button1.checkMouseOver(msg.x, msg.y);
        button2.checkMouseOver(msg.x, msg.y);
        button3.checkMouseOver(msg.x, msg.y);
        button4.checkMouseOver(msg.x, msg.y);
		button5.checkMouseOver(msg.x, msg.y);
        button1.draw();
        button2.draw();
        button3.draw();
        button4.draw();
		button5.draw();
        if (msg.message == WM_LBUTTONDOWN)
        {
            if (button1.checkClick(msg.x, msg.y))
            {
                option = 1;
                break;
            }
            else if (button2.checkClick(msg.x, msg.y))
            {
                option = 2;
                break;
            }
            else if (button3.checkClick(msg.x, msg.y))
            {
                option = 3;
                break;
            }
            else if (button4.checkClick(msg.x, msg.y))
            {
                option = 4;
                break;
            }
			else if (button5.checkClick(msg.x, msg.y))
			{
				option = 5;
				break;
			}
        } 
		EndBatchDraw();
    }
	return option;
}

int showprocess(const char*p)
{
	FILE* fp;
	int i, datacount = 0;
	POLYFITINFO pinfo = { "0",0,0,0,0.0,0.0,0.0,0.0,{0.0},{0.0},{0.0},{0.0},{0.0} };
	struct LinkNode* header = Initialize_LinkList("mymessage.dat");
	double error;		// 拟合误差
	int order, MaxOrder; // 多项式的阶次
	double datax[N], datay[N], fity[N],value1[N],value2[N];
	PLOTAREA  parea = { 200,400,824,700 }; // 直方图显示区域，
	PLOTAREA  farea = { 10,500,80,700 };   // 文字显示区域 
	PLOTAREA dataarea = { 50,10,950,300 }; // 数据曲线显示区域

	if ((fp = fopen(p, "r+")) == NULL)
	{
		MessageBox(GetHWnd(), _T("文件打开失败！"), _T("提示"), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	for (i = 0; i < N; i++)
	{
		fscanf(fp, "%lf %lf", &datax[i], &datay[i]);
		if (feof(fp) != 0) // 如果已经读到文件末尾，停止读文件
			break;
	}
	datacount = i; // 数据的行数
	fclose(fp);
	bool state1 = false, state21 = false, state22=false,state3 = false, state41 = false,state42=false,state5=false,
		state61=false,state62=false,state7=false,state8=false;
	button button1(0, 300, 300, 25, "原始数据展示"), button2(0, 325, 300, 25, "进行多项式拟合"),
		button3(0, 350, 300, 25, "通过直方图展示拟合误差"), button4(0, 375, 300, 25, "显示数据基本信息"),
		button5(0,400,300,25,"计算均值、方差、零点、极值点等"),button6(0,425,300,25,"显示差值特性"),
		button7(0,450,300,25,"保存文件信息"),button8(0, 475, 300, 25, "返回");

	//画出原始数据
	strcpy(pinfo.filename, p);
	pinfo.row = datacount;

	while (true)
	{
		BeginBatchDraw();
		cleardevice();
		ExMessage msg;
		msg = getmessage(EM_MOUSE);
		button1.checkMouseOver(msg.x, msg.y);
		button2.checkMouseOver(msg.x, msg.y);
		button3.checkMouseOver(msg.x, msg.y);
		button4.checkMouseOver(msg.x, msg.y);
		button5.checkMouseOver(msg.x, msg.y);
		button6.checkMouseOver(msg.x, msg.y);
		button7.checkMouseOver(msg.x, msg.y);
		button8.checkMouseOver(msg.x, msg.y);
		button1.draw();
		button2.draw();
		button3.draw();
		button4.draw();
		button5.draw();
		button6.draw();
		button7.draw();
		button8.draw();
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (button1.checkClick(msg.x, msg.y))
			{
				state1 = true;
			}
			else if (button2.checkClick(msg.x, msg.y))
			{
				state21 = true;
			}
			else if (button3.checkClick(msg.x, msg.y))
			{
				state3 = true;
			}
			else if (button4.checkClick(msg.x, msg.y))
			{
				state41 = true;
			}
			else if (button5.checkClick(msg.x, msg.y))
			{
				state5 = true;
			}
			else if (button6.checkClick(msg.x, msg.y))
			{
				state61 = true;
			}
			else if (button7.checkClick(msg.x, msg.y))
			{
				state7 = true;
			}
			else if (button8.checkClick(msg.x, msg.y))
			{
				state8 = true;
			}
		}
		if (state1)
		{
			//display data in the graphics window
			showdata(datax, datay, datacount, RED, dataarea);
			state62 = false;
		}
		if (state21)
		{
			// 利用最小二乘确定多项式拟合的系数
			printf("\n请输入你要拟合的最大阶次:");
			scanf("%d", &MaxOrder);
			fflush(stdin);
			system("cls");
			pinfo.MaxOrder = MaxOrder;
			for (order = 1; order <= MaxOrder; order++)
			{
				polyfit(datacount, datax, datay, order, pinfo.polyCoeff[order]);
			}
			state21 = false;
			state22 = true;
			state62 = false;
		}
		if (state22)
		{
			// 计算并记录拟合误差，画出拟合曲线。
			for (order = 1; order <= MaxOrder; order++)
			{
				error = 0;
				for (i = 0; i < datacount; i++)
				{
					fity[i] = fx(datax[i], pinfo.polyCoeff[order], order);
					error += (fity[i] - datay[i]) * (fity[i] - datay[i]);
				}
				pinfo.fitError[order] = error;
				showdata(datax, fity, datacount, COLOR[order], dataarea);
			}
		}
		if (state3)
		{
			// 用直方图表示不同阶次的拟合误差。
			showhisto(pinfo.fitError, MaxOrder, parea); // 在parea 显示直方图
		}
		if (state41)
		{
			// 输入最佳的多项式拟合阶次。
			printf("\n输入最优拟合效果的阶次:");
			scanf("%d", &pinfo.OptiOrder);
			for(i=0;i<datacount;i++)
			{ 
				fity[i] = fx(datax[i], pinfo.polyCoeff[pinfo.OptiOrder], pinfo.OptiOrder);
			}
			state41 = false; state42 = true;
		}
		if (state42)
		{
			showpinfo(pinfo, farea);  // 在farea 显示数据文件信息
		}
		if (state5)
		{
			double sum = 0;
			for (i = 0; i < datacount; i++)
			{
				sum += datay[i];
			}
			pinfo.mean = sum / double(datacount);
			sum = 0;
			for (i = 0; i < datacount; i++)
			{
				sum += pow(datay[i] - pinfo.mean, 2);
			}
			pinfo.var = sum / double(datacount);
			int k = 0;
			for (i = 1; i < datacount-1; i++)
			{
				if (fabs(fity[i - 1])< fabs(fity[i]) && fabs(fity[i + 1]) < fabs(fity[i]) )
					if (k < 5)
					{
						pinfo.limitpoint[k] = datax[i];
						pinfo.limit[k] = fity[i];
						k++;
					}
			}
			k = 0;
			for (i = 0; i < datacount-1; i++)
			{
				if ((fity[i]*fity[i+1])<=0)
					if (k < 5)
					{
						if (fabs(fity[i]) < 1e-3)
							pinfo.zeropoint[k] = datax[i];
						else if(fabs(fity[i+1])<1e-3)
							pinfo.zeropoint[k] = datax[i+1];
						else
							pinfo.zeropoint[k] = (datax[i + 1]+datax[i])/2.0;
						k++;
					}
			}
			i = 0;
			printf("本数据文件的零点：\n");
			while (i<5&& pinfo.zeropoint[i]!=0.0)
			{
				printf("%f\n", pinfo.zeropoint[i]);
				i++;
			}
			i = 0;
			printf("本数据文件的极值点：\n");
			while (i<5&& pinfo.limitpoint[i]!=0.0)
			{
				printf("%f\n",pinfo.limitpoint[i]);
				i++;
			}
			i = 0;
			printf("本数据文件的极值：\n");
			while (i < 5 && pinfo.limit[i] != 0.0)
			{
				printf("%f\n", pinfo.limit[i]);
				i++;
			}
			system("pause");
			system("cls");
			state5 = false;
		}
		if (state61)
		{
			double sum = 0;

			for (i = 0; i < datacount; i++)
			{
				value1[i] = datay[i] - fity[i];
				value2[i] = value1[i];
			}
			double t = 0;
			int j = 0;
			for(i=0;i<datacount;i++)
				for(j=i;j>0;j--)
					if (value2[j - 1] > value2[j])
					{
						t = value2[j - 1]; value2[j - 1] = value2[j]; value2[j] = t;
					}
			for (i = 0; i < datacount; i++)
			{
				sum += value1[i];
			}
			pinfo.error_mean = sum / double(datacount);
			sum = 0;
			for (i = 0; i < datacount; i++)
			{
				sum += pow(value1[i] - pinfo.error_mean, 2);
			}
			pinfo.error_var = sum / double(datacount);
			state61 = false; state62 = true; state22 = false; state1 = false;
		}
		if (state62)
		{
			showdata(datax, value2, datacount, LIGHTBLUE, dataarea);
			showdata(datax, value1, datacount, YELLOW, dataarea);
		}
		if (state7)
		{
			if ((fp = fopen("mymessage.dat", "ab")) == NULL)
			{
				MessageBox(GetHWnd(), _T("文件保存失败！"), _T("提示"), MB_OK | MB_ICONEXCLAMATION);
				return 0;
			}
			if(search_LinkList(header,pinfo.filename,true))
				MessageBox(GetHWnd(), _T("重复存储文件！"), _T("提示"), MB_OK);
			else
				fwrite(&pinfo, sizeof(pinfo), 1, fp);
			fclose(fp);
			state7 = false;
		}
		if (state8)
		{
			break;
		}
		EndBatchDraw();
	}
	return 0;
}

void data_process()
{
    int option3;
	const char* p;
    while (true)
    {
        option3 = Menu3();
		switch (option3)
		{
		case 1:
			p = "001.txt";
			showprocess(p);
			break;
		case 2:
			p = "002.txt";
			showprocess(p);
			break;
		case 3:
			p = "003.txt";
			showprocess(p);
			break;
		case 4:
			p = "004.txt";
			showprocess(p);
			break;
		}
		if (option3==5)
		{
			break;
		}
    }
}

