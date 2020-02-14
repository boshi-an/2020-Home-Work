#include <bits/stdc++.h>

using namespace std;

const int MV = 55;
const int ME = 105;
const int MX = 65536;
const double pi = acos(-1);
const double oo = 1e18;

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

struct Z
{
	double r, i;

	Z (const double &r0 = 0, const double &i0 = 0) : r(r0), i(i0) {}
	Z operator + (const Z &t) const {return Z(r+t.r, i+t.i);}
	Z operator - (const Z &t) const {return Z(r-t.r, i-t.i);}
	Z operator * (const Z &t) const {return Z(r*t.r-i*t.i, i*t.r+r*t.i);}
	Z operator / (const double &t) const {return Z(r/t, i/t);}
};

struct FFT
{
	int rev[MX], b, n;

	void init(int len)
	{
		n = 1, b = 0;
		while(n < len) n *= 2, b += 1;
		for(int i=1; i<n; i++) rev[i] = (rev[i>>1]>>1) | ((i&1)<<(b-1));
	}

	void dft(Z *x, int f)
	{
		for(int i=0; i<n; i++)
			if(i < rev[i])
				swap(x[i], x[rev[i]]);
		for(int i=1; i<n; i<<=1)
		{
			Z wn(cos(pi/i), f*sin(pi/i));
			for(int j=0; j<n; j+=(i<<1))
			{
				Z w(1, 0);
				for(int k=0; k<i; k++)
				{
					Z a = x[j+k], b = x[j+k+i]*w;
					x[j+k] = (a+b);
					x[j+k+i] = (a-b);
					w = w*wn;
				}
			}
		}
		if(f == -1) for(int i=0; i<n; i++) x[i] = x[i] / n;
	}
} F;

struct GRAPH
{
	int fst[MV], nxt[ME], u[ME], v[ME], w[ME], lnum;

	void addeg(int nu, int nv, int nw)
	{
		nxt[++lnum] = fst[nu];
		fst[nu] = lnum;
		v[lnum] = nv;
		w[lnum] = nw;
	}

	priority_queue<pair<int, int> > que;

	void dijkstra(int s, int *dis, int num)
	{
		fill(dis+1, dis+num+1, 1e8);
		dis[s] = 0;
		que.push(make_pair(0, s));
		while(!que.empty())
		{
			auto x = que.top();
			que.pop();
			if(-x.first != dis[x.second]) continue;
			for(int i=fst[x.second]; i; i=nxt[i])
			{
				auto y = make_pair(x.first-w[i], v[i]);
				if(-y.first < dis[y.second])
				{
					dis[y.second] = -y.first;
					que.push(y);
				}
			}
		}
	}
} G , R;

int n, m, tot, pen;
int dis[MV];
double pos[ME][MX], sumpos[ME][MX], fe[ME][MX], fv[MV][MX];

void input()
{
	read(n), read(m), read(tot), read(pen);
	for(int i=1; i<=m; i++)
	{
		int a, b, c;
		read(a), read(b), read(c);
		G.addeg(a, b, c);
		R.addeg(b, a, c);
		for(int j=1; j<=tot; j++)
		{
			int x;
			read(x);
			pos[i][j] = 1.0*x/1e5;
		}
		for(int j=tot; j>=0; j--) sumpos[i][j] = pos[i][j] + sumpos[i][j+1];
	}
	tot++;
}

Z tmp1[MX], tmp2[MX], tmp3[MX];

void calc(int l, int r)
{
	if(l == r)
	{
		for(int x=1; x<n; x++)
			for(int i=G.fst[x]; i; i=G.nxt[i])
				cmin(fv[x][l], fe[i][l]+G.w[i]);
	}
	else
	{
		int mid = (l+r)/2;
		calc(l, mid);
		int len1 = r-l+1, len2 = mid-l+1;
		F.init(len1+len2);
		for(int i=1; i<=m; i++)
		{
			fill(tmp1, tmp1+F.n, Z(0, 0));
			fill(tmp2, tmp2+F.n, Z(0, 0));
			for(int j=1; j<len1; j++) tmp1[j].r = pos[i][j];
			for(int j=0; j<len2; j++) tmp2[j].r = fv[G.v[i]][l+j];
			F.dft(tmp1, +1);
			F.dft(tmp2, +1);
			for(int j=0; j<F.n; j++) tmp3[j] = tmp1[j]*tmp2[j];
			F.dft(tmp3, -1);
			for(int j=mid+1; j<=r; j++) fe[i][j] += tmp3[j-l].r;
		}
		calc(mid+1, r);
	}
	
}

void work()
{
	R.dijkstra(n, dis, n);
	for(int i=1; i<=n; i++)
	{
		fv[i][0] = dis[i]+pen;
		if(i != n) for(int j=1; j<=tot; j++) fv[i][j] = 1e18;
	}
	for(int i=1; i<=m; i++)
		for(int j=0; j<=tot; j++)
			fe[i][j] = fv[G.v[i]][0] * sumpos[i][j];
	calc(1, tot);
	printf("%.8lf\n", fv[1][tot]);
}

int main()
{
	input();
	work();
	return 0;
}