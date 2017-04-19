//
//  linked_list.cpp
//  TestCPP
//
//  Created by zhang on 2017/1/16.
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
     在指定位置之前插入结点

     @param oldPosition 原结点
     @param newPosition 结点内容
     */
    void insertNode(int oldPosition, int newPosition);

    /**
     删除结点

     @param position position
     */
    void deleteNode(int position);

    /**
     打印链表
     */
    void outputList();

    /**
     查找结点
     */
    Node *findNode(int position);

    /**
     查找结点位于链表中的位置
     */
    int findNodePosition(int position);

    /**
     翻转链表
     */
    void reverseList();

    /**
     相邻两个位置翻转
     */
    void inreverseList();

    /**
     清空链表
     */
    void clearList();

    /**
     销毁链表
     */
    void destoryList();

    Node *getHead() {return head;};
};

void List::insertNode(int oldPosition, int newPosition)
{
    // 查找oldPosition的结点
    Node *findNode;
    // 存储findNode的上一个结点
    Node *prevFindNode = NULL;
    // 要插入的结点
    Node *newNode;
    newNode = (Node*)new(Node);
    newNode->position = newPosition;
    findNode = head;
    if (findNode == NULL) {
        // 如果是一个新表, next设为空
        head = newNode;
        newNode->next = NULL;
    } else if (findNode->position == oldPosition) {
        // 如果第一个结点就是要插入的结点
        // head改为newNode
        head = newNode;
        // next指向原先的第一个结点
        newNode->next = findNode;
    } else {
        // 查找结点oldPosition
        while (findNode->position != oldPosition && findNode->next != NULL) {
            prevFindNode = findNode->next;
            findNode = prevFindNode->next;
            if (findNode == NULL) {
                break;
            }
        }
        if (findNode != NULL && findNode->position == oldPosition) {
            // 找到结点oldPosition
            if (prevFindNode != NULL) {
                // 更改prevFindNode->next
                prevFindNode->next = newNode;
            }
            newNode->next = findNode;
        } else if (findNode != NULL) {
            // 找不到结点, 在最后插入
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
        // 如果findNode第一个结点就是要查找的位置
        head = NULL;
        return;
    }

    while (findNode->position != position && findNode->next != NULL) {
        prevFindNode = findNode;
        findNode = findNode->next;
    }
    if (findNode->position == position) {
        // 把找到结点位置的上一个结点指向找到结点位置的下一个结点
        // (node - 1)->next = node->next
        prevFindNode->next = findNode->next;
    }
}

Node* List::findNode(int position)
{
    Node *findNode = NULL;
    if (head == NULL) {
        return NULL;
    }
    findNode = head;
    while (findNode->position != position && findNode->next != NULL) {
        findNode = findNode->next;
    }
    if (findNode->position == position) {
        return findNode;
    }
    return NULL;
}

int List::findNodePosition(int position)
{
    if (head == NULL) {
        return -1;
    }
    Node *findNode = NULL;
    findNode = head;
    int temp = -1;
    while(findNode != NULL && findNode->position != position) {
        findNode = findNode->next;
        temp += 1;
    }
    if (temp == 0) {
        return -1;
    }
    return temp + 1;
}

void List::reverseList()
{
    Node *currentNode, *nextNode = NULL;
    if (head == NULL) {
        return;
    }
    // 找到head的下一个结点
    // 存入当前指向的结点
    currentNode = head->next;
    while (currentNode != NULL && currentNode->next != NULL) {
        // 找到当前结点指向的下一个结点存入nextNode
        nextNode = currentNode->next;
        // 更改当前结点的下一个指向
        // 指向到 node + 2
        currentNode->next = nextNode->next;
        // 更改nextNode的指向为当前结点
        nextNode->next = head->next;
        // 把head指向nextNode
        head->next = nextNode;
        this->outputList();
    }

    currentNode->next = head;
    head->next = NULL;
    head = nextNode;
}

void List::inreverseList()
{
    if (head == NULL || head->next == NULL) {
        return;
    }

    Node *prevNode = NULL, *currentNode = head, *nextNode = NULL;
    while (currentNode != NULL && currentNode->next != NULL) {
        if (prevNode != NULL) {
            // 不是第一次进入的, 更新prev的指向为当前结点的下一个结点
            prevNode->next = currentNode->next;
        } else {
            // 第一次进入, 更新head的指向到当前结点的指向
            head = currentNode->next;
        }
        // 把当前结点赋值给prev
        prevNode = currentNode;
        // 把当前结点的+2位置的结点赋值给next
        nextNode = currentNode->next->next;
        // 把当前结点转移到node + 2
        currentNode->next->next = currentNode;
        // 把当前结点的下一个指向更新为更改前的next
        currentNode->next = nextNode;
        // 重新赋值currentNode, 从node + 2位置开始
        currentNode = nextNode;
    }
}

void List::clearList()
{
    if (head == NULL) {
        return;
    }

    Node *currentNode, *nextNode;
    currentNode = head->next;
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    head->next = NULL;
}

void List::destoryList()
{
    if (head == NULL) {
        return;
    }

    Node *nextNode;
    while (head != NULL) {
        nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

void List::outputList()
{
    if (head == NULL) {
        cout << "list is NULL" << endl;
        return;
    } else if (head->next == NULL) {
        cout << "list is empty" << endl;
        return;
    }
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

    cout << "--------------" << endl;
    cout << "inreverse:" << endl;
    list->outputList();
    list->inreverseList();
    list->outputList();

    list->insertNode(6, 233);
    int position = list->findNodePosition(233);
    if (position == -1) {
        cout << "找不到233" << endl;
    } else {
        cout << "找到233, 位置在: " << position << endl;
        list->outputList();
    }
    Node *findNode = list->findNode(3);
    if (findNode != NULL) {
        cout << "find node:" << findNode->position << endl;
    }

    cout << "clear list" << endl;
    list->clearList();
    list->outputList();

    cout << "destory list" << endl;
    list->destoryList();
    list->outputList();
    return 0;
}
