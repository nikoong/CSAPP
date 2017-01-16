#include <stdio.h>
long int func1(long int x)
{

    return x & ~~0xFF;
}

long int func2(long int x)
{
    
    return x ^ ~0xff;
}


long int func3(long int x)
{
    x = x |0xff;
   
    return  x;
}

int main()
{
    long int x = 0x87654321;
    printf("%lx",x);
    printf("\n"); 
    printf("%lx",func1(x));
    printf("\n");  
    printf("%lx",func2(x));
    printf("\n");  
    printf("%lx",func3(x));
    printf("\n"); 
    return 0;
    
}
