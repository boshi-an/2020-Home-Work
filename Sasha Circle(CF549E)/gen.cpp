#include <bits/stdc++.h>

using namespace std;

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

const int MX = 10000;

set<pair<int, int> > mp;

pair<int, int> getp()
{
	int x = rand()%(2*MX)-MX, y = rand()%(2*MX)-MX;
	while(mp.count(make_pair(x, y))) x = rand()%(2*MX)-MX, y = rand()%(2*MX)-MX;
	mp.insert(make_pair(x, y));
	return make_pair(x, y);
}

int main()
{
	int sed;
	read(sed);
	srand(sed);
	int n = 5, m = 5;
	printf("%d %d\n", n, m);
	for(int i=1; i<=n; i++)
	{
		pair<int, int> tmp = getp();
		printf("%d %d\n", tmp.first, tmp.second);
	}
	for(int i=1; i<=m; i++)
	{
		pair<int, int> tmp = getp();
		printf("%d %d\n", tmp.first, tmp.second);
	}
	return 0;
}
