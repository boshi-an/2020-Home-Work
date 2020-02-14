#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 100005;

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

int n, q;
int fa[MX];
int deg[MX];
ll mass[MX];
ll self_son[MX];	//contribution from vertex it self and its sons

ll for_others(int i)
{
	return mass[i]/(deg[i]+1);
}

ll for_self(int i)
{
	return mass[i]-for_others(i)*deg[i];
}

struct SONS
{
	struct cmp
	{
		bool operator () (int a, int b) const
		{
			if(self_son[a] != self_son[b]) return self_son[a] < self_son[b];
			else return a < b;
		}
	};
	set<int, cmp> s;
	void most(vector<int> &ret)
	{
		if(!s.size()) return;
		else if(s.size() == 1) ret.push_back(*s.begin());
		else ret.push_back(*s.begin()), ret.push_back(*s.rbegin());
	}
} son[MX];

multiset<ll> global;

void input()
{
	read(n), read(q);
	for(int i=1; i<=n; i++) read(mass[i]);
	for(int i=1; i<=n; i++) read(fa[i]), deg[i]++, deg[fa[i]]++;
}

ll get_sum(int x)
{
	return self_son[x]+for_others(fa[x]);
}

void build()
{
	for(int i=1; i<=n; i++)
	{
		self_son[i] += for_self(i);
		self_son[fa[i]] += for_others(i);
	}
	for(int i=1; i<=n; i++) son[fa[i]].s.insert(i);
	for(int i=1; i<=n; i++)
	{
		vector<int> most;
		son[i].most(most);
		for(auto j : most) global.insert(get_sum(j));
	}
}

void work()
{
	for(int i=1; i<=q; i++)
	{
		int op;
		read(op);
		if(op == 1)
		{
			vector<int> most;
			int a, b, c;
			read(a), read(c), b = fa[a];
			
			most.clear();
			son[b].most(most);
			son[c].most(most);
			son[fa[b]].most(most);
			son[fa[c]].most(most);
			son[fa[fa[b]]].most(most);
			son[fa[fa[c]]].most(most);
			//for(int j=1; j<=n; j++) son[j].most(most);
			sort(most.begin(), most.end());
			most.erase(unique(most.begin(), most.end()), most.end());
			for(auto x : most) global.erase(global.find(get_sum(x)));

			son[b].s.erase(a);
			son[fa[b]].s.erase(b);
			son[fa[c]].s.erase(c);
			son[fa[fa[b]]].s.erase(fa[b]);
			son[fa[fa[c]]].s.erase(fa[c]);
			self_son[fa[b]] -= for_others(b);
			self_son[fa[c]] -= for_others(c);
			self_son[b] -= for_others(a);
			self_son[b] -= for_self(b);
			self_son[c] -= for_self(c);
			deg[b]--;

			fa[a] = c;

			deg[c]++;
			self_son[c] += for_self(c);
			self_son[b] += for_self(b);
			self_son[c] += for_others(a);
			self_son[fa[b]] += for_others(b);
			self_son[fa[c]] += for_others(c);
			son[fa[fa[b]]].s.insert(fa[b]);
			son[fa[fa[c]]].s.insert(fa[c]);
			son[fa[b]].s.insert(b);
			son[fa[c]].s.insert(c);
			son[c].s.insert(a);

			most.clear();
			son[b].most(most);
			son[c].most(most);
			son[fa[b]].most(most);
			son[fa[c]].most(most);
			son[fa[fa[b]]].most(most);
			son[fa[fa[c]]].most(most);
			//for(int j=1; j<=n; j++) son[j].most(most);
			sort(most.begin(), most.end());
			most.erase(unique(most.begin(), most.end()), most.end());
			for(auto x : most) global.insert(get_sum(x));
		}
		else if(op == 2)
		{
			int x;
			read(x);
			printf("%lld\n", get_sum(x));
		}
		else
		{
			printf("%lld %lld\n", *global.begin(), *global.rbegin());
		}
	}
}

int main()
{
	input();
	build();
	work();
	return 0;
}