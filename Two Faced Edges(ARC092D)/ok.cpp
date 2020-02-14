#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
const int Max_N(1050);
const int Max_M(200050);

namespace io
{
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush (){fwrite (obuf, 1, oS - obuf, stdout);oS = obuf;}
	inline void putc (char x){*oS ++ = x;if (oS == oT) flush ();}
	template <class I>
	inline void gi (I &x) {for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;}
	template <class I>
	inline void print (I x){
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;while(x) qu[++ qr] = x % 10 + '0',  x /= 10;while (qr) putc (qu[qr--]);}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io::gi;
using io::putc;
using io::print;

struct edge
{
	edge(int _t, int _pos) : t(_t), pos(_pos) {}
	int t, pos;
};
int N, M, S, Ans[Max_M];
vector<edge> G[Max_N];
bool done[Max_N], Can[Max_N][Max_N];

void dfs1(int u)
{
	if (Can[S][u])
		return;
	Can[S][u] = true;
	for (int i = 0, t;i < G[u].size();++i)
		dfs1(G[u][i].t);
}

void dfs2(int u)
{
	if (done[u])
		return;
	done[u] = true;
	for (int i = 0, t;i < G[u].size();++i)
		dfs2(G[u][i].t);
}

int main()
{
	gi(N), gi(M);
	for (int i = 1, s, t;i <= M;++i)
		gi(s), gi(t), G[s].push_back(edge(t, i)), Ans[i] = 0;
	for (S = 1;S <= N;++S)
	{
		Can[S][S] = true;
		for (int i = 0, t;i < G[S].size();++i)
			if (Can[S][t = G[S][i].t])
				Ans[G[S][i].pos] = 1;
			else
				dfs1(t);
	}
	for (S = 1;S <= N;++S)
	{
		memset(done, false, sizeof(done)), done[S] = true; 
		for (int i = G[S].size() - 1, t;i >= 0;--i)
			if (done[t = G[S][i].t])
				Ans[G[S][i].pos] = 1;
			else
				dfs2(t);
	}
	for (int s = 1;s <= N;++s)
		for (int i = 0;i < G[s].size();++i)
			if (Can[G[s][i].t][s])
				++Ans[G[s][i].pos];
	for (int i = 1;i <= M;++i)
	{
		if (Ans[i] != 1)
			putc('s'), putc('a'), putc('m'), putc('e');
		else
			putc('d'), putc('i'), putc('f'), putc('f');
		putc('\n');
	}
	return 0;
}
