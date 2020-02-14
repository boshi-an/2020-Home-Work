#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 606;

int n, d1, d2;

struct GRAPH
{
	vector<pair<int, int> > dir;
	int col[MX][MX], num[3];

	void bfs(int x, int y)
	{
		queue<pair<int, int> > que;
		que.push(make_pair(x, y));
		col[x][y] = 1;
		while(!que.empty())
		{
			auto a = que.front();
			que.pop();
			for(auto d : dir)
			{
				auto b = a;
				b.first += d.first;
				b.second += d.second;
				if(b.first>=0 && b.first<n*2 && b.second>=0 && b.second<n*2 && !col[b.first][b.second])
				{
					col[b.first][b.second] = 3-col[a.first][a.second];
					num[col[b.first][b.second]]++;
					que.push(b);
				}
			}
		}
	}

	void color()
	{
		for(int i=0; i<n*2; i++)
			for(int j=0; j<n*2; j++)
				if(!col[i][j])
					bfs(i, j);
	}
} G1, G2;

void build(GRAPH &g, int d)
{
	g.dir.clear();
	for(int i=0; i*i<=d; i++)
		for(int j=0; j*j<=d; j++)
			if(i*i + j*j == d)
			{
				g.dir.push_back(make_pair(i, j));
				g.dir.push_back(make_pair(i, -j));
				g.dir.push_back(make_pair(-i, j));
				g.dir.push_back(make_pair(-i, -j));
			}
}

void print()
{
	vector<pair<int, int> > typ[3][3];
	for(int i=0; i<n*2; i++)
		for(int j=0; j<n*2; j++)
			typ[G1.col[i][j]][G2.col[i][j]].push_back(make_pair(i, j));
	for(int i=1; i<=2; i++)
		for(int j=1; j<=2; j++)
			if(typ[i][j].size() >= n*n)
			{
				while(typ[i][j].size() > n*n) typ[i][j].pop_back();
				for(auto it : typ[i][j]) printf("%d %d\n", it.first, it.second);
				return;
			}
}

int main()
{
	scanf("%d%d%d", &n, &d1, &d2);
	build(G1, d1);
	build(G2, d2);
	G1.color();
	G2.color();
	print();
	return 0;
}