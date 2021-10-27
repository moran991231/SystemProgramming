// 20211027Static.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
// global variables: 프로그램 수행 내내 동일한 메모리 공간을 사용한다.
int ga; // BSS segment를 사용
int gb = 10; // DATA segment를 사용


int main()
{ 
    int a, b, c;
    static int sa; // BSS segment를 사용
    static int sb = 20; // DATA segment를 사용

    a = 10;
    b = 20;
    c = a + b;
    sa = a + sb;
    return 0;
}
 