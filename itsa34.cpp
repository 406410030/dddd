#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	char in[3];
	while(cin.getline(in,2)){
	int my = atoi(in);
	switch(my){
	case 1:
		cout<<"Person\n";
		break;

	case 2:
		cout<<"Fairy\n";
		break;

	case 3:
		cout<<"Dwarf\n";
		break;
	}
	}
	return 0;
}
