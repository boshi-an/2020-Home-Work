#include <bits/stdc++.h>

using namespace std;

const int MX = 2005;

int n;
int fst[MX], nxt[MX*2], v[MX*2], lnum;
char str[MX];

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
}

void input()
{
	scanf("%d", &n);
	scanf("%s", str+1);
	for(int i=1; i<n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addeg(a, b);
		addeg(b, a);
	}
}

int sdp[MX], sum[MX];
int mn[MX], mx[MX];

void dfs(int x, int f)
{
	sdp[x] = 0;
	if(str[x] == '1') sum[x] = 1;
	else sum[x] = 0;
	mn[x] = mx[x] = 0;
	for(int i=fst[x]; i; i=nxt[i])
		if(v[i] != f)
		{
			int y = v[i];
			dfs(y, x);
			mn[y] += sum[y];
			mx[y] += sum[y];
			if(mx[x] < mn[y]) mn[x] = mn[y]-mx[x];
			else if(mx[y] < mn[x]) mn[x] = mn[x]-mx[y];
			else mn[x] = 0;
			mx[x] = mx[x] + mx[y];
			sum[x] += sum[y];
			sdp[x] += sdp[y]+sum[y];
		}
}

void work()
{
	int ans = MX*MX;
	for(int i=1; i<=n; i++)
	{
		dfs(i, 0);
		if(sdp[i]&1) continue;
		if(mn[i] == 0) ans = min(ans, sdp[i]/2);
	}
	if(ans == MX*MX) printf("-1");
	else printf("%d\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}