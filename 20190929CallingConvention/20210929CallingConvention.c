#include <Windows.h>
int sum(int x, int y);
int WINAPI wsum(int x, int y);
void main() {
    int a, b, c;
    a = 10;
    b = 20;
    c = sum(a, b);
    c = sum(a, b);

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