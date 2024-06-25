#include "mysystem.h"

POLYFITINFO pinfo={ "0",0,0,0,0.0,0.0,0.0,0.0,{0.0},{0.0},{0.0},{0.0},{0.0} };

int compute_datas(const char* filename)
{
	FILE* fp;
	int end, temp;
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		MessageBox(GetHWnd(), _T("�ļ���ʧ�ܣ�"), _T("��ʾ"), MB_OK | MB_ICONEXCLAMATION);
	}
	fseek(fp, 0, SEEK_END);
	end = ftell(fp);
	temp = end / sizeof(pinfo);
	fclose(fp);
	return temp;
}

//��ʼ������
struct LinkNode* Initialize_LinkList(const char* filename)
{
	//����ͷ���
	//ͷ��㱾���������ݣ�ֻ�Ǳ�Ǹ��������ʼλ��                      
	struct LinkNode* header = (struct LinkNode*)malloc(sizeof(struct LinkNode));
	if (header == NULL)
		exit(0);

	header->data = pinfo;
	header->next = NULL;//ͷ����ʼ��

	//����βָ��
	//βָ��������ǰ��ĸ���ָ�룬����ȷ�������β��λ��
	//�Ա�����������ݣ�����ͨ��βָ�뽫ÿ�������������
	struct LinkNode* pRear = header;//βָ���ʼ��

	int num = compute_datas(filename);
	//��������
	FILE* fp;
	if ((fp = fopen(filename, "rb+")) == NULL)
	{
		MessageBox(GetHWnd(), _T("�ļ���ʧ�ܣ�"), _T("��ʾ"), MB_OK | MB_ICONEXCLAMATION);
	}
	for(int i = 0;i<num;i++)
	{
		//�����½��
		struct LinkNode* newnode = (struct LinkNode*)malloc(sizeof(struct LinkNode));
		fread(&newnode->data, sizeof(pinfo), 1, fp);
		newnode->next = NULL;
		//���½���������
		pRear->next = newnode;

		//����βָ��
		pRear = newnode;
	}
	return header;
}

//���������б�
bool search_LinkList(struct LinkNode* header,char *filename,bool flag)
{
	if (header == NULL)
		return false;

	//���帨��ָ��
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
			cout << "��ǰ�ļ�����" << pCurrent->data.filename << endl;
			cout << "����������" << pCurrent->data.row << endl;
			cout << "�����Ͻ�����" << pCurrent->data.MaxOrder << endl;
			cout << "�����Ͻ�����" << pCurrent->data.OptiOrder << endl;
			cout << "���ݾ�ֵ��" << pCurrent->data.mean << endl;
			cout << "���ݷ��" << pCurrent->data.var << endl;
			cout << "�������ֵ��" << pCurrent->data.error_mean << endl;
			cout << "������" << pCurrent->data.error_var << endl;
			int i = 1;
			cout << "��ͬ�״������" << endl;
			for(;i<pCurrent->data.MaxOrder;i++)
			{
				cout << pCurrent->data.fitError[i] << "\t" << endl;
			}
			i = 0;
			cout << "��㣺"<<endl;
			while (pCurrent->data.zeropoint[i] != 0)
			{
				cout << pCurrent->data.zeropoint[i] << "\t" << endl;
				i++;
			}
			if (i == 0)
				cout<<"������û�����"<<endl;
			i = 0;
			cout << "��ֵ�㣺" << endl;
			while (pCurrent->data.limitpoint[i] != 0)
			{
				cout << pCurrent->data.limitpoint[i] << "\t" << endl; 
				i++;
			}
			if (i == 0)
				cout << "������û�м�ֵ��" << endl;
			cout << "��ֵ��" << endl;
			while (pCurrent->data.limit[i] != 0)
			{ 
				cout << pCurrent->data.limit[i] << "\t" << endl;
				i++;
			}
			if (i == 0)
				cout << "������û�м�ֵ" << endl;
		}
	}
	return false;
}

//��������ѳ�ͷ�������Ľ��ȫ���ͷ��ڴ棩
void Destroy_LinkList(struct LinkNode* header)
{
	if (header == NULL)
		return;

	//���帨��ָ��
	struct LinkNode* pCurrent = header;//Destroy_LinkListֻ���Ϊheader����

	while (pCurrent != NULL)
	{
		//������һ����ַ
		struct LinkNode* pNext = pCurrent->next;

		//��յ�ǰ����ڴ�
		free(pCurrent);

		//ָ����һ�����
		pCurrent = pNext;
	}
	pCurrent = NULL;
}

//ɾ��ĳ�����
void Delete_LinkList(struct LinkNode* header, char* filename)
{
	if (header == NULL)
		return;

	//������������ָ��
	struct LinkNode* pPrev = header, * pCurrent = header->next;

	//��������
	while (pCurrent != NULL)
	{
		if (strcmp(pCurrent->data.filename, filename)==0)
			break;
		pPrev = pPrev->next;
		pCurrent = pCurrent->next;
	}

	if (pCurrent == NULL)
		return;

	//ɾ����Ӧ��� 
	pPrev->next = pCurrent->next;
	free(pCurrent);
	pCurrent = NULL;
}

//������д���ļ�
void write_LinkList(struct LinkNode* header,const char* filename)
{
	if (header == NULL)
		return;
	FILE* fp;
	if ((fp = fopen(filename, "wb")) == NULL)
	{
		MessageBox(GetHWnd(), _T("�ļ���ʧ�ܣ�"), _T("��ʾ"), MB_OK | MB_ICONEXCLAMATION);
	}
	fclose(fp);
	if ((fp = fopen(filename, "ab")) == NULL)
	{
		MessageBox(GetHWnd(), _T("�ļ���ʧ�ܣ�"), _T("��ʾ"), MB_OK | MB_ICONEXCLAMATION);
	}

	//���帨��ָ��
	struct LinkNode* pCurrent = header->next;
	while (pCurrent != NULL)
	{
		fwrite(&pCurrent->data, sizeof(pinfo), 1, fp);
		pCurrent = pCurrent->next;
	}
	fclose(fp);
}

//������ȡ�ļ���Ϣ
void read_filename(struct LinkNode* header)
{
	if (header == NULL)
		return;
	//���帨��ָ��
	struct LinkNode* pCurrent = header->next;

	while (pCurrent != NULL)
	{
		cout << pCurrent->data.filename<<endl;
		pCurrent = pCurrent->next;
	}
}

//������������������㣬�������
void Bubble(struct LinkNode* header)
{
	struct LinkNode *pre, *cur, *next, *end;//preǰһ�� cur��ǰ�� next��һ�� end����ѭ������(�Ż�ð��)
	end = NULL;

	while (header->next != end)	
	{
		//��ʼ������ָ�� ; �ж��Ƿ񵽴����λ�� ; ����ָ�뼯�����
		for (pre = header, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
		{
			if (cur->data.fitError[cur->data.OptiOrder] > next->data.fitError[next->data.OptiOrder]) //��С����
			{
				pre->next = next;
				cur->next = next->next;
				next->next = cur;

				//��ʱnext��ǰһ�cur���һ��  ����next cur
				struct LinkNode* temp = cur; cur = next; next = temp;
			}
		}
		//һ��ѭ������ ���һ���Ѿ��ź� end��ǰһ�� (ð��ԭ��)
		end = cur;
	}
	//���帨��ָ��
	struct LinkNode* pCurrent = header->next;
	while (pCurrent != NULL)
	{
		cout << pCurrent->data.filename<<"\t"<< pCurrent->data.fitError[pCurrent->data.OptiOrder] << endl;
		pCurrent = pCurrent->next;
	}
}

