#ifndef GUARD_kd_tree
#define GUARD_kd_tree

#include "Others.h"
#include "Triangle.h"
#define alpha 0.75

using namespace std;

struct Node
{
    float d[2], mn[2], mx[2];
    int id, size;
    bool is_erase;
    Node *lch, *rch;

    Node &operator = (const Point &n1)
    {
        d[0] = mn[0] = mx[0] = n1.d[0];
        d[1] = mn[1] = mx[1] = n1.d[1];
        id = n1.id;
        return *this;
    }

    Node()
    {
        lch = rch = NULL;
        id = is_erase = 0;
        size = 1;
        d[0] = mn[0] = mx[0] = 0;
        d[1] = mn[1] = mx[1] = 0;
    }

    void pushup()
    {
        for (int i=0;i<2;i++)
        {
            if (!is_erase) mn[i] = mx[i] = d[i];
            else mn[i] = MAX_POS, mx[i] = -MAX_POS;
            if (lch != NULL)
            {
                if (lch->mn[i] < mn[i]) mn[i] = lch->mn[i];
                if (lch->mx[i] > mx[i]) mx[i] = lch->mx[i];
            }
            if (rch != NULL)
            {
                if (rch->mn[i] < mn[i]) mn[i] = rch->mn[i];
                if (rch->mx[i] > mx[i]) mx[i] = rch->mx[i];
            }
        }
        size = !is_erase;
        if (lch != NULL) size += lch->size;
        if (rch != NULL) size += rch->size;
    }
};

struct kdtree
{
    Node *root;
    Node **rebuild_node;
    Point T;
    Triangle tri;
    Rect rectangle;
    int erase_id, rebuild_dim;

    bool NeedRebuild(Node *(&node))
    {
        if (node->lch != NULL && node->lch->size > alpha*(node->size) + 5) return true;
        if (node->rch != NULL && node->rch->size > alpha*(node->size) + 5) return true;
        return false;
    }

    Node *Build(int l,int r,int dim)
    {
        cur = dim;
        int mid = (l+r)>>1;
        nth_element(p+l, p+mid, p+r+1);
        Node *ret = new Node;
        *ret = p[mid];
        if (l<mid) ret->lch = Build(l,mid-1,dim^1);
        if (r>mid) ret->rch = Build(mid+1,r,dim^1);
        ret -> pushup();
        return ret;
    }

    void DFS(Node *(&node))
    {
        if (node == NULL) return;
        DFS(node->lch);
        DFS(node->rch);
        if (!node->is_erase)
            p[++cnt] = Point(node->id, node->d[0], node->d[1]);
    }

    void Rebuild(Node *(&node), int dim)
    {
    	cnt=0;
        DFS(node);
        node = Build(1, cnt, dim);
    }

    void Init() {root = NULL;}

    void PushbackAll(Node *(&node))
    {
        if (!node->is_erase) ans_id[node -> id] = 1;
        if (node->lch != NULL) PushbackAll(node->lch);
        if (node->rch != NULL) PushbackAll(node->rch);
    }

    void QueryTri(Node *(&node))
    {
        if (node == NULL) return;
        if (RectInTriangle(node->mn[0], node->mn[1], node->mx[0], node->mx[1], tri))
        {
            PushbackAll(node);
            return;
        }
        if (!IntersectRectTri(node->mn[0], node->mn[1], node->mx[0], node->mx[1], tri))
            return;
        if (!node->is_erase && PointInTriangle(node->d[0], node->d[1], tri))
            ans_id[node -> id] = 1;
        if (node->lch != NULL) QueryTri(node->lch);
        if (node->rch != NULL) QueryTri(node->rch);
    }

    void QueryRect(Node *(&node))
    {
        if (node == NULL) return;
        if (!IntersectRect(node->mn[0], node->mn[1], node->mx[0], node->mx[1], rectangle))
            return;
        if (!node->is_erase
            && rectangle.min[0]<=node->d[0] && node->d[0]<=rectangle.max[0]
            && rectangle.min[1]<=node->d[1] && node->d[1]<=rectangle.max[1])
            ans_id[node -> id] = 1;
        if (node->lch != NULL) QueryRect(node->lch);
        if (node->rch != NULL) QueryRect(node->rch);
    }

    void Insert(Node *(&node), int dim)
    {
        if (node == NULL)
        {
            node = new Node;
            *node = T;
            return;
        }
        if (T.d[dim] < node->d[dim] || (fabs(T.d[dim] - node->d[dim])<1e-8 && T.d[dim^1] < node->d[dim^1]))
            Insert(node->lch, dim^1);
        else
            Insert(node->rch, dim^1);
        node -> pushup();
        if (NeedRebuild(node)) rebuild_node = &node, rebuild_dim = dim;
    }

    void Erase(Node *(&node), int dim)
    {
        if (node == NULL) return;
        if (node->id == erase_id)
        {
            node->is_erase = 1;
            node->pushup();
            return;
        }
        if (T.d[dim] < node->d[dim] || (fabs(T.d[dim] - node->d[dim])<1e-8 && T.d[dim^1] < node->d[dim^1]))
            Erase(node->lch, dim^1);
        else
            Erase(node->rch, dim^1);
        node -> pushup();
        if (NeedRebuild(node)) rebuild_node = &node, rebuild_dim = dim;
    }

    void Solve(int op)
    {
        rebuild_node = NULL;
        if (op == 0) Insert(root, 0);
        else if (op == 1) Erase(root, 0);
        else if (op == 2) QueryTri(root);
        else if (op == 3) QueryRect(root);
        else puts("KD-Tree Operation Error!");
        if (rebuild_node != NULL) Rebuild(*rebuild_node, rebuild_dim);
    }
};

#endif
