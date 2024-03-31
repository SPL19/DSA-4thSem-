#include<stdio.h>
#include<stdlib.h>

struct Passenger {
    int passengerId;
    struct Passenger* next;
};

struct SecurityQueue {
    struct Passenger *rear, *front;
};

struct SecurityQueue* createSecurityQueue();
int isSecurityQueueEmpty(struct SecurityQueue*);
void enqueueSecurity(struct SecurityQueue*, int);
int dequeueSecurity(struct SecurityQueue*);
void processSecurityCheck(FILE*, FILE*);

int main() {
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    if (input == NULL || output == NULL) {
        printf("Error opening files");
        return 1;
    }

    processSecurityCheck(input, output);

    fclose(input);
    fclose(output);
    return 0;
}

struct SecurityQueue* createSecurityQueue() {
    struct SecurityQueue *queue = (struct SecurityQueue*)malloc(sizeof(struct SecurityQueue));
    queue->front = queue->rear = NULL;
    return queue;
}

int isSecurityQueueEmpty(struct SecurityQueue* queue) {
    return (queue->front == NULL);
}

void enqueueSecurity(struct SecurityQueue* queue, int passengerId) {
    struct Passenger *newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger));
    newPassenger->passengerId = passengerId;
    newPassenger->next = NULL;
    if (isSecurityQueueEmpty(queue)) {
        queue->front = queue->rear = newPassenger;
        return;
    }
    queue->rear->next = newPassenger;
    queue->rear = newPassenger;
}

int dequeueSecurity(struct SecurityQueue* queue) {
    if (isSecurityQueueEmpty(queue)) {
        printf("Dequeue not possible\n");
        return -1;
    }
    struct Passenger* temp = queue->front;
    int passengerId = temp->passengerId;
    queue->front = queue->front->next;
    free(temp);
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return passengerId;
}

void processSecurityCheck(FILE *input, FILE *output) {
    struct SecurityQueue* securityQueue = createSecurityQueue();
    int passengerId;
    while (fscanf(input, "%d\n", &passengerId) != EOF) {
        enqueueSecurity(securityQueue, passengerId);
    }
    fprintf(output, "Passengers processed at security check:\n");
    while (!isSecurityQueueEmpty(securityQueue)) {
        int processedPassengerId = dequeueSecurity(securityQueue);
        fprintf(output, "Passenger ID: %d\n", processedPassengerId);
    }
}
