// 20211103MultiThreadLinkedList.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef struct _node {
    int data;
    struct _node* pNext;
} node;

node* createNode(int data) {
    node* ret = (node*)malloc(sizeof(node));
    ret->data = data;
    ret->pNext = NULL;
    return ret;
}

void insertNode(node** ppHead, node* newNode) {
    newNode->pNext = *ppHead;
    *ppHead = newNode;
}

void printLL(node* pHead) {
    while (pHead != NULL) {
        printf("(%d) ", pHead->data);
        pHead = pHead->pNext;
    }
    printf("\n");
}

int countNode(node* pHead) {
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
    node* pHead = NULL;
    node** ppHead = &pHead; 
    HANDLE hThrd[5] = { 0 }; // thread와 관련된 여러 정보를 담고 있다.
    for (int i = 0; i < 5; i++)
    {
        hThrd[i] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)ppHead, 0,
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

    int cnt = countNode(*ppHead);
    printf("num node = %d", cnt);
}

DWORD WINAPI ThreadFunc(LPVOID in)
{
    node** ppHead = (node**)in;
    for (int i = 0; i < 1000000; i++)
        insertNode(ppHead, createNode(i));
    return 0;
}

