#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Room {
    int roomNumber;
    char guestName[100];
    struct Room* next;
};

struct Room* createRoomNode(int roomNumber, const char* guestName) {
    struct Room* newNode = (struct Room*)malloc(sizeof(struct Room));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->roomNumber = roomNumber;
    strcpy(newNode->guestName, guestName);
    newNode->next = NULL;
    return newNode;
}

struct Room* insertEnd(struct Room* head, int roomNumber, const char* guestName) {
    struct Room* newNode = createRoomNode(roomNumber, guestName);
    if (head == NULL) {
        return newNode;
    }
    struct Room* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head; // Return head of the list
}

void displayRooms(struct Room* head) {
    printf("Hotel Room Booking Status:\n");
    struct Room* temp = head;
    while (temp != NULL) {
        printf("Room Number: %d, Guest Name: %s\n", temp->roomNumber, temp->guestName);
        temp = temp->next;
    }
}

int main() {
    struct Room* roomList = NULL;
    int roomNumber, numRooms;
    char guestName[100];

    // File handling
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    if (fscanf(input, "%d", &numRooms) != 1) {
        printf("Error reading number of rooms.\n");
        return 1;
    }
    fgetc(input); // Consume newline character

    for (int i = 0; i < numRooms; i++) {
        if (fscanf(input, "%d", &roomNumber) != 1) {
            printf("Error reading room number from file.\n");
            return 1;
        }
        fgetc(input); // Consume newline character

        if (fgets(guestName, sizeof(guestName), input) == NULL) {
            printf("Error reading guest name from file.\n");
            return 1;
        }
        guestName[strcspn(guestName, "\n")] = '\0'; // Remove newline character

        roomList = insertEnd(roomList, roomNumber, guestName);
    }

    // Display room booking status to console
    displayRooms(roomList);

    // Write the room booking status to output file
    fprintf(output, "Hotel Room Booking Status:\n");
    struct Room* temp = roomList;
    while (temp != NULL) {
        fprintf(output, "Room Number: %d, Guest Name: %s\n", temp->roomNumber, temp->guestName);
        temp = temp->next;
    }

    fclose(input);
    fclose(output);

    // Free allocated memory
    while (roomList != NULL) {
        struct Room* temp = roomList;
        roomList = roomList->next;
        free(temp);
    }

    return 0;
}
