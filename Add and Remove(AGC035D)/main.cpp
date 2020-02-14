#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 18;
const ll oo = 1231231231231231231;

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

int n;
vector<ll> src;
map<pair<int, int>, ll> mp[MX][MX];

ll calc(int l, int r, int vl, int vr)
{
	if(l > r) return 0;
	auto it = mp[l][r].find(make_pair(vl, vr));
	if(it != mp[l][r].end()) return it->second;
	ll ret = +oo;
	for(int i=l; i<=r; i++) cmin(ret, calc(l, i-1, vl, vl+vr)+calc(i+1, r, vl+vr, vr)+src[i]*(vl+vr));
	mp[l][r][make_pair(vl,vr)] = ret;
	return ret;
}

int main()
{
	read(n);
	for(int i=0; i<n; i++)
	{
		ll x;
		read(x);
		src.emplace_back(x);
	}
	printf("%lld\n", calc(1, n-2, 1, 1)+src[0]+src[n-1]);
	return 0;
}
