#include<stdio.h>
#include<stdlib.h>
struct node
{
    struct node *left;
    int data;
    struct node *right;
};
struct queue
{
    struct node *array;
    int front;
    int rear;
    int capacity;
};
struct queue *createqueue()
{
    struct queue *Q=malloc(sizeof(struct queue));
    if(!Q)
      return NULL;
    Q->capacity=20;
    Q->front=Q->rear=-1;
    Q->array=(struct node*)malloc(Q->capacity*sizeof(struct node));
    return Q;  
}

struct node *createnode(int x)
{
    struct node *newnode;
    newnode=malloc(sizeof(struct node));
    if(!newnode)
        return NULL;
    else
    {
        newnode->left=NULL;
        newnode->data=x;
        newnode->right=NULL;
    }    
    return newnode;
}
struct node *minimum(struct node *root)
{
    struct node *x;
    if(root==NULL)
        root=NULL;
    else if(root->left!=NULL)
    {
        x=minimum(root->left);
        return x;
    }
    printf("\nyour minimum data is  %d",root->data);
    return root;    
}
struct node *insert(struct node *root,int x)
{
    if(root==NULL)
       root=createnode(x);
    else if(x<root->data)
       root->left=insert(root->left,x);
    else
       root->right=insert(root->right,x);
    return root;         
}
struct node *delete(struct node *root,int x)
{
    struct node *temp;
    if(root==NULL)
       return NULL;
    else if(x>root->data)
        root->right=delete(root->right,x);
    else if(x<root->data)
        root->left=delete(root->left,x);
    else
    {
        if(root->left==NULL||root->right==NULL)
        {
            if(root->right==NULL)
            {
                temp=root->left;
                free(root);
                return temp;
            }
            else
            {
                temp=root->right;
                free(root);
                return temp;
            }
        }
        else if(root->left==NULL&&root->right==NULL)
        {
            free(root);
            return NULL;
        }
        else
        {
            temp=minimum(root->right);
            root->data=temp->data;
            root->right=delete(root->right,temp->data);
        }
    }
    return root;        
}
void enqueue(struct node *root)
{
    createqueue();
    struct queue *Q;
    Q->array[++Q->rear]=root;
    return Q;
}
void specificorder(struct node *root)
{
    if(root==NULL)
       return;
    printf("\n%d\n",root->data);
    enqueue(root->left);
    enqueue(root->right);   
}
void inorder(struct node *root)
{
    if(root==NULL)
       return;
    inorder(root->left);
    printf(" %d ",root->data);
    inorder(root->right);   
}
int printlevelorder(struct node *root,int level)
{
    if(root==NULL)
        return NULL;
    else if(level==1)
    {
        printf(" %d ",root->data);
        return 1;
    }
    int left=printlevelorder(root->left,level-1);
    int right=printlevelorder(root->right,level-1);
    return left||right;    
}
void levelorder(struct node *root)
{
    int level=1;
    while(printlevelorder(root,level))
        level++;
}
void main()
{
    struct node *root;
    root=createnode(20);
    insert(root,5);
    insert(root,1);
    insert(root,15);
    insert(root,9);
    insert(root,7);
    insert(root,12);
    insert(root,30);
    insert(root,25);
    insert(root,40);
    insert(root, 45);
    insert(root, 42);
    printf("your inorder traversal is\n");
    inorder(root);
    printf("\n\nyour level order traversal is\n");
    levelorder(root);
    printf("\n");
    minimum(root);
    printf("\n\n");
    delete(root,45);
    printf("your inorder traversal after deletion is\n");
    inorder(root);
    printf("\n\nyour level order traversal after deletion is\n");
    levelorder(root);
}
