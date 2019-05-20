#include <stdlib.h>
#include <stdio.h>

int main()
{
  int i;
  int *p, *q, *a, *b, *c, *d;

  p = malloc(10 * sizeof(int));
  q = malloc(10 * sizeof(int));
  p = malloc(102 * sizeof(int));
  free(p);
  q = malloc(104 * sizeof(int));
  free(q);
  p = calloc(10 , sizeof(int));

  for(i = 0; i < 10; i++){
    p[i] = i;
  }

  for(i = 0; i < 10; i++){
    printf("%d\n", p[i]);
  }

  a = calloc(10 , sizeof(int));
  b = calloc(3 , sizeof(int));
  c = calloc(2 , sizeof(int));
  d = calloc(5 , sizeof(int));
  free(a);
  free(b);
  free(c);
  free(d);
  q = realloc(p , sizeof(int)*20);
  
  for(i = 0; i < 20; i++){
    printf("%d\n", q[i]);
  }
    
  free(p);
  free(q);

  return 0;
}
