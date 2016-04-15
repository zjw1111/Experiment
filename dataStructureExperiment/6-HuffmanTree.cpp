//kopyh
#include <bits/stdc++.h>
using namespace std;
class HuffmanTree
{
private:
    struct node //the huffman tree's node
    {
        int cha,val;
        int id,fa,lson,rson;
        void init(int pos,int vall,int tmpCha=129)
        {
            cha=tmpCha; val=vall; id=pos;
            fa=lson=rson=pos;
        }
        void print()
        {
            printf("%d %d %d %d %d %d\n",id,cha,val,fa,lson,rson);
        }
        friend bool operator < (node a,node b)
        {
            return a.val > b.val;
        }
    }tree[2*129],root;
    void link(int fa,int lson,int rson)
    {
        tree[fa].lson = lson;
        tree[fa].rson = rson;
        tree[lson].fa = tree[rson].fa = fa;
    }
    //build the Huffman Tree
    int build(int num[])
    {
        priority_queue<node> q;
        node a,b;
        int tot=0;
        for(int i=0;i<129;i++)
            if(num[i])
            {
                tree[tot].init(tot,num[i],i);
                q.push(tree[tot++]);
            }
        while(q.size()>1)
        {
            a = q.top();q.pop();
            b = q.top();q.pop();
            tree[tot].init(tot,a.val+b.val);
            link(tot,a.id,b.id);
            q.push(tree[tot++]);
        }
        root = q.top();
        return tot;
    }
    //get every char's huffman coding
    string res[129];
    void dfs(node pos, string ans)
    {
        if(pos.cha<129)res[pos.cha]=ans;
        else
        {
            if(pos.lson!=pos.id)dfs(tree[pos.lson],ans+"0");
            if(pos.rson!=pos.id)dfs(tree[pos.rson],ans+"1");
        }
    }
    //print every char's huffman coding
    void printHuf()
    {
        freopen("HufCode.txt","w",stdout);
        dfs(root,"");
        for(int i=0;i<128;i++)
            if(res[i]!="")
                printf("%c: %s\n",i,res[i].c_str());
    }
public:
    //initialize Huffman Tree
    void init(string pos)
    {
        freopen(pos.c_str(),"r",stdin);
        string s;
        int num[129]={0};
        while(getline(cin,s,'\n'))
            for(int i=0;i<=s.size();i++)
                num[s[i]]++;
        num[128] = 1;
        int tot = build(num);
        freopen("HufTree.dat","w",stdout);
        for(int i=0;i<tot;i++)
            tree[i].print();
        printHuf();
    }
    //use file restore Huffman Tree
    void getHuf(string pos)
    {
        freopen(pos.c_str(),"r",stdin);
        int id;
        while(scanf("%d",&id)!=EOF)
        {
            tree[id].id=id;
            scanf("%d%d%d%d%d",&tree[id].cha,&tree[id].val,&tree[id].fa,&tree[id].lson,&tree[id].rson);
        }
    }
    //use HuffmanTree compression file
    void compression(string pos)
    {
        freopen(pos.c_str(),"r",stdin);
        freopen("CodeFile.dat","w",stdout);
        char s[10001];
        int i,len,j=0,maxx=sizeof(unsigned char)*8;
        unsigned char t=0;
        while(gets(s))
            for(i=0,len=strlen(s);i<=len;i++)
            {
                for(int k=0;k<res[s[i]].size();k++)
                {
                    t<<=1;
                    t|=(res[s[i]][k]=='1'?1:0);
                    j++;
                    if(j==maxx)
                    {
                        printf("%c",t);
                        t=0;j=0;
                    }
                }
            }
        for(int k=0;k<res[128].size();k++)
        {
            t<<=1;
            t|=(res[s[i]][k]=='1'?1:0);
            j++;
            if(j==maxx)
            {
                printf("%c",t);
                t=0;j=0;
            }
        }
    }
    //use HuffmanTree decompression file
    void decompression(string pos)
    {
        freopen(pos.c_str(),"r",stdin);
        freopen("answer.txt","w",stdout);
        node now = root;
        unsigned char c,i,j;
        i = j = 1<<(sizeof(unsigned char)*8)-1;
        while(scanf("%c",&c)!=EOF)
        {
            while(i)
            {
                if(i&c)now = tree[now.rson];
                else now = tree[now.lson];
                if(now.cha<128)
                {
                    printf("%c",now.cha==0?'\n':now.cha);
                    now = root;
                }
                else if(now.cha==128)return;
                i>>=1;
            }
            i=j;
        }
    }
}hufTree;

int main()
{
    string s;
    printf("Please input the source file name:\n");
    cin>>s;
    hufTree.init(s);
    hufTree.compression(s);
    hufTree.decompression("CodeFile.dat");
    return 0;
}
