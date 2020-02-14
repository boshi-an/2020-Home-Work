#include <bits/stdc++.h>

using namespace std;

const int MX = 200005;
const int ME = 800005;
const int oo = 123123123;

template<typename T> void cmax(T &x, const T &y)
{
	if(y > x) x = y;
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

struct EDGE
{
	int v, c;

	EDGE (const int &v0 = 0, const int &c0 = 0) : v(v0), c(c0) {}
};

struct GRAPH	//板子
{
	EDGE e[ME];
	int fst[MX], nxt[ME], lnum;
	int dep[MX],q[MX];          //分层网络的深度，bfs 的队列

	void addeg(int nu, int nv, int nc)
	{
		nxt[++lnum] = fst[nu];
		fst[nu] = lnum;
		e[lnum] = EDGE(nv, nc);
	}

	void init()
	{
		memset(fst, 0xff, sizeof(fst));
		lnum = -1;
	}

	int bfs(int frm,int to)     //生成分层网络
	{
		int h=0,t=1,x,y;
		memset(dep,0xff,sizeof(dep));
		q[++h]=frm;
		dep[frm]=0;
		while(h>=t)
		{
			x=q[t++];
			for(int i=fst[x];i!=-1;i=nxt[i])
			{
				y=e[i].v;
				if(dep[y]==-1&&e[i].c)
				{
					dep[y]=dep[x]+1;
					q[++h]=y;
				}
			}
		}
		return (dep[to]>=0);    //返回分层网络是否成功生成
	}

	int cur[MX];                //当前弧优化的记录数组
	int dinic(int x,int mn,int tar)
	{
		if(x==tar)return mn;
		int y,a,now=0;
		for(int &i=cur[x];i!=-1;i=nxt[i])   //"int &i="这一句是当前弧优化的核心
		{
			y=e[i].v;
			if(e[i].c&&dep[y]==dep[x]+1)
			{
				a=dinic(y,min(mn-now,e[i].c),tar);
				now+=a;                     //整体流量优化，记录当前节点往下流的最大流量后再返回
				e[i].c-=a,e[i^1].c+=a;      //帮助 dinic 反悔
				if(mn==now)return now;
			}
		}
		return now;
	}

	int mxflow(int s, int t)
	{
		int tot=0;
		while(bfs(s,t))
		{
			memmove(cur,fst,sizeof(fst));
			tot+=dinic(s,+oo,t);
		}
		return tot;
	}
} G;

int n;
int global_s, global_t;

void input()
{
	G.init();
	read(n);
	global_s = n*2, global_t = n*2+1;
	for(int i=1; i<n; i++)
	{
		int c, x;
		read(c);
		for(int j=1; j<=c; j++)
		{
			read(x);
			G.addeg(x, n+i, 1);
			G.addeg(n+i, x, 0);
		}
	}
	for(int i=1; i<=n; i++)
	{
		G.addeg(global_s, i, 1);
		G.addeg(i, global_s, 0);
	}
	for(int i=1; i<n; i++)
	{
		G.addeg(n+i, global_t, 1);
		G.addeg(global_t, n+i, 0);
	}
}

int frm[MX];
pair<int, int> ans[MX];

void dfs(int x, int f)
{
	frm[x] = f;
	for(int i=G.fst[x]; ~i; i=G.nxt[i])
		if(G.e[i].c && !frm[G.e[i].v])
			dfs(G.e[i].v, x);
}

void work()
{
	if(G.mxflow(global_s, global_t) != n-1) puts("-1");
	else
	{
		int root = 0;
		for(int i=G.fst[global_s]; ~i; i=G.nxt[i])
			if(G.e[i].c)
				root = G.e[i].v;
		dfs(root, -1);
		bool fucked = 0;
		for(int i=1; i<=n; i++)
			if(!frm[i])
				fucked = 1;
		if(fucked) puts("-1");
		else
		{
			for(int i=1; i<=n; i++)
				if(i != root)
					ans[frm[i]-n] = make_pair(i, frm[frm[i]]);
			for(int i=1; i<n; i++)
				printf("%d %d\n", ans[i].first, ans[i].second);
		}
	}
}

int main()
{
	input();
	work();
	return 0;
}