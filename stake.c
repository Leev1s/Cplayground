/*
@File    :   stake.c
@Time    :   2022/10/03 20:05:17
@Author  :   Lev1s
@Version :   1.0
@Contact :   Lev1sStudio.cn@gmail.com
@PW      :   http://Lev1s.cn
@Github  :   https://github.com/o0Lev1s0o
    __             ___           ______
   / /   ___ _   _<  /____      / ____/
  / /   / _ \ | / / / ___/_____/ /     
 / /___/  __/ |/ / (__  )_____/ /___   
/_____/\___/|___/_/____/      \____/                                      
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

typedef int STdataType;
typedef struct stake
{
    STdataType* data;
    int top;
    int capacity;
}*Stack;

/////////////////////函数列表//////////////////////
Stack StackInit(int x);//栈的初始化          
void StackDestory(Stack p);//栈的销毁        
void StackPush(Stack p, STdataType x);//入栈
STdataType StackPop(Stack p);//出栈               
bool StackEmpty(Stack p);//判断栈是否为空    
STdataType StackTop(Stack p);//取栈顶元素
void StackPrinter(Stack P);//打印栈   
//////////////////////////////////////////////////

//栈的初始化 
Stack StackInit(int x){
    Stack p = (Stack)malloc(sizeof(Stack));
    p->data = (STdataType*)malloc(x * sizeof(STdataType));
    p->capacity = x;
    p->top = 0;
    puts("Stack Initiated");
    return p;
}

//栈的销毁 
void StackDestory(Stack p){
    free(p->data);
    free(p);
    puts("Stack Cleared");
}

//入栈
void StackPush(Stack p, STdataType x){
    if(p->top < p->capacity && p->top >=0){
        p->data[p->top] = x;
        p->top++;
        //puts("Push Succeed");
    }
    else{
        //puts("Stack Full!");
    }
}

//出栈
STdataType StackPop(Stack p){
    if(p->top <= p->capacity && p->top > 0){
        STdataType x = p->data[p->top - 1];
        p->top--;
        //printf("%d ", x);////////////////////////////////////////
        //puts("Pop Succeed");/////////////////////////////////////
        return x;
    }
    else{
        puts("Stack Already Empty!");
        return 0;
    }
}

//判断栈是否为空
bool StackEmpty(Stack p){
    return p->top == 0;
}

//打印栈
void StackPrinter(Stack p){
    if(p->top > 0){
        for(int i = p->top - 1; i >= 0; i--){
            printf("[%d]<-|\n", p->data[i]);
        }
        //puts("Print Finished");
    }
    else{
        puts("Empty!");
    }
}

void test(int n){
    Stack myStack = StackInit(n);
    for(int i = 0; i < n; i++){
        StackPush(myStack,i);
    }
    while(!StackEmpty(myStack)){
        //StackPrinter(myStack);
        StackPop(myStack);
    }
    StackDestory(myStack);    
}

void test_time(){
    clock_t start,stop;
    start = clock();
    test(100);
    stop = clock();
    printf("Tick Per Second:%d\n",CLOCKS_PER_SEC);
    printf("%f\n",(double)(stop-start));
    printf("S:%f\n",((double)(stop-start))/CLOCKS_PER_SEC);//For macos
    //printf("%f\n",((double)(stop-start))/CLK_TCK);

}

int main(void){
    test(5);
    getchar();
}