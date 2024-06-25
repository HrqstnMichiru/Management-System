#include "mysystem.h"

button::button(int x, int y, int width, int height, string text, bool flag , float scale ):
	 x(x), y(y), width(width), height(height), text(text){}

 void button::checkMouseOver(int mouseX, int mouseY)
{
    isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
    if (isMouseOver) {
        scale = 0.9; // 鼠标悬停时缩放按钮
    }
    else {
        scale = 1.0; // 恢复按钮原始大小
    }
}

 // 检查鼠标点击是否在按钮内，并执行函数
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
    int scaledWidth = width * scale; // 缩放后的按钮宽度
    int scaledHeight = height * scale; // 缩放后的按钮高度
    int scaledX = x + (width - scaledWidth) / 2; // 缩放后的按钮x坐标
    int scaledY = y + (height - scaledHeight) / 2; // 缩放后的按钮y坐标

    if (isMouseOver)
    {
        setlinecolor(RGB(0, 120, 215)); // 鼠标悬停时按钮边框颜色
        setfillcolor(RGB(229, 241, 251)); // 鼠标悬停时按钮填充颜色

    }
    else
    {
        setlinecolor(RGB(173, 173, 173)); // 按钮边框颜色
        setfillcolor(RGB(225, 225, 225)); // 按钮填充颜色
    }

    fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); // 绘制按钮
    settextcolor(BLACK); // 设置文本颜色为黑色
    setbkmode(TRANSPARENT); // 设置文本背景透明
    settextstyle(30 * scale, 0, _T("微软雅黑")); // 设置文本大小和字体
    //居中显示按钮文本
    int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2; // 计算文本在按钮中央的x坐标
    int textY = scaledY + (scaledHeight - textheight(_T("微软雅黑"))) / 2; // 计算文本在按钮中央的y坐标
    outtextxy(textX, textY, text.c_str()); // 在按钮上绘制文本
}

