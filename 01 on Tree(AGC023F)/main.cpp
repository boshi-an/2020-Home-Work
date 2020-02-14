#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 200002;
const ll oo = 1000000;

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

struct NODE
{
	int id, c0, c1;

	NODE (const int &i0 = 0, const int &x = 0, const int &y = 0) : id(i0), c0(x), c1(y) {}

	bool operator < (const NODE &t) const {return oo*c0*t.c1+id > oo*t.c0*c1+t.id;}
};

struct UNION
{
	int fa[MX];

	UNION (int n = 0) {for(int i=1; i<=n; i++) fa[i] = i;}

	int id(int x)
	{
		return (x==fa[x]) ? (x) : (fa[x]=id(fa[x]));
	}
};

int n, fa[MX], val[MX];
multiset<NODE> que;
int c0[MX], c1[MX], t[MX], nxt[MX];

void input()
{
	read(n);
	for(int i=2; i<=n; i++) read(fa[i]);
	for(int i=1; i<=n; i++) read(val[i]);
}

void work()
{
	UNION ufs(n);
	for(int i=1; i<=n; i++) t[i] = i;
	for(int i=2; i<=n; i++) que.insert(NODE(i, c0[i] = (val[i]==0), c1[i] = (val[i]==1)));
	for(int i=1; i<n; i++)
	{
		NODE tmp = *que.begin();
		que.erase(que.begin());
		int f = ufs.id(fa[tmp.id]);
		nxt[t[f]] = tmp.id;
		ufs.fa[tmp.id] = f;
		t[f] = t[tmp.id];
		if(f != 1)
		{
			que.erase(que.find(NODE(f, c0[f], c1[f])));
			c0[f] += c0[tmp.id], c1[f] += c1[tmp.id];
			que.insert(NODE(f, c0[f], c1[f]));
		}
	}
	int x = 1, tot1 = 0;
	ll rev = 0;
	while(x)
	{
		if(val[x] == 0) rev += tot1;
		else tot1++;
		x = nxt[x];
	}
	printf("%lld\n", rev);
}

int main()
{
	input();
	work();
	return 0;
}