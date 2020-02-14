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

const double pi = acos(-1);
vector<pair<int, int> > pot;

vector<pair<int, int> > gcirc(double r, int lim)
{
	vector<pair<int, int> > ret;
	for(double i=0; i<2*pi; i+=2*pi/lim) ret.push_back(make_pair(r*cos(i), r*sin(i)));
	sort(ret.begin(), ret.end());
	return ret;
}

int main()
{
	auto a = gcirc(10000, 10000);
	auto b = gcirc(9998, 10000);
	printf("%d %d\n", a.size(), b.size());
	for(auto i : a) printf("%d %d\n", i.first, i.second);
	for(auto i : b) printf("%d %d\n", i.first, i.second);
	return 0;
}
