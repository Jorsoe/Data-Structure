#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100 //栈的初始空间
#define STACKINREMENT 10    //栈空间分配增量
#define OK 1                //OK == 1
#define ERROR 0             //ERROR == 0
#define TRUE 1              //TRUE == 1
#define FALSE 0             //FALSE == 0


/**
*新的栈ADT
*特点是 参照课本的形式来写
*/
typedef int SElemType;  //元素数据类型，可以根据需求自定义类型
typedef int Status ;    //定义的函数数据类型

typedef struct node{
    SElemType *base;    //栈底，根据定义，可知其作用。构造前和销毁后base为空 （这里才是存储元素的地方（以数组形式就是顺序栈了））
    SElemType *top;     //栈顶指针 其指向的值一般都是下一个的空间
    int stacksize;      //栈的大小，就是元素个数，或者空间大小
}SqStack;

/**栈的创建
* s为传入的栈的指针
*/
Status InitStack(SqStack *s ){
    //分配空间
    s->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof (SElemType)); //创建了一个数组 长度STACK_INIT_SIZE
    if(!s->base)
        exit(ERROR);    //分配空间失败
    s->top = s->base;   //栈顶初始化
    s->stacksize = STACK_INIT_SIZE; //空间初始化
    return OK;

}

/**插入新元素
* s为栈的地址 e 为要插入的元素
*/
Status Push(SqStack *s , SElemType e){
    //判断栈是否已满，满则需要追加空间
    if(s->top - s->base >= s->stacksize){
        s->base = (SElemType*)realloc(s->base, (STACKINREMENT + s->stacksize)*sizeof(SElemType));
        if(!s->base) exit(ERROR);           //分配失败

        s->top = s->base + s->stacksize ;    //栈顶指向追加空间前的 栈的最顶端的下一个位置，也就是新增空间的第一个位置
        s->stacksize += STACKINREMENT ;     //空间追加
    }
    *(s->top++) = e;  //将元素压入栈中 ， 并且将栈顶指针上移
    return OK;
}

/**弹出栈顶元素
 s为栈的地址 e为要接收弹出元素的变量的指针（地址）
* 返回值为判断栈弹出的成功与否
*/
Status Pop(SqStack *s , SElemType *e){
    //如果栈是空的，则返回错误
    if(s->top == s->base) exit(ERROR);
    //如果栈不为空,栈顶指针下移 ,接收其值
    *e = *(--s->top);
    return OK;
}

/**获取栈顶元素
* s 为栈变量 e为接收的栈顶的元素的变量的地址
*/
Status GetTop(SqStack s , SElemType *e){
    //如果栈不为空将其栈顶元素用e接收 返回OK
    if(s.top == s.base) return ERROR;
    *e = *(s.top - 1);
    return OK;
}

/**获取栈的长度 元素个数
*
*/
int StackLength(SqStack s){
    return s.stacksize;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
