#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct musicPlaylist
{
    char songName[100];
    char artistName[100];
    struct musicPlaylist* next;
    struct musicPlaylist* prev;

};

struct musicPlaylist* createNode( const char songName[],const char artistName[])
{
    struct musicPlaylist* newnode=(struct musicPlaylist*)malloc(sizeof(struct musicPlaylist));
    if(newnode==NULL)
    {
        printf("error");
        exit(1);
    }
    newnode->next=NULL;
    newnode->prev=NULL;
    strcpy(newnode->songName,songName);
    strcpy(newnode->artistName,artistName);

    return newnode;

}

 struct musicPlaylist* insertAtEnd(struct musicPlaylist* head,const char songName[],const char artistName[])
{
    struct musicPlaylist* newnode=createNode(songName,artistName);
    if(head==NULL)
    {
        return newnode;
    }
  struct musicPlaylist *temp=head;

  while(temp->next)
  {
     temp=temp->next;
  }
  temp->next=newnode;
  newnode->next=NULL;
  newnode->prev=temp;

  return head;
}

void displayPlaylist(struct musicPlaylist* head)
{
    printf("Music Playlist:\n");
    struct musicPlaylist* temp = head;
    while (temp != NULL)
    {
        printf("Title: %s, Artist: %s\n", temp->songName, temp->artistName);
        temp = temp->next;
    }
}

int main()
{
    struct musicPlaylist* list=NULL;
    char songName[30],artistName[30];
    int numSongs;
    FILE *input=fopen("input.txt","r");
    FILE *output=fopen("output.txt","w");
    if(input==NULL || output==NULL)
    {
        printf("error");
        return 1;
    }
    if(fscanf(input,"%d",&numSongs)!=1)
    {
        printf("error\n");
        return 1;
    }
    fgetc(input);
    for(int i=0;i<numSongs;i++)
    {
        if(fgets(songName,sizeof(songName),input)==NULL)
        {
        printf("error\n");
        return 1;
        }
        songName[strcspn(songName,"\n")]='\0';
        if(fgets(artistName,sizeof(artistName),input)==NULL)
        {
        printf("error\n");
        return 1;
        }
        artistName[strcspn(artistName,"\n")]='\0';

        list=insertAtEnd( list, songName,artistName);
    }

        displayPlaylist(list);
        fprintf(output,"Playlist:\n");
        struct musicPlaylist* temp=list;
         while (temp != NULL)
    {
        fprintf(output, "song: %s artist: %s\n", temp->songName, temp->artistName);
        temp = temp->next;
    }

    fclose(input);
    fclose(output);


    while (list != NULL)
    {
        struct musicPlaylist* temp = list;
        list = list->next;
        free(temp);
    }

    return 0;
}


