#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Node structure for the stack
struct Node {
    char data;
    struct Node* next;
};

// Stack structure
struct Stack {
    struct Node* top;
};

// Function prototypes
void push(struct Stack* stack, char data);
char pop(struct Stack* stack);
int isEmpty(struct Stack* stack);
int isOperator(char c);
int precedence(char op);
void infixToPostfix(char infix[], char postfix[]);

int main() {
    FILE* input, * output;
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    // Open input file for reading
    input = fopen("input.txt", "r");
    if (!input) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    // Open output file for writing the result
    output = fopen("output.txt", "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return EXIT_FAILURE;
    }

    // Read infix expressions from input file and convert to postfix
    while (fgets(infix, sizeof(infix), input) != NULL) {
        // Remove newline character from the infix expression
        infix[strcspn(infix, "\n")] = '\0';

        // Convert infix to postfix
        infixToPostfix(infix, postfix);
        fprintf(output, "Infix: %s\tPostfix: %s\n", infix, postfix);
    }

    printf("Infix to postfix conversion completed. Results written to output.txt.\n");

    // Close file pointers
    fclose(input);
    fclose(output);

    return 0;
}

// Function to push an element onto the stack
void push(struct Stack* stack, char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    struct Node* temp = stack->top;
    stack->top = stack->top->next;
    char poppedData = temp->data;
    free(temp);
    return poppedData;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to get the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}


// Function to convert infix expression to postfix expression
void infixToPostfix(char infix[], char postfix[]) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;

    int i, j;
    char token, popped;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        token = infix[i];

        if (token == '(') {
            push(stack, token);
        } else if (token == ')') {
            while (!isEmpty(stack) && stack->top->data != '(') {
                popped = pop(stack);
                postfix[j++] = popped;
            }
            if (!isEmpty(stack) && stack->top->data == '(') {
                popped = pop(stack); // Discard '('
            }
        } else if (isOperator(token)) { // Operator
            while (!isEmpty(stack) && precedence(token) <= precedence(stack->top->data))
            {
                popped = pop(stack);
                postfix[j++] = popped;
            }
            push(stack, token);
        } else {
            // Append other characters (operands or spaces) directly to postfix
            postfix[j++] = token;
        }
    }

    // Pop remaining operators from the stack
    while (!isEmpty(stack)) {
        popped = pop(stack);
        postfix[j++] = popped;
    }

    postfix[j] = '\0'; // Null-terminate the postfix string

    free(stack);
}
