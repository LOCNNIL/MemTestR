#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <time.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[94m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define END     "\033[0m"

volatile bool shouldExit = false;

void print_help(char *name){
  printf(BLUE " Usage: %s <size> <unit> <interval>  \n\
          This program runs a loop that alocatates the giving <size> of\n \
          memory considering the giving <unit> (acepted units: B, KB, MB, GB). \n\
          and keeps alocating and dealocating this memory each <interval> (s) \n" END, name);
}

// Signal handler for CTRL+C
void signalHandler(int signal) {
    if (signal == SIGINT) {
        shouldExit = true;
    }
}

int select_multipliyer(char *unit){
  if(strcmp(unit, "B") == 0){
    return 1;
  } else if(strcmp(unit, "KB") == 0){
    return 1024;
  } else if(strcmp(unit, "MB") == 0){
    return 1024*1024;
  } else if(strcmp(unit, "GB") == 0){
    return 1024*1024*1024;
  } else {
    printf(RED "Invalid unit. Suppoted units: B, KB, MB, GB\n" END);
    exit(1);
  }
}

void allocation_loop(size_t memory, int interval){

  while(!shouldExit){
    char *ptr = malloc(memory);

    printf(GREEN "%zu bytes in use... \n" END, memory);
    memset(ptr, 'a', memory);

    printf("%.4s \n", &ptr[memory-5]);

    printf(GREEN "Take a nap...\n" END);
    sleep(interval);

    printf(GREEN "Free memory...\n" END);
    free(ptr);

    printf(GREEN "Second nap... \n" END);
    sleep(interval);
  }
}

int main(int argc, char **argv){
  print_help(argv[0]);

  signal(SIGINT, signalHandler);

  char *unit = "KB";
  int value = 5;
  int multipliyer = 1024; //kB 
  int time = 10;
  size_t memory;

  if (argc > 1 && atoi(argv[1])){
    value = atoi(argv[1]);
  }

  if (argc > 2){
    unit = argv[2];
    printf(BLUE "Chosen multipliyer: %s\n" END, unit);
    multipliyer = select_multipliyer(unit);
  } else {
    printf(YELLOW "No multipliyer selected using default: '%s'\n" END, unit);
  }

  if (argc > 3 && atoi(argv[3])){
    time = atoi(argv[3]);
  }

  printf(GREEN "Chosen interval: %d (s)\n" END, time);

  memory = value * multipliyer;
  printf(GREEN "Alocating: %d%s\n" END, value, unit);
  
  allocation_loop(memory, time);

  printf(BLUE "Exiting...\n" END);
  return 0;
}
