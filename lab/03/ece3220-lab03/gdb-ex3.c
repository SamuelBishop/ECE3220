#include <stdio.h>

int factorial ( int num )
{
    int i;
    int fact = 1;
    for(i=1; i<num; i++)
    {
	fact = fact*i;
    }
    return fact;
}

int main(void)
{
    int no;
    int ans;
    printf("Enter the number \n");
    scanf( "%d", &no );
    ans = factorial( no );
    printf("The factorial is %d", ans );
    return 0;
}
