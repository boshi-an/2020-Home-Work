#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 50005;

template<typename T> void read(T &x)
{
	char c = getchar(); x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
}

ll P, N, M, K;

struct MAT
{
	ll x[2][2];

	MAT () {memset(x, 0, sizeof(x));}

	MAT operator * (const MAT &t)
	{
		MAT ret;
		ret.x[0][0] = (x[0][0]*t.x[0][0] + x[0][1]*t.x[1][0]) % P;
		ret.x[0][1] = (x[0][0]*t.x[0][1] + x[0][1]*t.x[1][1]) % P;
		ret.x[1][0] = (x[1][0]*t.x[0][0] + x[1][1]*t.x[1][0]) % P;
		ret.x[1][1] = (x[1][0]*t.x[0][1] + x[1][1]*t.x[1][1]) % P;
		return ret;
	}
} I;

struct SEGT
{
	#define ls (a<<1)
	#define rs ((a<<1)|1)
	#define mid ((l+r)/2)

	MAT tre[MX*4];

	void build(int a, int l, int r, ll *seq)
	{
		if(l == r)
		{
			tre[a].x[0][0] = 0;
			tre[a].x[0][1] = 1;
			tre[a].x[1][0] = seq[(l+N-1) % N];
			tre[a].x[1][1] = seq[l];
		}
		else build(ls, l, mid, seq), build(rs, mid+1, r, seq), tre[a] = tre[rs] * tre[ls];
	}

	MAT qur(int a, int l, int r, int ql, int qr)
	{
		if(ql > qr) return I;
		else if(ql<=l && r<=qr) return tre[a];
		else if(ql > mid) return qur(rs, mid+1, r, ql, qr);
		else if(qr <= mid) return qur(ls, l, mid, ql, qr);
		else return qur(rs, mid+1, r, ql, qr) * qur(ls, l, mid, ql, qr);
	}

	#undef ls
	#undef rs
	#undef mid
} T;

MAT qpow(MAT x, ll t)
{
	MAT ret = I;
	while(t > 0)
	{
		if(t & 1) ret = ret * x;
		x = x*x;
		t >>= 1;
	}
	return ret;
}

ll seq[MX];
pair<ll, ll> mdf[MX];

void input()
{
	I.x[0][0] = I.x[1][1] = 1;
	read(K), read(P), read(N);
	for(int i=0; i<N; i++) read(seq[i]);
	read(M);
	for(int i=1; i<=M; i++) read(mdf[i].first), read(mdf[i].second);
	sort(mdf+1, mdf+M+1);
}

void work()
{
	T.build(1, 0, N-1, seq);
	MAT cur = I;
	ll lst = 0;
	while(M && mdf[M].first > K) M--;
	if(mdf[M].first != K) mdf[++M] = make_pair(K, seq[K%N]);
	for(int i=1; i<=M; i++)
	{
		if(lst/N == mdf[i].first/N)
		{
			cur = T.qur(1, 0, N-1, lst%N+1, mdf[i].first%N-1) * cur;
		}
		else
		{
			cur = T.qur(1, 0, N-1, lst%N+1, N-1) * cur;
			cur = qpow(T.qur(1, 0, N-1, 0, N-1), mdf[i].first/N - lst/N - 1) * cur;
			cur = T.qur(1, 0, N-1, 0, mdf[i].first%N-1) * cur;
		}

		MAT tmp;

		tmp.x[0][1] = 1, tmp.x[1][1] = mdf[i].second;
		if(i>1 && mdf[i-1].first==mdf[i].first-1) tmp.x[1][0] = mdf[i-1].second;
		else tmp.x[1][0] = seq[(mdf[i].first-1)%N];
		cur = tmp*cur;

		if(i!=M && mdf[i].first != mdf[i+1].first-1)
		{
			tmp.x[0][1] = 1, tmp.x[1][0] = mdf[i].second, tmp.x[1][1] = seq[(mdf[i].first+1) % N];
			cur = tmp*cur;
			lst = mdf[i].first+1;
		}
		else lst = mdf[i].first;
	}
	assert(lst == K);
	printf("%lld\n ", cur.x[0][1]);
}

int main()
{
	input();
	work();
	return 0;
}