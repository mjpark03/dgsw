#include <stdio.h>
#include "copy.h"

char line[MAXLINE];
char longest[MAXLINE];

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

  if(max > 0)
    printf("%s", longest);

  return 0;
}
