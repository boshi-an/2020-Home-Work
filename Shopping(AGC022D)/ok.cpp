#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXN = 3e5 + 10;

int n, l;
int x[MAXN], t[MAXN];

int main() {
	scanf("%d%d", &n, &l);
	for (int i = 1; i <= n; ++i) scanf("%d", &x[i]);
	LL cnt = 1;
	int L = 0, R = 0, LR = 0;
	for (int i = 1, t; i <= n; ++i) {
		scanf("%d", &t), cnt += t / (l << 1), t %= l << 1;
		if (!t) continue; ++cnt;
		int cl = t <= (l - x[i] << 1), cr = t <= (x[i] << 1);
		if (i == n) { cnt -= cl; break; }
		if (cr) LR += cl, ++R;
		else L += cl;
		while (R - L < (LR << 1)) LR ? --LR : --L;
	}
	printf("%lld\n", (cnt - L - LR) * (l << 1));
	return 0;
}
