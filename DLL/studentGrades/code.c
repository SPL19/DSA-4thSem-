#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[100];
    int id;
    float grade;
    struct Student* prev;
    struct Student* next;
};

struct Student* createStudentNode(const char* name, int id, float grade) {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newNode->name, name);
    newNode->id = id;
    newNode->grade = grade;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

struct Student* insertEnd(struct Student* head, const char* name, int id, float grade) {
    struct Student *newNode = createStudentNode(name, id, grade);
    if (head == NULL) {
        return newNode;
    }
    struct Student *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head; // Return head of the list
}

void displayGradeBook(struct Student* head) {
    printf("Student Grade Book:\n");
    struct Student* temp = head;
    while (temp != NULL) {
        printf("Name: %s, ID: %d, Grade: %.2f\n", temp->name, temp->id, temp->grade);
        temp = temp->next;
    }
}

int main() {
    struct Student* gradeBook = NULL;
    char name[100];
    int id, numStudents;
    float grade;

    // File handling
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    if (fscanf(input, "%d", &numStudents) != 1) {
        printf("Error reading number of students.\n");
        return 1;
    }
    fgetc(input); // Consume newline character

    for (int i = 0; i < numStudents; i++) {
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

        if (fscanf(input, "%f", &grade) != 1) {
            printf("Error reading grade from file.\n");
            return 1;
        }
        fgetc(input); // Consume newline character

        gradeBook = insertEnd(gradeBook, name, id, grade);
    }

    // Display grade book to console
    displayGradeBook(gradeBook);

    // Write the grade book contents to output file
    fprintf(output, "Student Grade Book:\n");
    struct Student* temp = gradeBook;
    while (temp != NULL) {
        fprintf(output, "Name: %s, ID: %d, Grade: %.2f\n", temp->name, temp->id, temp->grade);
        temp = temp->next;
    }

    fclose(input);
    fclose(output);

    // Free allocated memory
    while (gradeBook != NULL) {
        struct Student* temp = gradeBook;
        gradeBook = gradeBook->next;
        free(temp);
    }

    return 0;
}
