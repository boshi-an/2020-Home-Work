#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const int MX = 1000006;
const ll IV3 = 333333336;

ll inv[MX], kth[MX], pw3[MX], ans;
int n;

int main()
{
	scanf("%d", &n);
	inv[1] = 1, pw3[0] = 1;
	for(int i=2; i<=n; i++) inv[i] = (MOD*MOD - (MOD/i)*inv[MOD%i]) % MOD;
	for(int i=1; i<=n; i++) kth[i] = (kth[i-1] + inv[n]*inv[n-i+1]) % MOD;
	for(int i=1; i<=n; i++) pw3[i] = pw3[i-1] * IV3 % MOD;
	for(int i=1; i<=n; i++) ans = (ans + pw3[i]*2*kth[i]) % MOD;
	ans = (ans + pw3[n]*kth[n]) % MOD * IV3 % MOD;
	printf("%lld\n", ans);
	return 0;
}