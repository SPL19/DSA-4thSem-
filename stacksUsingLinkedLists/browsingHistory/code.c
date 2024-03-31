#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the stack
struct Node {
    char url[100];
    struct Node* next;
};

// Stack structure
struct Stack {
    struct Node* top;
};

// Function to create a new node
struct Node* createNode(char* url) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->url, url);
    newNode->next = NULL;
    return newNode;
}

// Function to push a URL onto the stack
void push(struct Stack* stack, char* url) {
    struct Node* newNode = createNode(url);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a URL from the stack
char* pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    struct Node* temp = stack->top;
    stack->top = stack->top->next;
    char* poppedUrl = strdup(temp->url); // Duplicate URL to return
    free(temp);
    return poppedUrl;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

int main() {
    struct Stack* historyStack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!historyStack) {
        perror("Memory allocation error");
        return EXIT_FAILURE;
    }
    historyStack->top = NULL;

    FILE *inputFile, *outputFile;
    char url[100];

    // Open input file for reading
    inputFile = fopen("input.txt", "r");
    if (!inputFile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    // Open output file for writing browsing history
    outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Error opening output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    // Read URLs from input file and simulate browsing history
    while (fgets(url, sizeof(url), inputFile) != NULL) {
        // Remove newline character from the URL
        url[strcspn(url, "\n")] = '\0';
        push(historyStack, url);
    }

    // Write browsing history to the output file
    while (!isEmpty(historyStack)) {
        char* visitedUrl = pop(historyStack);
        fprintf(outputFile, "%s\n", visitedUrl);
        free(visitedUrl); // Free duplicated URL memory
    }

    printf("Browsing history written to output.txt\n");

    // Close file pointers
    fclose(inputFile);
    fclose(outputFile);

    // Free allocated memory for stack
    while (!isEmpty(historyStack)) {
        pop(historyStack); // Free all remaining nodes
    }
    free(historyStack); // Free stack itself

    return 0;
}
