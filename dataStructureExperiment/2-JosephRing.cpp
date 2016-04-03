//kopyh
#include <bits/stdc++.h>
struct node
{
    int num,pwd;
    node *next;
    node(int x, node *p = NULL):num(x),next(p){}
};
int main()
{
    int n,m,i,j;
    char s[10];
    printf("Please input the number of people:\n");
    scanf("%d",&n);
    printf("Everyone's password is same?(Y/N)\n");
    scanf("%s",s);
    int flag=(strcmp(s,"Y")==0?1:0);
    printf("Please input password:\n");

    //init
    if(flag)scanf("%d",&m);
    node *p, *q, *start;
    i=1;
    while(i<=n)
    {
        p = new node(i++);
        if(flag)p->pwd = m;
        else scanf("%d",&p->pwd);
        if(i==2)start = p, m = start->pwd;
        else q->next = p;
        q = p;
    }
    p = start;
    q->next = p;

    //solve
    printf("Output order is:\n");
    i=1,j=0;
    while(j<n)
    {
        if(i == m)
        {
            if(j)printf(" -> ");
            printf("%d",p->num);
            m = p->pwd;
            q->next = p->next;
            delete(p);
            p = q->next;
            j++;
            i = 1;
        }
        else
            i++, p=p->next, q=q->next;
    }
    printf("\n");

    return 0;
}

