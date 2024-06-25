#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <math.h>
#include <string.h>
#include "conio.h"
#include <time.h>
#include <string>
#include <iostream>
using namespace std;


//结构体定义
//曲线拟合数据结构体
typedef struct
{
  char filename[20];        //数据文件名
  int row;                  //数据的条数
  int MaxOrder;             //最大拟合阶数
  int OptiOrder;            //最佳拟合阶数
  double mean;              //数据均值
  double var;               //数据方差
  double error_mean;        //拟合误差均值
  double error_var;         //拟合误差方差
  double polyCoeff[10][10]; //不同阶次多项式拟合参数
  double fitError[10];      //不同阶次多项式拟合误差
  double zeropoint[5];      //零点数组
  double limitpoint[5];     //极值点数组
  double limit[5];          //极值数组
}POLYFITINFO;               //曲线拟合数据类型

//绘图区域数据结构体
typedef struct 
{ 
	int x0,y0,x1,y1;        //左上角和右下角的坐标
}PLOTAREA;                  //绘图区域数据类型

//结点数据结构体
struct LinkNode
{
    POLYFITINFO data;       //结点数据
    struct LinkNode* next;  //结点指针
};

//登录数据结构体
typedef struct login_data
{
    char username[10];      //用户名
    char password[10];      //密码
}LOGIN;                     //登录数据类型                              


//类定义
//按钮类
class button
{
private:
    int x; // 按钮左上角x坐标
    int y; // 按钮左上角y坐标
    int width; // 按钮宽度
    int height; // 按钮高度
    float scale; // 缩放比例，用于实现鼠标悬停效果
    bool isMouseOver; // 表示鼠标是否在按钮上方
    string text; // 按钮文本
public:
    button(int x, int y, int width, int height, string text, bool flag = false, float scale = 1.0);
    void checkMouseOver(int mouseX, int mouseY);
    bool checkClick(int mouseX, int mouseY);
    void draw();
};

//文本框类
class textbox
{
private:
    int	m_x1, m_y1, m_x2, m_y2;		// 文本框位置			
    int	m_textlen;					// 用户输入字符串的长度
    int	m_fps;						// 每秒调用多少次（决定了光标闪烁速度）
    bool m_flag;
public:
    // 构造函数
    textbox(int x1, int  y1, int x2, int y2, int fps, bool flag = false);
    void append(char c);
    void draw1(int x, int y);
    void draw2();
    void draw3();
    bool checkClick(int mouseX, int mouseY);
    bool inputstate;
    char m_text[10];                // 用户输入的字符串
};


//全局变量定义
extern int COLOR[16];


//函数声明
//数组基本操作 文件：arrayop.cpp 
double arrayscale(double a[], int n);
double arraymin(double a[], int n);
double arraymax(double a[], int n);
void arraycopy(double target[],double source[],int n);
void arraysub(double x[],double y[],double z[],int n);// z=x-y;

//多项式拟合函数 文件：polyfit.cpp
void polyfit(int n,double x[],double y[],int poly_n,double p[]);
void gauss_solve(int n,double A[],double x[],double b[]);
void reverseP(double arr[],int size);

//多项式函数处理 文件：polyop.cpp
double fx(double x, double coeffs[], int degree);

//图形显示 文件：datagraph.cpp
void showhisto(double result[],int n, PLOTAREA area);
void showpinfo(POLYFITINFO pinfo,PLOTAREA farea);
void showdata(double dataX[],double dataY[],int n, long color, PLOTAREA p); 

//加载界面 文件：loading.cpp
void loading(void); 
void set_style(void);
void generate_background(void);

//注册与登录界面 文件：register_login.cpp
void __register(void);
bool login2(void);
int Menu1(void);

//数据处理系统 文件：DataProcessing.cpp
void data_process(void);

//信息管理系统 文件：MessageManagement.cpp
void msg_manage(void);

//链表操作 文件：dataread.cpp
struct LinkNode* Initialize_LinkList(const char* filename);
bool search_LinkList(struct LinkNode* header, char* filename,bool flag=false);
void Destroy_LinkList(struct LinkNode* header);
void Delete_LinkList(struct LinkNode* header, char* filename);
void write_LinkList(struct LinkNode* header,const char* filename);
void read_filename(struct LinkNode* header);
void Bubble(struct LinkNode* header);
int compute_datas(const char* filename);