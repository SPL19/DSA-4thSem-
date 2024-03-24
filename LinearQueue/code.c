#include <stdio.h>
#define size 10

struct queue
{
    int front;
    int rear;
    int a[size];
};

void initQueue(struct queue *q)
{
    q->front = -1;
    q->rear = -1;
}

int isEmpty(struct queue *q)
{
    return q->front == -1;
}

int isFull(struct queue *q)
{
    return q->rear == size - 1;
}

void enQueue(struct queue *q, int d, FILE *output)
{
    if (isFull(q))
    {
        fprintf(output, "Queue is FULL\n");
        return;
    }
    if (isEmpty(q))
    {
        q->front = q->rear = 0;
    }
    else
    {
        q->rear = q->rear + 1;
    }
    q->a[q->rear] = d;
}

int deQueue(struct queue *q, FILE *output)
{
    if (isEmpty(q))
    {
        fprintf(output, "Queue is Empty\n");
        return -1;
    }
    int d = q->a[q->front];
    if (q->front == q->rear)
    {
        q->front = q->rear = -1;
    }
    else
    {
        q->front = q->front + 1;
    }
    return d;
}

void display(struct queue *q, FILE *output)
{
    if (isEmpty(q))
    {
        fprintf(output, "Queue is Empty\n");
        return;
    }
    fprintf(output, "Queue elements are:\n");
    for (int i = q->front; i <= q->rear; i++)
    {
        fprintf(output, "%d\n", q->a[i]);
    }
}

int main()
{
    struct queue q;
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    if (input == NULL || output == NULL)
    {
        printf("Error in opening file.\n");
        return -1;
    }
    initQueue(&q);
    int val, n;
    char operation;
    while (fscanf(input, " %c", &operation) != EOF)
    {
        switch (operation)
        {
        case 'A':
            fscanf(input, " %d", &val);
            enQueue(&q, val, output);
            break;
        case 'B':
            n = deQueue(&q, output);
            fprintf(output, "Dequeued element: %d\n", n);
            break;
        case 'C':
            display(&q, output);
            break;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
