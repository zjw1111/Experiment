//kopyh
#include <bits/stdc++.h>
#define N 512
using namespace std;
class heap
{

private:
    struct node
    {
        int num,pos;
        friend bool operator < (node a, node b)
        {
            return a.num > b.num;
        }
    };

    vector<node>tree;

    int getFa(int now)
    {
        return now&1?(now+1)/2-1:now/2-1;
    }
    int getLson(int now)
    {
        return (now+1)*2-1;
    }
    int getRson(int now)
    {
        return (now+1)*2;
    }

    void pushup(int now)
    {
        if(now>0 && tree[now]<tree[getFa(now)])
        {
            swap(tree[now],tree[getFa(now)]);
            pushup(getFa(now));
        }
    }

    void adjustTree(int now)
    {
        int lson=getLson(now), rson=getRson(now);
        if(lson<tree.size() && tree[lson]<tree[now])
        {
            swap(tree[lson],tree[now]);
            adjustTree(lson);
            adjustTree(now);
        }
        else if(rson<tree.size() && tree[rson]<tree[now])
        {
            swap(tree[rson],tree[now]);
            adjustTree(rson);
        }
    }

public:
    void init()
    {
        tree.clear();
    }

    void push(int pos,int num)
    {
        node *a = new(node);
        a->num= num;
        a->pos= pos;
        tree.push_back(*a);
        pushup(tree.size()-1);
    }

    bool empty()
    {
        return tree.empty();
    }

    int top()
    {
        return tree[0].pos;
    }

    void pop()
    {
        swap(tree[0],tree[tree.size()-1]);
        tree.pop_back();
        adjustTree(0);
    }

    int size()
    {
        return tree.size();
    }
};

void solve1(int *num)
{
    int res1,res2,num1,num2;
    num1=num2=0;
    printf("In order to find:\n");
    for(int i=1;i<=N;i++)
    {
        if(num1<num[i])num2=num1,num1=num[i],res2=res1,res1=i;
        else if(num2<num[i])num2=num[i],res2=i;
    }
    printf("The max score is %d, and the second is %d\n",res1,res2);
}

void solve2(int *num)
{

}

void solve3(int *num)
{
    int res1,res2;
    printf("Use heap to find:\n");
    heap hp;
    hp.init();
    for(int i=1;i<=N;i++)
        hp.push(i,num[i]);
    res1=hp.top();
    hp.pop();
    res2=hp.top();
    printf("The max score is %d, and the second is %d\n",res1,res2);
}

int main()
{
    int num[N+1];
    srand(clock());
    for(int i=1;i<=N;i++)num[i]=rand()%1000;
//    for(int i=1;i<=N;i++)printf("%d ",num[i]);
//    printf("\n");
    solve1(num);
    solve2(num);
    solve3(num);
    return 0;
}
