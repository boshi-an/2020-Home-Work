#include <bits/stdc++.h>

using namespace std;

char str[100];

void print(int n)
{
	for(int i=1; i<=n; i++)
	{
		if(i>2 && str[i-1]==str[i-2]) str[i] = '0'+'1'-str[i-1];
		else str[i] = rand()%2 + '0';
	}
	for(int i=1; i<=n; i++) putchar(str[i]);
	putchar('\n');
}

int main()
{
	int sed;
	cin >> sed;
	srand(sed);
	int n = 6;
	printf("%d\n", n);
	print(n);
	print(n);
	return 0;
}