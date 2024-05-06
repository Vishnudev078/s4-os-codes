#include<stdio.h>
int main()
{
    int k,y,i,j,n,m,alloc[20][20],max[20][20],avail[40],flag=0,ind=0;
    printf("Enter the number of process");
    scanf("%d",&n);
    printf("Enter the number of resource");
    scanf("%d",&m);
    printf("Enter the allocation matrix");
    for(i=0;i<n;i++){
        for(j=0;j<m;j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }
    printf("Enter the max matrix");
    for(i=0;i<n;i++){
        for(j=0;j<m;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    printf("Enter the available");
    for(i=0;i<m;i++){
        scanf("%d",&avail[i]);
    }
    int finish[n],seq[n],work[m],need[n][m];
    //calculate need matrix
    for(i=0;i<n;i++){
        for(j=0;j<m;j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    printf("Need");
    for(i=0;i<n;i++)
    {
        printf("\n");
        for(j=0;j<m;j++){
            printf("%d ",need[i][j]);
        }
    }
    for(i=0;i<m;i++){
        work[i]=avail[i];
    }
        for(i=0;i<n;i++){
        finish[i]=0;
    }
    while (ind < n) {
    int found = 0; // Flag to check if a process is found to be executed

    for (i = 0;i< n;i++) {
        if (finish[i]== 0) {
            flag = 0;
            for (j = 0; j < m; j++) {
                if (need[i][j] > work[j]) {
                    flag  = 1;
                    break;
                }
            }

            if (flag == 0) {
                seq[ind++] = i;
                for (y = 0; y < m; y++) {
                    work[y] += alloc[i][y];
                }
                finish[i] = 1;
                found = 1; // Set flag indicating process is found
            }
        }
    }

    // If no process is found, break the loop
    if (!found) {
        break;
    }
}

    printf("\n following\n");
    for(i=0;i<=n-1;i++){
        printf("P%d ",seq[i]);
    }
    
}
