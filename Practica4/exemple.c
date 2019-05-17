#include <stdlib.h>
#include <stdio.h>

int main()
{
  int i;
  int *p, *q;

  p = malloc(10 * sizeof(int));
  q = malloc(10 * sizeof(int));
  p = malloc(102 * sizeof(int));
  q = malloc(104 * sizeof(int));
  //p = calloc(10 , sizeof(int));

  for(i = 0; i < 10; i++){
    p[i] = i;
  }

  for(i = 0; i < 10; i++){
    printf("%d\n", p[i]);
  }
    
  //q = realloc(p , sizeof(int)*20);
  
  for(i = 0; i < 20; i++){
    printf("%d\n", q[i]);
  }
    
  free(p);

  return 0;
}
