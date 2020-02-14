#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MX = 10011;
const int oo = 2000000002;

int fst[MX],nxt[MX*2],u[MX*2],v[MX*2],w[MX*2],c[MX*2],lnum;

void init()
{
    memset(fst,0xff,sizeof(fst));
    lnum=-1;
}

void addeg(int nu,int nv,int nw,int nc)
{
    lnum++;
    nxt[lnum]=fst[nu];
    fst[nu]=lnum;
    u[lnum]=nu;
    v[lnum]=nv;
    w[lnum]=nw;
    c[lnum]=nc;

	lnum++;
	nxt[lnum]=fst[nv];
	fst[nv]=lnum;
    u[lnum]=nv;
    v[lnum]=nu;
    w[lnum]=0;
    c[lnum]=-nc;
}

ll dist[MX];
int book[MX],q[MX],pre[MX],frnt,rare,now;
void spfa(int frm,int to,int *flow,ll *cost)
{
	memset(dist,0x9f,sizeof(dist));
    frnt=rare=1;
    q[rare]=frm;
    dist[frm]=0;
    book[frm]=1;
    pre[frm]=-1;
    while(frnt>=rare)
    {
        book[q[rare]]=0;
        now=q[rare++];
        for(int i=fst[now];i!=-1;i=nxt[i])
        {
            if(w[i]>0&&dist[v[i]]<dist[now]+c[i])
            {
                dist[v[i]]=dist[now]+c[i];
                pre[v[i]]=i;
                if(book[v[i]]==0)
                {
                    book[v[i]]=1;
                    q[++frnt]=v[i];
                }
            }
        }
    }
    int mxfl=+oo;
	ll mxcs=0;
    now=pre[to];
    while(now!=-1)
    {
        mxfl=min(mxfl,w[now]);
        mxcs+=c[now];
        now=pre[u[now]];
    }
    now=pre[to];
    while(now!=-1)
    {
        w[now]-=mxfl;
        w[now^1]+=mxfl;
        now=pre[u[now]];
    }
    *flow+=mxfl;
    *cost+=mxcs*mxfl;
}

void maxcost(int from,int to,int need)
{
    int flow=0;
	ll cost=0;
    while(flow<need) spfa(from,to,&flow,&cost);
	printf("%lld\n",cost);
}

int n, s;
int rx[MX],ry[MX],rc[MX],bx[MX],by[MX],bc[MX];
int S,T,V1,V2,V3,V4;

void input()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",rx+i,ry+i,rc+i),s+=rc[i];
	for(int i=1;i<=n;i++) scanf("%d%d%d",bx+i,by+i,bc+i);
}

void build()
{
	S=2*n+1,T=2*n+6;
	V1=2*n+2,V2=V1+1,V3=V2+1,V4=V3+1;
	for(int i=1;i<=n;i++)
	{
		addeg(S,i,rc[i],0);
		addeg(i,V1,rc[i],-rx[i]-ry[i]);
		addeg(i,V2,rc[i],+rx[i]-ry[i]);
		addeg(i,V3,rc[i],+rx[i]+ry[i]);
		addeg(i,V4,rc[i],-rx[i]+ry[i]);
		addeg(V1,n+i,bc[i],+bx[i]+by[i]);
		addeg(V2,n+i,bc[i],-bx[i]+by[i]);
		addeg(V3,n+i,bc[i],-bx[i]-by[i]);
		addeg(V4,n+i,bc[i],+bx[i]-by[i]);
		addeg(n+i,T,bc[i],0);
	}
}

int main()
{
    init();
	input();
	build();
	maxcost(S,T,s);
    return 0;
}