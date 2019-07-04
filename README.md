# Geo-fencing
![grid](README.asset/GeoFence.png)
<center><font size="1">This figure is from https://www.propellant.media/geofencing-marketing-company-providers/.</font></center>


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
| ---- | ---- | ---- | ---- | ---- | ---- | ----- |
|case_1|0|0|2000|15000|0|0|
|case_2|150000|0|0|0|0|200|
|case_3|100000|0|500|5000|0|300|
|case_4|0|0|2000|15000|1000|0|
|case_5|150000|20000|0|0|0|200|
|case_6|100000|10000|300|5000|500|300|


## Problem Analysis

### Spatial Indexing Data Structure

### Point in Polygon Strategies

## Solutions

### R-tree + Brute-Force

### k-d tree + Triangulation

### Quadtree + Triangulation

### Grid Method + Brute-Force

## Conclusion

## Acknowledgments