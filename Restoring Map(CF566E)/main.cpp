#include <bits/stdc++.h>

using namespace std;

const int MX = 1020;

typedef bitset<MX> bst;

template <typename T> void read(T &x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

bst near[MX], edge[MX], not_leaf;
int n;

void input()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		int num, ver;
		read(num);
		for(int j=1; j<=num; j++) read(ver), near[i][ver] = 1;
	}
}

void work()
{
	int found = 0, e1, e2;
	for(int i=1; i<=n; i++) edge[i][i] = 1;
	for(int i=1; i<=n; i++)
		for(int j=i+1; j<=n; j++)
		{
			auto tmp = near[i]&near[j];
			if(tmp.count() == 2)
			{
				vector<int> ver;
				for(auto b=1; b<=n; b++) if(tmp[b]) ver.push_back(b);
				if(edge[ver[0]][ver[1]]) continue;
				edge[ver[0]][ver[1]] = 1;
				edge[ver[1]][ver[0]] = 1;
				not_leaf[ver[0]] = not_leaf[ver[1]] = 1;
				printf("%d %d\n", ver[0], ver[1]);
				found++, e1 = ver[0], e2 = ver[1];
			}
		}
	if(found == 0) for(int i=2; i<=n; i++) printf("%d %d\n", 1, i);
	else if(found == 1)
	{
		int a = 0;
		bst all;
		for(int i=1; i<=n; i++) all[i] = 1;
		for(int i=1; i<=n; i++)
			if(!(near[i]==all))
			{
				a = i;
				break;
			}
		for(int i=1; i<=n; i++)
			if(near[a][i] && !not_leaf[i])
				printf("%d %d\n", i, e1);
			else if(!near[a][i] && !not_leaf[i])
				printf("%d %d\n", i, e2);
	}
	else for(int i=1; i<=n; i++)
	{
		if(not_leaf[i]) continue;
		int con = 0;
		bst mn;
		mn.set();
		for(int j=1; j<=n; j++)
			if(near[j][i] && near[j].count()<mn.count())
				mn = near[j];
		for(int j=1; j<=n; j++)
			if((mn&not_leaf) == edge[j])
			{
				con = j;
				break;
			}
		printf("%d %d\n", i, con);
	}
}

int main()
{
	input();
	work();
	return 0;
}

/*
9
3 1 2 3
4 1 2 3 4
5 1 2 3 4 5
6 2 3 4 5 6 7
7 3 4 5 6 7 8 9
4 4 5 6 7
6 4 5 6 7 8 9
4 5 7 8 9
4 5 7 8 9
*/