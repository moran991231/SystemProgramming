#include <stdio.h>

int main()
{
    int a, b, c; // 변수 선언: 변수의 자료형, 이름
    a = 10;		 // 대입연산: 우변의 값을 좌변의 저장장소로 이동
    b = 20;      // 리터럴: 프로그램에서 값을 표현
    b = 0x12345678; // 16진수 signed int 형 리터럴
    c = a + b;   // 산술연산자: 피연산자 2개 

    printf("c = %d\n", c);

    return 0;
}
