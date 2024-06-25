#include "mysystem.h"


void bk_draw2()
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
	drawtext("-----------------------------------------------------", &R1, DT_TOP | DT_CENTER | DT_SINGLELINE);
	drawtext("欢迎来到信息管理系统", &R1, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	drawtext("请选择你要进行的操作", &R1, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);
}

int Menu4(void)
{
    int option;
    button button1(350, 400, 300, 50, "查看已存入系统的文件信息"), button2(400, 450, 200, 50, "删除文件信息"),
        button3(400, 500, 200, 50, "检索文件信息"), button4(400, 550, 200, 50, "排序文件信息")
        ,button5(400, 600, 200, 50, "返回");
    while (true)
    {
        BeginBatchDraw();
        cleardevice();
        bk_draw2();
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

void msg_manage()
{
    int option4;
    POLYFITINFO pinfo;
    struct LinkNode* header = Initialize_LinkList("mymessage.dat");
    int numfile;
    char name[20];
    while (true)
    {
        option4 = Menu4();
        switch (option4)
        {
        case 1:
            numfile = compute_datas("mymessage.dat");
            if (numfile == 0)
                printf("There is no data in the database\n");
            else
            {
                printf("There are %d file data in the database：\n", numfile);
                read_filename(header);
            }
            system("pause");
            system("cls");
            break;
        case 2:
            cout << "请输入你要删除的文件名：" << endl;
            fflush(stdin);
            gets_s(name);
            Delete_LinkList(header, name);
            write_LinkList(header, "mymessage.dat");
            system("pause");
            system("cls");
            break;
        case 3:
            cout << "请输入你要检索的文件名：" << endl;
            gets_s(name);
            search_LinkList(header, name);
            system("pause");
            system("cls");
            break;
        case 4:
            cout << "按照拟合误差的大小对系统中的数据进行排序，结果如下："<<endl;
            cout << "文件名\t拟合误差大小" << endl;
            Bubble(header);
            system("pause");
            system("cls");
            break;
        }
        if (option4 == 5)
        {
            Destroy_LinkList(header);
            break;
        }
    }
}