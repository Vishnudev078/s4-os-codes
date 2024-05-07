#include<stdio.h>
#include<stdlib.h>
void main(){
    int RQ[50],i,j,n,index=-1,initial,move,TotalHeadMovement=0;
    printf("Enter the no of sequence");
    scanf("%d",&n);
    printf("Enter the sequence");
    for(i=0;i<n;i++)
    {
        scanf("%d",&RQ[i]);
    }
    printf("Enter the initial");
    scanf("%d",&initial);
    printf("Enter the 0 for low or 1 for high");
    scanf("%d",&move);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(RQ[j]>RQ[j+1])
            {
                int temp;
                temp=RQ[j];
                RQ[j]=RQ[j+1];
                RQ[j+1]=temp;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(initial<RQ[i])
        {
            index=i;
            break;
        }
    }
    if(move==1)
    {
        for(i=index;i<n;i++)
        {
            TotalHeadMovement+=abs(RQ[i]-initial);
            initial=RQ[i];
        }
        initial=RQ[i-1];
        for(i=index-1;i>=0;i--)
        {
            TotalHeadMovement+=abs(RQ[i]-initial);
            initial=RQ[i];
        }
    }
    else
    {
        for(i=index-1;i>=0;i--)
        {
            TotalHeadMovement+=abs(RQ[i]-initial);
            initial=RQ[i]; 
        }
        initial=RQ[0];
        for(i=index;i<n;i++)
        {
            TotalHeadMovement+=abs(RQ[i]-initial);
            initial=RQ[i];
        }
    }
    printf("Total Head Movement: %d",TotalHeadMovement);
}
