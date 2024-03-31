#include <stdio.h>
#include <stdlib.h>

struct Customer {
    int customerId;
    struct Customer* next;
};

struct CheckoutQueue {
    struct Customer *rear, *front;
};

struct CheckoutQueue* createCheckoutQueue();
int isCheckoutQueueEmpty(struct CheckoutQueue*);
void enqueueCheckout(struct CheckoutQueue*, int);
int dequeueCheckout(struct CheckoutQueue*);
void processSupermarketCheckout(FILE*, FILE*);

int main() {
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    if (input == NULL || output == NULL) {
        printf("Error opening files");
        return 1;
    }

    processSupermarketCheckout(input, output);

    fclose(input);
    fclose(output);
    return 0;
}

struct CheckoutQueue* createCheckoutQueue() {
    struct CheckoutQueue *queue = (struct CheckoutQueue*)malloc(sizeof(struct CheckoutQueue));
    queue->front = queue->rear = NULL;
    return queue;
}

int isCheckoutQueueEmpty(struct CheckoutQueue* queue) {
    return (queue->front == NULL);
}

void enqueueCheckout(struct CheckoutQueue* queue, int customerId) {
    struct Customer *newCustomer = (struct Customer*)malloc(sizeof(struct Customer));
    newCustomer->customerId = customerId;
    newCustomer->next = NULL;
    if (isCheckoutQueueEmpty(queue)) {
        queue->front = queue->rear = newCustomer;
        return;
    }
    queue->rear->next = newCustomer;
    queue->rear = newCustomer;
}

int dequeueCheckout(struct CheckoutQueue* queue) {
    if (isCheckoutQueueEmpty(queue)) {
        printf("Dequeue not possible\n");
        return -1;
    }
    struct Customer* temp = queue->front;
    int customerId = temp->customerId;
    queue->front = queue->front->next;
    free(temp);
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return customerId;
}

void processSupermarketCheckout(FILE *input, FILE *output) {
    struct CheckoutQueue* checkoutQueue = createCheckoutQueue();
    int customerId;
    while (fscanf(input, "%d\n", &customerId) != EOF) {
        enqueueCheckout(checkoutQueue, customerId);
    }
    fprintf(output, "Customers processed at checkout:\n");
    while (!isCheckoutQueueEmpty(checkoutQueue)) {
        int processedCustomerId = dequeueCheckout(checkoutQueue);
        fprintf(output, "Customer ID: %d\n", processedCustomerId);
    }
}
