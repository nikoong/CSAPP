#include <stdio.h>
void inplace_swap(int *x, int *y){   
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
    
}

void reverse_array(int a[], int cnt){
    int first, last;
    for (first = 0, last = cnt-1;
         first < last;
         first++,last--)
        
        inplace_swap(&a[first],&a[last]);
}
int main(){
    //////edit////////
    int count = 5;
    int a[] = {1,2,3,4,5};
    //////////////////
    reverse_array(a,count);
    int i;
    for (i=0;i<count;i++)
    {
         printf("%d",a[i]);
         printf("\n");
    }

    
    return 0;
}
