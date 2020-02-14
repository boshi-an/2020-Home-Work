#include <bits/stdc++.h>

using namespace std;

const int MX = 5005;

int n;
char str[MX], tar[MX];

void input()
{
	scanf("%d", &n);
	scanf("%s", str+1);
	scanf("%s", tar+1);
}

vector<int> get_seq(char *s)
{
	vector<int> ret;
	for(int i=1; i<=n+1; i++)
		if(s[i] != s[i-1])
			ret.push_back(i);
	return ret;
}

int calc(vector<int> a, vector<int> b)
{
	int ret = 0;
	for(int i=1; i<=a.size()||i<=b.size(); i++)
	{
		int va = (i>a.size()) ? 1 : a[a.size()-i];
		int vb = (i>b.size()) ? 1 : b[b.size()-i];
		ret += abs(va-vb);
	}
	return ret;
}

void work()
{
	int ans = 1e9;
	vector<int> s0 = get_seq(str), t0 = get_seq(tar), s, t;
	for(int i=(str[n]!=tar[n]); i<=s0.size(); i+=2)
	{
		s = s0, t = t0;
		for(int j=1; j<=i; j++) s.push_back(n+1);
		ans = min(calc(s, t), ans);

		s = s0, t = t0;
		int tmp = 0;
		for(int j=1; j<=i; j++) tmp += abs(n+1-s.back()), s.pop_back();
		/*reverse(s.begin(), s.end());
		reverse(t.begin(), t.end());
		for(auto &x : s) x = n+2-x;
		for(auto &x : t) x = n+2-x;
		for(int j=1; j<=i; j++) s.push_back(n+1);*/
		ans = min(calc(s, t)+tmp, ans);
	}
	printf("%d\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}