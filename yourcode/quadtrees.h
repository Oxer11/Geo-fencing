//
// Created by oxer on 18-12-24.
//

#ifndef MAIN_QUADTREES_H
#define MAIN_QUADTREES_H

#include <clocale>
#include <cmath>
#include <unordered_map>
#include "Others.h"
#define EPS 1e-4

struct quad_node
{
    double l[2], r[2];
    quad_node* ch[4];
    int id, size;

    quad_node(double l0, double r0, double l1, double r1)
    {
        l[0] = l0; r[0] = r0;
        l[1] = l1; r[1] = r1;
        size = 0;
        ch[0] = ch[1] = ch[2] = ch[3] = NULL;
    }
};

struct quadtrees
{
    quad_node* root;

    void Init()
    {
        root = new quad_node(-MAX_POS, MAX_POS, -MAX_POS, MAX_POS);
    }

    void insert(quad_node *(&node), double x, double y, int id)
    {
        if (fabs(node->r[0]-node->l[0])<EPS)
        {
            node->id = id;
            return;
        }
        double mid0 = (node->l[0] + node->r[0])/2.0;
        double mid1 = (node->l[1] + node->r[1])/2.0;
        if (x>mid0)
        {
            if (y>mid1)
            {
                if (node->ch[0] == NULL)
                    node->ch[0] = new quad_node(mid0, node->r[0], mid1, node->r[1]),
                    node->size++;
                insert(node->ch[0], x, y, id);
            }
            else
            {
                if (node->ch[1] == NULL)
                    node->ch[1] = new quad_node(mid0, node->r[0], node->l[1], mid1),
                    node->size++;
                insert(node->ch[1], x, y, id);
            }
        }
        else
        {
            if (y>mid1)
            {
                if (node->ch[2] == NULL)
                    node->ch[2] = new quad_node(node->l[0], mid0, mid1, node->r[1]),
                    node->size++;
                insert(node->ch[2], x, y, id);
            }
            else
            {
                if (node->ch[3] == NULL)
                    node->ch[3] = new quad_node(node->l[0], mid0, node->l[1], mid1),
                    node->size++;
                insert(node->ch[3], x, y, id);
            }
        }
    }

    bool erase(quad_node *(&node), double x, double y, int id)
    {
        if (fabs(node->r[0]-node->l[0])<EPS)
        {
            node = NULL;
            return 1;
        }
        double mid0 = (node->l[0] + node->r[0])/2.0;
        double mid1 = (node->l[1] + node->r[1])/2.0;
        if (x>mid0)
        {
            if (y>mid1)
            {
                if (node->ch[0]!=NULL && erase(node->ch[0], x, y, id)) node->size--;
            }
            else
            {
                if (node->ch[1]!=NULL && erase(node->ch[1], x, y, id)) node->size--;
            }
        }
        else
        {
            if (y>mid1)
            {
                if (node->ch[2]!=NULL && erase(node->ch[2], x, y, id)) node->size--;
            }
            else
            {
                if (node->ch[3]!=NULL && erase(node->ch[3], x, y, id)) node->size--;
            }
        }
        if (node != root && !node->size)
        {
            node = NULL;
            return 1;
        }
        return 0;
    }

    void query(quad_node *(&node), double x0, double y0, double x1, double y1)
    {
        if (fabs(node->r[0]-node->l[0])<EPS)
        {
            ans_id[node->id] = 1;
            return;
        }
        double mid0 = (node->l[0] + node->r[0]) / 2.0;
        double mid1 = (node->l[1] + node->r[1]) / 2.0;
        if (node->ch[0] != NULL && x1 > mid0 && y1 > mid1) query(node->ch[0], x0, y0, x1, y1);
        if (node->ch[1] != NULL && x1 > mid0 && y0 <= mid1) query(node->ch[1], x0, y0, x1, y1);
        if (node->ch[2] != NULL && x0 <= mid0 && y1 > mid1) query(node->ch[2], x0, y0, x1, y1);
        if (node->ch[3] != NULL && x0 <= mid0 && y0 <= mid1) query(node->ch[3], x0, y0, x1, y1);
    }
};

#endif //MAIN_QUADTREES_H
