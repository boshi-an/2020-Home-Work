#include <bits/stdc++.h>

using namespace std;

string str;
vector<int> e[2];
vector<vector<int> > seq;
vector<vector<int> > typ[2][2];

int main()
{
	cin >> str;
	for(int i=0; i<str.size(); i++)
	{
		int c = (str[i]=='R');
		if(e[c^1].empty())
		{
			e[c].push_back(seq.size());
			seq.push_back({i});
		}
		else seq[e[c^1].back()].push_back(i), e[c].push_back(e[c^1].back()), e[c^1].pop_back();
	}
	printf("%d\n", seq.size()-1);
	for(auto s : seq) typ[str[s[0]]=='R'][str[s.back()]=='R'].push_back(s);
	while(typ[0][0].size() && typ[1][1].size())
	{
		typ[0][1].push_back({});
		for(auto x : typ[0][0].back()) typ[0][1].back().push_back(x);
		for(auto x : typ[1][1].back()) typ[0][1].back().push_back(x);
		typ[0][0].pop_back();
		typ[1][1].pop_back();
	}
	if(!typ[0][0].size() && !typ[1][1].size() && typ[0][1].size() && typ[1][0].size())
	{
		if(typ[0][1].back().back() > typ[1][0].back().back())
		{
			typ[1][0].back().push_back(typ[0][1].back().back());
			typ[0][1].back().pop_back();
		}
		else
		{
			typ[0][1].back().push_back(typ[1][0].back().back());
			typ[1][0].back().pop_back();
		}
		for(auto s : typ[0][1]) for(auto x : s) printf("%d ", x+1);
		for(auto s : typ[1][0]) for(auto x : s) printf("%d ", x+1);
	}
	else if(typ[0][0].size())
	{
		for(auto s : typ[0][1]) for(auto x : s) printf("%d ", x+1);
		for(auto s : typ[0][0]) for(auto x : s) printf("%d ", x+1);
		for(auto s : typ[1][0]) for(auto x : s) printf("%d ", x+1);
	}
	else
	{
		for(auto s : typ[1][0]) for(auto x : s) printf("%d ", x+1);
		for(auto s : typ[1][1]) for(auto x : s) printf("%d ", x+1);
		for(auto s : typ[0][1]) for(auto x : s) printf("%d ", x+1);
	}
	return 0;
}