#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/types.h>
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
        printf("NO IDEAS ADDED TO THE LIST BY THE DEVELOPERS.....PLEASE WAIT FOR THE DEVELOPERS TO ADD SOME NEW IDEAS.\n\n\n");
        printf("\nPRESS ENTER TO RETURN TO MAIN MENU.\n");
        getchar();
        sem_post(sem);
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

void getIdea()
{
    system("clear");

    printf("FILE IS CURRENTLY IN EDIT MODE AND IS BEING USED BY ANOTHER USER\n\nWAITING FOR DATAFILE TO BECOME IDLE...\n");
    sem_wait(sem);
    system("clear");

    FILE *f = fopen(PATH, "rb+");
    
    if(f == NULL)
    {
        printf("NO IDEAS CURRENTLY IN THE DATA FILES.....PLEASE WAIT FOR THE DEVELOPERS TO ADD SOME NEW IDEAS.");
        printf("\n\nPRESS ENTER TO RETURN TO MAIN MENU.\n");
        getchar();
        sem_post(sem);
        return;
    }

    fseek(f, 0, SEEK_END);

    struct Idea id;
    printf("================================================\n");
    printf("              CHOOSING AN IDEA:\n");
    printf("================================================\n\n");

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
    i--;
    printf("************************************************\n");
    printf("************************************************\n\n");

    fclose(f);

    int choice;
    printf("ENTER THE IDEA NUMBER YOU WISH TO CHECKOUT, OR ENTER -1 TO EXIT:    ");
    scanf("%d", &choice);
    
    while((choice <= 0 && choice != -1) || choice > i)
        {
            printf("WRONG CHOICE ENTERED....PLEASE ENTER YOUR CHOICE AGAIN:    ");
            scanf("%d", &choice);
        }
    
    FILE *temp = fopen("temp.bin", "wb+");
    f = fopen(PATH, "rb");
    struct Idea tempId;
    
    fseek(f, 0, SEEK_SET);
    fseek(temp, 0, SEEK_SET);
    
    for (int j = 1; j < i+(choice == -1); j++)
    {
        if(j == choice)fseek(f, sizeof(tempId), SEEK_CUR);
        fread(&tempId, sizeof(tempId), 1, f);
        fwrite(&tempId, sizeof(tempId), 1, temp);
    }
    fclose(temp);
    remove(PATH);
    rename("temp.bin", PATH);
    
    if(choice == -1)printf("\n\n  NO IDEA SELECTED FOR CHECKOUT.....PRESS ENTER TO RETURN TO MAIN MENU.\n");
    else printf("\nSUCCESSFULLY COLLECTED THE IDEA.\nPRESS ENTER TO RETURN TO MAIN MENU.\n");

    sem_post(sem);
    getchar();
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
        printf("             HEY THERE CUSTOMER :)\n");
        printf("================================================\n\n");
        
        printf("    WHAT WOULD YOU LIKE TO DO TODAY?\n");
        printf("************************************************\n");
        printf("        1. SEE ALL THE CURRENT IDEAS.\n");
        printf("        2. CHOOSE AN IDEA FROM THE LIST.\n");
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
                getIdea();
                break;
            case 3:
                printf("******************************************************\n");
                printf(" THANK YOU VERY MUCH.....HAVE A GOOD DAY\n");
                printf("******************************************************\n");
                exit(0);        
            default:
                break;
        }

    }while (choice != 3);

    return 0;
}