// 20211006FunctionPointer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>  

int sum(int a, int b) {
    // 함수 선언:
    // 1. 함수 이름
    // 2. 매개변수의 개수와 각각의 자료형
    // 3. 반환형 (int)
    return a + b;
}

int main() {
    int a = 10;
    int* ptr;
    ptr = &a;

    *ptr = 100;

    printf("a = %d\n", a);

    // function pointer
    // 1. 변수 이름, 2. 매개변수의 개수와 각각의 자료형, 3. 반환형
    int (*fptr)(int, int); //declaration of function pointer
    fptr = sum; // 우변 sum : 함수 이름만 사용하면 함수 포인터값을 반환
    fptr = &sum; 

    int c = fptr(10, 20); // 
    printf("c = %d\n", c);

    // void*
    void* vptr;
    vptr = ptr;
    vptr = fptr;
    vptr = &a;
    vptr = sum;
    // ptr =  vptr; // error: 
    ptr = (int*)vptr;
    vptr = (void*)a; 

    return 0;
}