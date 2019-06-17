#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	char in[3];
	while(cin.getline(in,2)){
	char my = in[0];
	if(my == 'E')cout<<"ByeBye\n";
	else if(my == 'M')cout<<"Male\n";
	else if(my == 'F')cout<<"Female\n";
	}
	return 0;
}
