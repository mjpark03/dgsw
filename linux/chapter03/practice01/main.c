#include <stdio.h>
#include "copy.h"
#include "capitalize.h"

char line[MAXLINE];
char longest[MAXLINE];
char capitalization[MAXLINE];

main()
{
  int len;
  int max;

  max = 0;
  while(gets(line) && strcmp(line, "q")) {
    len = strlen(line);
    if(len > max) {
      max = len;
      copy(line, longest);
    }
  }

  if(max > 0) {
    capitalize(longest, capitalization);
    printf("[longest] %s \n", longest);
    printf("[capitalization] %s \n", capitalization);
  }

  return 0;
}
