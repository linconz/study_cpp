//
//  main.cpp
//  TestCPP
//
//  Created by letv on 2017/1/16.
//  Copyright © 2017年 zhang. All rights reserved.
//

#include <iostream>

using namespace std;

struct Node
{
    int position;
    Node *next;
};

class List {
    Node *head;
public:
    List() { head = NULL; };

    /**
     在指定位置之前插入节点

     @param oldPosition 原节点
     @param newPosition 节点内容
     */
    void insertNode(int oldPosition, int newPosition);

    /**
     删除节点

     @param position position
     */
    void deleteNode(int position);

    /**
     打印链表
     */
    void outputList();

    /**
     翻转链表
     */
    void reverseList();

    Node *getHead() {return head;};
};

void List::insertNode(int oldPosition, int newPosition)
{
    // 查找oldPosition的节点
    Node *findNode;
    // 存储findNode的上一个节点
    Node *prevFindNode = NULL;
    // 要插入的节点
    Node *newNode;
    newNode = (Node*)new(Node);
    newNode->position = newPosition;
    findNode = head;
    if (findNode == NULL) {
        // 如果是一个新表, next设为空
        head = newNode;
        newNode->next = NULL;
    } else if (findNode->position == oldPosition) {
        // 如果第一个节点就是要插入的节点
        // head改为newNode
        head = newNode;
        // next指向原先的第一个节点
        newNode->next = findNode;
        // 原先的第一个节点的next设为空
        findNode->next = NULL;
    } else {
        // 查找节点oldPosition
        while (findNode->position != oldPosition && findNode->next != NULL) {
            prevFindNode = findNode->next;
            findNode = prevFindNode->next;
            if (findNode == NULL) {
                break;
            }
        }
        if (findNode != NULL && findNode->position == oldPosition) {
            // 找到节点oldPosition
            if (prevFindNode != NULL) {
                // 更改prevFindNode->next
                prevFindNode->next = newNode;
            }
            newNode->next = findNode;
        } else if (findNode != NULL) {
            // 找不到节点, 在最后插入
            findNode->next = newNode;
            newNode->next = NULL;
        } else {
            prevFindNode->next = newNode;
            newNode->next = NULL;
        }
    }
}

void List::deleteNode(int position)
{
    if (head == NULL) {
        return;
    }
    Node *findNode = NULL;
    Node *prevFindNode = NULL;
    findNode = head;
    if (findNode->position == position) {
        // 如果findNode第一个节点就是要查找的位置
        delete findNode;
        head = NULL;
        return;
    }

    while (findNode->position != position && findNode->next != NULL) {
        prevFindNode = findNode;
        findNode = findNode->next;
    }
    if (findNode->position == position) {
        // 把找到节点位置的上一个节点指向找到节点位置的下一个节点
        // (node - 1)->next = node->next
        prevFindNode->next = findNode->next;
    }
}

void List::reverseList()
{
    Node *currentNode = NULL, *nextNode = NULL;
    if (head == NULL) {
        return;
    }
    // 找到head的下一个节点
    // 存入当前指向的节点
    currentNode = head->next;
    while (currentNode != NULL && currentNode->next != NULL) {
        // 找到当前节点指向的下一个节点存入nextNode
        nextNode = currentNode->next;
        // 更改当前节点的下一个指向
        // 指向到 node + 2
        currentNode->next = nextNode->next;
        // 更改nextNode的指向为当前节点
        nextNode->next = head->next;
        // 把head指向nextNode
        head->next = nextNode;
        this->outputList();
    }

    currentNode->next = head;
    head->next = NULL;
    head = nextNode;
}

void List::outputList()
{
    Node *currentNode = head;
    while(currentNode != NULL) {
        cout << currentNode->position;
        currentNode = currentNode->next;
        if (currentNode != NULL) {
            cout << " -> ";
        }
    }
    cout << endl;
}


int main(int argc, const char * argv[]) {

    List *list = new List();
    for (int i=0; i<5; i++) {
        list->insertNode(1, i);
    }
    list->outputList();
    cout << "--------------" << endl;
    cout << "insert 666:" << endl;
    list->insertNode(2, 666);
    list->outputList();
    cout << "--------------" << endl;
    cout << "delete 666:" << endl;
    list->deleteNode(666);
    list->outputList();
    cout << "--------------" << endl;
    cout << "reverse:" << endl;
    list->outputList();
    list->reverseList();
    list->outputList();
    return 0;
}