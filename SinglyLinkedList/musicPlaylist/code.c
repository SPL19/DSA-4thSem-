#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song {
    char title[100];
    char artist[100];
    struct Song* next;
};

struct Song* createSongNode(const char* title, const char* artist) {
    struct Song* newNode = (struct Song*)malloc(sizeof(struct Song));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newNode->title, title);
    strcpy(newNode->artist, artist);
    newNode->next = NULL;
    return newNode;
}

struct Song* insertEnd(struct Song* head, const char* title, const char* artist) {
    struct Song *newNode = createSongNode(title, artist);
    if (head == NULL) {
        return newNode;
    }
    struct Song *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head; // Return head of the list
}

void displayPlaylist(struct Song* head) {
    printf("Music Playlist:\n");
    struct Song* temp = head;
    while (temp != NULL) {
        printf("Title: %s, Artist: %s\n", temp->title, temp->artist);
        temp = temp->next;
    }
}

int main() {
    struct Song* playlist = NULL;
    char title[100], artist[100];
    int numSongs;

    // File handling
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    if (fscanf(input, "%d", &numSongs) != 1) {
        printf("Error reading number of songs.\n");
        return 1;
    }
    fgetc(input); // Consume newline character

    for (int i = 0; i < numSongs; i++) {
        if (fgets(title, sizeof(title), input) == NULL) {
            printf("Error reading title from file.\n");
            return 1;
        }
        title[strcspn(title, "\n")] = '\0'; // Remove newline character

        if (fgets(artist, sizeof(artist), input) == NULL) {
            printf("Error reading artist from file.\n");
            return 1;
        }
        artist[strcspn(artist, "\n")] = '\0'; // Remove newline character

        playlist = insertEnd(playlist, title, artist);
    }

    // Display playlist to console
    displayPlaylist(playlist);

    // Write the playlist contents to output file
    fprintf(output, "Music Playlist:\n");
    struct Song* temp = playlist;
    while (temp != NULL) {
        fprintf(output, "Title: %s, Artist: %s\n", temp->title, temp->artist);
        temp = temp->next;
    }

    fclose(input);
    fclose(output);

    // Free allocated memory
    while (playlist != NULL) {
        struct Song* temp = playlist;
        playlist = playlist->next;
        free(temp);
    }

    return 0;
}
