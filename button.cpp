#include "mysystem.h"

button::button(int x, int y, int width, int height, string text, bool flag , float scale ):
	 x(x), y(y), width(width), height(height), text(text){}

 void button::checkMouseOver(int mouseX, int mouseY)
{
    isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
    if (isMouseOver) {
        scale = 0.9; // �����ͣʱ���Ű�ť
    }
    else {
        scale = 1.0; // �ָ���ťԭʼ��С
    }
}

 // ���������Ƿ��ڰ�ť�ڣ���ִ�к���
bool button::checkClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        return true;
    }
    else
        return false;
}

void button::draw()
{
    int scaledWidth = width * scale; // ���ź�İ�ť���
    int scaledHeight = height * scale; // ���ź�İ�ť�߶�
    int scaledX = x + (width - scaledWidth) / 2; // ���ź�İ�ťx����
    int scaledY = y + (height - scaledHeight) / 2; // ���ź�İ�ťy����

    if (isMouseOver)
    {
        setlinecolor(RGB(0, 120, 215)); // �����ͣʱ��ť�߿���ɫ
        setfillcolor(RGB(229, 241, 251)); // �����ͣʱ��ť�����ɫ

    }
    else
    {
        setlinecolor(RGB(173, 173, 173)); // ��ť�߿���ɫ
        setfillcolor(RGB(225, 225, 225)); // ��ť�����ɫ
    }

    fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); // ���ư�ť
    settextcolor(BLACK); // �����ı���ɫΪ��ɫ
    setbkmode(TRANSPARENT); // �����ı�����͸��
    settextstyle(30 * scale, 0, _T("΢���ź�")); // �����ı���С������
    //������ʾ��ť�ı�
    int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2; // �����ı��ڰ�ť�����x����
    int textY = scaledY + (scaledHeight - textheight(_T("΢���ź�"))) / 2; // �����ı��ڰ�ť�����y����
    outtextxy(textX, textY, text.c_str()); // �ڰ�ť�ϻ����ı�
}

