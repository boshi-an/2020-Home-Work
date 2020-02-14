#include <bits/stdc++.h>

using namespace std;

const int MX = 105;
const int MV = 205;
const int ME = 22222;

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

struct GRAPH
{
	int fst[MV],nxt[ME],v[ME],w[ME],lnum;
	int dep[MV],q[MV];          //分层网络的深度，bfs 的队列

	void addeg(int nu,int nv,int nw)
	{
		nxt[++lnum] = fst[nu];
		fst[nu] = lnum;
		v[lnum] = nv;
		w[lnum] = nw;
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
				y=v[i];
				if(dep[y]==-1&&w[i])
				{
					dep[y]=dep[x]+1;
					q[++h]=y;
				}
			}
		}
		return (dep[to]>=0);    //返回分层网络是否成功生成
	}

	int cur[MV];                //当前弧优化的记录数组
	int dinic(int x,int mn,int t)
	{
		if(x==t)return mn;
		int y,a,now=0;
		for(int &i=cur[x];i!=-1;i=nxt[i])   //"int &i="这一句是当前弧优化的核心
		{
			y=v[i];
			if(w[i]&&dep[y]==dep[x]+1)
			{
				a=dinic(y,min(mn-now,w[i]),t);
				now+=a;                     //整体流量优化，记录当前节点往下流的最大流量后再返回
				w[i]-=a,w[i^1]+=a;      //帮助 dinic 反悔
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
			tot+=dinic(s,MX,t);
		}
		return tot;
	}

	void init()
	{
		memset(fst, 0xff, sizeof(fst));
		lnum = -1;
	}
} G;

int n, m;
int A[MX][MX], B[MX][MX], C[MX][MX];
int targx[MX*MX], targy[MX*MX];
vector<int> have[MX][MX];

void input()
{
	read(n), read(m);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
		{
			read(A[i][j]);
			targx[A[i][j]] = (A[i][j]-1)/m+1;
			targy[A[i][j]] = (A[i][j]-1)%m+1;
			have[i][targx[A[i][j]]].push_back(A[i][j]);
		}
}

void work()
{
	for(int i=1; i<=m; i++)
	{
		G.init();
		for(int x=1; x<=n; x++)
			for(int y=1; y<=n; y++)
				if(have[x][y].size())
					G.addeg(x, n+y, 1), G.addeg(n+y, x, 0);
		for(int x=1; x<=n; x++)
		{
			G.addeg(n*2+1, x, 1);
			G.addeg(x, n*2+1, 0);
			G.addeg(n+x, n*2+2, 1);
			G.addeg(n*2+2, n+x, 0);
		}
		int f = G.mxflow(n*2+1, n*2+2);
		for(int x=1; x<=n; x++)
		{
			for(int e=G.fst[x]; ~e; e=G.nxt[e])
			{
				if(G.v[e]>n && G.v[e]<=n*2 && !G.w[e])
				{
					assert(have[x][G.v[e]-n].size());
					B[x][i] = have[x][G.v[e]-n].back();
					have[x][G.v[e]-n].pop_back();
				}
			}
		}
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			C[targx[B[i][j]]][j] = B[i][j];
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++) printf("%d ", B[i][j]);
		putchar('\n');
	}
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++) printf("%d ", C[i][j]);
		putchar('\n');
	}
}

int main()
{
	input();
	work();
	return 0;
}
