 
#include <stdio.h> 
#include <stdlib.h>
#include <windows.h>
typedef struct _node {
    int data;
    struct _node* pNext;
} node;

typedef struct List { 
    node* pHead;
    CRITICAL_SECTION criticalSection;
};

typedef struct MyThreadData {
    List* l1, * l2;
    int id, trial;
};

// functions for list
void DeleteList(List* pList);
void swapLists(List* list1, List* list2, int time);

// functions for node
node* createNode(int data);
void insertNode(List* pList, node* newNode);

//functions for thread
DWORD WINAPI ThreadFunc(LPVOID in);

int main()
{
    // make list
    List* lists[2] = { NULL, NULL };
    lists[0] = (List*)malloc(sizeof(List));
    lists[1] = (List*)malloc(sizeof(List));
    lists[0]->pHead = lists[1]->pHead = NULL;
    insertNode(lists[0], createNode(111));
    insertNode(lists[1], createNode(222));

    // init critical section
    InitializeCriticalSection(&(lists[0]->criticalSection));
    InitializeCriticalSection(&(lists[1]->criticalSection));

    // make thread data
    MyThreadData data[2];
    data[0] = { lists[0], lists[1], 1 };
    data[1] = { lists[1], lists[0],2 };

    printf("Thread data: (L1 %d) (L2 %d) \n", lists[0]->pHead->data, lists[1]->pHead->data);

    // create thread
    HANDLE hThrd[2] = { 0 }; // thread와 관련된 여러 정보를 담고 있다.
    for (int i = 0; i < 2; i++)
    {
        hThrd[i] = CreateThread(NULL, 0, ThreadFunc, (LPVOID) & (data[i]), 0, NULL);
        if (hThrd[i])        
            printf("Thread launched %d\n", i + 1);        
        else {
            printf("error creating a thread\n");
            return 0;
        }
    }

    // wait for all threads
    WaitForMultipleObjects(2, hThrd, TRUE, INFINITE);
    printf("All threads are ended: (L1 %d) (L2 %d)\n",lists[0]->pHead->data, lists[1]->pHead->data);

    // release lists
    DeleteList(lists[0]);
    DeleteList(lists[1]);
}

DWORD WINAPI ThreadFunc(LPVOID in)
{
    MyThreadData* d = (MyThreadData*)in;

    for (d->trial = 1; d->trial < 2000000; d->trial++) {
        swapLists(d->l1, d->l2, d->trial);
        printf("thread %d swaped %d -times: (L1 %d) (L2 %d)\n", d->id, d->trial, d->l1->pHead->data, d->l2->pHead->data);
    }
    return 0;
}

void DeleteList(List* pList) {
    node* pnode = pList->pHead;
    node* pnext = NULL;
    free(pList);
    while (pnode != NULL) {
        pnext = pnode->pNext;
        free(pnode);
        pnode = pnext;
    }
}
void swapLists(List* list1, List* list2, int time) {
    node* tmp_list;
    // grasp resources
    EnterCriticalSection(&(list1->criticalSection));
    if (time % 10 == 0)
        Sleep(1); // <-- dead lock occurs
    EnterCriticalSection(&(list2->criticalSection));

    // swap
    tmp_list = list1->pHead;
    list1->pHead = list2->pHead;
    list2->pHead = tmp_list;

    // release resources
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

