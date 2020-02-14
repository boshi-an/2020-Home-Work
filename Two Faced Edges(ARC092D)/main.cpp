#include <bits/stdc++.h>

using namespace std;

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

const int MV = 1003;
const int ME = 200005;

int n, m;
vector<int> v[MV];
int frm[ME], tar[ME];
int way1[MV][MV], way2[MV][MV], dir[MV][MV];

void input()
{
	read(n), read(m);
	for(int i=1; i<=m; i++)
	{
		read(frm[i]), read(tar[i]);
		dir[frm[i]][tar[i]]++;
		v[frm[i]].push_back(tar[i]);
	}
}

bool ban[MV];

void dfs(int x, int *s)
{
	for(auto y : v[x])
		if(!s[y] && !ban[y])
		{
			s[y]++;
			dfs(y, s);
		}
}

void work()
{
	for(int x=1; x<=n; x++)
	{
		ban[x] = 1;
		for(int i=0; i<v[x].size(); i++) ban[v[x][i]] = 1, dfs(v[x][i], way1[x]), ban[v[x][i]] = 0;
		for(int i=v[x].size()-1; i>=0; i--) ban[v[x][i]] = 1, dfs(v[x][i], way2[x]), ban[v[x][i]] = 0;
		ban[x] = 0;
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			dir[i][j] += way1[i][j]+way2[i][j];
	for(int i=1; i<=m; i++)
	{
		int a = frm[i], b = tar[i];
		if(dir[a][b]==1 && !dir[b][a]) puts("same");
		else if(dir[a][b]>=2 && !dir[b][a]) puts("diff");
		else if(dir[a][b]==1 && dir[b][a]) puts("diff");
		else if(dir[a][b]>=2 && dir[b][a]) puts("same");
	}
}

int main()
{
	input();
	work();
	return 0;
}