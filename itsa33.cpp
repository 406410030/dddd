#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int a, b, t;
	cin>>a>>b;
	if(a < b)
	a ^= b ^= a ^= b;
	while((a % b) != 0){
	t = a%b;
	a = b;
	b = t;
	}
	cout<<b<<"\n";
}
