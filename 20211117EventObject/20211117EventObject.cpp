#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
typedef struct _node {
    int data;
    struct _node* pNext;
} node;

typedef struct list { // List 구조체
    node* pHead;
    HANDLE hEO;
};

// function: createList()
// input: -
// ouput: pointer of new list struct object

list* createList() {
    list* pList = (list*)malloc(sizeof(list));
    pList->pHead = NULL;
    pList->hEO = CreateEvent(NULL,FALSE/*auto reset*/, TRUE/*initially signaled*/, NULL);
    return pList;
}
/// <summary>
/// insert a node into the head of the list
/// </summary>
/// <param name="pList">pointer of the list</param>
/// <param name="newNode">pointer of the new node</param>
void insertHead(list* pList, node* newNode) {
    WaitForSingleObject(pList->hEO, INFINITE); // 현제 mutex가 nonsignaled상태이면 signaled상태가 될 때까지 기다린다.
    // 만약 mutex의 상태가 signaled로 변한다면
    // 다음 문장으로 넘어간다.
    // mutex의 상태를 nonsignaled로 만든다 (side effect) --> event object의 autoreset
    newNode->pNext = pList->pHead;
    pList->pHead = newNode;
    SetEvent(pList->hEO); // mutex의 상태를 signaled로 바꾼다.
}

/// <summary>
/// delete(free) list
/// </summary>
/// <param name="pList"> pointer of a list</param>
void deleteList(list* pList) {
    CloseHandle(pList->hEO);
    free(pList);
}

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
    clock_t start = clock();
    list* myList = createList(); // create empty list
    HANDLE hThrd[5] = { 0 }; // thread와 관련된 여러 정보를 담고 있다.
    for (int i = 0; i < 5; i++)
    {
        hThrd[i] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)myList, 0,
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
    int cnt = countNode(myList);
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    printf("elapsed time: %lf    num node = %d", elapsed, cnt);
    deleteList(myList);
}

DWORD WINAPI ThreadFunc(LPVOID in)
{
    list* pList = (list*)in;
    for (int i = 0; i < 1000000; i++)
        insertHead(pList, createNode(i));
    return 0;
}

