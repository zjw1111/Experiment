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
    };
    void init()
    {
        freopen("in.in","r",stdin);
        for(int i=0;i<10;i++)for(int j=0;j<3;j++)scanf("%d",&cla[i].course[j]);
        string a,b;
        int c;
        double d,e,f;
        while(cin>>a)
        {
            cin>>b>>c>>d>>e>>f;
            Student
        }
    }
};


int main()
{
    return 0;
}
