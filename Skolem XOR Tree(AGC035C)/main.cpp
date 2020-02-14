#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, t = 1<<30;
	scanf("%d", &n);
	while(t > n) t >>= 1;
	if(n == t) puts("No");
	else
	{
		puts("Yes");
		for(int i=2; i<n; i+=2)
		{
			printf("%d %d\n", 1, i);
			printf("%d %d\n", i, i+1);
			printf("%d %d\n", 1, n+i+1);
			printf("%d %d\n", n+i+1, n+i);
		}
		printf("%d %d\n", n+1, 3);
		if(!(n&1))
		{
			printf("%d %d\n", n, n^t);
			printf("%d %d\n", n*2, n+(t^1));
		}
	}
	return 0;
}