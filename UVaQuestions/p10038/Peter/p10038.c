/* Xulin Yang, 904904, time: 2018-2-26 20:23:08, description: UVA 10038
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int n;   
    while(scanf("%d",&n)!=EOF)  
    {  
        int arr[3001]={0}, str[3001]={0}, i;  
          
        for(i=0; i<n; i++)  
            scanf("%d",&arr[i]);  
              
        for(i=0; i<n-1; i++)
            str[abs(arr[i]-arr[i+1])]=1;   
              
        int count=0;      
        for(i=1; i<=n-1; i++) 
            if(str[i]==1) count++;  
          
        if(count==n-1) printf("Jolly\n");  
        else printf("Not jolly\n");   
    } 
}