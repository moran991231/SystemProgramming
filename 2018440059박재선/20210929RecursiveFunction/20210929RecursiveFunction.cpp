// 20210929RecursiveFunction.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>

// Recursive function (재귀함수)
// 함수 안에서 자신을 호출

void r_function(int a) {
    r_function(a);
}

int main()
{ 
    int x = 10;
    r_function(x);
    return 11;
} 

// 디버깅하지 않고 시작-> main함수 리턴값: -1073741571
/*
* That is the signed integer representation of Microsoft's "stack overflow/stack exhaustion" error code 0xC00000FD.
* STATUS_STACK_OVERFLOW
*/