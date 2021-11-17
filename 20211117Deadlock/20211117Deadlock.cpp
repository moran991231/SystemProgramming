// 20211117Deadlock.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <stdio.h> 
#include <stdlib.h>
#include <windows.h>
typedef struct _node {
    int data;
    struct _node* pNext;
} node;

typedef struct List { // List 구조체
    node* pHead;
    CRITICAL_SECTION criticalSection;
};

void swapLists(List* list1, List* list2, int time) {
    node* tmp_list;
    EnterCriticalSection(&(list1->criticalSection));
    if(time>50)
        Sleep(1);
    EnterCriticalSection(&(list2->criticalSection));
    tmp_list = list1->pHead;
    list1->pHead = list2->pHead;
    list2->pHead = tmp_list;
    LeaveCriticalSection(&(list1->criticalSection));
    LeaveCriticalSection(&(list2->criticalSection));
}
node* createNode(int data) {
    node* ret = (node*)malloc(sizeof(node));
    ret->data = data;
    ret->pNext = NULL;
    return ret;
}

void insertNode(List* pList, node* newNode) {
    newNode->pNext = pList->pHead;
    pList->pHead = newNode;
}
 
typedef struct MyThreadData {
    List* l1, *l2;
    int num;
};
DWORD WINAPI ThreadFunc(LPVOID in);
int main()
{ 
    List* lists[2] = {NULL, NULL};
    lists[0] = (List*)malloc(sizeof(List));
    lists[1] = (List*)malloc(sizeof(List));
    lists[0]->pHead = lists[1]->pHead = NULL;
    insertNode(lists[0], createNode(111));
    insertNode(lists[1], createNode(222));

    InitializeCriticalSection(&(lists[0]->criticalSection));
    InitializeCriticalSection(&(lists[1]->criticalSection));



    MyThreadData data[2] ;
    data[0]= { lists[0], lists[1], 1 };
    data[1] = { lists[1], lists[0],2 };



    HANDLE hThrd[2] = { 0 }; // thread와 관련된 여러 정보를 담고 있다.
    for (int i = 0; i < 2; i++)
    {
        hThrd[i] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)&(data[i]), 0, NULL);
        if (hThrd[i])
        {
            printf("Thread launched %d\n", i+1);
        }
        else {
            printf("error creating a thread\n");
            return 0;
        }
    }

    WaitForMultipleObjects(2, hThrd, TRUE, INFINITE);

}

DWORD WINAPI ThreadFunc(LPVOID in)
{
    MyThreadData* d = (MyThreadData*)in;

    for (int i = 1; i < 2000000000; i++) {
        swapLists(d->l1, d->l2, i);
        printf("thread %d swaped %d-times\n", d->num, i);
    }
    return 0;
}

