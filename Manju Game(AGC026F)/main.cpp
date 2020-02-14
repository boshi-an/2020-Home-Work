#include <bits/stdc++.h>

const int MX = 300005;

using namespace std;

int a[MX];

int main()
{
	int n, odd = 0, evn = 0;
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
	{
		scanf("%d", &a[i]);
		if(i&1) odd += a[i];
		else evn += a[i];
	}
	if(n & 1)
	{
		int l = 1, r = 300000000, mid, ans;
		auto check = [=](int need)
		{
			int sum = a[1];
			for(int i=2; i<=n; i+=2)
			{
				if(sum >= need) sum = max(sum+a[i+1]-a[i], a[i+1]);
				else sum += a[i+1]-a[i];
			}
			return sum >= need;
		};
		while(l < r)
		{
			mid = (l+r+1) / 2;
			if(check(mid)) l = ans = mid;
			else r = ans = mid-1;
		}
		printf("%d %d\n", evn+ans, odd-ans);
	}
	else printf("%d %d\n", max(odd, evn), min(odd, evn));
	return 0;
}