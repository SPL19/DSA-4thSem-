#include <stdio.h>
#include <stdlib.h>

struct Node {
    int carId;
    struct Node* next;
};

struct Queue {
    struct Node *front, *rear;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

int isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(struct Queue* queue, int carId) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->carId = carId;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    struct Node* temp = queue->front;
    int carId = temp->carId;

    queue->front = queue->front->next;
    free(temp);

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return carId;
}

void processDriveThrough(FILE *input, FILE *output) {
    struct Queue* orderQueue = createQueue();
    int carId;

    while (fscanf(input, "%d", &carId) != EOF) {
        enqueue(orderQueue, carId);
    }

    fprintf(output, "Orders processed at the drive-through:\n");

    while (!isEmpty(orderQueue)) {
        int processedCarId = dequeue(orderQueue);
        fprintf(output, "Car ID: %d\n", processedCarId);
    }

    free(orderQueue); // Free the queue structure
}

int main() {
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    processDriveThrough(input, output);

    fclose(input);
    fclose(output);

    return 0;
}
