// 20210929Structure.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <stdlib.h>
// 구조체 선언

struct _complex {
    double real, imag; // 멤버변수
};

typedef struct _complex complex; // 자료형(struct _complex)를 complex라고 부름

/*
typedef struct _complex{
    double real, imag;
    } complex;

    라고 쓸 수도 있다.
*/

int main()
{
    //struct complex c1, c2; //구조체 변수 선언: 스택영역에 할당
    //c1.real = 1.0; // 구조체변수.멤버변수
    //c1.imag = 4.0;

    // 구조체를 포인터 변수를 통해 접근하자.
    struct _complex* ptr1;
    ptr1 = (struct _complex*)malloc(sizeof(struct _complex));

    complex* ptr2;
    ptr2 = (complex*)malloc(sizeof(complex));

    ptr1->real = 3.0; // 구조체포인터변수->멤버변수
    ptr1->imag = 4.0;
    (*ptr1).real = 3.0;

}
