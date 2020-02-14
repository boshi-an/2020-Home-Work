#include <bits/stdc++.h>

using namespace std;

const int MX = 2005;

int n, m;
int fst[MX], nxt[MX*2], v[MX*2], lnum;
vector<pair<int, int> > ori;

template <typename T> void read(T &x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
}

void input()
{
	read(n), read(m);
	for(int i=1; i<n; i++)
	{
		int a, b;
		read(a), read(b);
		addeg(a, b);
		addeg(b, a);
	}
	for(int i=1; i<=m; i++)
	{
		pair<int, int> tmp;
		read(tmp.first), read(tmp.second);
		ori.push_back(tmp);
	}
}

int vis[MX];

vector<int> solve(vector<int> rem, vector<int> fa, vector<pair<int, int> > qur)
{
	if(rem.size() == 0) return {};
	int x = rem.back();
	rem.pop_back();
	vector<pair<int, int> > nq, frm(qur.size());
	int lst = -1;
	for(int i=0; i<qur.size(); i++)
	{
		auto t = qur[i];
		if(t.first == t.second) continue;
		else if(t.first == x)
		{
			if(lst == -1) lst = i;
			else if(qur[lst].first == x)
			{
				frm[lst] = make_pair(nq.size(), -1);
				frm[i] = make_pair(nq.size(), +1);
				nq.push_back(make_pair(qur[lst].second, t.second));
				lst = -1;
			}
			else if(qur[lst].second == x)
			{
				frm[lst] = make_pair(nq.size(), +1);
				frm[i] = make_pair(nq.size(), +1);
				nq.push_back(make_pair(qur[lst].first, t.second));
				lst = -1;
			}
		}
		else if(t.second == x)
		{
			if(lst == -1) lst = i;
			else if(qur[lst].first == x)
			{
				frm[lst] = make_pair(nq.size(), -1);
				frm[i] = make_pair(nq.size(), -1);
				nq.push_back(make_pair(qur[lst].second, t.first));
				lst = -1;
			}
			else if(qur[lst].second == x)
			{
				frm[lst] = make_pair(nq.size(), +1);
				frm[i] = make_pair(nq.size(), -1);
				nq.push_back(make_pair(qur[lst].first, t.first));
				lst = -1;
			}
		}
		else
		{
			frm[i] = make_pair(nq.size(), +1);
			nq.push_back(t);
		}
	}
	if(lst != -1)
	{
		if(qur[lst].first == x)
		{
			frm[lst] = make_pair(nq.size(), +1);
			nq.push_back(make_pair(fa[x], qur[lst].second));
		}
		else
		{
			frm[lst] = make_pair(nq.size(), +1);
			nq.push_back(make_pair(qur[lst].first, fa[x]));
		}
	}
	vector<int> way = solve(rem, fa, nq), ret;
	for(int i=0; i<qur.size(); i++)
	{
		if(qur[i].first == qur[i].second) ret.push_back(+1);
		else ret.push_back(frm[i].second * way[frm[i].first]);
	}
	/*cout<<rem.size()+1<<" answer:"<<endl;
	for(int i=0; i<ret.size(); i++)
		if(ret[i] == +1) printf("%d %d\n", qur[i].first, qur[i].second);
		else printf("%d %d\n", qur[i].second, qur[i].first);*/
	return ret;
}

void work()
{
	vector<int> fa(n+1), dep(n+1), seq;
	function<void(int, int)> dfs = [&](int x, int f)
	{
		fa[x] = f;
		dep[x] = dep[f]+1;
		for(int i=fst[x]; i; i=nxt[i])
		{
			int y = v[i];
			if(y != f) dfs(y, x);
		}
		seq.push_back(x);
	};
	dfs(1, 0);
	reverse(seq.begin(), seq.end());
	auto ans = solve(seq, fa, ori);
	//cout<<"answer:"<<endl;
	function<void(int, int)> cover = [&](int x, int y)
	{
		while(x != y)
		{
			if(dep[x] < dep[y]) swap(x, y);
			vis[x]++;
			x = fa[x];
		}
	};
	for(int i=0; i<ori.size(); i++) cover(ori[i].first, ori[i].second);
	int sum = 0;
	for(int i=1; i<=n; i++) sum += min(2, vis[i]);
	printf("%d\n", sum);
	for(int i=0; i<ans.size(); i++)
		if(ans[i] == +1) printf("%d %d\n", ori[i].first, ori[i].second);
		else printf("%d %d\n", ori[i].second, ori[i].first);
}

int main()
{
	input();
	work();
	return 0;
}