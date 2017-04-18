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
    void insertNode(int oldPosition, int newPosition);
    void deleteNode(int position);
    void outputList();

    Node *getHead() {return head;};
};

void List::insertNode(int oldPosition, int newPosition)
{
    // 查找oldPosition的节点
    Node *findNode;
    // 存储findNode的上一个节点
    Node *beforeFindNode = NULL;
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
            beforeFindNode = findNode->next;
            findNode = beforeFindNode->next;
            if (findNode == NULL) {
                break;
            }
        }
        if (findNode != NULL && findNode->position == oldPosition) {
            // 找到节点oldPosition
            if (beforeFindNode != NULL) {
                // 更改beforeFindNode->next
                beforeFindNode->next = newNode;
            }
            newNode->next = findNode;
        } else if (findNode != NULL) {
            // 找不到节点, 在最后插入
            findNode->next = newNode;
            newNode->next = NULL;
        } else {
            beforeFindNode->next = newNode;
            newNode->next = NULL;
        }
    }
}

void List::deleteNode(int position)
{
    if (head == NULL) {
        return;
    }
    Node *findNode;
    Node *beforeFindNode = NULL;
    findNode = head;
    if (findNode->position == position) {
        // 如果findNode第一个节点就是要查找的位置
        delete findNode;
        head = NULL;
        return;
    }

    while (findNode->position != position && findNode->next != NULL) {
        beforeFindNode = findNode;
        findNode = findNode->next;
    }
    if (findNode->position == position) {
        beforeFindNode->next = findNode->next;
        delete findNode;
    }
}

void List::outputList()
{
    Node *currentNode = head;
    while(currentNode != NULL) {
        cout << "Now node is: " << currentNode->position << endl;
        currentNode = currentNode->next;
    }
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
    return 0;
}

