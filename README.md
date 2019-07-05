# Geo-fencing
[![grid](README.asset/GeoFence.png)](https://www.propellant.media/geofencing-marketing-company-providers/)

Geo-fencing Project for *Data Structure* 2018 Fall @ Fudan University, by [**Zuobai Zhang**](<https://oxer11.github.io/>)

## Introduction

This is the final project for our Data Structure course. In this project, we are required to apply data structures to a practical scenario. Specifically, we are supposed to employ a spatial indexing data structure to solve the geo-fencing task, in which there are a great amount of insertion, deletion and query operations about the spatial relation between points and polygons.

We first make comprehensive analysis about geo-fencing and then propose four strategies to solve this problem efficiently. Results show that Grid Method outperforms other methods on the test dataset. [Here](Report.pdf) is our report of this project.

## Problem Definition

Geo-fencing is a location-based service that businesses use to engage their audience by sending relevant messages to smartphone users who enter a pre-defined location or geographic area.

From an abstract perspective, it is equivalent to the following problem. Given a two-dimension plane, you should utilize a data structure to support six operations efficiently:
1. **Point Addition**: Add a point to the point set.
2. **Point Deletion**: Delete a point from the point set.
3. **Point Query**: Given a point, query how many polygons the point locates in.
4. **Polygon Addition**: Add a polygon to the polygon set.
5. **Polygon Deletion**: Delete a polygon from the polygon set.
6. **Polygon Query**: Given a polygon, query how many points the polygon contains.

The scale of final test  data is listed in the following table:

|  | 1 | 2 | 3 | 4 | 5 | 6 |
| ---- | :---- | :---- | :---- | :---- | :---- | :----- |
|case_1|0|0|2000|15000|0|0|
|case_2|150000|0|0|0|0|200|
|case_3|100000|0|500|5000|0|300|
|case_4|0|0|2000|15000|1000|0|
|case_5|150000|20000|0|0|0|200|
|case_6|100000|10000|300|5000|500|300|

## Methods

To address this problem, four solutions are proposed aiming to reduce the time cost.

### Alg. 1: R-tree + Brute-Force

[R-tree](https://en.wikipedia.org/wiki/R-tree) is a tree data structure used for storing spatial data indexes in an efficient manner. R-trees are highly useful for spatial data queries and storage, especially for processing rectangles. We have empolyed R-tree template in https://github.com/nushoin/RTree for this problem.

In this problem, we combine R-tree and ray-method to derive a brute-force solution. For operation 1, 2, 6, we treat points as small rectangles and then put them into R-tree via corresponding operations. And for operation 3, 4, 5, we approximate polygons with their bounding rectangles. In this way, all operations about points and polygons are transformed to rectangle operations in R-tree. For query 3, we first select those rectangles intersecting with query one and then apply ray-method to check whether the point locates in the polygons.

In spite of the outstanding performance on the test dataset, Alg. 1 suffers from approximate deviation seriously. More specifically, the time complexity of Alg. 1 are not guaranteed when bounding rectangles cannot approximate polygons accurately, as is common for non-convex polygons.

### Alg. 2: k-d tree + Triangulation

The bottleneck of Alg. 1 is the ray-method, which implies that a more efficient strategies for 'point in polygon' is needed to accelerate the algorithm. Triangulation gives a natural solution to this problem. According to https://github.com/ivanfratric/polypartition, we can partition a non-convex polygons into triangles in O(n log n) time. In total, we will obtain numerous triangles, the number of which is about the same as the number of edges of all polygons.

To maintain the information of points efficiently, [k-d tree](https://en.wikipedia.org/wiki/K-d_tree) is the best choice. A k-d Tree(also called as k-dimensional Tree) is a binary search tree where data in each node is a k-dimensional point in space. In short, it is a space partitioning data structure for organizing points in a k-dimensional space. With the primary objective of accelerating point processing, for each tree node, we maintain the bounding rectangles of its subtree. If a query triangle has no intersect with the bounding rectangles, we can simply avoid the query in the subtree.

Though with a strict theoretical time complexity guarantee, Alg. 2 performs nearly the same as Alg. 1 in practice. The main reason is that there are only 150 edges in each polygons in test dataset. Our experiments show that Alg. 2 outperforms other solutions when the number of polygon edges is extremely high.

### Alg. 3: Quadtree + Triangulation

Alg. 2 takes only polygon query into consideration. As for point query, we resort to [Quadtree](https://en.wikipedia.org/wiki/Quadtree) data structure. A quadtree is a tree data structure in which each internal node has exactly four children. Quadtrees are most often used to partition a two-dimensional space by recursively subdividing it into four quadrants or regions. Similarly, by partitioning polygons into small rectangles, we put them into Quadtree. Thus, a point query will be transformed to a query in Quadtree without checking 'point in polygons' explicitly.

However, it seems that we fail to implement Alg. 3 in a correct way. Alg. 3 performs the worst in these four methods and it even renders my computer crashed when running a large-scale test case.

### Alg. 4: Grid Method + Brute-Force

The final solution invokes another 'point in polygon' strategy, called [Grid Method](http://erich.realtimerendering.com/ptinpoly/). The idea is to impose a grid inside the bounding box containing the polygon. Each grid cell is categorized as being fully inside, fully outside, or indeterminate. The indeterminate cells also have a list of edges which overlap the cell, and also one corner (or more) is determined to be inside or outside using a traditional test. It is quick to determine the state of these corners by dealing with those on each latitude line by flipping the state of each corner to the right of the edge's crossing point. To test a point against this structure is extremely quick in most cases.

Incorporating Grid Method into our algorithm, we only need to enumerate all polygons and points and check them for each query. This brute-force algorithm, however, give the best performance among four methods, thanks to the fast implementation of Grid Method provided at http://www.realtimerendering.com/resources/GraphicsGems//gemsiv/ptpoly_haines/.

## Conclusion

In this project, we make a deep analysis about geo-fencing problem. Three spatial indexing data structures and three 'point in polygon' strategies are discussed thoroughly. Although the final solution is a rather simple one, it still takes us great effort to implement all these four methods. In conclusion, it's a few-code project with heavy workload! :innocent:

## Acknowledgments

- Thanks to the teaching assistants for revising our work.
- Thanks to my classmate [**Chenhao Wang**](https://github.com/wch19990119) for his helpful discussion with me.