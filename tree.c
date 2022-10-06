/*
@File    :   tree.c
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

//先序遍历
void preorder(Ptree root){
    if(root){printf("%d",root->data);preorder(root->L);preorder(root->R);}
}

//中序遍历
void inorder(Ptree root){
    if(root){inorder(root->L);printf("%d",root->data);inorder(root->R);}
}

//后序遍历
void postorder(Ptree root){
    if(root){postorder(root->L);postorder(root->R);printf("%d",root->data);}
}

//删除节点及后继
void delete(tree** root){
    if(*root){
        delete(&(*root)->L);
        delete(&(*root)->R);
        free(*root);
        *root = NULL;
    }
}

//查找并返回元素所在层
void find(Ptree root,int target,int level,bool* flag,int* result,bool delete_bool){
    if(!*flag){//判断是否找到
        if(root){
            if(root->data == target){
                printf("已在第%d层找到了目标元素!\n",level);
                *result = level;//以指针返回层数
                *flag = true;//是否找的的标识，若找到后序堆栈都不会对目标节点进行探索
                if(delete_bool){delete(&root);root = NULL;}//删除节点及后继
                return;
            }
            find(root->L,target,level+1,flag,result,delete_bool);
            find(root->R,target,level+1,flag,result,delete_bool);
        }
    }
}

int main(void){
    bool flag = false;
    bool delete_bool = true;
    int level = 0;//首层层数定义为0
    char txt[] = "1246@7@@@5@9@@3@@";
    printf("%s\n",txt);
    Ptree myTree = tree_generat(txt);//创建
    preorder(myTree);printf("\n");//先序
    inorder(myTree);printf("\n");//中序
    postorder(myTree);printf("\n");//后序
    int myTreeLevel;//以指针传入需要返回的层数
    int target = 5;//需要寻找的元素
    find(myTree,target,level,&flag,&myTreeLevel,delete_bool);
    preorder(myTree);printf("\n");//先序
    printf("End...");
    getchar();
}