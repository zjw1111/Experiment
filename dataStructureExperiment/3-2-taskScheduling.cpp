//kopyh
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
const int N = 10001;

class queue
{

private:
    struct node
    {
        string id;
        double time, len;
        node *next;
    };

    node *frontNode = NULL, *endNode = frontNode;
    int sum=0;

public:
    void init()
    {
        endNode = frontNode = NULL;
        sum=0;
    }

    void push(string id, double time, double len)
    {
        node *a = new(node);
        a->id= id;
        a->time = time;
        a->len = len;
        a->next = NULL;
        sum++;
        if(endNode==NULL)
            frontNode = endNode = a;
        else
            endNode->next = a, endNode = a;
    }

    bool empty()
    {
        return sum==0;
    }

    node front()
    {
        return *frontNode;
    }

    void pop()
    {
        node *t = frontNode;
        if(frontNode == endNode)frontNode=endNode=NULL;
        else frontNode = frontNode->next;
        sum--;
        delete(t);
    }

    int size()
    {
        return sum;
    }
};

class priority_queue
{

private:
    struct node
    {
        string id;
        double time, len;
        friend bool operator < (node a, node b)
        {
            return a.len < b.len;
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

    void push(string id, double time, double len)
    {
        node *a = new(node);
        a->id= id;
        a->time = time;
        a->len = len;
        tree.push_back(*a);
        pushup(tree.size()-1);
    }

    bool empty()
    {
        return tree.empty();
    }

    node top()
    {
        return tree[0];
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

//Common task queue
void solve1(string id[], double time[], double len[], int n)
{
    queue q;
    q.init();
    int now = 0;
    double timeSum = 0.0, waitSum=0.0;
    while(!q.empty() || now<n)
    {
        if(q.empty()&&timeSum<time[now])timeSum = time[now];
        while(now<n&&timeSum>=time[now])q.push(id[now],time[now],len[now]),now++;
        printf("%s:  ",q.front().id.c_str());
        printf("%7.2lfs  ->",timeSum);
        printf("%7.2lfs   ",timeSum+q.front().len);
        printf("wait:%.2lfs\n",timeSum-q.front().time);
        waitSum += timeSum-q.front().time;
        timeSum = timeSum+q.front().len;
        q.pop();
    }
    printf("average wait: %.2lfs\n\n",waitSum/n);
}

//priority task queue
void solve2(string id[], double time[], double len[], int n)
{
    priority_queue q;
    q.init();
    int now = 0;
    double timeSum = 0.0, waitSum=0.0;
    while(!q.empty() || now<n)
    {
        if(q.empty()&&timeSum<time[now])timeSum = time[now];
        while(now<n&&timeSum>=time[now])q.push(id[now],time[now],len[now]),now++;
        printf("%s:  ",q.top().id.c_str());
        printf("%7.2lfs  ->",timeSum);
        printf("%7.2lfs   ",timeSum+q.top().len);
        printf("wait:%.2lfs\n",timeSum-q.top().time);
        waitSum += timeSum-q.top().time;
        timeSum = timeSum+q.top().len;
        q.pop();
    }
    printf("average wait: %.2lfs\n\n",waitSum/n);
}

int main()
{
    freopen("test.txt","r",stdin);
    int n;
    string id[N];
    double time[N],len[N];
    printf("Please input the number of process:\n");
    scanf("%d",&n);
    printf("input every process's name, submit time and required time:\n");
    for(int i=0;i<n;i++)
        cin>>id[i]>>time[i]>>len[i];
    solve1(id, time, len, 5);
    solve2(id, time, len, 5);
    return 0;
}
