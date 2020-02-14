#include <cstdio>

using namespace std;
const int MOD(998244353);

constexpr int Mult(int a, int b)
{
	return a * 1LL * b % MOD;
}

constexpr int Add(int a, int b)
{
	return a + b >= MOD ? a + b - MOD : a + b;
}

constexpr int Sub(int a, int b)
{
	return a - b < 0 ? a - b + MOD : a - b;
}

void exgcd(int a, int b, int &x, int &y)
{
	if (b == 0)
		x = 1, y = 0;
	else
		exgcd(b, a % b, y, x), y -= x * (a / b);
}

inline int inverse(int a)
{
	int invx, invy;
	exgcd(a, MOD, invx, invy);
	return (invx % MOD + MOD) % MOD;
}

const int Max_N(500050);

int N, M, Fac[Max_N], Inv[Max_N], Ans;

inline int Com(int n, int m)
{
	return 0 <= m && m <= n ? Mult(Fac[n], Mult(Inv[m], Inv[n - m])) : 0;
}

int main()
{
	scanf("%d%d", &N, &M);
	Fac[0] = 1;
	for (int i = 1;i <= M;++i)
		Fac[i] = Mult(Fac[i - 1], i);
	Inv[M] = inverse(Fac[M]);
	for (int i = M - 1;i >= 0;--i)
		Inv[i] = Mult(Inv[i + 1], i + 1);
	for (int R = N;R <= M;++R)
		Ans = Add(Ans, Sub(Com(M, R), Com(M, R * 2 - N + 1)));
	printf("%d", Ans);
	return 0;
}