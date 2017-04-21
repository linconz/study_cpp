//
//  linked_list.cpp
//  TestCPP
//
//  Created by zhang on 2017/1/16.
//  Copyright © 2017年 zhang. All rights reserved.
//

#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    int value;
    Node *next;
};

class List {
public:
    Node *head;
    List() { head = NULL; };

    /**
     在链表的最后增加结点

     @param value 结点value
     */
    void addNode(int value);

    /**
     在指定结点之前插入结点

     @param oldValue 原结点
     @param newValue 结点内容
     */
    void insertNode(int oldValue, int newValue);

    /**
     删除结点

     @param value 结点value
     */
    void deleteNode(int value);

    /**
     打印链表
     */
    void outputList();

    /**
     使用递归方式从尾到头打印链表
     */
    void routputList(Node *prevNode);

    /**
     使用栈从尾到头打印链表
     */
    void routputListWithStack();

    /**
     查找结点
     */
    Node *findNode(int value);

    /**
     查找结点位于链表中的位置

     @param value 结点value

     @return 第一次出现位置
     */
    int findNodePosition(int value);

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

    /**
     判断是否有环

     @return 链表是否有环: -1 无环
     */
    int hasLoop();

    /**
     求出链表中结点总数

     @return 总数
     */
    int count();

    Node *getHead() {return head;};
};

void List::addNode(int value)
{
    if (head == NULL) {
        head = (Node *)new(Node);
        head->value = value;
        head->next = NULL;
        return;
    }
    Node *findNode = head;
    while (findNode->next != NULL) {
        findNode = findNode->next;
    }
    Node *newNode = (Node *)new(Node);
    newNode->value = value;
    newNode->next = NULL;
    findNode->next = newNode;
}

void List::insertNode(int oldValue, int newValue)
{
    // 查找oldPosition的结点
    Node *findNode;
    // 存储findNode的上一个结点
    Node *prevFindNode = NULL;
    // 要插入的结点
    Node *newNode;
    newNode = (Node*)new(Node);
    newNode->value = newValue;
    findNode = head;
    if (findNode == NULL) {
        // 如果是一个新表, next设为空
        head = newNode;
        newNode->next = NULL;
    } else if (findNode->value == oldValue) {
        // 如果第一个结点就是要插入的结点
        // head改为newNode
        head = newNode;
        // next指向原先的第一个结点
        newNode->next = findNode;
    } else {
        // 查找结点oldPosition
        while (findNode->value != oldValue && findNode->next != NULL) {
            prevFindNode = findNode->next;
            findNode = prevFindNode->next;
            if (findNode == NULL) {
                break;
            }
        }
        if (findNode != NULL && findNode->value == oldValue) {
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

void List::deleteNode(int value)
{
    if (head == NULL) {
        return;
    }
    Node *findNode = NULL;
    Node *prevFindNode = NULL;
    findNode = head;
    if (findNode->value == value) {
        // 如果findNode第一个结点就是要查找的位置
        head = NULL;
        return;
    }

    while (findNode->value != value && findNode->next != NULL) {
        prevFindNode = findNode;
        findNode = findNode->next;
    }
    if (findNode->value == value) {
        // 把找到结点位置的上一个结点指向找到结点位置的下一个结点
        // (node - 1)->next = node->next
        prevFindNode->next = findNode->next;
    }
}

Node* List::findNode(int value)
{
    Node *findNode = NULL;
    if (head == NULL) {
        return NULL;
    }
    findNode = head;
    while (findNode->value != value && findNode->next != NULL) {
        findNode = findNode->next;
    }
    if (findNode->value == value) {
        return findNode;
    }
    return NULL;
}

int List::findNodePosition(int value)
{
    if (head == NULL) {
        return -1;
    }
    if (head->value == value) {
        return 0;
    }
    Node *findNode = NULL;
    findNode = head;
    int temp = 0;
    while(findNode != NULL && findNode->value != value) {
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

int List::hasLoop()
{
    // 思路: 声明两个步数
    Node *currentNode = head;
    // 第一个用来记录外层递归次数
    int currentStep = 0;
    while (currentNode != NULL && currentNode->next != NULL) {
        Node *currentNode2 = head;
        // 第二个用来记录内层递归次数
        int currentStep2 = 0;
        currentStep ++;
        while (currentNode2 != NULL && currentNode2->next != NULL) {
            currentStep2 ++;
            if (currentNode2 == currentNode) {
                if (currentStep == currentStep2) {
                    break;
                } else {
                    // 如果当前两个结点相同
                    // 同时步数不同, 说明遇到了链表环
                    // 链表:          0 -> 1 -> 2 -> 3 -> 2 -> 3 ...
                    // 第一层步数:     1    2    3    4    5 第二层已经到了环
                    // 第二层步数:     5    5    5    5    3 第二层因为从0又开始计数,这时候步数是3
                    return currentStep2 + 1;
                }
            }
            currentNode2 = currentNode2->next;
        }
        currentNode = currentNode->next;
    }
    return -1;
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
        cout << currentNode->value;
        currentNode = currentNode->next;
        if (currentNode != NULL) {
            cout << " -> ";
        }
    }
    cout << endl;
}

void List::routputList(Node *prevNode)
{
    if (prevNode == NULL) {
        return;
    }
    this->routputList(prevNode->next);
    cout << prevNode->value;
    if (prevNode != head) {
        cout << " <- ";
    } else {
        cout << endl;
    }
}

void List::routputListWithStack()
{
    std::stack<Node *>s;
    Node *findNode = head;
    while (findNode != NULL) {
        s.push(findNode);
        findNode = findNode->next;
    }
    while (!s.empty()) {
        findNode = s.top();
        cout << findNode->value;
        s.pop();
        if (s.empty()) {
            cout << endl;
        } else {
            cout << " <- ";
        }
    }
}

int List::count()
{
    if (head == NULL) {
        return 0;
    }
    if (head->next == NULL) {
        return 1;
    }
    Node *findNode = head;
    int temp = 1;
    while (findNode->next != NULL) {
        findNode = findNode->next;
        temp ++;
    }
    return temp;
}

int main(int argc, const char * argv[]) {

    List *list = new List();
    for (int i=0; i<5; i++) {
        list->addNode(i);
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

    list->insertNode(3, 233);
    int position = list->findNodePosition(233);
    if (position == -1) {
        cout << "找不到233" << endl;
    } else {
        cout << "找到233, 位置在: " << position << endl;
        list->outputList();
    }
    Node *findNode = list->findNode(3);
    if (findNode != NULL) {
        cout << "find node:" << findNode->value << endl;
    }

    /*
     cout << "insert loop" << endl;
     Node *temp = list->findNode(0);
     temp->next = list->findNode(2);
     ((Node *) list->findNode(2))->next = list->findNode(3);
     cout << temp << endl;

     int loopPos = list->hasLoop();
     if (loopPos > -1) {
     cout << "has loop, loop position is: " << loopPos << endl;
     }
     */
    list->outputList();
    int count = list->count();
    cout << "count is: " << count << endl;

    cout << "reverse output list:" << endl;
    list->routputList(list->head);

    cout << "clear list" << endl;
    list->clearList();
    list->outputList();
    
    cout << "destory list" << endl;
    list->destoryList();
    list->outputList();
    return 0;
}
