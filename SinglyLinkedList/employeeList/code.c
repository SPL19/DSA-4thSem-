#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct Employee {
    int id;
    char name[50];
    char department[50];
    float salary;
    struct Employee *next;
};

struct Employee* createEmployeeNode(int id, char name[], char department[], float salary) {
    struct Employee* emp = (struct Employee*)malloc(sizeof(struct Employee));
    emp->id = id;
    strcpy(emp->name, name);
    strcpy(emp->department, department);
    emp->salary = salary;
    emp->next = NULL;
    return emp;
}

void addEmployee(struct Employee** head, struct Employee* newEmp) {
    if (*head == NULL) {
        *head = newEmp;
    } else {
        struct Employee* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newEmp;
    }
}

void displayEmployees(struct Employee* head) {
    struct Employee* temp = head;
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Department: %s, Salary: %.2f\n",
               temp->id, temp->name, temp->department, temp->salary);
        temp = temp->next;
    }
}

int main() {
    struct Employee* empList = NULL;
    FILE* input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }
    printf("Input file opened successfully.\n");

    int id;
    char name[50];
    char department[50];
    float salary;

    while (fscanf(input, "%d %s %s %f", &id, name, department, &salary) == 4) {
        struct Employee* newEmp = createEmployeeNode(id, name, department, salary);
        addEmployee(&empList, newEmp);
    }

    fclose(input);
    printf("Employee data read from input file.\n");

    printf("Employee Records:\n");
    displayEmployees(empList);

    // Writing employee records to file
    FILE* output = fopen("output.txt", "w");
    if (output == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }
    printf("Output file opened successfully.\n");

    struct Employee* temp = empList;
    while (temp != NULL) {
        fprintf(output, "%d %s %s %.2f\n", temp->id, temp->name, temp->department, temp->salary);
        temp = temp->next;
    }

    fclose(output);
    printf("Output written to 'output.txt' successfully.\n");

    // Free allocated memory
    while (empList != NULL) {
        struct Employee* temp = empList;
        empList = empList->next;
        free(temp);
    }

    return 0;
}
