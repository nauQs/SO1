#include <stdlib.h>
#include <stdio.h>

int main()
{
  int i;
  int *p, *q;

  //p = malloc(10 * sizeof(int));
   p = calloc(10 , sizeof(int));
   q = realloc(p , sizeof(int)*20);

  for(i = 0; i < 10; i++)
    p[i] = i;

  for(i = 0; i < 10; i++)
    printf("%d\n", p[i]);

  free(p);

  return 0;
}
