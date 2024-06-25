#include "mysystem.h"

LOGIN input_data1 = { "0","0" }, input_data2;

int Menu1(void)
{
    int option;
    button button1(400, 400, 200, 50, "��¼"), button2(400, 500, 200, 50, "ע��"), button3(400, 600, 200, 50, "�˳�");
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

void register_draw(void)
{
    int r1[] = { 0,0,1000,300 };
    RECT R1 = { r1[0],r1[1],r1[2],r1[3] };
    setfillcolor(RGB(230, 230, 250));
    solidrectangle(r1[0], r1[1], r1[2], r1[3]);
    setfillcolor(RGB(255, 255, 240));
    solidrectangle(0, 300, 1000, 800);
    LOGFONT f1;
    gettextstyle(&f1);
    _tcscpy(f1.lfFaceName, _T("�п�"));
    f1.lfQuality = ANTIALIASED_QUALITY;
    f1.lfHeight = 40, f1.lfWeight = 40;
    settextstyle(&f1);
    settextcolor(BLUE);
    drawtext("--------------------------------------------------", &R1, DT_TOP | DT_CENTER | DT_SINGLELINE);
    drawtext("ע�����", &R1, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    drawtext("--------------------------------------------------", &R1, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);
    set_style();
    outtextxy(350, 350, _T("�û�����"));
    setfillcolor(WHITE);
    outtextxy(350, 400, _T("��  �룺"));
}

void login_draw(void)
{
    int r1[] = { 0,0,1000,300 };
    RECT R1 = { r1[0],r1[1],r1[2],r1[3] };
    setfillcolor(RGB(230, 230, 250));
    solidrectangle(r1[0], r1[1], r1[2], r1[3]);
    setfillcolor(RGB(255, 255, 240));
    solidrectangle(0, 300, 1000, 800);
    LOGFONT f1;
    gettextstyle(&f1);
    _tcscpy(f1.lfFaceName, _T("�п�"));
    f1.lfQuality = ANTIALIASED_QUALITY;
    f1.lfHeight = 40, f1.lfWeight = 40;
    settextstyle(&f1);
    settextcolor(BLUE);
    drawtext("--------------------------------------------------", &R1, DT_TOP | DT_CENTER | DT_SINGLELINE);
    drawtext("��¼����", &R1, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    drawtext("--------------------------------------------------", &R1, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);
    set_style();
    outtextxy(350, 350, _T("�û�����"));
    setfillcolor(WHITE);
    outtextxy(350, 400, _T("��  �룺"));
}

void __register(void)
{
    button button1(400, 500, 200, 50, "ע��"), button2(400, 600, 200, 50, "����");
    textbox textbox1(450, 350, 650, 375,20), textbox2(450, 400, 650, 425, 20,true);
    int i = 1, j = 1;
    char key;
    char* text;
    while (true)
    {
        BeginBatchDraw();
        cleardevice();
        register_draw();
        ExMessage msg;
        msg = getmessage(EM_MOUSE| EM_CHAR);
        button1.checkMouseOver(msg.x, msg.y);
        button2.checkMouseOver(msg.x, msg.y);
        button1.draw();
        button2.draw();
        textbox1.draw1(msg.x, msg.y);
        textbox2.draw1(msg.x, msg.y);
        key = (char)msg.ch;
        if (msg.message == WM_LBUTTONDOWN)
        {
            if (button1.checkClick(msg.x, msg.y))
            {
                if (input_data1.username[0] != 0 && input_data1.password[0] != 0)
                {
                    MessageBox(GetHWnd(), _T("ע��ɹ���"), _T("��ʾ"), MB_OK);
                    break;
                }
            }
            else if (button2.checkClick(msg.x, msg.y))
            {
                MessageBox(GetHWnd(), _T("��ȷ��Ҫ������"), _T("��ʾ"), MB_OKCANCEL);
                break;
            }
            if (textbox1.checkClick(msg.x, msg.y))
            {
                textbox1.inputstate = true;
            }
            if (textbox2.checkClick(msg.x, msg.y))
            {
                textbox2.inputstate = true;
            }
        }
        if (textbox1.inputstate)
        {
            textbox1.append(key);
            strcpy(input_data1.username, textbox1.m_text);
            textbox1.draw2();
            
        }
        if (textbox2.inputstate)
        {
            textbox2.append(key);
            strcpy(input_data1.password, textbox2.m_text);

            textbox2.draw2();
        }
        textbox1.draw3();
        textbox2.draw3();
        EndBatchDraw();
    }
}

bool login2(void)
{
    button button1(400, 500, 200, 50, "��¼"), button2(400, 600, 200, 50, "����");
    textbox textbox1(450, 350, 650, 375,20), textbox2(450, 400, 650, 425, 20,true);
    int i = 1;
    char key;
    char *text;
    while (true)
    {
        BeginBatchDraw();
        cleardevice();
        login_draw();
        ExMessage msg;
        msg = getmessage(EM_MOUSE | EM_CHAR);
        button1.checkMouseOver(msg.x, msg.y);
        button2.checkMouseOver(msg.x, msg.y);
        button1.draw();
        button2.draw();
        textbox1.draw1(msg.x, msg.y);
        textbox2.draw1(msg.x, msg.y);
        key = (char)msg.ch;
        if (msg.message == WM_LBUTTONDOWN)
        {
            if (button1.checkClick(msg.x, msg.y))
            {
                if ((strcmp(input_data1.username, input_data2.username) == 0) && (strcmp(input_data1.password, input_data2.password) == 0))
                {
                    // ��¼�ɹ����˳�ѭ��
                    MessageBox(GetHWnd(), _T("��¼�ɹ���"), _T("��ʾ"), MB_OK);
                    return true;
                }
                else
                {                   
                    // ��¼ʧ�ܣ�������ʾ����
                    MessageBox(GetHWnd(), _T("�û������������"), _T("��ʾ"), MB_OK | MB_ICONEXCLAMATION);
                }
            }
            if (button2.checkClick(msg.x, msg.y))
            {
                MessageBox(GetHWnd(), _T("��ȷ��Ҫ������"), _T("��ʾ"), MB_OKCANCEL);
                return false;
            }
            else if (textbox1.checkClick(msg.x, msg.y))
            {
                textbox1.inputstate = true;
            }
            else if (textbox2.checkClick(msg.x, msg.y))
            {
                textbox2.inputstate = true;
            }
        }
        if (textbox1.inputstate)
        {
            textbox1.append(key);
            strcpy(input_data2.username, textbox1.m_text);
            textbox1.draw2();

        }
        if (textbox2.inputstate)
        {
            textbox2.append(key);
            strcpy(input_data2.password, textbox2.m_text);
            textbox2.draw2();
        }
        textbox1.draw3();
        textbox2.draw3();
        EndBatchDraw();
    }
}


