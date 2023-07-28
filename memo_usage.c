#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <time.h>


volatile bool shouldExit = false;

void print_help(char *name){
  printf("Usage: %s <size> <unit> <interva>\n\
          This program runs a loop that alocatates the giving <size> of \n \
          memory considering the giving <unit> (acepted units: B, KB, MB, GB). \n\
          and keeps alocating and dealocating this memory each <interval> (s)\n", name);
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
    printf("Invalid unit. Suppoted units: B, KB, MB, GB\n");
    exit(1);
  }
}

void allocation_loop(size_t memory, int interval){

  while(!shouldExit){
    char *ptr = malloc(memory);

    printf("%zu bytes in use... \n", memory);
    memset(ptr, 'a', memory);

    printf("%.4s \n", &ptr[memory-5]);

    printf("Take a nap...\n");
    sleep(interval);

    printf("Free memory...\n");
    free(ptr);

    printf("Second nap... \n");
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
    printf("Chosen multipliyer: %s\n", unit);
    multipliyer = select_multipliyer(unit);
  } else {
    printf("No multipliyer selected using default: '%s'\n", unit);
  }

  if (argc > 3 && atoi(argv[3])){
    time = atoi(argv[3]);
  }

  printf("Chosen interval: %d\n", time);

  memory = value * multipliyer;
  printf("Alocating: %d%s\n", value, unit);
  
  allocation_loop(memory, time);

  printf("Exiting...\n");
  return 0;
}
