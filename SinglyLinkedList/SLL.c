#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void addNodeAtEnd(struct node **,int);
void displayList(struct node *);
void addNodeAtBeg(struct node **,int);
int deleteAtBeg(struct node **);
int deleteAtEnd(struct node **);
int main()
{
    struct node *head=NULL;
    int ch;
    int e;
    FILE *input,*output;
    input=fopen("input.txt","r");
    output=fopen("output.txt","w");
    if(input==NULL)
    {
        perror(" ");
        return 1;
    }

  while(1)
    {
        printf("\n1. Add node at end\n");
        printf("2. Add node at beginning\n");
        printf("3. Delete node at beginning\n");
        printf("4. Delete node at end\n");
        printf("5.Display list\n");
        printf("6. enter choice\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("enter data\n");
                    scanf("%d",&e);
                    addNodeAtEnd(&head,e);
                    break;
            case 2:printf("enter data\n");
                    scanf("%d",&e);
                    addNodeAtBeg(&head,e);
                    break;
            case 3:e=deleteAtBeg(&head);
                   printf("the deleted node is %d",e);
                   fprintf(output,"%d\n",e);
                    break;
            case 4:e=deleteAtEnd(&head);
                   printf("the deleted node is %d",e);
                   fprintf(output,"%d\n",e);
                    break;
            case 5: printf("List is:\n");
                    displayList(head);
                    break;
            case 6:exit(0);

        }
    }


}
void addNodeAtEnd(struct node **head,int e)
{
    struct node *q;
    struct node *p=(struct node *)malloc(sizeof(struct node));
    if(p==NULL)
    {
        perror("");
        return;
    }
    p->data=e;
    p->next=NULL;
    if(*head==NULL)
    {
        *head=p;
    }
    else
    {
       q=*head;
       while(q->next!=NULL)
       {
           q=q->next;

       }
       q->next=p;
    }


}
void addNodeAtBeg(struct node **head,int e)
{
    struct node *p=(struct node *)malloc(sizeof(struct node));
    if(p==NULL)
    {
        perror("");
        return;
    }
    p->data=e;
    p->next=*head;
    *head=p;
}
int deleteAtBeg(struct node **head)
{
    struct node*p=*head;
    int e;
    *head=(*head)->next;
    e=p->data;
    free(p);
    return e;
}
int deleteAtEnd(struct node **head)
{
    struct node *prev=NULL;
    struct node *cur=*head;
    int e;
    while(cur->next!=NULL)
    {
        prev=cur;
        cur=cur->next;
    }
    e=cur->data;
    if(prev!=NULL)
    {
        prev->next=NULL;

    }
    else
    {
        *head=NULL;
    }
}

void displayList(struct node *head)
{
    struct node *cur;
    cur=head;
    while(cur!=NULL)
    {

        printf("%d ",cur->data);
        cur=cur->next;
    }
}
