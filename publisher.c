#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#define PATH "ideas.bin"

sem_t *sem;

struct Idea
{
    char topic[50];
    char desc[150];
};

void printAll()
{
    system("clear");

    printf("FILE IS CURRENTLY IN EDIT MODE AND IS BEING USED BY ANOTHER USER\n\nWAITING FOR DATAFILE TO BECOME IDLE...\n");
    sem_wait(sem);
    
    system("clear");

    FILE *f = fopen(PATH, "rb+");

    if(f == NULL)
    {
        printf("FILE IS NOT YET CREATED....ADD SOME IDEAS FIRST TO CREATE THE FILE.\n\n\n");
        sem_post(sem);
        printf("\nPRESS ENTER TO RETURN TO MAIN MENU.");
        getchar();
        return;
    }
    
    struct Idea id;
    fseek(f, 0, SEEK_SET);

    printf("************************************************\n");
    printf(" LIST OF IDEAS:\n");
    printf("************************************************\n");

    int i = 1;
    while (fread(&id, sizeof(id), 1, f))
    {
        printf("\n IDEA %d:\n", i);
        printf("  TOPIC:\n\t%s", id.topic);
        printf("  DESCRIPTION:\n\t%s", id.desc);

        i++;
    }
    printf("************************************************\n");
    printf("************************************************\n\n");


    fclose(f);
    sem_post(sem);

    
    printf("\nPRESS ENTER TO RETURN TO MAIN MENU.\n");
    getchar();
}

void addIdea()
{
    system("clear");

    printf("FILE IS CURRENTLY IN EDIT MODE AND IS BEING USED BY ANOTHER USER\n\nWAITING FOR DATAFILE TO BECOME IDLE...\n");
    sem_wait(sem);
    system("clear");

    FILE *f = fopen(PATH, "rb+");
    
    if(f == NULL)
    {
        f = fopen(PATH, "wb+");
    }

    fseek(f, 0, SEEK_END);

    struct Idea id;
    
    printf("================================================\n");
    printf("            ADDING A NEW IDEA:\n");
    printf("================================================\n\n");
    printf("    TOPIC OF THE IDEA(MAX 50 CHARACTERS):  ");
    fgets(id.topic, 50, stdin);
    printf("    DESCRIPTION OF THE IDEA(MAX 150 CHARACTERS):  ");
    fgets(id.desc, 150, stdin);
    
    fwrite(&id, sizeof(id), 1, f);

    fclose(f);
    sem_post(sem);
    
    printf("\nSUCCESSFULLY ADDED THE IDEA.\nPRESS ENTER TO RETURN TO MAIN MENU.\n");
    getchar();
}

int main()
{
    sem = sem_open(PATH, O_CREAT, 0666, 1);
    if(sem == NULL)
    {
        printf("SEMAPHORE INITIALIZATION FAILED...TERMINATING THE PROGRAM.\n");
        return 1;
    }
    
    int choice;
    do
    {
        system("clear");
        printf("================================================\n");
        printf("             HEY THERE DEVELOPER :)\n");
        printf("================================================\n\n");
        
        printf("    WHAT WOULD YOU LIKE TO DO TODAY?\n");
        printf("************************************************\n");
        printf("        1. SEE ALL THE CURRENT IDEAS.\n");
        printf("        2. ADD A NEW IDEA TO THE LIST.\n");
        printf("        3. EXIT.\n");
        
        printf("\nPLEASE ENTER YOUR CHOICE:    ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice)
        {
            case 1:
                printAll();
                break;
            
            case 2:
                addIdea();
                break;
            case 3:
                printf("******************************************************\n");
                printf(" THANK YOU FOR YOUR CONTRIBUTION.....HAVE A GOOD DAY\n");
                printf("******************************************************\n");
                exit(0);        
            default:
                break;
        }

    }while (choice != 3);

    return 0;
}