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

string calca(string s)
{
	vector<int> pa, pb;
	string ret;
	for(int i=0; i<s.length(); i++)
		if(s[i] == 'a') pa.push_back(i);
		else pb.push_back(i);
	int lst = -1;
	for(int i=0; i<pa.size(); i++)
		if(pa[i] > lst) ret += "ab", lst = pb[i];
	return ret;
}

string calcb(string s)
{
	vector<int> pa, pb;
	string ret;
	for(int i=0; i<s.length(); i++)
		if(s[i] == 'a') pa.push_back(i);
		else pb.push_back(i);
	for(int i=0; i<pa.size(); i++)
	{
		string cur;
		auto ia = pa.begin()+i, ib = pb.begin()+i;
		while(ia!=pa.end() && ib!=pb.end())
			if(*ia < *ib) cur.push_back('a'), ia++;
			else cur.push_back('b'), ib++;
		while(ia != pa.end()) cur.push_back('a'), ia++;
		while(ib != pb.end()) cur.push_back('b'), ib++;
		cmax(ret, cur);
	}
	return ret;
}

int main()
{
	int n;
	string str;
	read(n);
	cin >> str;
	int sum = 0;
	string cur, nxt;
	vector<string> ans;
	for(auto c : str)
	{
		if(c == 'a') sum--;
		else sum++;
		cur.push_back(c);
		if(sum == 0)
		{
			if(*cur.begin() == 'a') nxt = calca(cur);
			else nxt = calcb(cur);
			while(ans.size())
			{
				bool greater = 0;
				for(int i=0; i<min(nxt.length(), ans.back().length()); i++)
					if(nxt[i] != ans.back()[i])
					{
						if(ans.back()[i] < nxt[i]) greater = 1;
						break;
					}
				if(greater) ans.pop_back();
				else break;
			}
			ans.push_back(nxt);
			cur.clear();
		}
	}
	for(auto i : ans) cout << i;
	cout << endl;
	return 0;
}