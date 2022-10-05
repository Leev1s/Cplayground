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
#include <string.h>

//定义树结构体
typedef struct tree{
    int data;
    struct tree *L;
    struct tree *R;
}tree,*Ptree;

//递归创建
void create(tree** p_root,char** txt){
    char C = **txt;(*txt)++;
    if(C == '@'){
        *p_root = NULL;
    }
    else{
        *p_root = (Ptree)malloc(sizeof(tree));
        (*p_root)->data = C - '0';
        create(&(*p_root)->L,txt);
        create(&(*p_root)->R,txt);
    }
}

//通过字符串创建树
Ptree tree_generat(char* txt){
    tree** p_root = (tree**)malloc(sizeof(tree**));
    char** pt = &txt;
    create(p_root,pt);
    return *p_root;//返回root
}

int main(void){
    char txt[] = "1246@7@@@5@9@@@3@@";
    char* pt = txt;
    printf("%s\n",pt);
    printf("%d\n",(int)strlen(txt));
    Ptree root = tree_generat(txt);
    getchar();
}