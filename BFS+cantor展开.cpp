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
#include<queue>
using namespace std;

map <long long, int> m;
char str[10];
int a[10], tar[10] = {1, 2, 3, 8, 9, 4, 7, 6, 5};
const int factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
int dep[400010];

inline int cantor(int *p)
{
	int ans = 0;
	for (int i = 0; i < 9; i ++)
	{
		int cnt = 0;
		for (int j = i + 1; j < 9; j ++)
			if (*(p + i) > *(p + j))
				++ cnt;
		ans += cnt * factorial[8 - i];
	}
	return ans;
}

inline void decantor(int x)
{
	bool vis[10];
	for (int i = 1; i <= 9; i ++)
		vis[i] = 0;
	for (int i = 0; i < 9; i ++)
	{
		a[i] = x / factorial[8 - i];
		for (int j = 1; j <= 9; j ++)
		{
			if (vis[j]) continue;
			if (!a[i])
			{
				a[i] = j;
				vis[j] = 1;
				break;
			}
			a[i] --;
		}
			
		x %= factorial[8 - i];
	}
	return;
}

int bfs()
{
	int aim = cantor(tar);
	queue <int> q;
	int temp = cantor(a);
	q.push(temp);
	dep[temp] = 0;
	while (!q.empty())
	{
		int now = q.front(); q.pop();
		if (now == aim) return dep[now];
		decantor(now);
		int pos;
		for (int i = 0; i < 9; i ++)
			if (a[i] == 9)
				pos = i;
		if (pos > 2)
		{
			swap(a[pos], a[pos - 3]);
			temp = cantor(a);
			if (dep[temp] == -1)
			{
				dep[temp] = dep[now] + 1;
				q.push(temp);
			}
			swap(a[pos], a[pos - 3]);
		}
		if (pos < 6)
		{
			swap(a[pos], a[pos + 3]);
			temp = cantor(a);
			if (dep[temp] == -1)
			{
				dep[temp] = dep[now] + 1;
				q.push(temp);
			}
			swap(a[pos], a[pos + 3]);
		}
		if (pos % 3)
		{
			swap(a[pos], a[pos - 1]);
			temp = cantor(a);
			if (dep[temp] == -1)
			{
				dep[temp] = dep[now] + 1;
				q.push(temp);
			}
			swap(a[pos], a[pos - 1]);
		}
		if (pos % 3 < 2)
		{
			swap(a[pos], a[pos + 1]);
			temp = cantor(a);
			if (dep[temp] == -1)
			{
				dep[temp] = dep[now] + 1;
				q.push(temp);
			}
			swap(a[pos], a[pos + 1]);
		}
	}
}

int main()
{
	int T = 1;
	//T = read();
	while (T --)
	{
		cin >> str;
		memset (dep, -1, sizeof (dep));
		for (int i = 0; i < 9; i ++)
			if (str[i] == '0')
				a[i] = 9;
			else
				a[i] = str[i] - '0';
		cout << bfs();
	}
	return 0;
}
