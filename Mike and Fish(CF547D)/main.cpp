#include <bits/stdc++.h>

using namespace std;

const int MX = 1000005;

int n;
int fst[MX], nxt[MX], v[MX], deg[MX], lnum;

template<typename T> void read(T &x)
{
	char c = getchar(); x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
}

void init()
{
	memset(fst, 0xff, sizeof(fst));
	lnum = -1;
}

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
	deg[nv]++;
}

bool vis[MX];
bool usd[MX];

void euler_path(int x)
{
	vis[x] = 1;
	for(int i=fst[x]; i; i=nxt[i])
	{
		int ni = nxt[i];
		fst[x] = ni;
		if(!vis[v[i]]) euler_path(v[i]), usd[i] = 1;
	}
}

void input()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		int x, y;
		read(x), read(y);
		addeg(x, 2e5+y);
		addeg(2e5+y, x);
	}
	vector<int> odd;
	for(int i=1; i<=4e5; i++)
		if(deg[i] & 1)
			odd.push_back(i);
	for(int i=0; i<odd.size(); i+=2)
		addeg(odd[i], odd[i+1]), addeg(odd[i+1], odd[i]);
	for(int i=1; i<=4e5; i++)
		if(!vis[i])
			euler_path(i);
	for(int i=0; i<n*2; i+=2)
		if(usd[i]) putchar('r');
		else putchar('b');
	putchar('\n');
}

int main()
{
	init();
	input();
	return 0;
}