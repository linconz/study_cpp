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

    /**
     查找结点位于链表中的位置

     @param value 结点value

     @return 第一次出现位置
     */
    int findNodePosition(int value);

    /**
     查找结点
     */
    Node *findNode(int value);

    /**
     使用while的方式返回倒数的某个结点

     @param position 位置

     @return Node结点
     */
    Node *findPositionAtBackward(unsigned int position);

    /**
     使用两个指针的方式返回倒数的某个结点

     @param position 位置

     @return Node结点
     */
    Node *findPositionAtBackwardWithPoint(unsigned int position);

    /**
     获得链表中间的结点

     @return Node结点
     */
    Node *findMiddleNode();

    Node *getHead() {return head;};

    /**
     合并两个有序链表

     @param list1 链表1
     @param list2 链表2

     @return 返回合并后的链表
     */
    Node* mergeList(Node *list1, Node *list2);

    /**
     使用两个指针方式合并两个有序链表

     @param list1 链表1
     @param list2 链表2

     @return 返回合并后的链表
     */
    Node* mergeListWithPoint(Node *list1, Node *list2);
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
    if (head->value == value) {
        // 如果findNode第一个结点就是要查找的位置
        // 判断next是不是空的
        if (head->next != NULL) {
            Node *temp = head->next;
            delete head;
            head = temp;
        }
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
        delete findNode;
    }
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

Node* List::findPositionAtBackward(unsigned int position)
{
    if (head == NULL || head->next == NULL) {
        return NULL;
    }
    // 循环查找:
    // 位置 = 链表总数 - 查找位置
    unsigned int findPosition = this->count() - position;
    unsigned int tempPosition = 1;
    Node *findNode = head;
    while (tempPosition < findPosition) {
        findNode = findNode->next;
        tempPosition ++;
    }
    return findNode;
}

Node* List::findPositionAtBackwardWithPoint(unsigned int position)
{
    // 使用两个指针，先让前面的指针走到正向第position个结点
    // 这样前后两个指针的距离差是position-1，之后前后两个指针一起向前走
    // 前面的指针走到最后一个结点时，后面指针所指结点就是倒数第position个结点。
    if (position == 0 || head == NULL) {
        return NULL;
    }
    Node *aheadNode = head;
    Node *behindNode = head;
    // aheadNode先走到position的位置
    while (position > 1 && aheadNode != NULL) {
        aheadNode = aheadNode->next;
        position --;
    }
    if (position > 1 || aheadNode == NULL) {
        return NULL;
    }
    // 两个一起走
    // 当aheadNode走到末尾, behindNode就是position的位置
    while (aheadNode->next != NULL) {
        behindNode = behindNode->next;
        aheadNode = aheadNode->next;
    }
    return behindNode;
}

Node* List::findMiddleNode()
{
    // 获取单链表中间结点，若链表长度为n(n>0)，则返回第n/2+1个结点
    // 两个指针同时向前走，前面的指针每次走两步
    // 后面的指针每次走一步，前面的指针走到最后一个结点时，后面的指针所指结点就是中间结点
    if (head == NULL || head->next == NULL) {
        return NULL;
    }
    Node *aheadNode = head;
    Node *behindNode = head;
    while (aheadNode->next != NULL) {
        aheadNode = aheadNode->next;
        behindNode = behindNode->next;
        if (aheadNode->next != NULL) {
            aheadNode = aheadNode->next;
        }
    }
    return behindNode;
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

Node* List::mergeList(Node *list1, Node *list2)
{
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    Node *newNode = NULL;
    // 对两个value做比较
    // 值小的在前
    if (list1->value < list2->value) {
        newNode = list1;
        // 赋值后下一次的递归用next传递
        newNode->next = mergeList(list1->next, list2);
    } else {
        newNode = list2;
        newNode->next = mergeList(list1, list2->next);
    }
    return newNode;
}

Node* List::mergeListWithPoint(Node *list1, Node *list2)
{
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    // 定义一个标尺链表
    Node *newList = NULL;
    // 第一步先比较两个链表的首位
    if (list1->value < list2->value) {
        newList = list1;
        list1 = list1->next;
    } else {
        newList = list2;
        list2 = list2->next;
    }
    // 存储新链表的head
    Node *newListHead = newList;
    while (list1 != NULL && list2 != NULL) {
        if (list1->value < list2->value) {
            newList->next = list1;
            list1 = list1->next;
        } else {
            newList->next = list2;
            list2 = list2->next;
        }
        // 把标尺往下移动
        newList = newList->next;
    }
    // 如果某个链表还没有走完, 继续赋值
    if (list1 != NULL) {
        newList->next = list1;
    } else if (list2 != NULL) {
        newList->next = list2;
    }
    // 最后得到合并后的链表
    return newListHead;
}

void mergeLinkedLists();

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

//    list->deleteNode(233);
    cout << "find backward position" << endl;
    list->outputList();
    int findPosition = 5;
    findNode = list->findPositionAtBackward(findPosition);
    if (findNode != NULL) {
        cout << "find Node value is:" << findNode->value << endl;
    } else {
        cout << "can not find position " << findPosition << endl;
    }

    list->insertNode(233, 666);
    list->outputList();
    cout << "find middle node:";
    findNode = list->findMiddleNode();
    if (findNode) {
        cout << findNode->value << endl;
    } else {
        cout << "can not find middle node" << endl;
    }

    cout << "clear list" << endl;
    list->clearList();
    list->outputList();
    
    cout << "destory list" << endl;
    list->destoryList();
    list->outputList();

    mergeLinkedLists();
    return 0;
}

/**
 合并两个有序链表
 */
void mergeLinkedLists()
{
    List *list1 = new List();
    Node *node1 = new(Node);
    node1->value = 1;
    Node *node3 = new(Node);
    node3->value = 3;
    node1->next = node3;
    Node *node5 = new(Node);
    node5->value = 5;
    node3->next = node5;
    node5->next = NULL;

    List *list2 = new List();
    Node *node2 = new(Node);
    node2->value = 2;
    Node *node4 = new(Node);
    node4->value = 4;
    node2->next = node4;
    Node *node6 = new(Node);
    node6->value = 6;
    node4->next = node6;
    node6->next = NULL;

    list1->head = node1;
    list2->head = node2;

    cout << "list 1 is: " << endl;
    list1->outputList();
    cout << "list 2 is: " << endl;
    list2->outputList();

    List *mergeList = new List();
#if 1
    Node *newNode = mergeList->mergeListWithPoint(node1, node2);
#else
    Node *newNode = mergeList->mergeList(node1, node2);
#endif
    mergeList->head = newNode;
    mergeList->outputList();
    mergeList->destoryList();
}