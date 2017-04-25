//
//  linked_list.cpp
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
     计算二叉树总共有多少个结点

     @param node 头结点

     @return 结点总数
     */
    int count(BinaryTreeNode *node);

    /**
     计算二叉树深度

     @param node 头结点

     @return 结点总数
     */
    int deep(BinaryTreeNode *node);

    /**
     计算二叉树宽度

     @param node 头结点

     @return 叶子结点最宽数
     */
    int leaf(BinaryTreeNode *node);

    /**
     先序遍历
     先遍历左孩子再遍历右孩子

     @param node 二叉树头结点
     */
    void outputListWithPreorderTraversal(BinaryTreeNode *node);

    /**
     中序遍历

     @param node 二叉树头结点
     */
    void outputListWithInorderTraversal(BinaryTreeNode *node);

    /**
     后序遍历

     @param node 二叉树头结点
     */
    void outputListWithPostorderTraversal(BinaryTreeNode *node);
};

int List::count(BinaryTreeNode *node)
{
    if (node == NULL)
        return 0;
    return this->count(node->leftNode) + this->count(node->rightNode) + 1;
}

int List::deep(BinaryTreeNode *node)
{
    if (node == NULL) {
        return 0;
    }
    int ldeep = this->deep(node->leftNode);
    int rdeep = this->deep(node->rightNode);
    return ( ldeep > rdeep ) ? (ldeep + 1) : (rdeep + 1);
}

int List::leaf(BinaryTreeNode *node)
{
    if (node == NULL) {
        return 0;
    }
    if (node->leftNode == NULL && node->rightNode == NULL){
        return 1;
    }
    return this->leaf(node->leftNode) + this->leaf(node->rightNode);
}

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

void List::outputListWithInorderTraversal(BinaryTreeNode *node)
{
    if (node == NULL) {
        return;
    }
    this->outputListWithInorderTraversal(node->leftNode);
    cout << node->value << endl;
    this->outputListWithInorderTraversal(node->rightNode);
}

void List::outputListWithPostorderTraversal(BinaryTreeNode *node)
{
    if (node == NULL) {
        return;
    }
    this->outputListWithPostorderTraversal(node->leftNode);
    this->outputListWithPostorderTraversal(node->rightNode);
    cout << node->value << endl;
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

    BinaryTreeNode *rightNode5 = new(BinaryTreeNode);
    rightNode5->value = 25;
    rightNode5->leftNode = NULL;
    rightNode5->rightNode = NULL;

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

    // rightNode3 = 23
    rightNode3->rightNode = rightNode5;

    List *list = new List();
    cout << "先序遍历:" << endl;
    list->outputListWithPreorderTraversal(nodeHead);

    cout << "中序遍历" << endl;
    list->outputListWithInorderTraversal(nodeHead);

    cout << "后序遍历" << endl;
    list->outputListWithPostorderTraversal(nodeHead);

    int count = list->count(nodeHead);
    cout << "总结点数:" << count << endl;
    int deep = list->deep(nodeHead);
    cout << "结点深度:" << deep << endl;
    int leaf = list->leaf(nodeHead);
    cout << "leaf:" << leaf << endl;
    return 0;
}
