#include <bits/stdc++.h>

using namespace std;

const int MX = 800005;

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
	int fst[MX], nxt[MX], v[MX], w[MX], lnum;

	GRAPH () {memset(fst, 0xff, sizeof(fst)), lnum = -1;}

	void addeg(int nu, int nv, int nw)
	{
		nxt[++lnum] = fst[nu];
		fst[nu] = lnum;
		v[lnum] = nv;
		w[lnum] = nw;
	}

	int dep[MX],q[MX];
	int bfs(int frm,int to)
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
		return (dep[to]>=0);
	}

	int cur[MX];
	int dinic(int x,int mn,int tar)
	{
		if(x==tar)return mn;
		int y,a,now=0;
		for(int &i=cur[x];i!=-1;i=nxt[i])
		{
			y=v[i];
			if(w[i]&&dep[y]==dep[x]+1)
			{
				a=dinic(y,min(mn-now,w[i]),tar);
				now+=a;
				w[i]-=a,w[i^1]+=a;
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
} G;

int n;
int P[MX], Q[MX];

void input()
{
	read(n);
	for(int i=1; i<=n; i++) read(P[i]), P[i]++;
	for(int i=1; i<=n; i++) read(Q[i]), Q[i]++;
}

int idp[MX], idq[MX], vp[MX], vq[MX], cp, cq;

void build()
{
	for(int i=1; i<=n; i++)
	{
		if(!vp[i])
		{
			cp++;
			int x = i;
			while(!vp[x])
			{
				vp[x] = 1;
				idp[x] = cp;
				x = P[x];
			}
		}
		if(!vq[i])
		{
			cq++;
			int x = i;
			while(!vq[x])
			{
				vq[x] = 1;
				idq[x] = cq;
				x = Q[x];
			}
		}
	}
	int s = cp+cq+1, t = cp+cq+2;
	int ans = n;
	for(int i=1; i<=n; i++)
	{
		int ip = idp[i], iq = idq[i];
		if(P[i]==i && Q[i]==i)
		{
			ans--;
		}
		else if(P[i]==i && Q[i]!=i)
		{
			G.addeg(s, cp+iq, 1);
			G.addeg(cp+iq, s, 0);
		}
		else if(P[i]!=i && Q[i]==i)
		{
			G.addeg(ip, t, 1);
			G.addeg(t, ip, 0);
		}
		else if(P[i] != Q[i])
		{
			G.addeg(ip, cp+iq, 1);
			G.addeg(cp+iq, ip, 0);
		}
		else
		{
			G.addeg(ip, cp+iq, 1);
			G.addeg(cp+iq, ip, 1);
		}
	}
	printf("%d\n", ans-G.mxflow(s, t));
}

int main()
{
	input();
	build();
	return 0;
}
