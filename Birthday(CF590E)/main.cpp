#include <bits/stdc++.h>

using namespace std;

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

const int oo = 123123123;
const int ME = 1127000;
const int ML = 10000005;
const int MX = 755;
const int MV = 1505;

struct AC
{
	int cnt, rot, usd;
	int son[ML][2], fal[ML], near[ML];
	vector<int> app[ML];

	AC () {cnt = rot = 1, usd = 0;}

	void insert(string str, int id)
	{
		int x = rot;
		for(auto c : str)
		{
			if(!son[x][c-'a']) son[x][c-'a'] = ++cnt;
			x = son[x][c-'a'];
		}
		app[x].push_back(id);
	}

	void build()
	{
		queue<int> que;
		fal[rot] = rot;
		for(int i=0; i<2; i++)
			if(!son[rot][i]) son[rot][i] = rot;
			else fal[son[rot][i]] = rot, que.push(son[rot][i]);
		while(!que.empty())
		{
			int x = que.front();
			que.pop();
			if(app[x].size()) near[x] = x;
			else near[x] = near[fal[x]];
			for(int i=0; i<2; i++)
				if(son[x][i]) fal[son[x][i]] = son[fal[x]][i], que.push(son[x][i]);
				else son[x][i] = son[fal[x]][i];
		}
	}

	void match(string str, bool *tar)
	{
		int x = rot;
		for(auto c : str)
		{
			for(auto i : app[near[x]]) tar[i] = 1;
			for(auto i : app[near[fal[x]]]) tar[i] = 1;
			x = son[x][c-'a'];
		}
		for(auto i : app[near[x]]) tar[i] = 1;
		for(auto i : app[near[fal[x]]]) tar[i] = 1;
	}
} A;

struct EDGE
{
	int v, c;

	EDGE (const int &v0 = 0, const int &c0 = 0) : v(v0), c(c0) {}
};

struct GRAPH	//板子
{
	EDGE e[ME];
	int fst[MV], nxt[ME], lnum;
	int dep[MV],q[MV];          //分层网络的深度，bfs 的队列

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

	int cur[MV];                //当前弧优化的记录数组
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
string str[MX];
bool contain[MX][MX];

void input()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		cin >> str[i];
		A.insert(str[i], i);
	}
}

void work()
{
	G.init();
	A.build();
	for(int i=1; i<=n; i++) A.match(str[i], contain[i]);
	for(int k=1; k<=n; k++)
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				contain[i][j] |= (contain[i][k]&contain[k][j]);
	int src = n*2+1, tar = n*2+2;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(i!=j && contain[i][j])
			{
				//cout<<i<<" "<<j<<endl;
				G.addeg(i, n+j, 1), G.addeg(n+j, i, 0);
			}
	for(int i=1; i<=n; i++)
	{
		G.addeg(src, i, 1), G.addeg(i, src, 0);
		G.addeg(n+i, tar, 1), G.addeg(tar, n+i, 0);
	}
	printf("%d\n", n-G.mxflow(src, tar));
	//for(int i=1; i<=n; i++) cout<<G.dep[i]<<" "<<G.dep[i+n]<<endl;
	for(int i=1; i<=n; i++)
		if(G.dep[i]!=-1 && G.dep[n+i]==-1)
			printf("%d ", i);
	putchar('\n');
}

int main()
{
	input();
	work();
	return 0;
}

/*
5
abab
aba
aabab
ababb
bab
*/