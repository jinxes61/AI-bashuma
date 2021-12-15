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
using namespace std;

char str[10];
int a[10], tar[10] = {1, 2, 3, 8, 0, 4, 7, 6, 5}, ans;
int pos[10] = {0, 1, 2, 5, 8, 7, 6, 3};
int dis[10][10]; 

struct record
{
	int from, to;
};
record re[100];

inline int dif()
{
	int cnt = 0;
	for (int i = 0; i < 9; i ++)
		if (a[i])
			cnt += dis[i][pos[a[i] - 1]];//哈密顿距离之和
	return cnt;
}

bool IDA_star(int dep, int pre)
{
	if (dep == 0)
	{
		bool flag = true;
		for (int i = 0; i < 9; i ++)
			if (a[i] != tar[i])
				flag = false;
		if (flag)
		{
//			for (int i = ans; i >= 1; i --)
//				printf ("move %d to %d\n", re[i].from + 1, re[i].to + 1);
		}
		return flag;
	}
	int diff = dif();
	if (diff > dep) return false;
		
	int pos;
	for (int i = 0; i < 9; i ++)
		if (!a[i])
			pos = i;
			
	bool flag = false;
	if (pos > 2 && pre != 2)
	{
		swap(a[pos], a[pos - 3]);
		re[dep].from = pos - 3;
		re[dep].to = pos;
		flag |= IDA_star(dep - 1, 1);
		swap(a[pos], a[pos - 3]);
	}
	if (flag) return flag;
	if (pos < 6 && pre != 1)
	{
		swap(a[pos], a[pos + 3]);
		re[dep].from = pos + 3;
		re[dep].to = pos;
		flag |= IDA_star(dep - 1, 2);
		swap(a[pos], a[pos + 3]);
	}
	if (flag) return flag;
	if (pos % 3 && pre != 4)
	{
		swap(a[pos], a[pos - 1]);
		re[dep].from = pos - 1;
		re[dep].to = pos;
		flag |= IDA_star(dep - 1, 3);
		swap(a[pos], a[pos - 1]);
	}
	if (flag) return flag;
	if (pos % 3 < 2 && pre != 3)
	{
		swap(a[pos], a[pos + 1]);
		re[dep].from = pos + 1;
		re[dep].to = pos;
		flag |= IDA_star(dep - 1, 4);
		swap(a[pos], a[pos + 1]);
	}
	if (flag) return flag;
	return false;
}

void init_dis()//初始化两个位置的dis
{
	const int inf = 1e9;
	for (int i = 0; i < 9; i ++)
		for (int j = 0; j < 9; j ++)
			if (i != j)
				dis[i][j] = inf;//初始化距离为inf
	//相邻的点建长度为1的边
	for (int i = 0; i < 9; i ++)
		if (i % 3 < 2)
			dis[i][i + 1] = dis[i + 1][i] = 1;
	for (int i = 0; i < 6; i ++)
		dis[i][i + 3] = dis[i + 3][i] = 1;
	//floyd算法求多源最短路
	for (int k = 0; k < 9; k ++)
		for (int i = 0; i < 9; i ++)
			for (int j = 0; j < 9; j ++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]); 
	return;
}

int main()
{
	int T = 1;
	//T = read();
	init_dis();
	while (T --)
	{
		cin >> str;
		for (int i = 0; i < 9; i ++)
			a[i] = str[i] - '0';
		int cnt = 0;
		for (int i = 1; i < 9; i ++)
		{
			for (int j = 0; j < i; j ++)
			if (a[i] && a[i] < a[j])
				++ cnt;
		}
		ans = 0;
		while (!IDA_star(ans, 0)) 
			++ ans;
			
		cout << ans;
	}
	return 0;
}

