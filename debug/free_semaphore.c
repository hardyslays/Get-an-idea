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

int main()
{
    sem = sem_open(PATH, O_CREAT, 0666, 1);
    if(sem == NULL)
    {
        printf("SEMAPHORE INITIALIZATION FAILED...TERMINATING THE PROGRAM.\n");
        return 1;
    }

    sem_post(sem);
    printf("Success\n");

    return 0;
}