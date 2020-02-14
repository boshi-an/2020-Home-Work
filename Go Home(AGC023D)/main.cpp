#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 100005;

template <typename T> void read(T &x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

ll n, s;
int pos[MX];
ll num[MX];

pair<int, ll> calc(int l, int r)
{
	if(s <= pos[l]) return make_pair(pos[r], pos[r]-s);
	else if(s >= pos[r]) return make_pair(pos[l], s-pos[l]);
	else if(l+1 == r)
	{
		if(num[l] >= num[r]) return make_pair(pos[r], (s-pos[l]) + (pos[r]-pos[l]));
		else return make_pair(pos[l], (pos[r]-s) + (pos[r]-pos[l]));
	}
	else if(num[l] >= num[r])
	{
		num[l] += num[r];
		pair<int, ll> ret = calc(l, r-1);
		return  make_pair(pos[r], ret.second+pos[r]-ret.first);
	}
	else
	{
		num[r] += num[l];
		pair<int, ll> ret = calc(l+1, r);
		return  make_pair(pos[l], ret.second+ret.first-pos[l]);
	}
}

int main()
{
	read(n), read(s);
	for(int i=1; i<=n; i++) read(pos[i]), read(num[i]);
	printf("%lld\n", calc(1, n).second);
	return 0;
}