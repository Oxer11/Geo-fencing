#ifndef GUARD_kd_tree
#define GUARD_kd_tree

#define INF 0x3f3f3f3f 
#define N 1000010
#define lim 80000

#include<cstdio>
#include<algorithm>

using namespace std;

int cur;
int n,m,x,y,opt;

struct Point
{
    int d[2];
    Point(){};
    Point(int x,int y) {d[0]=x,d[1]=y;}
    bool operator < (const Point &n1) const {return d[cur]<n1.d[cur];}
}p[N];

struct kdtree
{
    struct Node
	{
        int d[2], mn[2], mx[2];
        Node *lch, *rch;
        Node &operator = (const Point &n1)
        {
            d[0] = mn[0] = mx[0] = n1.d[0];
            d[1] = mn[1] = mx[1] = n1.d[1];
            return *this;
        }
        Node();
        void pushup();
    }*null;
    
    Node::Node() {lch = rch = null;}
    
	void Node::pushup()
    {
        for (int i=0;i<2;i++)
        {
        	mn[i] = mx[i] = d[i];
            if (lch != null)
            {
                mn[i] = min(mn[i], lch->mn[i]);
                mx[i] = max(mx[i], lch->mx[i]);
            }
            if (rch != null)
            {
                mn[i] = min(mn[i], rch->mn[i]);
                mx[i] = max(mx[i], rch->mx[i]);
            }
        }
    }

    Node pool[N];
    int poolt;
    Node *Root;
    Point T;
    int ans,cnt;

    Node *NewNode()
    {
        pool[poolt]=Node();
        return &pool[poolt++];
    }
    Node *build(int l,int r,int dim)//������[l,r]��ά��
    {
        cur=dim;
        int mid=(l+r)>>1;
        nth_element(p+l,p+mid,p+r+1);
        Node *ret=NewNode();
        *ret=p[mid];
        if (l<mid) ret->lch=build(l,mid-1,dim^1);
        if (r>mid) ret->rch=build(mid+1,r,dim^1);
        ret -> pushup();
        return ret;
    }
    void Init()
    {
        null=NewNode();
        *null=Node();
        Root=build(1,n,0);
    }
    void query_mn(Node *node)//������ѯ
    {
        ans=min(ans,node->get_dis(T));
        int disl=INF,disr=INF;
        if (node->lch!=null)
            disl=node->lch->get_mn(T);
        if (node->rch!=null)
            disr=node->rch->get_mn(T);
        if (disl<disr)
        {
            if (disl<ans) query_mn(node->lch);
            if (disr<ans) query_mn(node->rch);
        }
        else
        {
            if (disr<ans) query_mn(node->rch);
            if (disl<ans) query_mn(node->lch);
        }
    }
    int solve_mn(Point n1)//ע���ʼ������Ϣ
    {
        ans=INF;
        T=n1;
        query_mn(Root);
        return ans;
    }
    void insert(Node *node,int dim)//����
    {
        if (T.d[dim]<node->d[dim])
            if (node->lch!=null)
                insert(node->lch,dim^1);
            else
            {
                node->lch=NewNode();
                *node->lch=T;
            }
        else
            if (node->rch!=null)
                insert(node->rch,dim^1);
            else
            {
                node->rch=NewNode();
                *node->rch=T;
            }
        node->pushup();
    }
    void solve_insert(Point n1)//cnt�Ǽ�����
    {
        cnt++;
        if (cnt==lim)
        {
            poolt=1;
            Root=build(1,n,0);
            cnt=0;
        }
        else
        {
            T=n1;
            insert(Root,0);
        }
    }
}

#endif
