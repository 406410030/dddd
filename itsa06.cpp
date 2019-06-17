//AC C_AR49
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;
int main()
{
    char tmp[101] = "";
    char newt[101] = "";
    int n;
    cin.getline(tmp,101);
    cin>>n;
    int i;
    for(i = 0; i < strlen(tmp); i++){
   //     if(n >= 0){
        if((tmp[i] >= 'A'&&tmp[i] <= 'Z')||(tmp[i] >= 'a'&&tmp[i] <= 'z')||(tmp[i] >= '0' &&tmp[i] <= '9')){
                if(tmp[i] >= 'A'&&tmp[i] <= 'Z'){
                        if(('Z' - tmp[i])<n)newt[i] = 'A'+(n - ('Z' - tmp[i]))-1;
                        else
                        newt[i] = tmp[i] +n;
                }
                else if(tmp[i] >= 'a'&&tmp[i] <= 'z'){
                        if(('z' - tmp[i])<n)newt[i] = 'a'+(n - ('z' - tmp[i]))-1;
                        else
                        newt[i] = tmp[i] +n;
                }
                else if(tmp[i] >= '0' &&tmp[i] <= '9'){
                        if(('9' - tmp[i])<n)newt[i] = '0'+(n - ('9' - tmp[i]))-1;
                        else
                        newt[i] = tmp[i] +n;
                        }
                else
                newt[i] = tmp[i];
            }
        else
        newt[i] = tmp[i];
//        }
  /*      else{
            if((tmp[i] >= 'A'&&tmp[i] <= 'Z')||(tmp[i] >= 'a'&&tmp[i] <= 'z')||(tmp[i] >= '0' &&tmp[i] <= '9')){
                if(tmp[i] >= 'A'&&tmp[i] <= 'Z'){
                        if((tmp[i] - 'A') < abs(n))newt[i] = 'Z' - (abs(n)-(tmp[i] - 'A'))+1;
                        else
                        newt[i] = tmp[i] +n;
                }
                else if(tmp[i] >= 'a'&&tmp[i] <= 'z'){
                        if((tmp[i] - 'a') < abs(n))newt[i] = 'z' - (abs(n)-(tmp[i] - 'a'))+1;
                        else
                        newt[i] = tmp[i] +n;
                }
                else if(tmp[i] >= '0' &&tmp[i] <= '9'){
                        cout<<"a\n";
                        if((tmp[i] - '0')<n)newt[i] = '9' - (abs(n) - (tmp[i] - '0')) + 2;
                        else
                        newt[i] = tmp[i] - n;
                        }
                else
                newt[i] = tmp[i];
            }
        else
        newt[i] = tmp[i];
        }*/
    }
    cout<<newt<<"\n";
    return 0;
}
