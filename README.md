***
---

# Get-an-idea

##INTRODUCTION
This is a producer-consumer problem demonstrating shared memory synchronization and application of semaphore to achieve mutual exclusion in synchronization of memory.

The project consists of two interfaces: a Publisher(also called Developer) and a Consumer(also called Customer). Both interfaces are written in C language and both use POSIX semaphores to acheive their goals.

This application is intended to run on Linux only and **does not have cross platform compilation**.

---

## STEPS OF INSTALLATION

1. First step is to compile the programs. You will need **pthread** and **rt** libraries. Don't worry, they generally come preinstalled with linux distros. To compile the programs:

   > gcc publicher.c -o publisher -lrt -lpthread
   > gcc consumer.c -o consumer -lrt -lpthread

2. After successful compilation of the programs, you can just run them. the DataFile will be created by the program itself, whenever needed.
   > **FOR PUBLISHER:** ./publisher
   > **FOR CONSUMER:** ./consumer

---

## WORKING OF PROGRAMS:

The publisher can perform 2 functionalities:

- Adding a new idea to the Datafile.
- Displaying the list of ideas present in the Datafile.

The consumer can perform 2 functionalities:

- Extracting an idea from the Datafile.
- Displaying the list of ideas present in Datafile.

When the datafile is being accessed by any instance of one of the programs, it is said to be in the **Critical section**, and at that time if any other instance requests for the Datafile, it has to wait till this instance frees the Datafile.
This ensures mutual excluson and avoids the occurance of producer-consumer problem.

---

If you are facing any issue in the program, you can raise an issue in this repo.

### HAPPY CODING!!!

---

---
