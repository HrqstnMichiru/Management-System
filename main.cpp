#include "mysystem.h"

int Menu2()
{
	int option;
	button button1(400, 400, 200, 50, "���ݴ���ϵͳ"), button2(400, 500, 200, 50, "��Ϣ����ϵͳ"), button3(400, 600, 200, 50, "�˳�");
	while (true)
	{
		BeginBatchDraw();
		cleardevice();
		generate_background();
		ExMessage msg;
		msg = getmessage(EM_MOUSE);
		button1.checkMouseOver(msg.x, msg.y);
		button2.checkMouseOver(msg.x, msg.y);
		button3.checkMouseOver(msg.x, msg.y);
		button1.draw();
		button2.draw();
		button3.draw();
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
		}
		EndBatchDraw();
	}
	return option;
}

void submenu(void)
{
	int option2;
	while (true)
	{
		option2 = Menu2();
		switch (option2)
		{
		case 1:
			data_process();
			break;
		case 2:
			msg_manage();
			break;
		case 3:
			printf("ллʹ��ϵͳ���ټ���\n");
			exit(0);
			break;
		}
	}
}

int main()
{
	int option1;
	int loginState=false;
	initgraph(1000, 800,EX_SHOWCONSOLE);
	setbkcolor(RGB(230, 230, 250));
	cleardevice();
	loading();
	while (true)
	{
		option1 = Menu1();
		switch (option1)
		{
		case 1:
			loginState = login2();
			if (loginState)
				submenu();
			break;
		case 2:
			__register();
			break;
		default:
			exit(1);
		}
	}
	return 0;
}
	
