//����:���������� 
//���: ���������ͻ����� ����
//�����̸�: functionpointer.cpp
//������¥: 2016��12��14��
//�ۼ���: �ּ���
#include <stdio.h>
int sum(int a, int b) {
    return (a + b);
}
int minus(int a, int b) {
    return (a - b);
}
//�Լ��������� Ÿ���� �����Ѵ�.
//��, myFunctType�� int�� ��ȯ�ϰ�, �Ű������� 2���̰�, ���� int����
//�Լ����������ϴ�.
typedef int (myFunctType)(int, int);

//�Լ� �����͸� �Ű������� ����� ��� �Լ������� ��ġ�ؾ� �Ѵ�.
int what(int a, int b, myFunctType pFcnt) {
    //int what(int a, int b, int (pFcnt) (int, int) ) {
    int c;
    c = pFcnt(a, b);
    return c;
}

void ppp(int a, int b) {
    a = a - b;
}

int main() {
    int x = 100, y = 50, z;
    //�Լ� ������: �Լ��� ����� �����Ǿ� �����ϱ� ���� �޸𸮿� �ö󰡴µ�
    //�� �Լ��� �����ϴ� �޸��� ù �ּҰ� �Լ� �����Ͱ� �ȴ�.

    //�Լ��� �̸����� ����ϸ� �Լ��� �����Ͱ� �ȴ�.
    //�Լ� �����͸� �Ű������� ����� ��� �Լ������� ��ġ�ؾ� �Ѵ�.
    z = what(x, y, sum);
    printf("The sum is %d\n", z);

    z = what(x, y, minus);
    printf("The minus is %d\n", z);

    //error: �Լ������� ��ġ���� �ʴ´�.
    //z = what(x, y, ppp); 

    return 0;
}


