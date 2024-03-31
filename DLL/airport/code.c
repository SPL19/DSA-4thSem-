#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Passenger {
    char name[100];
    int id;
    struct Passenger* prev;
    struct Passenger* next;
};

struct Passenger* createPassengerNode(const char* name, int id) {
    struct Passenger* newNode = (struct Passenger*)malloc(sizeof(struct Passenger));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newNode->name, name);
    newNode->id = id;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

struct Passenger* insertEnd(struct Passenger* head, const char* name, int id) {
    struct Passenger *newNode = createPassengerNode(name, id);
    if (head == NULL) {
        return newNode;
    }
    struct Passenger *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head; // Return head of the list
}

void displayPassengers(struct Passenger* head) {
    printf("Passenger List:\n");
    struct Passenger* temp = head;
    while (temp != NULL) {
        printf("Name: %s, ID: %d\n", temp->name, temp->id);
        temp = temp->next;
    }
}

int main() {
    struct Passenger* passengerList = NULL;
    char name[100];
    int id, numPassengers;

    // File handling
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    if (fscanf(input, "%d", &numPassengers) != 1) {
        printf("Error reading number of passengers.\n");
        return 1;
    }
    fgetc(input); // Consume newline character

    for (int i = 0; i < numPassengers; i++) {
        if (fgets(name, sizeof(name), input) == NULL) {
            printf("Error reading name from file.\n");
            return 1;
        }
        name[strcspn(name, "\n")] = '\0'; // Remove newline character

        if (fscanf(input, "%d", &id) != 1) {
            printf("Error reading ID from file.\n");
            return 1;
        }
        fgetc(input); // Consume newline character

        passengerList = insertEnd(passengerList, name, id);
    }

    // Display passenger list 
    displayPassengers(passengerList);

    // Write the passenger list to output file
    fprintf(output, "Passenger List:\n");
    struct Passenger* temp = passengerList;
    while (temp != NULL) {
        fprintf(output, "Name: %s, ID: %d\n", temp->name, temp->id);
        temp = temp->next;
    }

    fclose(input);
    fclose(output);

    // Free allocated memory
    while (passengerList != NULL) {
        struct Passenger* temp = passengerList;
        passengerList = passengerList->next;
        free(temp);
    }

    return 0;
}
