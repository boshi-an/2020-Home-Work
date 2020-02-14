#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 100005;
const ll oo = 1e18;

template<typename T> void cmin(T &x, const T &y)
{
	if(y < x) x = y;
}

template<typename T> void read(T &x)
{
	x = 0;
	char c = getchar();
	bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

struct NODE
{
	int x, ida, idb;

	NODE (const int &x0 = 0, const int &ia = 0, const int &ib = 0) : x(x0), ida(ia), idb(ib) {}

	bool operator < (const NODE &t) const {return x<t.x;}
};

int n;
int a[MX], b[MX];

void input()
{
	read(n);
	for(int i=1; i<=n; i++) read(a[i]), read(b[i]);
}

int ha[MX], hb[MX];

ll calc(vector<NODE> seq)
{
	ll sum = 0;
	bool single_a = 1, single_b = 1;
	memset(ha, 0, sizeof(ha));
	memset(hb, 0, sizeof(hb));
	for(auto i : seq) ha[i.ida]++, hb[i.idb]++, sum += i.x;
	for(int i=1; i<=n; i++)
		if(ha[i] && hb[i]) return sum;
		else if(ha[i]) single_b = 0;
		else if(hb[i]) single_a = 0;
	return (single_a||single_b) ? sum : +oo;
}

void work()
{
	vector<NODE> seq, tmp;
	for(int i=1; i<=n; i++)
	{
		seq.push_back(NODE(a[i], i, 0));
		seq.push_back(NODE(b[i], 0, i));
	}
	sort(seq.begin(), seq.end());
	tmp.insert(tmp.end(), seq.begin(), seq.begin()+n);
	ll ans = calc(tmp);
	tmp.pop_back();
	tmp.push_back(*(seq.begin()+n));
	cmin(ans, calc(tmp));
	tmp.pop_back();
	tmp.push_back(*(seq.begin()+n+1));
	cmin(ans, calc(tmp));
	tmp.pop_back(), tmp.pop_back();
	tmp.push_back(*(seq.begin()+n)), tmp.push_back(*(seq.begin()+n-1));
	cmin(ans, calc(tmp));
	printf("%lld\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}