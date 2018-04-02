#include <stdio.h>

int
reduce(const int array[], const size_t n, const int init, int(*f)(const int, const int))
{
  if (n == 0) {
    return init;
  } else {
    return f(reduce(array, n - 1, init, f), array[n - 1]);
  }
}


int
add(const int x, const int y)
{
  return x + y;
}

int
functional_sum(const int array[], const size_t n)
{
  return reduce(array, n, 0, add);
}

int
main()
{
    int a[5];
    int i;
    for(i = 0; i < 5; i++)
    {
        a[i]=i;
    }
    printf("%d\n", functional_sum(a,5));
    return 0;
}