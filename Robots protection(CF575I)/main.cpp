#include <bits/stdc++.h>

using namespace std;

const int MX = 5050;
const int MQ = 100005;

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

struct FEN
{
	int sum[MX][MX*2];

	void add(int x, int y, int v)
	{
		for(int i=x+1; i; i-=i&-i)
			for(int j=y+1; j; j-=j&-j)
				sum[i][j] += v;
	}

	int qur(int x, int y)
	{
		int v = 0;
		for(int i=x+1; i<MX; i+=i&-i)
			for(int j=y+1; j<MX*2; j+=j&-j)
				v += sum[i][j];
		return v;
	}

	void reset()
	{
		memset(sum, 0, sizeof(sum));
	}
} F, G;

int n, q;
int px[MQ], py[MQ], pl[MQ], dir[MQ], typ[MQ];
int ans[MQ];

void input()
{
	read(n), read(q);
	for(int i=1; i<=q; i++)
	{
		read(typ[i]);
		if(typ[i] == 1)
		{
			read(dir[i]);
			read(px[i]);
			read(py[i]);
			read(pl[i]);
		}
		else read(px[i]), read(py[i]), pl[i] = i;
	}
}

void work()
{
	cerr<<"a"<<endl;
	for(int i=1; i<=q; i++)
	{
		int x = px[i], y = py[i], l = pl[i];
		if(typ[i]==1 && dir[i]==1)
		{
			F.add(x+l, y-1, -1);
			F.add(x-1, y-1, +1);
			G.add(x+l, x+l+y, +1);
			G.add(x-1, x+l+y, -1);
		}
		else if(typ[i] == 2) ans[l] += F.qur(x, y) + G.qur(x, x+y);
	}
	cerr<<"b"<<endl;
	F.reset(), G.reset();
	for(int i=1; i<=q; i++)
	{
		int x = px[i], y = py[i], l = pl[i];
		if(typ[i]==1 && dir[i]==2)
		{
			F.add(x+l, y, +1);
			F.add(x-1, y, -1);
			G.add(x+l, y-l-x-1+MX, -1);
			G.add(x-1, y-l-x-1+MX, +1);
		}
		else if(typ[i] == 2) ans[l] += F.qur(x, y) + G.qur(x, y-x+MX);
	}
	cerr<<"c"<<endl;
	F.reset(), G.reset();
	for(int i=1; i<=q; i++)
	{
		int x = px[i], y = py[i], l = pl[i];
		if(typ[i]==1 && dir[i]==3)
		{
			F.add(x, y-1, -1);
			F.add(x-l-1, y-1, +1);
			G.add(x, y+l-x+MX, +1);
			G.add(x-l-1, y+l-x+MX, -1);
		}
		else if(typ[i] == 2) ans[l] += F.qur(x, y) + G.qur(x, y-x+MX);
	}
	cerr<<"d"<<endl;
	F.reset(), G.reset();
	for(int i=1; i<=q; i++)
	{
		int x = px[i], y = py[i], l = pl[i];
		if(typ[i]==1 && dir[i]==4)
		{
			F.add(x, y, +1);
			F.add(x-l-1, y, -1);
			G.add(x, x+y-l-1, -1);
			G.add(x-l-1, x+y-l-1, +1);
		}
		else if(typ[i] == 2) ans[l] += F.qur(x, y) + G.qur(x, x+y);
	}
	for(int i=1; i<=q; i++) if(typ[i] == 2) printf("%d\n", ans[pl[i]]);
}

int main()
{
	input();
	work();
	return 0;
}