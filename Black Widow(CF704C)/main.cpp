#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MX = 100005;
const ll MOD = 1000000007;

template <typename T> void cmin(T &x, const T &y)
{
	if(y < x) x = y;
}

template <typename T> void cmax(T &x, const T &y)
{
	if(y > x) x = y;
}

template <typename T> void add(T &x, const T &y)
{
	x = (x+y) % MOD;
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
int siz[MX];
vector<pii> app[MX];
int fst[MX], nxt[MX*2], v[MX*2], w[MX*2], deg[MX], lnum;

void addeg(int nu, int nv, int nw)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
	w[lnum] = nw;
	deg[nv]++;
}

void input()
{
	read(n), read(m);
	for(int i=1; i<=n; i++)
	{
		int x;
		read(siz[i]);
		for(int j=1; j<=siz[i]; j++)
		{
			read(x);
			if(x > 0) app[x].push_back(make_pair(i, 0));
			else app[-x].push_back(make_pair(i, 1));
		}
	}
}

bool vis[MX];
ll f[MX][2][2][2];
int cur;

void calc(vector<int> seq)
{
	cur = 1;
	for(auto wi : seq)
	{
		cur++;
		memset(f[cur], 0, sizeof(f[cur]));
		for(int l=0; l<2; l++)
			for(int r=0; r<2; r++)
				for(int c=0; c<2; c++)
					for(int a=0; a<2; a++)
						add(f[cur][l][a][c^((r^wi)|a)], f[cur-1][l][r][c]);
	}
}

void work()
{
	ll ans[2];
	ans[0] = 1, ans[1] = 0;
	for(int i=1; i<=m; i++)
	{
		if(!app[i].size()) ans[0] = ans[0]*2 % MOD, ans[1] = ans[1]*2 % MOD;
		else if(app[i].size() == 2)
		{
			if(app[i][0].first != app[i][1].first)
			{
				addeg(app[i][0].first, app[i][1].first, app[i][0].second^app[i][1].second);
				addeg(app[i][1].first, app[i][0].first, app[i][0].second^app[i][1].second);
			}
			else
			{
				vis[app[i][0].first] = 1;
				if(app[i][0].second == app[i][1].second) ans[0] = ans[1] = (ans[0]+ans[1]) % MOD;
				else swap(ans[0], ans[1]), ans[0] = ans[0]*2 % MOD, ans[1] = ans[1]*2 % MOD;
			}
		}
	}
	for(int i=1; i<=n; i++)
	{
		if(vis[i]) continue;
		if(deg[i] == 1)
		{
			memset(f[1], 0, sizeof(f[1]));
			int x = i;
			if(siz[i] == 1)
			{
				f[1][0][0][0] = 1;
				f[1][1][1][1] = 1;
			}
			else
			{
				f[1][0][0][0] = 1;
				f[1][0][1][1] = 1;
				f[1][1][0][1] = 1;
				f[1][1][1][1] = 1;
			}
			vector<int> val;
			bool flg = 1;
			while(flg)
			{
				vis[x] = 1;
				flg = 0;
				for(int i=fst[x]; i; i=nxt[i])
				{
					int y = v[i];
					if(!vis[y])
					{
						assert(!flg);
						x = y, flg = 1;
						val.push_back(w[i]);
					}
				}
			}
			calc(val);
			ll con[2], tmp[2];
			con[0] = con[1] = 0;
			tmp[0] = tmp[1] = 0;
			for(int l=0; l<2; l++)
				for(int r=0; r<2; r++)
					for(int c=0; c<2; c++)
						if(siz[x] == 2)
							add(con[c], f[cur][l][r][c]);
						else add(con[c^(r^val.back())], f[cur-1][l][r][c]);
			for(int a=0; a<2; a++)
				for(int b=0; b<2; b++)
					add(tmp[a^b], ans[a]*con[b]);
			ans[0] = tmp[0], ans[1] =  tmp[1];
		}
	}
	for(int i=1; i<=n; i++)
	{
		if(deg[i]==2 && !vis[i])
		{
			memset(f[1], 0, sizeof(f[1]));
			int x = i;
			f[1][0][0][0] = 1;
			f[1][0][1][1] = 1;
			f[1][1][0][1] = 1;
			f[1][1][1][1] = 1;
			vector<int> val;
			int last_w = 0;
			bool flg = 1;
			while(flg)
			{
				vis[x] = 1;
				flg = 0;
				for(int i=fst[x]; i; i=nxt[i])
				{
					int y = v[i];
					if(!vis[y])
					{
						if(!flg)
						{
							x = y, flg = 1;
							val.push_back(w[i]);
						}
						else last_w = w[i];
					}
				}
			}
			calc(val);
			ll con[2], tmp[2];
			con[0] = con[1] = 0;
			tmp[0] = tmp[1] = 0;
			for(int l=0; l<2; l++)
				for(int r=0; r<2; r++)
					for(int c=0; c<2; c++)
						if((l^r) == last_w)
							add(con[c], f[cur][l][r][c]);
			for(int a=0; a<2; a++)
				for(int b=0; b<2; b++)
					add(tmp[a^b], ans[a]*con[b]);
			ans[0] = tmp[0], ans[1] =  tmp[1];
		}
		else if(!vis[i] && deg[i]==0 && siz[i]==1) ans[0] = ans[1] = (ans[0]+ans[1]) % MOD;
		else if(!vis[i] && deg[i]==0 && siz[i]==2)
		{
			ll con[2], tmp[2];
			con[0] = 1, con[1] = 3;
			tmp[0] = tmp[1] = 0;
			for(int a=0; a<2; a++)
				for(int b=0; b<2; b++)
					add(tmp[a^b], ans[a]*con[b]);
			ans[0] = tmp[0], ans[1] =  tmp[1];
		}
	}
	printf("%lld\n", ans[1]);
}

int main()
{
	input();
	work();
	return 0;
}

/*
10 71995
2 -32701 59200
1 3140
2 38963 -22093
2 30741 -5776
2 3140 -32701
2 -23558 21596
1 22093
2 16008 -30741
2 5776 16008
2 21596 11974

ans:742866463
*/