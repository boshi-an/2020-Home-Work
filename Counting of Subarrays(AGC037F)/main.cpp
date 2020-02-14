#include <bits/stdc++.h>

using namespace std;

const int MX = 200005;

typedef long long ll;
typedef pair<int, int> pii;

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

struct NODE
{
	int pre, nxt, wl, wr;

	NODE () {pre = nxt = wl = wr = 0;}
};

ll ans;
NODE chn[MX];
int n, m;
priority_queue<pii, vector<pii>, greater<pii> > que;

void link(int a, int b)
{
	chn[a].nxt = b;
	chn[b].pre = a;
}

bool near(int a, int b)
{
	return (chn[a].nxt == b);
}

void input()
{
	read(n), read(m);
	for(int i=1; i<=n; i++)
	{
		int x;
		read(x);
		chn[i].wl = chn[i].wr = 1;
		link(i, i+1);
		que.push(make_pair(x, i));
	}
}

void calc(int x, vector<int> pos)
{
	int suml = 0;
	for(int i=0; i<pos.size(); i++)
	{
		if(i-m+1 >= 0) suml += chn[pos[i-m+1]].wl;
		ans += 1ll*suml*chn[pos[i]].wr;
	}
	if(pos.size() / m)
	{
		vector<NODE> new_node(pos.size() / m);
		for(int i=0; i<pos.size(); i++)
		{
			if(i >= m-1) new_node[(i+1)/m-1].wr += chn[pos[i]].wr;
			if(pos.size()-i >= m) new_node[new_node.size()-(pos.size()-i)/m].wl += chn[pos[i]].wl;
		}
		suml = 0;
		for(int i=0; i<new_node.size(); i++)
		{
			if(i-m+1 >= 0) suml += new_node[i-m+1].wl;
			ans -= 1ll*suml*new_node[i].wr;
		}
		for(int i=0; i<new_node.size(); i++)
		{
			chn[pos[i]].wl = new_node[i].wl;
			chn[pos[i]].wr = new_node[i].wr;
			que.push(make_pair(x+1, pos[i]));
		}
		link(pos[new_node.size()-1], chn[pos.back()].nxt);
	}
	else link(chn[*pos.begin()].pre, n+1), link(0, chn[pos.back()].nxt);
}

void work()
{
	while(!que.empty())
	{
		int curx = que.top().first;
		vector<int> pos, subpos;
		while(!que.empty() && que.top().first==curx) pos.push_back(que.top().second), que.pop();
		for(auto i : pos)
		{
			if(subpos.empty() || near(subpos.back(), i)) subpos.push_back(i);
			else calc(curx, subpos), subpos.clear(), subpos.push_back(i);
		}
		calc(curx, subpos);
	}
	printf("%lld\n", ans+n);
}

int main()
{
	input();
	work();
	return 0;
}
