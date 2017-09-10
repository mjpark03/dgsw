#include <stdio.h>
#include "capitalize.h"

void capitalize(char from[], char to[])
{
  int i;

  i = 0;
  while(from[i] != '\0') {
    to[i] = toupper(from[i]);
    ++i;
  }
}  
