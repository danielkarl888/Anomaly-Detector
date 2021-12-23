/*
 * Author: 208388140 - Dvir Landau
 */
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <assert.h>
#include <algorithm>
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------



float distance(const Point& a, const Point& b);
// Function to check whether a point lies inside
// or on the boundaries of the circle

bool is_inside(const Circle& c, const Point& p);
// The following two functions are used
// To find the equation of the circle when
// three points are given.
Point get_circle_center(float bx, float by,
                        float cx, float cy);
// Function to return a unique circle that
// intersects three points
Circle circle_from(const Point& p1, const Point& p2,
                   const Point& p3);

// Function to return the smallest circle
// that intersects 2 points
Circle circle_from(const Point& p1, const Point& p2);
// Function to check whether a circle
// encloses the given points
bool is_valid_circle(const Circle& c,
                     const vector<Point>& P);
// Function to return the minimum enclosing
// circle for N <= 3
Circle min_circle_simple(vector<Point>& pts);

// Returns the MEC using Welzl's algorithm
// Takes a set of input points P and a set R
// points on the circle boundary.
// n represents the number of points in P
// that are not yet processed.
Circle welzl_helper(vector<Point>& pts,
                    vector<Point> R, int n);
Circle findMinCircle(Point** points,size_t size);


#endif /* MINCIRCLE_H_ */
