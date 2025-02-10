#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXIT_SUCCESS    0
#define EXIT_MALLOCFAIL 1
#define EXIT_ONUSERWISH 2

void showUsage(char **argv) {
  printf("%s - keep running a command\n", argv[0]);
  printf("Usage: %s -c <COMMAND> <OPTIONS>\n", argv[0]);
  printf("  -n  - number of times to repeat a command\n");
  printf("        (info): default is 10 times.\n");
  printf("                pass `loop` to go on forever.\n\n");
  printf("  -t  - time taken between command in milliseconds\n");
  printf("        (info): default is 25 seconds\n\n");
  printf("  -h  - shows this message\n");
}

void warnAboutTime(int t) {
  if (t < 150) {
    printf("WAIT!!!! it is dangerous to to this with such a low duration.\n");
    printf("Waiting 5 seconds for user's response. [ctrl + c] to quit execution\n");
    sleep(5);
    
    exit(EXIT_ONUSERWISH);
  }
}

void update(char *c, bool forever, int times, int s) {
  warnAboutTime(s);

  if (forever && times == 0) {
    for (;;) {
      printf("running block where forever is true and times is zero\n");

      system("clear");

      system(c);
      usleep(s);
    }
  } else if (forever && times == 0 && s != 0) {
    for (int i = 0; i < times; i++) {
      printf("running block where its not\n");

      system("clear");

      system(c);
      usleep(s);
    }
  }

  return;
}

int main(int argc, char **argv) {
  char *command = malloc(sizeof(char*));

  int timesBeforeExit = 5;
  bool forever = false;

  int durationOfCommand = 1;

  int c;

  if (command == NULL) {
    fprintf(stderr, "Cannot start right now.\n");
    exit(EXIT_MALLOCFAIL);
  }

  while ((c = getopt(argc, argv, "c:n:t:h")) != -1) {
    switch (c) {
      case 'c':
        strcpy(command, optarg);
        break;

      case 'n':
        if (strcmp(optarg, "loop") == 0) {
          forever = true; 
          timesBeforeExit = 0;
        } else {
          forever = false;
        }

        if (forever == false) timesBeforeExit = atoi(optarg);

        break;

      case 't':
        durationOfCommand = atoi(optarg);
        break;

      case 'h':
        showUsage(argv);
        break;
    }
  }

  printf("-c: %s; -n: %d; -t: %d\n", command, timesBeforeExit, durationOfCommand);
  update(command, forever, timesBeforeExit, durationOfCommand);

  return EXIT_SUCCESS;
}
