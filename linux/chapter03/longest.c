#include <stdio.h> // 표준입출력 라이브러리 추가
#define MAXLINE 100 // 상수 선언

void copy(char from[], char to[]); // 문자열 복사하는 함수 선언

char line[MAXLINE]; // 표준 입력으로 입력받은 문자열을 저장하기 위한 char 배열 선언
char longest[MAXLINE]; // 입력받은 문자열 중 가장 긴 문자열을 저장하기 위한 char 배열 선언

main() // main 함수 정의
{
  int len; // 입력받은 문자열의 길이를 저장하기 위한 int 변수 선언 
  int max; // 입력받은 문자열 중 가장 긴 문자열의 길이를 저장하기 위한 int 변수 선언

  max = 0; // max 변수 초기화
  while(gets(line) && strcmp(line, "q")) { // 사용자가 q를 입력하기 전 까지 사용자로부터 문자열을 입력받기 위한 반복문
    printf("input: %s \n", line);
    
    len = strlen(line); // 입력받은 문자열의 길이를 구하는 함수 호출 및 저장
    if(len > max) { // 입력받은 문자열의 길이가 현재까지 가장 긴 문자열의 길이보다 큰지 확인
      max = len; // 가장 긴 문자열 길이 할당
      copy(line, longest); // longest 배열에 현재까지 가장 긴 문자열 복사
    }
  }

  if(max > 0) // 사용자가 문자열을 한 번이라도 입력했는지 확인
    printf("%s \n", longest); // 가장 긴 문자열을 표준 출력

  return 0; // 함수 종료
}

void copy(char from[], char to[]) // 문자열 복사하는 함수 정의
{
  int i; // index를 위한 변수 선언

  i = 0; // index 변수 초기화
  while((to[i] = from[i]) != '\0') // char 배열에서 NULL값을 만나기 전 까지 복사
    ++i; // index 증가
}
