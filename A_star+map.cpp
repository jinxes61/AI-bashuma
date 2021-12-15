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

map <long long, bool> m;
char str[10];
int a[10], tar[10] = {1, 2, 3, 8, 0, 4, 7, 6, 5}; 

struct node
{
	int val, dep;
	long long hash;
	bool operator <(const node &a) const
	{
		return val > a.val;
	}
};

priority_queue <node> q;

inline long long getHash()
{
	long long temp = 0;
	for (int i = 0; i < 9; i ++)
		temp = temp * 10 + a[i];
	return temp;
}

inline int dif()
{
	int cnt = 0;
	for (int i = 0; i < 9; i ++)
		if (a[i] && a[i] != tar[i])
			++ cnt;
	return cnt;
}

void hashToArray(long long hash)
{
	for (int i = 8; i >= 0; i --)
	{
		a[i] = hash % 10;
		hash /= 10;
	}
	return;
}

int A_star()
{
	node temp;
	temp.hash = getHash();
	temp.val = dif();
	temp.dep = 0;
	q.push(temp);
	bool flag = false;
	while (!q.empty())
	{
		node now = q.top(); q.pop();
		m[now.hash] = 1;
		hashToArray(now.hash);
		if (!dif()) return now.val;
		int pos;
		for (int i = 0; i < 9; i ++)
			if (!a[i])
				pos = i;
		if (pos > 2)
		{
			swap (a[pos], a[pos - 3]);
			temp.hash = getHash();
			if (!m[temp.hash])
			{
				temp.val = now.dep + 1 + dif();
				temp.dep = now.dep + 1;
				q.push(temp);
			}
			swap (a[pos], a[pos - 3]);
		}
		if (pos < 6)
		{
			swap (a[pos], a[pos + 3]);
			temp.hash = getHash();
			if (!m[temp.hash])
			{
				temp.val = now.dep + 1 + dif();
				temp.dep = now.dep + 1;
				q.push(temp);
			}
			swap (a[pos], a[pos + 3]);
		}
		if (pos % 3)
		{
			swap (a[pos], a[pos - 1]);
			temp.hash = getHash();
			if (!m[temp.hash])
			{
				temp.val = now.dep + 1 + dif();
				temp.dep = now.dep + 1;
				q.push(temp);
			}
			swap (a[pos], a[pos - 1]);
		}
		if (pos % 3 != 2)
		{
			swap (a[pos], a[pos + 1]);
			temp.hash = getHash();
			if (!m[temp.hash])
			{
				temp.val = now.dep + 1 + dif();
				temp.dep = now.dep + 1;
				q.push(temp);
			}
			swap (a[pos], a[pos + 1]);
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
		for (int i = 0; i < 9; i ++)
			a[i] = str[i] - '0';
		cout << A_star();
	}
	return 0;
}
