#include <bits/stdc++.h>

using namespace std;

template<typename T> void cmax(T &x, const T &y)
{
	if(y > x) x = y;
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

int n, k;
vector<int> p, q;

vector<int> operator + (vector<int> a, vector<int> b)
{
	vector<int> c(n+1);
	for(int i=1; i<=n; i++) c[i] = a[b[i]];
	return c;
}

vector<int> operator * (vector<int> a, int num)
{
	vector<int> c(n+1), vis(n+1);
	for(int i=1; i<=n; i++)
	{
		if(vis[i]) continue;
		int x = i;
		vector<int> loop;
		while(!vis[x])
		{
			loop.push_back(x);
			vis[x] = 1;
			x = a[x];
		}
		for(int j=0; j<loop.size(); j++) c[loop[j]] = a[loop[(j+num-1+loop.size())%loop.size()]];
	}
	return c;
}

vector<int> rev(vector<int> a)
{
	vector<int> c(n+1);
	for(int i=1; i<=n; i++) c[a[i]] = i;
	return c;
}

void print(vector<int> a)
{
	for(int i=1; i<=n; i++) printf("%d ", a[i]);
	putchar('\n');
}

int main()
{
	read(n), read(k), k--;
	p.resize(n+1), q.resize(n+1);
	for(int i=1; i<=n; i++) read(p[i]);
	for(int i=1; i<=n; i++) read(q[i]);
	int pre = k/6;
	vector<int> id(n+1);
	for(int i=1; i<=n; i++) id[i] = i;
	auto l = (q+rev(p)+rev(q)+p)*pre;
	switch (k % 6)
	{
	case 0:
		print(l+p+rev(l));
		break;
	case 1:
		print(l+q+rev(l));
		break;
	case 2:
		print(l+q+rev(p)+rev(l));
		break;
	case 3:
		print(l+q+rev(p)+rev(q)+rev(l));
		break;
	case 4:
		print(l+q+rev(p)+rev(q)+p+rev(q)+rev(l));
		break;
	case 5:
		print(l+q+rev(p)+rev(q)+p+p+rev(q)+rev(l));
		break;
	default:
		break;
	}
	return 0;
}