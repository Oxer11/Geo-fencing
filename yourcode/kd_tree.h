#ifndef GUARD_kd_tree
#define GUARD_kd_tree

#include "all.h"
#define N 1000010
#define alpha 0.5

int cur;
int n,m,x,y,cnt;

struct Point
{
    double d[2];
    Point(){};
    Point(double x,double y) {d[0]=x,d[1]=y;}
    bool operator < (const Point &n1) const {return d[cur]<n1.d[cur];}
}p[N];

struct Node
{
    double d[2], mn[2], mx[2];
    int id, size;
    bool is_erase;
    Node *lch, *rch;

    Node &operator = (const Point &n1)
    {
        d[0] = mn[0] = mx[0] = n1.d[0];
        d[1] = mn[1] = mx[1] = n1.d[1];
        return *this;
    }

    Node()
    {
        lch = rch = NULL;
        id = is_erase = 0;
        size = 1;
    }

    void pushup()
    {
        for (int i=0;i<2;i++)
        {
            mn[i] = mx[i] = d[i];
            if (lch != NULL)
            {
                mn[i] = min(mn[i], lch->mn[i]);
                mx[i] = max(mx[i], lch->mx[i]);
            }
            if (rch != NULL)
            {
                mn[i] = min(mn[i], rch->mn[i]);
                mx[i] = max(mx[i], rch->mx[i]);
            }
        }
        size = 1;
        if (lch != NULL) size += lch->size;
        if (rch != NULL) size += rch->size;
    }
};

struct kdtree
{
    vector<Node> pool;
    stack<Node*> st;
    Node *root, *rebuild_node;
    Point T;
    Triangle tri;
    int erase_id, rebuild_dim;

    Node *NewNode()
    {
        Node *ans;
        if (st.empty()) pool.push_back(Node()), ans = &(*pool.end());
        else ans = st.top(), st.pop();
        return ans;
    }

    bool NeedRebuild(Node *node)
    {
        if (node->lch != NULL && node->lch->size > alpha*node->size + 5) return true;
        if (node->rch != NULL && node->rch->size > alpha*node->size + 5) return true;
        return false;
    }

    Node *Build(int l,int r,int dim)
    {
        cur = dim;
        int mid = (l+r)>>1;
        nth_element(p+l, p+mid, p+r+1);
        Node *ret = NewNode();
        *ret = p[mid];
        if (l<mid) ret->lch = Build(l,mid-1,dim^1);
        if (r>mid) ret->rch = Build(mid+1,r,dim^1);
        ret -> pushup();
        return ret;
    }

    void DFS(Node *node)
    {
        if (node == NULL) return;
        DFS(node->lch);
        DFS(node->rch);
        if (!node->is_erase) p[++cnt] = Point(node->d[0], node->d[1]);
        node->is_erase = node->id = node->size = 0;
        node->lch = node->rch = NULL;
        node->d[0] = node->d[1] = 0;
        node->mn[0] = node->mn[1] = 0;
        node->mx[0] = node->mx[1] = 0;
        st.push(node);
    }

    void Rebuild(Node *node, int dim)
    {
        DFS(node);
        node = Build(1, cnt, dim);
    }

    void Init() {root = NULL;}

    void PushbackAll(Node *node)
    {
        if (!node->is_erase) ans_id[node->id] = 1;
        if (node->lch != NULL) PushbackAll(node->lch);
        if (node->rch != NULL) PushbackAll(node->rch);
    }

    void Query(Node *node)
    {
        if (RectInTriangle(node->mn[0], node->mn[1], node->mx[0], node->mx[1], tri))
        {
            PushbackAll(node);
            return;
        }
        if (!IntersectRectTri(node->mn[0], node->mn[1], node->mx[0], node->mx[1], tri))
            return;
        if (!node->is_erase && PointInTriangle(node->d[0], node->d[1], tri))
            ansid.push_back(node -> id);
        if (node->lch != NULL) Query(node->lch);
        if (node->rch != NULL) Query(node->rch);
    }

    void Insert(Node *node, int dim)
    {
        if (node == NULL)
        {
            node = NewNode();
            *node = T;
            return;
        }
        if (T.d[dim] < node->d[dim])
            Insert(node->lch, dim^1);
        else
            Insert(node->rch, dim^1);
        node -> pushup();
        if (NeedRebuild(node)) rebuild_node = node, rebuild_dim = dim;
    }

    void Erase(Node *node, int dim)
    {
        if (node->id == erase_id)
        {
            node->is_erase = 1;
            node->size--;
            return;
        }
        if (T.d[dim] < node->d[dim])
            Erase(node->lch, dim^1);
        else
            Erase(node->rch, dim^1);
        node -> pushup();
        if (NeedRebuild(node)) rebuild_node = node, rebuild_dim = dim;
    }

    void Solve(int op)
    {
        rebuild_node = NULL;
        if (op == 0) Insert(root, 0);
        else if (op == 1) Erase(root, 0);
        else puts("KD-Tree Operation Error!");
        if (rebuild_node != NULL) Rebuild(rebuild_node, rebuild_dim);
    }

}

#endif
