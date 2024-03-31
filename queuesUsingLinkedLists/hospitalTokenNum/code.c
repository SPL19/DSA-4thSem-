#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};
struct Queue
{
    struct Node *rear,*front;
};
struct Queue* createQueue();
int isEmpty(struct Queue*);
void enqueue(struct Queue*,int);
int dequeue(struct Queue*);
void processHospitalEmergency(FILE *,FILE *);

int main()
{
    FILE *input,*output;
    input=fopen("input.txt","r");
    output=fopen("output.txt","w");
    if(input==NULL || output==NULL)
    {
        printf("error opening files");
        return 1;

    }
    processHospitalEmergency(input,output);

    fclose(input);
    fclose(output);

}
struct Queue* createQueue()
{
    struct Queue *queue=(struct Queue*)malloc(sizeof(struct Queue));
    queue->front=queue->rear=NULL;
    return queue;
}
int isEmpty(struct Queue* queue)
{
    return (queue->front==NULL);
}
void enqueue(struct Queue* queue,int data)
{
    struct Node *newnode=(struct Node*)malloc(sizeof(struct Node));
    newnode->data=data;
    newnode->next=NULL;
    if(isEmpty(queue))
    {
        queue->front=queue->rear=newnode;
    }
    queue->rear->next=newnode;
    queue->rear=newnode;
}
int dequeue(struct Queue* queue)
{
    if(isEmpty(queue))
    {
        printf("dequeue not possible");
        return -1;
    }
    struct Node* temp=queue->front;
    int data=temp->data;
    queue->front=queue->front->next;
    free(temp);
    if(queue->front==NULL)
    {
        queue->rear=NULL;
    }
    return data;
}
void processHospitalEmergency(FILE *input,FILE *output)
{
    struct Queue* order=createQueue();
    int num;
    while(fscanf(input,"%d\n",&num)!=EOF)
    {
        enqueue(order,num);
    }
    fprintf(output,"appointment number processed is:\n");
    while(!isEmpty(order))
    {
        int a=dequeue(order);
        fprintf(output,"%d\n",a);
    }

    free(order);

}
