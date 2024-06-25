#include "mysystem.h"

POLYFITINFO pinfo={ "0",0,0,0,0.0,0.0,0.0,0.0,{0.0},{0.0},{0.0},{0.0},{0.0} };

int compute_datas(const char* filename)
{
	FILE* fp;
	int end, temp;
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		MessageBox(GetHWnd(), _T("文件打开失败！"), _T("提示"), MB_OK | MB_ICONEXCLAMATION);
	}
	fseek(fp, 0, SEEK_END);
	end = ftell(fp);
	temp = end / sizeof(pinfo);
	fclose(fp);
	return temp;
}

//初始化链表
struct LinkNode* Initialize_LinkList(const char* filename)
{
	//创建头结点
	//头结点本身不储存数据，只是标记该链表的起始位置                      
	struct LinkNode* header = (struct LinkNode*)malloc(sizeof(struct LinkNode));
	if (header == NULL)
		exit(0);

	header->data = pinfo;
	header->next = NULL;//头结点初始化

	//定义尾指针
	//尾指针类似于前面的辅助指针，用于确定链表的尾部位置
	//以便后续插入数据，可以通过尾指针将每个结点连接起来
	struct LinkNode* pRear = header;//尾指针初始化

	int num = compute_datas(filename);
	//数据输入
	FILE* fp;
	if ((fp = fopen(filename, "rb+")) == NULL)
	{
		MessageBox(GetHWnd(), _T("文件打开失败！"), _T("提示"), MB_OK | MB_ICONEXCLAMATION);
	}
	for(int i = 0;i<num;i++)
	{
		//创建新结点
		struct LinkNode* newnode = (struct LinkNode*)malloc(sizeof(struct LinkNode));
		fread(&newnode->data, sizeof(pinfo), 1, fp);
		newnode->next = NULL;
		//将新结点插入链表
		pRear->next = newnode;

		//更新尾指针
		pRear = newnode;
	}
	return header;
}

//遍历检索列表
bool search_LinkList(struct LinkNode* header,char *filename,bool flag)
{
	if (header == NULL)
		return false;

	//定义辅助指针
	struct LinkNode* pCurrent = header->next;

	while (pCurrent != NULL)
	{
		if (strcmp(pCurrent->data.filename, filename) == 0)
			break;
		pCurrent = pCurrent->next;
	}
	if (flag)
	{
		if (pCurrent != NULL)
		{
			return true;
		}
		else
			return false;
	}
	else
	{ 
		if (pCurrent == NULL)
			cout << "The file is not saved." << endl;
		else
		{
			cout << "当前文件名：" << pCurrent->data.filename << endl;
			cout << "数据条数：" << pCurrent->data.row << endl;
			cout << "最高拟合阶数：" << pCurrent->data.MaxOrder << endl;
			cout << "最佳拟合阶数：" << pCurrent->data.OptiOrder << endl;
			cout << "数据均值：" << pCurrent->data.mean << endl;
			cout << "数据方差：" << pCurrent->data.var << endl;
			cout << "拟合误差均值：" << pCurrent->data.error_mean << endl;
			cout << "拟合误差方差：" << pCurrent->data.error_var << endl;
			int i = 1;
			cout << "不同阶次拟合误差：" << endl;
			for(;i<pCurrent->data.MaxOrder;i++)
			{
				cout << pCurrent->data.fitError[i] << "\t" << endl;
			}
			i = 0;
			cout << "零点："<<endl;
			while (pCurrent->data.zeropoint[i] != 0)
			{
				cout << pCurrent->data.zeropoint[i] << "\t" << endl;
				i++;
			}
			if (i == 0)
				cout<<"本数据没有零点"<<endl;
			i = 0;
			cout << "极值点：" << endl;
			while (pCurrent->data.limitpoint[i] != 0)
			{
				cout << pCurrent->data.limitpoint[i] << "\t" << endl; 
				i++;
			}
			if (i == 0)
				cout << "本数据没有极值点" << endl;
			cout << "极值：" << endl;
			while (pCurrent->data.limit[i] != 0)
			{ 
				cout << pCurrent->data.limit[i] << "\t" << endl;
				i++;
			}
			if (i == 0)
				cout << "本数据没有极值" << endl;
		}
	}
	return false;
}

//清空链表（把除头结点以外的结点全部释放内存）
void Destroy_LinkList(struct LinkNode* header)
{
	if (header == NULL)
		return;

	//定义辅助指针
	struct LinkNode* pCurrent = header;//Destroy_LinkList只需改为header即可

	while (pCurrent != NULL)
	{
		//保存下一结点地址
		struct LinkNode* pNext = pCurrent->next;

		//清空当前结点内存
		free(pCurrent);

		//指向下一个结点
		pCurrent = pNext;
	}
	pCurrent = NULL;
}

//删除某个结点
void Delete_LinkList(struct LinkNode* header, char* filename)
{
	if (header == NULL)
		return;

	//定义两个辅助指针
	struct LinkNode* pPrev = header, * pCurrent = header->next;

	//遍历链表
	while (pCurrent != NULL)
	{
		if (strcmp(pCurrent->data.filename, filename)==0)
			break;
		pPrev = pPrev->next;
		pCurrent = pCurrent->next;
	}

	if (pCurrent == NULL)
		return;

	//删除对应结点 
	pPrev->next = pCurrent->next;
	free(pCurrent);
	pCurrent = NULL;
}

//遍历并写入文件
void write_LinkList(struct LinkNode* header,const char* filename)
{
	if (header == NULL)
		return;
	FILE* fp;
	if ((fp = fopen(filename, "wb")) == NULL)
	{
		MessageBox(GetHWnd(), _T("文件打开失败！"), _T("提示"), MB_OK | MB_ICONEXCLAMATION);
	}
	fclose(fp);
	if ((fp = fopen(filename, "ab")) == NULL)
	{
		MessageBox(GetHWnd(), _T("文件打开失败！"), _T("提示"), MB_OK | MB_ICONEXCLAMATION);
	}

	//定义辅助指针
	struct LinkNode* pCurrent = header->next;
	while (pCurrent != NULL)
	{
		fwrite(&pCurrent->data, sizeof(pinfo), 1, fp);
		pCurrent = pCurrent->next;
	}
	fclose(fp);
}

//遍历读取文件信息
void read_filename(struct LinkNode* header)
{
	if (header == NULL)
		return;
	//定义辅助指针
	struct LinkNode* pCurrent = header->next;

	while (pCurrent != NULL)
	{
		cout << pCurrent->data.filename<<endl;
		pCurrent = pCurrent->next;
	}
}

//插入排序链表并交换结点，遍历输出
void Bubble(struct LinkNode* header)
{
	struct LinkNode *pre, *cur, *next, *end;//pre前一项 cur当前项 next后一项 end控制循环次数(优化冒泡)
	end = NULL;

	while (header->next != end)	
	{
		//初始化三个指针 ; 判断是否到达结束位置 ; 三个指针集体后移
		for (pre = header, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
		{
			if (cur->data.fitError[cur->data.OptiOrder] > next->data.fitError[next->data.OptiOrder]) //从小到大
			{
				pre->next = next;
				cur->next = next->next;
				next->next = cur;

				//此时next变前一项，cur变后一项  交换next cur
				struct LinkNode* temp = cur; cur = next; next = temp;
			}
		}
		//一轮循环结束 最后一项已经排好 end提前一项 (冒泡原理)
		end = cur;
	}
	//定义辅助指针
	struct LinkNode* pCurrent = header->next;
	while (pCurrent != NULL)
	{
		cout << pCurrent->data.filename<<"\t"<< pCurrent->data.fitError[pCurrent->data.OptiOrder] << endl;
		pCurrent = pCurrent->next;
	}
}

