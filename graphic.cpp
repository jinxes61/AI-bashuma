#include <graphics.h>
#include <conio.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
#include<queue>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<ctime>
#include<Windows.h>
using namespace std;

map <long long, int> m;//���ڼ�¼����
char str[10];
int board[10], tar[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 }, ans;//��ǰ������Ŀ�����

//���ڼ�¼�𰸵Ĳ��跽��
struct record
{
	int from, to;
};
record re[100];

//���ۺ�������ǰ����Ӧ���ڵ�λ���ϵ��������
inline int dif()
{
	int cnt = 0;
	for (int i = 0; i < 9; i++)
		if (tar[i] && tar[i] != board[i])
			++cnt;
	return cnt;
}

//IDA*�����ڵ�������������A*�㷨
bool IDA_star(int dep)
{
	if (dep == 0)
	{
		bool flag = true;
		for (int i = 0; i < 9; i++)
			if (board[i] != tar[i])
				flag = false;
		if (flag)
		{
			for (int i = ans; i >= 1; i--)
				printf("move %d to %d\n", re[i].from + 1, re[i].to + 1);
		}
		return flag;
	}

	//�����ۺ������м�֦
	int diff = dif();
	if (diff > dep) return false;
	
	//����ǰ�������м�¼�����ظ��������֦
	long long temp = 0;
	for (int i = 0; i < 9; i++)
		temp = temp * 10 + board[i];
	if (m[temp] && m[temp] >= dep)
		return false;
	m[temp] = dep;

	//�ҵ��հ�֮��
	int pos;
	for (int i = 0; i < 9; i++)
		if (!board[i])
			pos = i;

	//���ĸ������ƶ���������
	bool flag = false;
	if (pos > 2)
	{
		swap(board[pos], board[pos - 3]);
		re[dep].from = pos - 3;
		re[dep].to = pos;
		flag |= IDA_star(dep - 1);
		swap(board[pos], board[pos - 3]);
	}
	if (flag) return flag;
	if (pos < 6)
	{
		swap(board[pos], board[pos + 3]);
		re[dep].from = pos + 3;
		re[dep].to = pos;
		flag |= IDA_star(dep - 1);
		swap(board[pos], board[pos + 3]);
	}
	if (flag) return flag;
	if (pos % 3)
	{
		swap(board[pos], board[pos - 1]);
		re[dep].from = pos - 1;
		re[dep].to = pos;
		flag |= IDA_star(dep - 1);
		swap(board[pos], board[pos - 1]);
	}
	if (flag) return flag;
	if (pos % 3 < 2)
	{
		swap(board[pos], board[pos + 1]);
		re[dep].from = pos + 1;
		re[dep].to = pos;
		flag |= IDA_star(dep - 1);
		swap(board[pos], board[pos + 1]);
	}
	if (flag) return flag;
	return false;
}

//�����Ѿ���ʼ����ϣ��������Ĺ���
bool solve()
{
	int T = 1;
	//T = read();
	while (T--)
	{
		int cnt = 0;
		for (int i = 1; i < 9; i++)
		{
			for (int j = 0; j < i; j++)
				if (board[i] && board[i] < board[j])
					++cnt;
		}
		if (cnt & 1)
			return false;

		//��������
		ans = 0;
		while (!IDA_star(ans))
		{
			m.clear();
			++ans;
		}
		return true;
	}
}


//��ʼ��
void init()
{
	// ������ͼ���ڣ���СΪ 640x640 ���أ����ñ�����ɫΪ��ɫ  
	setbkcolor(RGB(255, 255, 255));
	cleardevice();

	//������֡����������⡱�ͼ���������ť
	settextcolor(RGB(0, 0, 0));
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 36;						// ��������߶�Ϊ36
	f.lfWeight = 5;
	_tcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	char s[] = "����������";
	outtextxy(230, 50, s);
	f.lfHeight = 24;
	f.lfWeight = 3;
	_tcscpy_s(f.lfFaceName, _T("Consolas"));
	settextstyle(&f);
	char s1[] = "restart";
	outtextxy(520, 180, s1);
	char s2[] = "confirm";
	outtextxy(520, 280, s2);
	char s3[] = "start demo";
	outtextxy(500, 380, s3);

	//���ƾŹ���
	setlinecolor(RGB(0, 0, 0));
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
	line(170, 150, 170, 450);
	line(270, 150, 270, 450);
	line(370, 150, 370, 450);
	line(470, 150, 470, 450);
	line(170, 150, 470, 150);
	line(170, 250, 470, 250);
	line(170, 350, 470, 350);
	line(170, 450, 470, 450);

	for (int i = 0; i < 9; i++)
		board[i] = 0;
}

//չʾ��С�����Ķ���
void showdemo()
{
	LOGFONT f;
	gettextstyle(&f);

	for (int i = ans; i > 0; i--)
	{
		Sleep(1000);
		int x = 170 + re[i].from % 3 * 100, y = 150 + re[i].from / 3 * 100;
		int xx = 170 + re[i].to % 3 * 100, yy = 150 + re[i].to / 3 * 100;
		int num = board[re[i].from];
		setfillcolor(RGB(180, 180, 180));
		solidrectangle(x + 2, y + 2, x + 98, y + 98);
		setfillcolor(RGB(255, 255, 255));
		solidrectangle(xx + 2, yy + 2, xx + 98, yy + 98);
		f.lfHeight = 64;
		settextstyle(&f);
		outtextxy(xx + 34, yy + 18, char(num + '0'));
		swap(board[re[i].from], board[re[i].to]);
		f.lfHeight = 24;
		settextstyle(&f);
		int temp = ans - i + 1;
		char s[] = "Step   ";
		if (temp < 10)
			s[5] = temp + '0';
		else
		{
			s[5] = temp / 10 + '0';
			s[6] = temp % 10 + '0';
		}
		outtextxy(278, 500, s);
	}
}

//���ں��û����л������õ���ʼ��״̬
void getNumber()
{
	MOUSEMSG m;
	LOGFONT f;
	gettextstyle(&f);
	int cnt = 1;	//��¼Ŀǰ�������������
	while (1 && cnt <= 8)
	{
		char s[] = "place number  :";
		s[13] = (char)(cnt + '0');
		f.lfHeight = 24;
		settextstyle(&f);
		outtextxy(0, 280, s);

		//�Ÿ���������ƶ���ȥ���ɫ
		m = GetMouseMsg();
		int x = m.x, y = m.y;
		for (int i = 0; i < 9; i++)
		{
			if (board[i]) continue;
			int xx = 170 + i % 3 * 100, yy = 150 + i / 3 * 100;
			if (xx <= x && x <= xx + 100 && yy <= y && y <= yy + 100)
			{
				setfillcolor(RGB(180, 180, 180));
				solidrectangle(xx + 2, yy + 2, xx + 98, yy + 98);
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					setfillcolor(RGB(255, 255, 255));
					solidrectangle(xx + 2, yy + 2, xx + 98, yy + 98);
					board[i] = cnt;
					f.lfHeight = 64;
					settextstyle(&f);
					outtextxy(xx + 34, yy + 18, char(cnt + '0'));
					++cnt;
				}
			}
			else
			{
				setfillcolor(RGB(255, 255, 255));
				solidrectangle(xx + 2, yy + 2, xx + 98, yy + 98);
			}
		}

		//�������restart
		if (520 <= x && x <= 604 && 180 <= y && y <= 204)
		{
			setbkcolor(RGB(180, 180, 180));
			char s1[] = "restart";
			f.lfHeight = 24;
			settextstyle(&f);
			outtextxy(520, 180, s1);
			setbkcolor(RGB(255, 255, 255));
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				init();
				return;
			}
		}
		else
		{
			char s1[] = "restart";
			f.lfHeight = 24;
			settextstyle(&f);
			outtextxy(520, 180, s1);
		}
	}

	//ȷ����8��λ��֮��
	char s[] = " click confirm \0";
	f.lfHeight = 24;
	settextstyle(&f);
	outtextxy(0, 280, s);

	bool flag = false;//�Ƿ��н�

	while (1)
	{
		//�������restart
		m = GetMouseMsg();
		int x = m.x, y = m.y;
		if (520 <= x && x <= 604 && 180 <= y && y <= 204)
		{
			setbkcolor(RGB(180, 180, 180));
			char s1[] = "restart";
			f.lfHeight = 24;
			settextstyle(&f);
			outtextxy(520, 180, s1);
			setbkcolor(RGB(255, 255, 255));
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				init();
				return;
			}
		}
		else
		{
			char s1[] = "restart";
			f.lfHeight = 24;
			settextstyle(&f);
			outtextxy(520, 180, s1);
		}

		if (520 <= x && x <= 604 && 280 <= y && y <= 304)
		{
			setbkcolor(RGB(180, 180, 180));
			char s1[] = "confirm";
			f.lfHeight = 24;
			settextstyle(&f);
			outtextxy(520, 280, s1);
			setbkcolor(RGB(255, 255, 255));
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				outtextxy(520, 280, s1);
				setfillcolor(RGB(255, 255, 255));
				solidrectangle(0, 280, 168, 340);
				flag = solve();
				break;
			}
		}
		else
		{
			char s1[] = "confirm";
			f.lfHeight = 24;
			settextstyle(&f);
			outtextxy(520, 280, s1);
		}
	}

	if (!flag)
	{
		char s[] = "No legal answer! Please restart";
		outtextxy(150, 550, s);
	}
	else
	{
		char s[] = "The minimum steps:   , click to start demo";
		if (ans < 10)
			s[19] = ans + '0';
		else
		{
			s[19] = ans / 10 + '0';
			s[20] = ans % 10 + '0';
		}
		outtextxy(100, 550, s);
	}

	while (1)
	{
		//�������restart
		m = GetMouseMsg();
		int x = m.x, y = m.y;
		if (520 <= x && x <= 604 && 180 <= y && y <= 204)
		{
			setbkcolor(RGB(180, 180, 180));
			char s1[] = "restart";
			f.lfHeight = 24;
			settextstyle(&f);
			outtextxy(520, 180, s1);
			setbkcolor(RGB(255, 255, 255));
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				init();
				return;
			}
		}
		else
		{
			char s1[] = "restart";
			f.lfHeight = 24;
			settextstyle(&f);
			outtextxy(520, 180, s1);
		}

		//show demo
		if (flag)
		{
			if (500 <= x && x <= 620 && 380 <= y && y <= 404)
			{
				setbkcolor(RGB(180, 180, 180));
				char s1[] = "start demo";
				f.lfHeight = 24;
				settextstyle(&f);
				outtextxy(500, 380, s1);
				setbkcolor(RGB(255, 255, 255));
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					outtextxy(500, 380, s1);
					showdemo();
					break;
				}
			}
			else
			{
				char s1[] = "start demo";
				f.lfHeight = 24;
				settextstyle(&f);
				outtextxy(500, 380, s1);
			}
		}
	}

	setfillcolor(RGB(255, 255, 255));
	solidrectangle(0, 455, 640, 640);
	f.lfHeight = 24;
	settextstyle(&f);
	char s1[] = "please click restart";
	outtextxy(200, 550, s1);
	while (1)
	{
		//�������restart
		m = GetMouseMsg();
		int x = m.x, y = m.y;
		if (520 <= x && x <= 604 && 180 <= y && y <= 204)
		{
			setbkcolor(RGB(180, 180, 180));
			char s1[] = "restart";
			f.lfHeight = 24;
			settextstyle(&f);
			outtextxy(520, 180, s1);
			setbkcolor(RGB(255, 255, 255));
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				init();
				return;
			}
		}
		else
		{
			char s1[] = "restart";
			f.lfHeight = 24;
			settextstyle(&f);
			outtextxy(520, 180, s1);
		}
	}
}

int main()
{
	initgraph(640, 640);
	while (1)
	{
		init();
		getNumber();
	}
	_getch();              // �����������
	closegraph();          // �رջ�ͼ����
}