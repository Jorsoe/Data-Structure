#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100 //ջ�ĳ�ʼ�ռ�
#define STACKINREMENT 10    //ջ�ռ��������
#define OK 1                //OK == 1
#define ERROR 0             //ERROR == 0
#define TRUE 1              //TRUE == 1
#define FALSE 0             //FALSE == 0


/**
*�µ�ջADT
*�ص��� ���տα�����ʽ��д
*/
typedef int SElemType;  //Ԫ���������ͣ����Ը��������Զ�������
typedef int Status ;    //����ĺ�����������

typedef struct node{
    SElemType *base;    //ջ�ף����ݶ��壬��֪�����á�����ǰ�����ٺ�baseΪ�� ��������Ǵ洢Ԫ�صĵط�����������ʽ����˳��ջ�ˣ���
    SElemType *top;     //ջ��ָ�� ��ָ���ֵһ�㶼����һ���Ŀռ�
    int stacksize;      //ջ�Ĵ�С������Ԫ�ظ��������߿ռ��С
}SqStack;

/**ջ�Ĵ���
* sΪ�����ջ��ָ��
*/
Status InitStack(SqStack *s ){
    //����ռ�
    s->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof (SElemType)); //������һ������ ����STACK_INIT_SIZE
    if(!s->base)
        exit(ERROR);    //����ռ�ʧ��
    s->top = s->base;   //ջ����ʼ��
    s->stacksize = STACK_INIT_SIZE; //�ռ��ʼ��
    return OK;

}

/**������Ԫ��
* sΪջ�ĵ�ַ e ΪҪ�����Ԫ��
*/
Status Push(SqStack *s , SElemType e){
    //�ж�ջ�Ƿ�������������Ҫ׷�ӿռ�
    if(s->top - s->base >= s->stacksize){
        s->base = (SElemType*)realloc(s->base, (STACKINREMENT + s->stacksize)*sizeof(SElemType));
        if(!s->base) exit(ERROR);           //����ʧ��

        s->top = s->base + s->stacksize ;    //ջ��ָ��׷�ӿռ�ǰ�� ջ����˵���һ��λ�ã�Ҳ���������ռ�ĵ�һ��λ��
        s->stacksize += STACKINREMENT ;     //�ռ�׷��
    }
    *(s->top++) = e;  //��Ԫ��ѹ��ջ�� �� ���ҽ�ջ��ָ������
    return OK;
}

/**����ջ��Ԫ��
 sΪջ�ĵ�ַ eΪҪ���յ���Ԫ�صı�����ָ�루��ַ��
* ����ֵΪ�ж�ջ�����ĳɹ����
*/
Status Pop(SqStack *s , SElemType *e){
    //���ջ�ǿյģ��򷵻ش���
    if(s->top == s->base) exit(ERROR);
    //���ջ��Ϊ��,ջ��ָ������ ,������ֵ
    *e = *(--s->top);
    return OK;
}

/**��ȡջ��Ԫ��
* s Ϊջ���� eΪ���յ�ջ����Ԫ�صı����ĵ�ַ
*/
Status GetTop(SqStack s , SElemType *e){
    //���ջ��Ϊ�ս���ջ��Ԫ����e���� ����OK
    if(s.top == s.base) return ERROR;
    *e = *(s.top - 1);
    return OK;
}

/**��ȡջ�ĳ��� Ԫ�ظ���
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
