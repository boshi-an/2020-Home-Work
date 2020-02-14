#include <bits/stdc++.h>

using namespace std;

int main()
{
	system("g++ -o gen gen.cpp -O2");
	system("g++ -o main main.cpp -O2");
	system("g++ -o ok ok.cpp -O2");
	for(int i=1; i<=100000; i++)
	{
		char str[100];
		sprintf(str, "echo %d | ./gen > in", i);
		system(str);
		system("./main < in > out");
		system("./ok < in > ans");
		if(system("diff out ans"))
		{
			printf("??\n");
			exit(0);
		}
		else printf("%d\n", i);
	}
	return 0;
}