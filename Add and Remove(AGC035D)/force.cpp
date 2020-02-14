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

int n;
vector<ll> src;
ll ans = 1231231231231231231;

ll calc(vector<ll> card)
{
	ll sum = accumulate(card.begin(), card.end(), 0);
	for(auto i=0; i+2<card.size(); i++) sum += card[i];
	return sum;
}

void dfs(vector<ll> card)
{
	if(card.size() == 2)
	{
		if(card[0]+card[1] < ans) cout<<card[0]+card[1]<<endl;
		cmin(ans, card[0]+card[1]);
	}
	else if(calc(card) >= ans) return;
	else
	{
		vector<int> pos;
		for(int i=1; i+1<card.size(); i++) pos.push_back(i);
		random_shuffle(pos.begin(), pos.end());
		for(auto p : pos)
		{
			vector<ll> tmp = card;
			tmp[p-1] += tmp[p];
			tmp[p+1] += tmp[p];
			tmp.erase(tmp.begin()+p);
			dfs(tmp);
		}
	}
}

ll greedy(vector<ll> card)
{
	while(card.size() > 2)
	{
		auto p = min_element(card.begin()+1, card.end()-1);
		auto a = p, b = p;
		a--, b++;
		*a += *p;
		*b += *p;
		card.erase(p);
	}
	return card[0]+card[1];
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
	ans = greedy(src);
	dfs(src);
	printf("%lld\n", ans);
	return 0;
}
