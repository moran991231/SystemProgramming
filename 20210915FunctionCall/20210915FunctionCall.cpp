/*
�ֿ� �̽�:
1. �Լ� ȣ�� �� �Ű������� ��� ���޵Ǵ°�?
2. Ű���� WINAPI�� �ǹ̰� �����ΰ�?
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