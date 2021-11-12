#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef struct _node {
    int data;
    struct _node* pNext;
} node;

typedef struct list { // List 구조체
    node* pHead;
};

node* createNode(int data) {
    node* ret = (node*)malloc(sizeof(node));
    ret->data = data;
    ret->pNext = NULL;
    return ret;
}

void insertNode(list* pList, node* newNode) {
    newNode->pNext = pList->pHead;
    pList->pHead = newNode;
}

void printLL(list* pList) {
    node* pHead = pList->pHead;
    while (pHead != NULL) {
        printf("(%d) ", pHead->data);
        pHead = pHead->pNext;
    }
    printf("\n");
}

int countNode(list* pList) {
    node* pHead = pList->pHead;
    int cnt = 0;
    while (pHead != NULL) {
        cnt++;
        pHead = pHead->pNext;
    }
    return cnt;
}
DWORD threadId;
DWORD WINAPI ThreadFunc(LPVOID in);

int main()
{
    list myList = { NULL }; // create empty list
    HANDLE hThrd[5] = { 0 }; // thread와 관련된 여러 정보를 담고 있다.
    for (int i = 0; i < 5; i++)
    {
        hThrd[i] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)&myList, 0,
            &threadId);
        if (hThrd[i])
        {
            printf("Thread launched %d\n", i);
        }
        else {
            printf("error creating a thread\n");
            return 0;
        }
    }

    WaitForMultipleObjects(5, hThrd, TRUE, INFINITE);
    for (int i = 0; i < 5; i++)
        CloseHandle(hThrd[i]);

    int cnt = countNode(&myList);
    printf("num node = %d", cnt);
}

DWORD WINAPI ThreadFunc(LPVOID in)
{
    list* pList = (list*)in;
    for (int i = 0; i < 1000000; i++)
        insertNode(pList, createNode(i));
    return 0;
}

