#include <iostream>
using namespace::std;

#define INITFAIL -1
#define OVERFLOW -2
#define OUTOFRANGE -3

#define SUCCESS 1
#define FAIL 0
#define MAXSIZE 5
typedef int DataType;

typedef struct {
    DataType *data;
    int length;
    int listsize;
} SeqList;

void mallocList(SeqList *l)
{
    DataType *newbase;
    newbase = (DataType *)realloc(l->data,
                                  (l->listsize + MAXSIZE) * sizeof(DataType));
    if (!newbase)
        exit(OVERFLOW);
    l->data = newbase;
    l->listsize += MAXSIZE;
}

/**
 初始化线表

 @param l list
 */
void initList(SeqList *l)
{
    l->data = (DataType *)malloc(MAXSIZE * sizeof(DataType));
    if (!l->data) {
        exit(INITFAIL);
    }
    l->length = 0;
    l->listsize = MAXSIZE;
}

/**
 在表头插入元素

 @param l list
 @param newData data
 */
void insertAtFirst(SeqList * l, DataType newData)
{
    if (l->length >= l->listsize)
        mallocList(l);

    for (int i=l->length-1; i>=0; i--) {
        l->data[i + 1] = l->data[i];
    }
    l->data[0] = newData;
    l->length++;
}

/**
 在表尾插入元素

 @param l list
 @param newData data
 */
void insertAtList(SeqList *l, DataType newData)
{
    if (l->length >= l->listsize)
        mallocList(l);
    l->data[l->length] = newData;
    l->length++;
}

/**
 在指定位置插入元素

 @param l list
 @param newData data
 @param position position
 @return fail or success
 */
int insertAtPosition(SeqList *l, DataType newData, int position)
{
    if (position < 1 || position > l->length + 1)
        return FAIL;

    // 存储空间不够,需要分配新的空间
    if (l->length >= l->listsize)
        mallocList(l);
    for (int i=l->length-1; i>=position - 1; i--) {
        l->data[i + 1] = l->data[i];
    }
    l->data[position - 1] = newData;
    l->length ++;

    return SUCCESS;
}

/**
 在指定位置移除元素,并返回移除的值

 @param l list
 @param position position
 @return 元素值
 */
DataType removeDataAtPosition(SeqList *l, int position)
{
    DataType temp;
    if (position < 1 || position > l->length)
        exit(OUTOFRANGE);

    temp = l->data[position - 1];
    for (int i=position; i<l->length; i++) {
        // position之后的往前移动
        l->data[i - 1] = l->data[i];
    }
    l->length--;
    return temp;
}

/**
 判断是否为空表

 @param l list
 @return true or false
 */
bool isEmpty(SeqList *l)
{
    return l->length == 0;
}

/**
 遍历顺序表

 @param l list
 */
void traverseList(SeqList *l)
{
    cout << "list is : ";
    for (int i=0; i<l->length; i++) {
        cout << l->data[i] << " ";
    }
    cout << endl;
}

/**
 翻转顺序表

 @param l list
 */
void reverseList(SeqList *l)
{
    // 时间复杂度 O(n/2)
    int middleLength = l->length / 2;
    int min = 0, max = l->length - 1;
    DataType temp;
    for (int i=0; i<middleLength; i++) {
        temp = l->data[min];
        l->data[min++] = l->data[max];
        l->data[max--] = temp;
    }
}

int findDataInList(SeqList *l, DataType data)
{
    for (int i=0; i<l->length; i++) {
        if (l->data[i] == data) {
            return i;
        }
    }
    return OUTOFRANGE;
}

/**
 把顺序表B合并到顺序表A

 @param la list
 @param lb list
 */
void mergeListBToA(SeqList *la, SeqList *lb)
{
    la->listsize = la->length + lb->length;
    for (int i=0; i<lb->length; i++) {
        insertAtList(la, lb->data[i]);
    }
}

int main(int argc, char* argv[])
{
    SeqList list;
    bool isListEmpty = isEmpty(&list);
    if (isListEmpty) {
        cout << "list is empty" << endl;
    }
    initList(&list);
    for (int i=0; i<MAXSIZE; i++) {
        DataType data = i;
        insertAtFirst(&list, data);
    }
    traverseList(&list);

    int middlePosition = (&list)->length / 2;
    DataType insertData = 666;
    cout << "在" << middlePosition << "位置插入" << insertData << endl;
    insertAtPosition(&list, insertData, middlePosition);
    traverseList(&list);
    cout << "在" << middlePosition << "位置删除元素" << endl;
    DataType removeValue = removeDataAtPosition(&list, middlePosition);
    traverseList(&list);
    cout << "删除的元素值是" << removeValue << endl;

    cout << "在末尾追加 777" << endl;
    insertAtList(&list, 777);
    traverseList(&list);

    cout << "在头增加 888" << endl;
    insertAtFirst(&list, 888);
    traverseList(&list);

    cout << "翻转顺序表" << endl;
    reverseList(&list);
    traverseList(&list);

    cout << "查找元素666的位置,";
    int position = findDataInList(&list, 666);
    if (position != OUTOFRANGE) {
        cout << "找到位置" << position << endl;
    } else {
        cout << "未找到" << endl;
    }

    cout << "查找元素888的位置,";
    position = findDataInList(&list, 888);
    if (position != OUTOFRANGE) {
        cout << "找到位置" << position << endl;
    } else {
        cout << "未找到" << endl;
    }

    cout << "初始化顺序表b" << endl;
    SeqList listb;
    initList(&listb);
    for (int i=6; i<10; i++) {
        DataType data = i;
        insertAtList(&listb, data);
    }
    traverseList(&listb);
    cout << "合并顺序表b到顺序表a之后" << endl;
    mergeListBToA(&list, &listb);
    traverseList(&list);
    return 0;
}

