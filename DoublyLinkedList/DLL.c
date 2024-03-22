#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;
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


  while(1)
    {
        printf("\n1. Add node at end\n");
        printf("2. Add node at beginning\n");
        printf("3. Delete node at beginning\n");
        printf("4. Delete node at end\n");
        printf("5.Display list\n");
        printf("Enter choice:\n");
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

                    break;
            case 4:e=deleteAtEnd(&head);
                   printf("the deleted node is %d",e);

                    break;
            case 5: printf("List is:\n");
                    displayList(head);
                    break;
            default:exit(0);

        }
    }


}
void addNodeAtEnd(struct node **head,int e)
{

    struct node *p=(struct node *)malloc(sizeof(struct node));
    if(p==NULL)
    {
        perror("");
        return;
    }
    p->data=e;
    p->next=NULL;
    p->prev=NULL;
    if(*head==NULL)
    {
        *head=p;
    }
    else
    {
        struct node *q=*head;
       while(q->next!=NULL)
       {
          q=q->next;
       }
       q->next=p;
       p->prev=q;

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
    p->next=NULL;
    p->prev=NULL;

    if(*head==NULL)
    {
        *head=p;
    }
    else
    {
        p->next=*head;
       (*head)->prev=p;
       *head=p;
    }



}
int deleteAtBeg(struct node **head)
{
    struct node*p=*head;
    int e;
    *head=(*head)->next;
    e=p->data;
    free(p);
    if(*head!=NULL)
    {
        (*head)->prev=NULL;
    }
    return e;
}
int deleteAtEnd(struct node **head)
{

    struct node *cur=*head;
    int e;
    while(cur->next!=NULL)
    {
        cur=cur->next;
    }
    e=cur->data;
    if(cur->prev!=NULL)
    {
        cur->prev->next=NULL;
    }
    else
            {
              *head=NULL;
            }

    free(cur);
    return e;

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
