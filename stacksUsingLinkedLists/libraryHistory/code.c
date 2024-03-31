#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the stack
struct Node {
    char bookName[100];
    struct Node* next;
};

// Stack structure
struct Stack {
    struct Node* top;
};

// Function to create a new node
struct Node* createNode(char* bookName) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->bookName, bookName);
    newNode->next = NULL;
    return newNode;
}

// Function to push a book onto the stack
void push(struct Stack* stack, char* bookName) {
    struct Node* newNode = createNode(bookName);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a book from the stack
char* pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    struct Node* temp = stack->top;
    stack->top = stack->top->next;
    char* poppedBook = strdup(temp->bookName); // Duplicate book name to return
    free(temp);
    return poppedBook;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

int main() {
    FILE *input, *output;
    char action[10], bookName[100];
    struct Stack* lendingStack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!lendingStack) {
        perror("Memory allocation error");
        return EXIT_FAILURE;
    }
    lendingStack->top = NULL;

    // Open input file for reading
    input = fopen("input.txt", "r");
    if (!input) {
        perror("Error opening input file");
        free(lendingStack);
        return EXIT_FAILURE;
    }

    // Open output file for writing lending history
    output = fopen("output.txt", "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        free(lendingStack);
        return EXIT_FAILURE;
    }

    // Process commands from input file
    while (fscanf(input, "%s %s", action, bookName) != EOF) {
        if (strcmp(action, "Borrow") == 0) {
            push(lendingStack, bookName);
            fprintf(output, "Borrowed: %s\n", bookName);
        } else if (strcmp(action, "Return") == 0) {
            if (!isEmpty(lendingStack)) {
                char* returnedBook = pop(lendingStack);
                fprintf(output, "Returned: %s\n", returnedBook);
                free(returnedBook); // Free duplicated book name memory
            } else {
                fprintf(output, "No books to return\n");
            }
        }
    }

    printf("Lending history written to output.txt\n");

    // Close file pointers
    fclose(input);
    fclose(output);

    // Free allocated memory for stack
    while (!isEmpty(lendingStack)) {
        pop(lendingStack); // Free all remaining nodes
    }
    free(lendingStack); // Free stack itself

    return 0;
}
