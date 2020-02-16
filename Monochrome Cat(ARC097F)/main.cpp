#include <bits/stdc++.h>

using namespace std;

const int MX = 200005;

int n, root;
char str[MX];
int fst[MX], nxt[MX], v[MX], lnum;

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
}

void input()
{
	scanf("%d", &n);
	for(int i=1; i<n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addeg(a, b);
		addeg(b, a);
	}
	scanf("%s", str+1);
	for(int i=1; i<=n; i++) if(str[i] == 'W') root = i;
}

int sum[MX], deg[MX], ans, mxl;

void dfs(int x, int f)
{
	sum[x] = (str[x] == 'W');
	for(int i=fst[x]; i; i=nxt[i])
	{
		int y = v[i];
		if(y == f) continue;
		dfs(y, x);
		sum[x] += sum[y];
		if(sum[y]) deg[x]++;
	}
	if(sum[x] && f) deg[x]++, ans+=2;
	ans += ((deg[x]&1)^(str[x]=='W'));
}

pair<int, int> calc(int x, int f)
{
	pair<int, int> best(0, - ((deg[x]&1)^1^(str[x]=='W')) + ((deg[x]&1)^(str[x]=='W')));
	for(int i=fst[x]; i; i=nxt[i])
	{
		int y = v[i];
		if(y==f || !sum[y]) continue;
		pair<int, int> tmp = calc(y, x);
		mxl = max(mxl, best.first+tmp.second+1);
		mxl = max(mxl, best.second+tmp.first+1);
		best.first = max(best.first, tmp.first + 1 - (deg[x]&1^1^(str[x]=='W')) + (deg[x]&1^(str[x]=='W')));
		best.second = max(best.second, tmp.second + 1 - (deg[x]&1^1^(str[x]=='W')) + (deg[x]&1^(str[x]=='W')));
	}
	return best;
}

void work()
{
	dfs(root, 0);
	calc(root, 0);
	printf("%d\n", ans-mxl);
}

int main()
{
	input();
	work();
	return 0;
}