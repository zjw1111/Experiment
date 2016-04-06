//kopyh
#include <bits/stdc++.h>
using namespace std;
class tutorSystem
{
private:
    struct node
    {
        int type;
        string name,data;
        node *include, *next, *fa;
        node(int t, string nt, string dt):type(t),name(nt),data(dt){include=next=fa=NULL;}
    };
    node *head;
    void nodeInit(node *t){t->next = NULL;}
    node *dfs(string fa, node *pos)
    {
        if(pos!=NULL && pos->name == fa)return pos;
        node *tmp, *now = pos->include;
        if(now != NULL)
        {
            tmp = dfs(fa,now);
            if(tmp!=NULL)return tmp;
        }
        now = pos->next;
        if(now != NULL)
        {
            tmp = dfs(fa,now);
            if(tmp!=NULL)return tmp;
        }
        return NULL;
    }
public:
    void init(){head = NULL;}
    void push(int type, string name, string data, string fa="")
    {
        if(type == 0)
        {
            if(head == NULL)
            {
                head = new node(type,name,data);
                return ;
            }
            node *tmp = head;
            while(tmp->next != NULL)tmp = tmp->next;
            tmp->next = new node(type,name,data);
        }
        else
        {
            node *tmp = dfs(fa, head);
            if(tmp==NULL || tmp->type==2)
                printf("error!\n");
            else
            {
                if(tmp->include == NULL)
                {
                    tmp->include = new node(type,name,data);
                    tmp->include->fa = tmp;
                }
                else
                {
                    node *now = tmp->include;
                    while(now->next != NULL)now = now->next;
                    now->next = new node(type,name,data);
                    now->next->fa = tmp;
                }
            }
        }
    }
    void change(string name, string fa)
    {
        node *now = dfs(name, head);
        node *tmp = dfs(fa, head);
        node *ff = tmp;
        if(tmp == NULL)printf("inexistence\n");
        else
        {
            if(tmp->include != NULL)
            {
                tmp = tmp->include;
                while(tmp->next != NULL)tmp = tmp->next;
                tmp->next = now;
            }
            else
                tmp->include = now;
            node *f = now->fa;
            if(f->include == now)f->include = now->next;
            else
            {
                f = f->include;
                while(f->next!=now)f=f->next;
                f->next = now->next;
            }
            now->fa = ff;
            nodeInit(now);
        }
    }
    void erase(string name)
    {
        node *era, *tmp = dfs(name, head);
        if(tmp == NULL)printf("inexistence\n");
        else
        {
            if(tmp->type == 0)
            {
                node *now = tmp->include;
                node *fa = (head==tmp?head->next:head);
                if(fa==NULL)printf("No teacher!\n");
                else
                {
                    while(now!=NULL)
                    {
                        era = now->next;
                        change(now->name,fa->name);
                        fa = fa->next;
                        if(fa == tmp) fa = tmp->next;
                        if(fa == NULL)fa = (head==tmp?head->next:head);
                        now = era;
                    }
                }
                if(head == tmp)head = tmp->next;
                else
                {
                    era = head;
                    while(era->next != tmp)era = era->next;
                    era->next = tmp->next;
                }
            }
            else if(tmp->type == 1)
            {
                int flag=1;
                node *now = tmp->include;
                node *fa = tmp->fa->include;
                while(fa!=NULL && (fa->type!=1||fa==tmp))fa = fa->next;
                if(fa == NULL)flag=0,fa=tmp->fa;
                while(now!=NULL)
                {
                    era = now->next;
                    change(now->name,fa->name);
                    if(flag)
                    {
                        fa = fa->next;
                        while(fa!=NULL && (fa->type!=1||fa==tmp))fa = fa->next;
                        if(fa == NULL)fa = tmp->fa->include;
                        while(fa!=NULL && (fa->type!=1||fa==tmp))fa = fa->next;
                    }
                    now = era;
                }
                if(tmp->fa->include == tmp)tmp->fa->include = tmp->next;
                else
                {
                    era = tmp->fa->include;
                    while(era->next != tmp)era = era->next;
                    era->next = tmp->next;
                }
            }
            else
            {
                node *fa = tmp->fa;
                if(fa->include == tmp)fa->include = tmp->next;
                else
                {
                    fa = fa->include;
                    while(fa->next!=tmp)fa=fa->next;
                    fa->next = tmp->next;
                }
            }
            delete(tmp);
        }
    }
    void find(string name)
    {
        node *tmp = dfs(name, head);
        if(tmp == NULL)printf("inexistence\n");
        else
        {
            if(tmp->type != 0)printf("%s's teacher is %s(%s)\n",name.c_str(),tmp->fa->name.c_str(),tmp->fa->data.c_str());
            if(tmp->include != NULL)
            {
                printf("%s's student is %s(%s)",name.c_str(),tmp->include->name.c_str(),tmp->include->data.c_str());
                tmp = tmp->include;
                while(tmp->next != NULL)
                {
                    tmp = tmp->next;
                    printf(",%s(%s)",tmp->name.c_str(),tmp->data.c_str());
                }
                printf("\n");
            }
        }
    }
    void count(string name)
    {
        node *tmp = dfs(name, head);
        if(tmp == NULL)printf("inexistence\n");
        else
        {
            int x=0,y=0;
            if(tmp->include != NULL)
            {
                tmp = tmp->include;
                tmp->type==1?x++:y++;
                if(tmp->include != NULL)
                {
                    node *now = tmp->include;
                    now->type==1?x++:y++;
                    while(now->next != NULL)
                        now = now->next, now->type==1?x++:y++;
                }
                while(tmp->next != NULL)
                {
                    tmp = tmp->next, tmp->type==1?x++:y++;
                    if(tmp->include != NULL)
                    {
                        node *now = tmp->include;
                        now->type==1?x++:y++;
                        while(now->next != NULL)
                            now = now->next, now->type==1?x++:y++;
                    }
                }
            }
            printf("%s have %d master and %d bachelor\n",name.c_str(),x,y);
        }
    }
    void output(string name)
    {
        node *tmp = dfs(name, head);
        if(tmp == NULL)printf("inexistence\n");
        else
        {
            printf("(%s",name.c_str());
            if(tmp->include != NULL)
            {
                printf(",(");
                tmp = tmp->include;
                printf("%s",tmp->name.c_str());
                if(tmp->include != NULL)
                {
                    printf(",(");
                    node *now = tmp->include;
                    printf("%s",now->name.c_str());
                    while(now->next != NULL)
                    {
                        now = now->next;
                        printf(",%s",now->name.c_str());
                    }
                    printf(")");
                }
                while(tmp->next != NULL)
                {
                    tmp = tmp->next;
                    printf(",%s",tmp->name.c_str());
                    if(tmp->include != NULL)
                    {
                        printf(",(");
                        node *now = tmp->include;
                        printf("%s",now->name.c_str());
                        while(now->next != NULL)
                        {
                            now = now->next;
                            printf(",%s",now->name.c_str());
                        }
                        printf(")");
                    }
                }
                printf(")");
            }
            printf(")\n");
        }
    }
};
int main()
{
    int t;
    string a,b,c;
    tutorSystem ts;
    ts.init();
    printf("--------------------本科生导师制度处理程序--------------------\n");
    printf("请输入操作项目序号:\n");
    printf("1:插入,  2:删除,  3:查询,  4:统计,  5:输出,  6:移动，  0:退出.\n");
    while(scanf("%d",&t)!=EOF&&t)
    {
        switch(t)
        {
            case(1):
            {
                printf("输入成员类型(老师==0 研究生==1 本科生==2)  姓名  其他信息\n");
                cin>>t>>a>>b;
                if(t)
                {
                    printf("请输入该学生的导师或负责研究生姓名:\n");
                    cin>>c;
                    ts.push(t,a,b,c);
                }
                else
                    ts.push(t,a,b);
                break;
            }
            case(2):
            {
                printf("输入要删除成员姓名：\n");
                cin>>a;
                ts.erase(a);
                break;
            }
            case(3):
            {
                printf("输入要查询成员姓名：\n");
                cin>>a;
                ts.find(a);
                break;
            }
            case(4):
            {
                printf("输入要查询成员姓名：\n");
                cin>>a;
                ts.count(a);
                break;
            }
            case(5):
            {
                printf("输入要查询老师姓名：\n");
                cin>>a;
                ts.output(a);
                break;
            }
            case(6):
            {
                printf("输入要移动学生姓名及新的导师姓名：\n");
                cin>>a>>b;
                ts.change(a,b);
                break;
            }
        }
        printf("\n请输入操作项目序号:\n");
        printf("1:插入,  2:删除,  3:查询,  4:统计,  5:输出,  6:移动，  7:退出.\n");
    }
    return 0;
}

