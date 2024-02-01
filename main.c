#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char*data;
    struct node*left;
    struct node*right ;
} node;
node *newnode(char *value)
{
    node*n=malloc(sizeof(node));
    n->data=malloc(strlen(value)+1);
    strcpy(n->data,value);
    n->left=NULL;
    n->right=NULL;
    return n;
}
void Inorder(node*root)
{
    if(root!=NULL)
    {
        Inorder(root->left);
        printf("%s\n",root->data);
        Inorder(root->right);
    }
}
node*insert(node*node,char*key)
{
    if(node==NULL)
        return newnode(key);
    if(strcasecmp(key,node->data)<0)
        node->left=insert(node->left,key);
    else if(strcasecmp(key,node->data)>0)
        node->right=insert(node->right,key);
    return node;
}
node *searchtree(node *root, char* value)
{
    if(root==NULL)
        return NULL;
    if(strcasecmp(root->data,value)==0)
        return root;
    else if (strcasecmp(root->data,value)>0)
        return searchtree(root->left,value);
    else
        return searchtree(root->right,value);
}
int count (node *root)
{
    if(root==NULL)
        return 0;
    else
        return 1+ count(root->left)+count(root->right);
}
int getmaximum(int num1,int num2)
{
    if (num1>num2)
        return num1;
    return num2;
}
int treeheight(node*root)
{
    if(root==NULL)
        return 0;
    return 1+getmaximum(treeheight(root->left),treeheight(root->right));
}
node*lastnode(node*root,char*value)
{
    if(root==NULL)
        return NULL;
    if(strcasecmp(value,root->data)<0)
    {
        if(root->left==NULL)
            return root;
        return lastnode(root->left,value);
    }
    else if(root->right==NULL)
        return root;
    return lastnode(root->right,value);
}
node*mininode(node*root)
{
    if(root==NULL)
        return NULL;
    else if(root->left==NULL)
        return root;
    else
        return mininode(root->left);
}
node*maxinode(node*root)
{
    if(root==NULL)
        return NULL;
    else if(root->right==NULL)
        return root;
    else
        return maxinode(root->right);
}
node*successor(node*treeroot,char*value)
{
    //minimum in right if it has a right child
    node*success=NULL;
    node*temp=treeroot;
    while(temp!=NULL)
    {
        if(strcasecmp(value,temp->data)<0)
        {
            success=temp;
            temp=temp->left;
        }
        else if(strcasecmp(value,temp->data)>0)
            temp=temp->right;
        else
        {
            if(temp->right!=NULL)
                return mininode(temp->right);
            else
                return success;
        }
    }
}
node*predecessor(node*treeroot,char*value)
{
    //maximum in left if it has a left child
    node*pre=NULL;
    node*temp=treeroot;
    while(temp!=NULL)
    {
        if(strcasecmp(value,temp->data)>0)
        {
            pre=temp;
            temp=temp->right;
        }
        else if(strcasecmp(value,temp->data)<0)
            temp=temp->left;


        else
        {
            if(temp->left!=NULL)
                return maxinode(temp->left);
            else
                return pre;
        }
    }

}
int main()
{
    node *treeroot= NULL;
    FILE *f= fopen("EN-US-Dictionary.txt","r");
    char exep[30];
    while(!feof(f))
    {
        fscanf(f,"%s",exep);
        treeroot=insert(treeroot,exep);
    }
    if(f)
        printf("Dictionary Loaded Successfully!\n...............................\n");
    printf("Size = %d\n...............................\n",count(treeroot));
    //Inorder(treeroot);
    printf("Height = %d\n...............................\n",treeheight(treeroot));
    char x[100];
    while(1)
    {
        printf("Choose one of the following options\n");
        printf("1.Search\n2.Quit\n");
        gets(x);
        if(strcmp(x,"1")==0)
        {
            char fullsent[200];
            printf("Enter a sentence:\n");
            gets(fullsent);
            char *word= strtok(fullsent," ");
            while(word!=NULL)
            {
                node*srch=searchtree(treeroot,word);
                if(srch!=NULL)
                {
                    printf("\n%s - Found\n",word);
                }
                else
                {
                    printf("\n%s - Not Found, \nSuggestions : ",word);
                    node*firstsug=lastnode(treeroot,word);
                    printf("1.%s ",firstsug->data);
                    node*success=successor(treeroot,firstsug->data);
                    if(success!=NULL)
                        printf("2.%s ",success->data);
                    node*pre=predecessor(treeroot,firstsug->data);
                    if(pre!=NULL)
                        printf("3.%s",pre->data);
                     printf("\n");
                }
                word=strtok(NULL," ");

            }
        }

    else if(strcmp(x,"2")==0)
        exit(0);
    else
        printf("\nEnter a valid number\n");
}


    return 0;
}
