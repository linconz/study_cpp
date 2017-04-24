//
//  binary_tree.cpp
//  TestCPP
//
//  Created by zhang on 2017/1/16.
//  Copyright © 2017年 zhang. All rights reserved.
//

#include <iostream>

using namespace std;

struct BinaryTreeNode
{
    int value;
    BinaryTreeNode *leftNode;
    BinaryTreeNode *rightNode;
};

class List {
public:
    BinaryTreeNode *head;

    /**
     先序遍历
     先遍历左孩子再遍历右孩子

     @param node 二叉树结点
     */
    void outputListWithPreorderTraversal(BinaryTreeNode *node);
};

void List::outputListWithPreorderTraversal(BinaryTreeNode *node)
{
    if (node == NULL) {
        return;
    }
    cout << node->value << endl;
    if (node->leftNode != NULL) {
        this->outputListWithPreorderTraversal(node->leftNode);
    }
    if (node->rightNode != NULL) {
        this->outputListWithPreorderTraversal(node->rightNode);
    }
}

int main(int argc, const char * argv[]) {

    BinaryTreeNode *nodeHead = new(BinaryTreeNode);
    nodeHead->value = 0;
    nodeHead->leftNode = NULL;
    nodeHead->rightNode = NULL;

    BinaryTreeNode *leftNode1 = new(BinaryTreeNode);
    leftNode1->value = 11;
    leftNode1->leftNode = NULL;
    leftNode1->rightNode = NULL;

    BinaryTreeNode *leftNode2 = new(BinaryTreeNode);
    leftNode2->value = 12;
    leftNode2->leftNode = NULL;
    leftNode2->rightNode = NULL;

    BinaryTreeNode *leftNode3 = new(BinaryTreeNode);
    leftNode3->value = 13;
    leftNode3->leftNode = NULL;
    leftNode3->rightNode = NULL;

    BinaryTreeNode *rightNode1 = new(BinaryTreeNode);
    rightNode1->value = 21;
    rightNode1->leftNode = NULL;
    rightNode1->rightNode = NULL;

    BinaryTreeNode *rightNode2 = new(BinaryTreeNode);
    rightNode2->value = 22;
    rightNode2->leftNode = NULL;
    rightNode2->rightNode = NULL;

    BinaryTreeNode *rightNode3 = new(BinaryTreeNode);
    rightNode3->value = 23;
    rightNode3->leftNode = NULL;
    rightNode3->rightNode = NULL;

    BinaryTreeNode *rightNode4 = new(BinaryTreeNode);
    rightNode4->value = 24;
    rightNode4->leftNode = NULL;
    rightNode4->rightNode = NULL;

    // nodeHead = 0
    nodeHead->leftNode = leftNode1;
    nodeHead->rightNode = rightNode1;

    // leftNode1 = 11
    leftNode1->leftNode = leftNode2;
    leftNode1->rightNode = rightNode2;

    // rightNode1 = 21
    rightNode1->leftNode = leftNode3;
    rightNode1->rightNode = rightNode3;

    // rightNode2 = 22
    rightNode2->rightNode = rightNode4;

    List *list = new List();
    list->outputListWithPreorderTraversal(nodeHead);

    return 0;
}

