#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll MOD = 998244353;

template <typename T> void add(T &x, const T &y)
{
	x = (x+y) % MOD;
}

template <typename T> void read(T &x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

unordered_map<ull, ll> mp;

ull get_hash(string s)
{
	ull h = 0;
	for(auto x : s) h = h*31 + x;
	return h;
}

string str_and(string s, string t)
{
	string ret(s.length(), '0');
	assert(s.length() == t.length());
	for(int i=0; i<s.length(); i++)
		if(s[i]=='1' && t[i]=='1')
			ret[i] = '1';
	return ret;
}

ll calc(string s)
{
	if(!s.length()) return 1;
	else if(s.length() == 1) return s[0]-'0'+1;
	ull h = get_hash(s);
	if(mp.count(h)) return mp[h];
	ll ret = calc(s.substr(1)) * (s[0]-'0'+1) % MOD;
	for(int i=1; i*2<=s.length(); i++)
	{
		string ns = s.substr(0, i);
		for(int j=2; i*j<=s.length(); j++)
		{
			ns = str_and(ns, s.substr(i*(j-1), i));
			add(ret, calc(ns) * calc(s.substr(i*j, s.length()-i*j)));
		}
	}
	mp[h] = ret;
	return ret;
}

int main()
{
	string s;
	cin >> s;
	cout << calc(s) << endl;
	return 0;
}