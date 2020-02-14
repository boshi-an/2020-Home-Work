#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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

int n, fa[100005], dep[100005];
map<ll, pair<int, int> > st;
vector<pair<int, int> > edge;
vector<int> seq;

int main()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		ll d;
		read(d);
		st.insert(make_pair(d, make_pair(1, i)));
	}
	for(int i=1; i<n; i++)
	{
		auto x = *st.rbegin();
		seq.push_back(x.second.second);
		st.erase(--st.end());
		ll y = x.first-(n-x.second.first)+x.second.first;
		auto it = st.find(y);
		if(it == st.end()) {printf("-1\n"); return 0;}
		else
		{
			it->second.first += x.second.first;
			fa[x.second.second] = it->second.second;
			edge.emplace_back(x.second.second, it->second.second);
		}
	}
	ll sum = 0;
	for(int i=seq.size()-1; i>=0; i--) dep[seq[i]] = dep[fa[seq[i]]]+1, sum += dep[seq[i]];
	if(sum != st.begin()->first) puts("-1");
	else for(auto i : edge) printf("%d %d\n", i.first, i.second);
	return 0;
}
