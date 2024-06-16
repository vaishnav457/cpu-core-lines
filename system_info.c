#include <stdio.h>
#include<string.h>
#include <stdlib.h>


#define PROC_CPUINFO "/proc/cpuinfo"
#define PROC_MEMINFO "/proc/meminfo"

int get_cpu_cores() 
{
    FILE *cpuinfo = fopen(PROC_CPUINFO, "r");
    if (cpuinfo == NULL) 
	{
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    char line[256];
    int cpu_cores = 0;
    while (fgets(line, sizeof(line), cpuinfo) != NULL) 
	{
        if (strncmp(line, "processor", 9) == 0) 
		{
            cpu_cores++;
        }
    }
    fclose(cpuinfo);
    return cpu_cores;
}

void get_memory_info(long *total_memory, long *free_memory) 
{
    FILE *meminfo = fopen(PROC_MEMINFO, "r");
    if (meminfo == NULL) 
	{
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    char line[256];
    while (fgets(line, sizeof(line), meminfo) != NULL) 
	{
        if (sscanf(line, "MemTotal: %ld kB", total_memory) == 1) 
		{
            continue;
        }
        if (sscanf(line, "MemFree: %ld kB", free_memory) == 1) 
		{
            continue;
        }
    }

    fclose(meminfo);
}

int main(int argc, char *argv[]) 
{
    int cpu_cores = get_cpu_cores();
    long total_memory = 0, free_memory = 0;

    get_memory_info(&total_memory, &free_memory);

    printf("Number of CPU cores: %d\n", cpu_cores);
    printf("Total Memory: %ld kB\n", total_memory);
    printf("Free Memory: %ld kB\n", free_memory);
    printf("Used Memory: %ld kB\n", total_memory - free_memory);

    return 0;
}

