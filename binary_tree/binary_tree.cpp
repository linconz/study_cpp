//
//  linked_list.cpp
//  TestCPP
//
//  Created by zhang on 2017/1/16.
//  Copyright © 2017年 zhang. All rights reserved.
//

#include <iostream>
#include <queue>

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

    /**
     分层遍历二叉树
     按层从上往下 每层从左到右

     @param node 二叉树头结点
     */
    void outputListWithLevelTraverse(BinaryTreeNode *node);

    /**
     获取第k层的节点数量

     @param node 根节点
     @param k 层数
     @return size_t 节点数量
     */
    size_t getLevelSize(BinaryTreeNode *node, size_t k);

    /**
     查找二叉树的某个节点的value

     @param node 根节点
     @param value 值
     @return bool 是否存在
     */
    bool findBinaryTreeNode(BinaryTreeNode *node, int value);
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

void List::outputListWithLevelTraverse(BinaryTreeNode *node)
{
    if (node == NULL) {
        return;
    }
    queue<BinaryTreeNode *> q;
    q.push(node);
    while (!q.empty()) {
        BinaryTreeNode *findNode = q.front();
        q.pop();
        cout << findNode->value << endl;
        if (findNode->leftNode != NULL) {
            q.push(findNode->leftNode);
        }
        if (findNode->rightNode != NULL) {
            q.push(findNode->rightNode);
        }
    }
}

size_t List::getLevelSize(BinaryTreeNode *node, size_t k)
{
	if (k <= 0) {
		return 0;
	}
	
	size_t count = 0;
	if (NULL == node) {
		return 0;
	}
	if (k == 1) {
		count ++;
	} else {
		count = getLevelSize(node->leftNode, k-1) + getLevelSize(node->rightNode, k-1);
	}
	
	return count;
}

bool List::findBinaryTreeNode(BinaryTreeNode *node, int value)
{
    bool result = false;
    if (NULL == node) {
        result = false;
    } else if (node->value == value) {
        result = true;
    } else {
        if (node->leftNode && !result) {
            result = this->findBinaryTreeNode(node->leftNode, value);
        }
        if (node->rightNode && !result) {
            result = this->findBinaryTreeNode(node->rightNode, value);
        }
    }

    return result;
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

    cout << "分层遍历" << endl;
    list->outputListWithLevelTraverse(nodeHead);

    int count = list->count(nodeHead);
    cout << "总结点数:" << count << endl;
    int deep = list->deep(nodeHead);
    cout << "结点深度:" << deep << endl;
    int leaf = list->leaf(nodeHead);
    cout << "leaf:" << leaf << endl;
    int level = 3;
	int levelSize = list->getLevelSize(nodeHead, level);
	cout << "第" << level << "层的节点个数是:" << levelSize << endl;

    int findValue = 4;
    bool isInList = list->findBinaryTreeNode(nodeHead, findValue);
    cout << "值" << findValue << (isInList ? "存在" : "不存在") << endl;
    return 0;
}
