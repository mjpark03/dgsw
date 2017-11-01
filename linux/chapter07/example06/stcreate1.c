#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[]) {
  struct student rec;
  FILE *fp;

  if (argc != 2) {
    fprintf(stderr, "입력 오류");
    return 1;
  }

  fp = fopen(argv[1], "wb");
  printf("%-9s %-7s %-4s \n", "학번", "이름", "점수");

  while(scanf("%d %s %d", &rec.id, rec.name, &rec.score)==3) {
     //printf("charbuf: %d, bufsize: %d", fp->_charbuf, fp->_bufsize);, 
     fwrite(&rec, sizeof(rec), 1, fp);
  }

  fclose(fp);
  return 0;
}
