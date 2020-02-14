#include <bits/stdc++.h>

using namespace std;

int main()
{
	int k;
	cin >> k;
	int n = (k+3)/4*2;
	if(k == 1) n = 1;
	printf("%d\n", n);
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			int c = (!(i&1)) ? (j-i+n)%n : n+(j-i+n)%n;
			if(c >= k) c -= n;
			printf("%d ", c+1);
		}
		putchar('\n');
	}
	return 0;
}