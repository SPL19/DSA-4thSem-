#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

struct Queue {
    int front, rear;
    int capacity;
    int *ticketNumbers;
};

struct Queue* createQueue(int capacity) {
    struct Queue *queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->ticketNumbers = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(struct Queue *queue) {
    return ((queue->rear + 1) % queue->capacity == queue->front);
}

int isEmpty(struct Queue *queue) {
    return (queue->front == -1);
}

void enqueue(struct Queue *queue, int ticketNumber) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->ticketNumbers[queue->rear] = ticketNumber;
    if (queue->front == -1) {
        queue->front = queue->rear;
    }
}

int dequeue(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    int ticketNumber = queue->ticketNumbers[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }
    return ticketNumber;
}

void processTicketCounter(FILE *input, FILE *output) {
    struct Queue *ticketQueue = createQueue(MAX_QUEUE_SIZE);
    int ticketNumber;

    while (fscanf(input, "%d", &ticketNumber) != EOF) {
        enqueue(ticketQueue, ticketNumber);
    }

    fprintf(output, "Ticket Numbers processed at the counter:\n");

    while (!isEmpty(ticketQueue)) {
        int processedTicketNumber = dequeue(ticketQueue);
        fprintf(output, "%d\n", processedTicketNumber);
    }

    free(ticketQueue->ticketNumbers);
    free(ticketQueue); // Free the memory allocated for the queue structure itself
}

int main() {
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    processTicketCounter(input, output);

    fclose(input);
    fclose(output);

    return 0;
}
