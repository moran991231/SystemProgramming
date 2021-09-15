/*
주요 이슈:
1. 함수 호출 시 매개변수가 어떻게 전달되는가?
2. 키워드 WINAPI의 의미가 무엇인가?
*/
#include <Windows.h>

int sum(int, int);
int WINAPI wsum(int, int);

int main() {
    int a, b, c;
    a = 10;
    b = 20;
    c = a + b;
    c = sum(a, b);
    c = wsum(a, b);

    return 0;
}

int sum(int x, int y) {
    int z;
    z = x + y;
    return z;
}

int WINAPI wsum(int x, int y) {
    int z;
    z = x + y;
    return z;
}