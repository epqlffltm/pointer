/*
2026-02-08
포인터 기초 강의
*, & 의 의미
*/

#include<stdio.h>

int main(void)
{
  int n = 0;
  int *pn;//포인터 선언

  pn = &n;

  printf("n = %d\n",n);
  printf("*pn = %d\n",n);

  n = 10;

  printf("n = %d\n",n);
  printf("*pn = %d\n",n);

  printf("n의 주소: %p\n",&n);
  printf("*pn의 주소: %p\n",pn);

  return 0;
}