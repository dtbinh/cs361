/*
 * CS-450 Fall 2015
 * Demo of IPC using Shared Memory
 * Written By:
 *  1- Dr. Mohamed Aboutabl
 *  Submitted on:
 */
typedef struct {
    int started;
    int finished;
    double d1;
    double d2;
} shared_data;

#define SHMEM_KEY 0x100
#define SHMEM_SIZE sizeof(shared_data)

