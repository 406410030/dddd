#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int dollar;
	cin>>dollar;
	int nt10, nt5, nt1;
	nt10 = dollar/10;
	nt5 = (dollar%10)/5;
	nt1 = (dollar%10)%5;
	cout<<"NT10="<<nt10<<"\n";
	cout<<"NT5="<<nt5<<"\n";
	cout<<"NT1="<<nt1<<"\n";
	return 0;
}
