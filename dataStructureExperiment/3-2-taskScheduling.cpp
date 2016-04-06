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
        double time;
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

    void push(string id, double time)
    {
        node *a = new(node);
        a->id= id;
        a->time = time;
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
        frontNode = frontNode->next;
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
        double time;
        friend bool operator < (node a, node b)
        {
            return a.time < b.time;
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

    void push(string id, double time)
    {
        node *a = new(node);
        a->id= id;
        a->time = time;
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
void solve1(string id[], double time[], int n)
{
    queue q;
    q.init();
    for(int i=0;i<n;i++)
        q.push(id[i],time[i]);
    double timeSum = 0.0, waitSum=0.0;
    while(!q.empty())
    {
        printf("%s:  ",q.front().id.c_str());
        printf("%7.2lfs  ->",timeSum);
        printf("%7.2lfs   ",timeSum+q.front().time);
        printf("wait:%.2lfs\n",timeSum);
        waitSum += timeSum;
        timeSum = timeSum+q.front().time;
        q.pop();
    }
    printf("average wait: %.2lfs\n\n",waitSum/n);
}

//priority task queue
void solve2(string id[], double time[], int n)
{
    priority_queue q;
    q.init();
    for(int i=0;i<n;i++)
        q.push(id[i],time[i]);
    double timeSum = 0.0, waitSum=0.0;
    while(!q.empty())
    {
        printf("%s:  ",q.top().id.c_str());
        printf("%7.2lfs  ->",timeSum);
        printf("%7.2lfs   ",timeSum+q.top().time);
        printf("wait:%.2lfs\n",timeSum);
        waitSum += timeSum;
        timeSum = timeSum+q.top().time;
        q.pop();
    }
    printf("average wait: %.2lfs\n\n",waitSum/n);
}

int main()
{
    int n;
    string id[N];
    double time[N];
    printf("Please input the number of process:\n");
    scanf("%d",&n);
    printf("input every process's name and time:\n");
    for(int i=0;i<n;i++)
        cin>>id[i]>>time[i];
    solve1(id, time, 5);
    solve2(id, time, 5);
    return 0;
}
