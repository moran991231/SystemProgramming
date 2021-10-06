// 20210929LinkedList.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdlib.h> 
#include<stdio.h>   

typedef struct _node {
    int data;
    struct _node* pNext;
} node;

 
/// <summary>
/// create a node
/// </summary>
/// <param name="data"> data of the new node</param>
/// <returns> addr of the new node</returns>
node* createNode(int data) {
    node* ret = (node*)malloc(sizeof(node));
    ret->data = data;
    ret->pNext = NULL;
    return ret;
}

/// <summary>
/// insert new node in front of the list
/// </summary>
/// <param name="ppHead">the addr of head  </param>
/// <param name="newNode"></param>
void insertNode(node** ppHead, node* newNode) {
    newNode->pNext = *ppHead;
    *ppHead = newNode;
}

/// <summary>
/// print whole list
/// </summary>
/// <param name="pHead"></param>
void printLL(node* pHead) {
    while (pHead != NULL) {
        printf("(%d) ", pHead->data);
        pHead = pHead->pNext;
    }
    printf("\n");
}


int main()
{
    node* pHead = NULL;
    for (int i = 0; i < 10; i++) {
        insertNode(&pHead, createNode(i));
    }
    printLL(pHead);


}

