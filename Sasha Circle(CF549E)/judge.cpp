#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

template <typename T> void read(T& x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

int main()
{
	srand(time(0));
	system("g++ -o main main.cpp -O2");
	system("g++ -o ok ok.cpp -O2");
	system("g++ -o gen gen.cpp -O2");
	for(int i=1; i<=100000; i++)
	{
		char str[100];
		sprintf(str, "echo %d | ./gen > in", rand());
		system(str);
		system("./main < in > out");
		system("./ok < in > ans");
		if(system("diff out ans"))
		{
			printf("??\n");
			break;
		}
		else printf("%d\n", i);
	}
	return 0;
}
