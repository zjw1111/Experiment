//kopyh
#include <bits/stdc++.h>
using namespace std;
class examSystem
{
public:
    struct Class
    {
        int course[3];
    }cla[10];
    struct Student
    {
        string id,name;
        int classId;
        double score[3],totScore;
        Student(string ID,string NAME,int Class,double sc1,double sc2,double sc3):id(ID),name(NAME),classId(Class)
        {
            totScore=0;
            score[0]=sc1,totScore+=sc1;
            score[1]=sc2,totScore+=sc2;
            score[2]=sc3,totScore+=sc3;
        }
        friend bool operator < (Student a, Student b)
        {
            return a.totScore < b.totScore;
        }
    };
    vector<Student>stu;
    int t;
    struct cmp1
    {
        bool operator()(const Student &a,const Student &b)
        {
            return a.totScore>b.totScore;
        }
    };
    struct cmp2
    {
        bool operator()(const Student &a,const Student &b)
        {
            if(a.classId == b.classId)return a.totScore > b.totScore;
            else return a.classId < b.classId;
        }
    };
    void init()
    {
        stu.clear();
        freopen("in.in","r",stdin);
        for(int i=0;i<10;i++)for(int j=0;j<3;j++)scanf("%d",&cla[i].course[j]);
        string a,b;
        int c;
        double d,e,f;
        while(cin>>a)
        {
            cin>>b>>c>>d>>e>>f;
            stu.push_back(Student(a,b,c,d,e,f));
        }
        freopen("CON","r",stdin);
    }
    void output(Student *a)
    {
        cout<<a->id<<" "<<a->name<<" "<<a->classId<<" ";
        for(int j=0;j<3;j++)cout<<a->score[j]<<" ";
        cout<<"total:"<<a->totScore<<endl;
    }
    int solve1()
    {
        printf("Output everyone's information?(1/0)\n");
        scanf("%d",&t);
        if(t)
        {
            printf("Distinguish between class?(1/0)\n");
            scanf("%d",&t);
            if(t)sort(stu.begin(),stu.end(),cmp2());
            else sort(stu.begin(),stu.end(),cmp1());
            for(int i=0;i<stu.size();i++)
                output(&stu[i]);
        }
        else
        {
            printf("Please choose a class:\n");
            scanf("%d",&t);
            sort(stu.begin(),stu.end(),cmp2());
            for(int i=0;i<stu.size();i++)
                if(stu[i].classId==t)
                    output(&stu[i]);
        }
    }
    int solve2()
    {
        int a,b,c,d,e;
        a=b=c=d=e=0;
        printf("Output everyone's information?(1/0)\n");
        scanf("%d",&t);
        if(!t)
        {
            printf("Statistics every course?(1/0)\n");
            scanf("%d",&t);
            if(t)
            {
                for(int i=0;i<stu.size();i++)
                {
                    if(stu[i].totScore/3>=90)a++;
                    else if(stu[i].totScore/3>=80)b++;
                    else if(stu[i].totScore/3>=70)c++;
                    else if(stu[i].totScore/3>=60)d++;
                    else e++;
                }
            }
            else
            {
                printf("Please choose a course:\n");
                scanf("%d",&t);
                for(int i=0;i<stu.size();i++)
                {
                    for(int j=0;j<3;j++)
                    {
                        if(cla[stu[i].classId].course[j]==t)
                        {
                            if(stu[i].score[j]>=90)a++;
                            else if(stu[i].score[j]>=80)b++;
                            else if(stu[i].score[j]>=70)c++;
                            else if(stu[i].score[j]>=60)d++;
                            else e++;
                        }
                    }
                }
            }
            printf("90~100:%d 80~90:%d 70~80:%d 60~70:%d 0~60:%d\n",a,b,c,d,e);
        }
        else
        {
            printf("Choose class or course?(1/2)\n");
            scanf("%d",&t);
            if(t==1)
            {
                printf("Please choose a class:\n");
                scanf("%d",&t);
                sort(stu.begin(),stu.end(),cmp2());
                for(int i=0;i<stu.size();i++)
                    if(stu[i].classId==t)
                    {
                        if(stu[i].totScore/3>=90)a++;
                        else if(stu[i].totScore/3>=80)b++;
                        else if(stu[i].totScore/3>=70)c++;
                        else if(stu[i].totScore/3>=60)d++;
                        else e++;
                    }
                printf("90~100:%d 80~90:%d 70~80:%d 60~70:%d 0~60:%d\n",a,b,c,d,e);
                for(int i=0;i<stu.size();i++)
                    if(stu[i].classId==t)
                        output(&stu[i]);
            }
            else
            {
                printf("Please choose a course:\n");
                scanf("%d",&t);
                for(int i=0;i<stu.size();i++)
                {
                    for(int j=0;j<3;j++)
                    {
                        if(cla[stu[i].classId].course[j]==t)
                        {
                            if(stu[i].score[j]>=90)a++;
                            else if(stu[i].score[j]>=80)b++;
                            else if(stu[i].score[j]>=70)c++;
                            else if(stu[i].score[j]>=60)d++;
                            else e++;
                        }
                    }
                }
                printf("90~100:%d 80~90:%d 70~80:%d 60~70:%d 0~60:%d\n",a,b,c,d,e);
                for(int i=0;i<stu.size();i++)
                {
                    for(int j=0;j<3;j++)
                    {
                        if(cla[stu[i].classId].course[j]==t)
                            output(&stu[i]);
                    }
                }
            }
        }
    }
    int solve3()
    {
        double x,y;
        int sum=0,cl;
        printf("everyone,a class or a student?(1/2/3)\n");
        scanf("%d",&t);
        if(t==1)
        {
            printf("Total score or a course?(1/2)\n");
            scanf("%d",&t);
            if(t==1)
            {
                printf("Please input score range:\n");
                scanf("%lf%lf",&x,&y);
                for(int i=0;i<stu.size();i++)
                        if(stu[i].totScore/3>=min(x,y)&&stu[i].totScore/3<=max(x,y))sum++;
                printf("%.2lf~%.2lf: %d\n",x,y,sum);
                for(int i=0;i<stu.size();i++)
                    if(stu[i].totScore/3>=min(x,y)&&stu[i].totScore/3<=max(x,y))
                        output(&stu[i]);
            }
            else
            {
                printf("Please choose a course:\n");
                scanf("%d",&t);
                for(int i=0;i<stu.size();i++)
                    for(int j=0;j<3;j++)
                        if(cla[stu[i].classId].course[j]==t)
                            if(stu[i].score[j]>=min(x,y)&&stu[i].score[j]<=max(x,y))sum++;
                printf("%.2lf~%.2lf: %d\n",x,y,sum);
                for(int i=0;i<stu.size();i++)
                    for(int j=0;j<3;j++)
                        if(cla[stu[i].classId].course[j]==t)
                            if(stu[i].score[j]>=min(x,y)&&stu[i].score[j]<=max(x,y))
                                output(&stu[i]);
            }
        }
        else if(t==2)
        {
            printf("Please choose a class:\n");
            scanf("%d",&cl);
            printf("Total score or a course?(1/2)\n");
            scanf("%d",&t);
            if(t==1)
            {
                printf("Please input score range:\n");
                scanf("%lf%lf",&x,&y);
                for(int i=0;i<stu.size();i++)
                    if(stu[i].classId==cl)
                        if(stu[i].totScore/3>=min(x,y)&&stu[i].totScore/3<=max(x,y))sum++;
                printf("%.2lf~%.2lf: %d\n",x,y,sum);
                for(int i=0;i<stu.size();i++)
                    if(stu[i].classId==cl)
                        if(stu[i].totScore/3>=min(x,y)&&stu[i].totScore/3<=max(x,y))
                            output(&stu[i]);
            }
            else
            {
                printf("Please choose a course:\n");
                scanf("%d",&t);
                for(int i=0;i<stu.size();i++)
                    if(stu[i].classId==cl)
                        for(int j=0;j<3;j++)
                            if(cla[stu[i].classId].course[j]==t)
                                if(stu[i].score[j]>=min(x,y)&&stu[i].score[j]<=max(x,y))sum++;
                printf("%.2lf~%.2lf: %d\n",x,y,sum);
                for(int i=0;i<stu.size();i++)
                    if(stu[i].classId==cl)
                        for(int j=0;j<3;j++)
                            if(cla[stu[i].classId].course[j]==t)
                                if(stu[i].score[j]>=min(x,y)&&stu[i].score[j]<=max(x,y))
                                    output(&stu[i]);
            }
        }
        else
        {
            char s[10];
            printf("Please choose a student:\n");
            scanf("%s",s);
            string ss(s);
            for(int i=0;i<stu.size();i++)
                if(stu[i].id==ss)
                    output(&stu[i]);
        }
    }
    int solve()
    {
        init();
        printf("--------------Please choose the operation:------------\n");
        printf("1:显示考试情况  2:统计考试成绩  3:查找成绩  0:结束程序\n");
        while(scanf("%d",&t)&&t)
        {
            if(t==1)solve1();
            if(t==2)solve2();
            if(t==3)solve3();
            printf("\n1:显示考试情况  2:统计考试成绩  3:查找成绩  0:结束程序\n");
        }
        return 0;
    }
};

int main()
{
    examSystem es;
    es.solve();
    return 0;
}
