//AC C_AR36
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
#include<vector>
using namespace std;
int main()
{
    int month, day;
    cin>>month>>day;
    if(month == 1){
        if(day >= 21)
        cout<<"Aquariu\n";
        else
            cout<<"Capricorn\n";
    }
    if(month == 2){
        if(day >= 19)
        cout<<"Pisces\n";
        else
            cout<<"Aquariu\n";
    }
    if(month == 3){
        if(day >= 21)
        cout<<"Aries\n";
        else
            cout<<"Pisces\n";
    }
    if(month == 4){
        if(day >= 21)
        cout<<"Taurus\n";
        else
            cout<<"Aries\n";
    }
    if(month == 5){
        if(day >= 22)
        cout<<"Gemini\n";
        else
            cout<<"Taurus\n";
    }
    if(month == 6){
        if(day >= 22)
        cout<<"Cancer\n";
        else
            cout<<"Gemini\n";
    }
    if(month == 7){
        if(day >= 23)
        cout<<"Leo\n";
        else
            cout<<"Cancer\n";
    }
    if(month == 8){
        if(day >= 24)
        cout<<"Virgo\n";
        else
            cout<<"Leo\n";
    }
    if(month == 9){
        if(day >= 24)
        cout<<"Libra\n";
        else
            cout<<"Virgo\n";
    }
    if(month == 10){
        if(day >= 24)
        cout<<"Scorpio\n";
        else
            cout<<"Libra\n";
    }
    if(month == 11){
        if(day >= 23)
        cout<<"Sagittarius\n";
        else
            cout<<"Scorpio\n";
    }
    if(month == 12){
        if(day >= 22)
        cout<<"Capricorn\n";
        else
            cout<<"Sagittarius\n";
    }
    return 0;
}


