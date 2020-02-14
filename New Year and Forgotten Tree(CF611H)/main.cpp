#include <bits/stdc++.h>
#define mov(x) (1<<(x))

using namespace std;

const int MX = 200055;

template <typename T> void cmin(T &x, const T &y)
{
	if(y < x) x = y;
}

template <typename T> void cmax(T &x, const T &y)
{
	if(y > x) x = y;
}

template <typename T> void read(T &x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

int n, m;
int ver[7], edge[7][7];
int vid[7];
int in[7];

void input()
{
	read(n);
	for(int i=1; i<n; i++)
	{
		string a, b;
		cin >> a >> b;
		int la = a.length(), lb = b.length();
		if(la > lb) swap(la, lb);
		edge[la][lb]++;
	}
	auto digit_num = [](int a){int d = 0; while(a) a /= 10, d++; return d;};
	for(int i=1; i<=n; i++)
	{
		int len = digit_num(i);
		vid[len] = i;
		ver[len]++;
	}
	m = digit_num(n);
}

bool check()
{
	for(int s=1; s<mov(m)-1; s++)
	{
		int lft = 0, rgt = 0;
		for(int i=1; i<=m; i++)
		{
			if(s & mov(i-1))
			{
				lft += ver[i];
				for(int j=i; j<=m; j++) rgt += edge[i][j];
				for(int j=1; j<i; j++)
					if(!(s&mov(j-1)))
						rgt += edge[j][i];
			}
		}
		if(lft > rgt) return false;
	}
	return true;
}

void work()
{
	if(!check()) puts("-1");
	else
	{
		in[1]++, vid[1]--, ver[1]--;
		vector<pair<int, int> > ans;
		while(ans.size() < n-1)
		{
			for(int i=1; i<=m; i++)
			{
				if(in[i])
				{
					for(int j=1; j<=m; j++)
					{
						if(edge[min(i, j)][max(i, j)] && ver[j])
						{
							edge[min(i, j)][max(i, j)]--, ver[j]--;
							if(check()) in[j]++, ans.push_back(make_pair(vid[i]+1, vid[j])), vid[j]--;
							else edge[min(i, j)][max(i, j)]++, ver[j]++;
						}
					}
				}
			}
		}
		for(auto i : ans) printf("%d %d\n", i.first, i.second);
	}
}

int main()
{
	input();
	work();
	return 0;
}
