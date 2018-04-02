#include <stdio.h>

int
procedualSum(const int array[], int n)
{
    int sum = 0;
    for(size_t i=0; i < n; i++)
    {
        sum +=array[i];
    }
    return sum;
}

int
main()
{
    int a[5];
    for(int i = 0; i < 5; i++)
    {
        a[i]=i;
    }
    printf("%d\n", procedualSum(a,5));
}