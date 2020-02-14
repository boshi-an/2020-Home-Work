#include <bits/stdc++.h>

using namespace std;

const int MS = 1005;
const int MD = 55;
const int MOD = 1000000007;

template<typename T> void add(T &x, const T &y)
{
	x += y;
	x %= MOD;
}

template<typename T> void read(T &x)
{
	x = 0;
	char c = getchar();
	bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

struct AC
{
	int cnt, rot;
	int son[MS*MD/2][10], fal[MS*MD/2];
	bool ed[MS*MD/2];

	AC () {cnt = rot = 1;}

	void insert(string str)
	{
		int x = rot;
		for(auto c : str)
		{
			if(!son[x][c-'0']) son[x][c-'0'] = ++cnt;
			x = son[x][c-'0'];
		}
		ed[x] = 1;
	}

	void build()
	{
		queue<int> que;
		for(auto &y : son[rot])
			if(y) fal[y] = rot, que.push(y);
			else y = 1;
		while(!que.empty())
		{
			int x = que.front();
			que.pop();
			if(ed[x]) for(auto &y : son[x]) y = x;
			else
			{
				for(int i=0; i<10; i++)
					if(son[x][i]) fal[son[x][i]] = son[fal[x]][i], que.push(son[x][i]);
					else son[x][i] = son[fal[x]][i];
			}
		}
	}
} A;

string s, up, dn;
int d;

void input()
{
	cin >> s >> dn >> up;
	d = dn.length();
	while(s.length() >= (d/2)) A.insert(s.substr(s.length()-(d/2), s.length())), s.pop_back();
	A.build();
}

int f[MD][MS*MD/2][2];

int work(string lim, bool eq)
{
	memset(f, 0, sizeof(f));
	f[0][1][1] = 1;
	for(int i=1; i<=d; i++)
	{
		int c = lim[i-1]-'0';
		for(int j=1; j<=A.cnt; j++)
		{
			add(f[i][A.son[j][c]][1], f[i-1][j][1]);
			for(int d=0; d<c; d++) add(f[i][A.son[j][d]][0], f[i-1][j][1]);
			for(int d=0; d<10; d++)	add(f[i][A.son[j][d]][0], f[i-1][j][0]);
		}
	}
	int ans = 0;
	for(int i=1; i<=A.cnt; i++)
		if(A.ed[i])
			add(ans, f[d][i][0] + f[d][i][1]*eq);
	return ans;
}

int main()
{
	input();
	printf("%d\n", (work(up, 1)-work(dn, 0)+MOD) % MOD);
	return 0;
}