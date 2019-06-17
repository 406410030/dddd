//AC C_MM14
#include<stdio.h>
#include<iostream>
#define d 86400
#define h 3600
#define m 60
using namespace std;
int main()
{
	int times;
	cin>>times;
	int day, hr, minu, sec;
	day = times/d;
	hr = (times%d)/h;
	minu = ((times%d)%h)/m;
	sec = ((times%d)%h)%m;
	cout<<day<<" days\n";
	cout<<hr<<" hours\n";
	cout<<minu<<" minutes\n";
	cout<<sec<<" seconds\n";
	return 0;
}