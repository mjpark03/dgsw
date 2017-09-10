#include <stdio.h>

int main(int argc, char *argv[])
{
  char ch;
  FILE *fp;
  
  long total = 0;
  long lineTotal = 0;

  if((fp = fopen(argv[1], "r")) == -1)
    perror(argv[1]);

  while((ch = fgetc(fp)) != EOF) {
    total++;
    
    if(ch == '\n')
      lineTotal++;
  }

  close(fp);
  printf("%s 파일 크기: %ld 바이트 %ld 라인\n", argv[1], total, lineTotal);
  exit(0);
}
