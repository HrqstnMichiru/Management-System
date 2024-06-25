#include "mysystem.h"

textbox::textbox(int x1, int  y1, int x2, int y2, int fps,bool flag)
{
	m_x1 = x1;	m_y1 = y1;	m_x2 = x2;	m_y2 = y2;
	m_text[0] = '\0';
	m_textlen = 0;
	m_fps = fps;
	inputstate = false;
	m_flag = flag;
}

void textbox::append(char c)
{
	if (inputstate)
	{
		if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		{
			if (m_textlen < 10)
			{
				m_text[m_textlen] = c;
				m_text[m_textlen + 1] = '\0';
				m_textlen++;
			}
		}
		else if (c == 8)
		{
			if (m_textlen > 0)
			{
				m_textlen--;
				m_text[m_textlen] = '\0';
			}
		}
		else if (c == 13)
			inputstate = false;
	}
}

void textbox::draw1(int x,int y)
{
	// 画边框
	if (checkClick(x,y))
	{
		setlinecolor(RGB(0, 120, 215)); // 鼠标悬停时按钮边框颜色
		setfillcolor(RGB(229, 241, 251)); // 鼠标悬停时按钮填充颜色

	}
	else
	{
		setlinecolor(RGB(173, 173, 173)); // 按钮边框颜色
		setfillcolor(RGB(225, 225, 225)); // 按钮填充颜色
	}
	fillrectangle(m_x1, m_y1, m_x2, m_y2);
}

void textbox::draw2()
{
	static int fps = 0;				// 统计字母个数计算光标位置

	// 绘制光标 
	fps++;
	if (fps < (m_fps / 4))
	{
		setlinecolor(BLACK);
		int sx = m_x1 + 10 + textwidth(m_text);
		line(sx, m_y1 + (m_y2 - m_y1 - 20) / 2, sx, m_y1 + (m_y2 - m_y1 - 20) / 2 + 20);
	}
	else if (fps > (m_fps / 2))
		fps = 0;
}

void textbox::draw3()
{
	// 设置文字输出样式
	settextstyle(20, 0, _T("Verdana"));
	// 输出用户输入的字符串
	if (m_flag)
	{
		int len;
		len = strlen(m_text);
		string output(len, '*');
		outtextxy(m_x1 + 5, m_y1 + (m_y2 - m_y1 - 10) / 2, output.c_str());
	}
	else
	{ 
	outtextxy(m_x1 + 5, m_y1 + (m_y2 - m_y1 - 10) / 2, m_text);
	}
}

bool textbox::checkClick(int mouseX, int mouseY)
{
	if (mouseX >= m_x1 && mouseX <= m_x2 && mouseY >= m_y1 && mouseY <= m_y2)
	{
		return true;
	}
	else
		return false;
}
