#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	char in[30];
	while(cin.getline(in,29)){
	long long int num = atoi(in);
	if(num%2 == 1)cout<<"odd\n";
	else cout<<"even\n";
	}
	return 0;
}
