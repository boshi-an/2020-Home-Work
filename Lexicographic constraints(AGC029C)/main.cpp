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

struct NODE
{
	int c, num;

	NODE (const int &c0 = 0, const int &n0 = 0) : c(c0), num(n0) {}
};

int n;
vector<int> len;
vector<NODE> stk;

bool check(int mid)
{
	stk.clear();
	stk.emplace_back(NODE(1, *len.begin()));
	for(int i=1; i<n; i++)
	{
		if(len[i] > len[i-1]) stk.emplace_back(NODE(1, len[i]-len[i-1]));
		else
		{
			int need = len[i-1]-len[i];
			while(need)
			{
				if(need >= stk.back().num) need -= stk.back().num, stk.pop_back();
				else stk.back().num -= need, need = 0;
			}
			int p = stk.size()-1;
			while(p>=0 && stk[p].c==mid) p--;
			if(p < 0) return false;
			else
			{
				int add = 0;
				while(stk.size() > p+1) add += stk.back().num, stk.pop_back();
				NODE tmp = stk.back();
				stk.pop_back();
				if(tmp.num == 1) stk.emplace_back(NODE(tmp.c+1, 1));
				else stk.emplace_back(NODE(tmp.c, tmp.num-1)), stk.emplace_back(NODE(tmp.c+1, 1));
				if(add) stk.emplace_back(NODE(1, add));
			}
		}
	}
	return true;
}

int main()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		int x;
		read(x);
		len.emplace_back(x);
	}
	int l = 1, r = n, mid = 1, ans = 1;
	while(l < r)
	{
		mid = (l+r) / 2;
		if(check(mid)) r = ans = mid;
		else l = ans = mid+1;
	}
	printf("%d\n", ans);
	return 0;
}