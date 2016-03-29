//kopyh
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    printf("Please input the size of MagicSquare:\n");
    scanf("%d",&n);
    while(n%2==0 || n>1000)
    {
        if(n%2==0)printf("Please input a odd number:\n");
        else if(n>1000)printf("The size is too huge:\n");
        scanf("%d",&n);
    }

    //generate magic square
    int ans[n][n];
    memset(ans,0,sizeof(ans));
    int x=0,y=n/2,xx,yy;
    for(int i=1;i<=n*n;i++)
    {
        xx = (x-1+n)%n;
        yy = (y+1)%n;
        if(ans[xx][yy])xx = (x+1)%n, yy = y;
        ans[xx][yy] = i;
        x=xx;y=yy;
    }

    //output
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            printf("%d ",ans[i][j]);
        printf("\n");
    }
    return 0;
}
