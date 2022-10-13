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
    char data;
    struct tree *L;
    struct tree *R;
}tree,*Ptree;

//定义返回节点结构体
typedef struct node{
    int level;
    Ptree tree;
}node,*Pnode;

//递归创建
void create(tree** p_root,char** txt){
    char C = **txt;(*txt)++;
    if(C == '@'){
        *p_root = NULL;
    }
    else{
        *p_root = (Ptree)malloc(sizeof(tree));
        (*p_root)->data = C;
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
    if(root!=NULL){printf("%c",root->data);preorder(root->L);preorder(root->R);}
}

//中序遍历
void inorder(Ptree root){
    if(root){inorder(root->L);printf("%c",root->data);inorder(root->R);}
}

//后序遍历
void postorder(Ptree root){
    if(root){postorder(root->L);postorder(root->R);printf("%c",root->data);}
}

//删除节点及后继
void delete(tree** root){
    if(*root){
        delete(&(*root)->L);
        delete(&(*root)->R);
        free(*root);
        *root = NULL;//！！！！！！！！！！！！！！！！！？？？？？？？？？？
    }
}

//查找并返回元素所在层
void find(Ptree root,char target,int level,bool* flag,Pnode result){
    if(!*flag){//判断是否找到
        if(root){
            if(root->data == target){
                printf("已在第%d层找到了目标元素%c!\n",level,target);
                result->tree = root;
                result->level = level;//以指针返回层数
                *flag = true;//是否找的的标识，若找到后序堆栈都不会对目标节点进行探索
                return;
            }
            find(root->L,target,level+1,flag,result);
            find(root->R,target,level+1,flag,result);
        }
    }
}

int main(void){
    printf("######################_Tree_######################\n");
    printf("Tree example:abd@@efh@@@g@@c@@\n");
    char txt[50];
    char target;//需要寻找的元素
    int level = 0;//首层层数定义为0
    bool delete_bool = true;
    while(true){
        bool flag = false;
        printf("Give me a tree:");
        scanf("%s",txt);
        getchar();
        printf("Give me your target:");
        scanf("%c",&target);
        Ptree myTree = tree_generat(txt);//创建
        Pnode myNode = (Pnode)malloc(sizeof(node));//以指针传入需要返回的内容
        /////////////////////////////////////////////////////////////////////////////////
        printf("###########Start############\n");
        printf("%s\n",txt);
        printf("Preorder :");preorder(myTree);printf("\n");//先序
        printf("Inorder  :");inorder(myTree);printf("\n");//中序
        printf("Postorder:");postorder(myTree);printf("\n");//后序
        find(myTree,target,level,&flag,myNode);
        //printf("已在第%d层找到了目标元素%c!\n",myNode->level,target);
        printf("目标元素子树:\n");
        printf("Preorder :");preorder(myNode->tree);printf("\n");//先序
        printf("Inorder  :");inorder(myNode->tree);printf("\n");//中序
        printf("Postorder:");postorder(myNode->tree);printf("\n");//后序
        //delete(&myNode->tree);//！！！！！！尚未完成！！！！！！！！！！！！！！！删除后无法置空指针！！！！！
        printf("############End#############\n");
    }
}