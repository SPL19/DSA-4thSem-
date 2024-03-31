#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the stack
struct Node
{
    char data;
    struct Node* next;
};

// Stack structure
struct Stack
{
    struct Node* top;
};
int main()
{
    FILE *input, *output;
    char exp[100];

    // Open input file for reading
    input = fopen("input.txt", "r");
    if (!input)
    {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    // Open output file for writing the result
    output = fopen("output.txt", "w");
    if (!output)

    {
        perror("Error opening output file");
        fclose(input);
        return EXIT_FAILURE;
    }

    // Read expression from input file and check for balanced parentheses
    while (fgets(exp, sizeof(exp), input) != NULL)
    {
        // Remove newline character from the expression
        exp[strcspn(exp, "\n")] = '\0';

        if (isBalanced(exp))
        {
            fprintf(output, "%s - Balanced\n", exp);
        } else
        {
            fprintf(output, "%s - Unbalanced\n", exp);
        }
    }

    printf("Balanced parentheses check completed. Results written to output.txt.\n");

    // Close file pointers
    fclose(input);
    fclose(output);

    return 0;
}


// Function to create a new node
struct Node* createNode(char data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to push an element onto the stack
void push(struct Stack* stack, char data)
{
    struct Node* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop an element from the stack
char pop(struct Stack* stack)
{
    if (stack->top == NULL)
    {
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
int isEmpty(struct Stack* stack)
{
    return stack->top == NULL;
}

// Function to check if two characters form a matching pair of parentheses
int isMatchingPair(char character1, char character2)
{
    if (character1 == '(' && character2 == ')')
        return 1;
    else if (character1 == '{' && character2 == '}')
        return 1;
    else if (character1 == '[' && character2 == ']')
        return 1;
    else
        return 0;
}

// Function to check if the given expression has balanced parentheses
int isBalanced(char exp[])
{
    int i = 0;
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;

    while (exp[i])
    {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
        {
            push(stack, exp[i]);
        } else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
        {
            if (isEmpty(stack))
            {
                free(stack);
                return 0;
            } else
            {
                char poppedChar = pop(stack);
                if (!isMatchingPair(poppedChar, exp[i]))
                {
                    free(stack);
                    return 0;
                }
            }
        }
        i++;
    }
    int result = isEmpty(stack);
    free(stack);
    return result;
}
