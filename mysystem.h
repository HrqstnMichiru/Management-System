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


//�ṹ�嶨��
//����������ݽṹ��
typedef struct
{
  char filename[20];        //�����ļ���
  int row;                  //���ݵ�����
  int MaxOrder;             //�����Ͻ���
  int OptiOrder;            //�����Ͻ���
  double mean;              //���ݾ�ֵ
  double var;               //���ݷ���
  double error_mean;        //�������ֵ
  double error_var;         //�������
  double polyCoeff[10][10]; //��ͬ�״ζ���ʽ��ϲ���
  double fitError[10];      //��ͬ�״ζ���ʽ������
  double zeropoint[5];      //�������
  double limitpoint[5];     //��ֵ������
  double limit[5];          //��ֵ����
}POLYFITINFO;               //���������������

//��ͼ�������ݽṹ��
typedef struct 
{ 
	int x0,y0,x1,y1;        //���ϽǺ����½ǵ�����
}PLOTAREA;                  //��ͼ������������

//������ݽṹ��
struct LinkNode
{
    POLYFITINFO data;       //�������
    struct LinkNode* next;  //���ָ��
};

//��¼���ݽṹ��
typedef struct login_data
{
    char username[10];      //�û���
    char password[10];      //����
}LOGIN;                     //��¼��������                              


//�ඨ��
//��ť��
class button
{
private:
    int x; // ��ť���Ͻ�x����
    int y; // ��ť���Ͻ�y����
    int width; // ��ť���
    int height; // ��ť�߶�
    float scale; // ���ű���������ʵ�������ͣЧ��
    bool isMouseOver; // ��ʾ����Ƿ��ڰ�ť�Ϸ�
    string text; // ��ť�ı�
public:
    button(int x, int y, int width, int height, string text, bool flag = false, float scale = 1.0);
    void checkMouseOver(int mouseX, int mouseY);
    bool checkClick(int mouseX, int mouseY);
    void draw();
};

//�ı�����
class textbox
{
private:
    int	m_x1, m_y1, m_x2, m_y2;		// �ı���λ��			
    int	m_textlen;					// �û������ַ����ĳ���
    int	m_fps;						// ÿ����ö��ٴΣ������˹����˸�ٶȣ�
    bool m_flag;
public:
    // ���캯��
    textbox(int x1, int  y1, int x2, int y2, int fps, bool flag = false);
    void append(char c);
    void draw1(int x, int y);
    void draw2();
    void draw3();
    bool checkClick(int mouseX, int mouseY);
    bool inputstate;
    char m_text[10];                // �û�������ַ���
};


//ȫ�ֱ�������
extern int COLOR[16];


//��������
//����������� �ļ���arrayop.cpp 
double arrayscale(double a[], int n);
double arraymin(double a[], int n);
double arraymax(double a[], int n);
void arraycopy(double target[],double source[],int n);
void arraysub(double x[],double y[],double z[],int n);// z=x-y;

//����ʽ��Ϻ��� �ļ���polyfit.cpp
void polyfit(int n,double x[],double y[],int poly_n,double p[]);
void gauss_solve(int n,double A[],double x[],double b[]);
void reverseP(double arr[],int size);

//����ʽ�������� �ļ���polyop.cpp
double fx(double x, double coeffs[], int degree);

//ͼ����ʾ �ļ���datagraph.cpp
void showhisto(double result[],int n, PLOTAREA area);
void showpinfo(POLYFITINFO pinfo,PLOTAREA farea);
void showdata(double dataX[],double dataY[],int n, long color, PLOTAREA p); 

//���ؽ��� �ļ���loading.cpp
void loading(void); 
void set_style(void);
void generate_background(void);

//ע�����¼���� �ļ���register_login.cpp
void __register(void);
bool login2(void);
int Menu1(void);

//���ݴ���ϵͳ �ļ���DataProcessing.cpp
void data_process(void);

//��Ϣ����ϵͳ �ļ���MessageManagement.cpp
void msg_manage(void);

//������� �ļ���dataread.cpp
struct LinkNode* Initialize_LinkList(const char* filename);
bool search_LinkList(struct LinkNode* header, char* filename,bool flag=false);
void Destroy_LinkList(struct LinkNode* header);
void Delete_LinkList(struct LinkNode* header, char* filename);
void write_LinkList(struct LinkNode* header,const char* filename);
void read_filename(struct LinkNode* header);
void Bubble(struct LinkNode* header);
int compute_datas(const char* filename);