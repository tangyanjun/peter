/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  BeTree.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(08/05/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "08/05/2017 07:36:41 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct BTree{
    char data;
    struct BTree *lChild;
    struct BTree *rChild;
} BinTree;



BinTree* CreateTree(BinTree *p)
{
    char ch;
    scanf("%c", &ch);
    if(ch == '#')
    {
        return NULL;
    }

    p = (BinTree*)malloc(sizeof(BinTree));
    p->data = ch;
    p->lChild = CreateTree(p->lChild);
    p->rChild = CreateTree(p->rChild);
    return p;
}

  
BinTree* BTreeSetNull(BinTree* tree)
{
    if(NULL == tree)
    {
        return;
    }
    BTreeSetNull(tree->lChild);
    BTreeSetNull(tree->rChild);
    free(tree);
    tree = NULL;
    return tree;
}



void PreOrder(BinTree *T)
{
    if(T)
    {
        printf("%c", T->data);
        PreOrder(T->lChild);
        PreOrder(T->rChild);
    }
}



void InfixOrder(BinTree *T)
{
    if(T)
    {
        InfixOrder(T->lChild);
        printf("%c", T->data);
        InfixOrder(T->rChild);
    }
}



void Epilogue(BinTree *T)
{
    if(T)
    {
        Epilogue(T->lChild);
        Epilogue(T->rChild);
        printf("%c", T->data);
    }
}



int Depth(BinTree *T)
{
    int dep = 0;
    int depl = 0;
    int depr = 0;

    if(!T)
    {
        dep = 0;
    }
    else
    {
        depl = Depth(T->lChild);
        depr = Depth(T->rChild);
        dep = (depl > depr ? depl : depr);
    }
    return dep;
}




BinTree* CopyBtree(BinTree* root)
{
    BinTree* newnode;
    if(!root)
    {
        return NULL;
    }
    else
    {
        newnode = (BinTree*)malloc(sizeof(BinTree));
        newnode->data = root->data;
        newnode->lChild = CopyBtree(root->lChild);
        newnode->rChild = CopyBtree(root->rChild);
        return newnode;
    }
}




int Leaf(BinTree *T)
{
    int sum = 0;
    int m = 0;
    int n = 0;

    if(T)
    {
        if((!T->lChild) && (!T->rChild))
        {
            sum++;
        }

        m = Leaf(T->lChild);
        sum += m;

        n = Leaf(T->rChild);
        sum += m;
    }
    return sum;
}


int main(int argc, char **argv)
{
    BinTree* Tree;
    Tree = CreateTree(Tree);
    PreOrder(Tree);
    printf("\n");
    InfixOrder(Tree);
    printf("\n");

    Tree =  BTreeSetNull(Tree);

    InfixOrder(Tree);
    return 0;
}
