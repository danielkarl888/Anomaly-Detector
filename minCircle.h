
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


/**
 * @param a is the 1st pnt
 * @param b is 2nd pnt
 * @return the distance between two points
 */
float distance(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
// Function to check whether a point lies inside
// or on the boundaries of the circle
/**
 *
 * @param c is the generated circle
 * @param p is the point to check
 * @return if the point lies inside or on the boundaries of the circle
 */
bool is_inside(const Circle& c, const Point& p)
{
    return distance(c.center, p) <= c.radius;
}
// The following two functions are used
// To find the equation of the circle when
// three points are given.
Point get_circle_center(float bx, float by,
                        float cx, float cy)
{
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return { (((cy * B - by * C) / (2 * D))),
             (((bx * C - cx * B) / (2 * D))) };
}
// Function to return a unique circle that
// intersects three points
Circle circle_from(const Point& p1, const Point& p2,
                   const Point& p3)
{
    Point center = get_circle_center(p2.x - p1.x, p2.y - p1.y,
                                p3.x - p1.x, p3.y - p1.y);

    center.x += p1.x;
    center.y += p1.y;
    return { center, distance(center, p1) };
}

// Function to return the smallest circle
// that intersects 2 points
Circle circle_from(const Point& p1, const Point& p2)
{
    // Set the center to be the midpoint of A and B
    Point center = { static_cast<float>((p1.x + p2.x) / 2.0), static_cast<float>((p1.y + p2.y) / 2.0) };

    // Set the radius to be half the distance AB
    return { center, static_cast<float>(distance(p1, p2) / 2.0) };
}
// Function to check whether a circle
// encloses the given points
bool is_valid_circle(const Circle& c,
                     const vector<Point>& P)
{
    // Iterating through all the points
    // to check  whether the points
    // lie inside the circle or not
    for (const Point& p : P)
        if (!is_inside(c, p))
            return false;
    return true;
}
// Function to return the minimum enclosing
// circle for N <= 3
Circle min_circle_simple(vector<Point>& pts)
{
    assert(pts.size() <= 3);
    if (pts.empty()) {
        return { { 0, 0 }, 0 };
    }
    else if (pts.size() == 1) {
        return { pts[0], 0 };
    }
    else if (pts.size() == 2) {
        return circle_from(pts[0], pts[1]);
    }

    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = circle_from(pts[i], pts[j]);
            if (is_valid_circle(c, pts))
                return c;
        }
    }
    return circle_from(pts[0], pts[1], pts[2]);
}
// Returns the MEC using Welzl's algorithm
// Takes a set of input points P and a set R
// points on the circle boundary.
// n represents the number of points in P
// that are not yet processed.
Circle welzl_helper(vector<Point>& pts,
                    vector<Point> R, int n)
{
    // Base case when all points processed or |R| = 3
    if (n == 0 || R.size() == 3) {
        return min_circle_simple(R);
    }

    // Pick a random point randomly
    int idx = rand() % n;
    Point p = pts[idx];

    // Put the picked point at the end of P
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(pts[idx], pts[n - 1]);

    // Get the MEC circle d from the
    // set of points P - {p}
    Circle d = welzl_helper(pts, R, n - 1);

    // If d contains p, return d
    if (is_inside(d, p)) {
        return d;
    }

    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);

    // Return the MEC for P - {p} and R U {p}
    return welzl_helper(pts, R, n - 1);
}
Circle welzl(const vector<Point>& pts)
{
    vector<Point> pts_copy = pts;
    random_shuffle(pts_copy.begin(), pts_copy.end());
    return welzl_helper(pts_copy, {}, pts_copy.size());
}
Circle findMinCircle(Point** points,size_t size) {
    vector<Point> pts;
    for (int i = 0; i < size; ++i) {
        pts.push_back(*points[i]);
    }
    return welzl(pts);

}


#endif /* MINCIRCLE_H_ */
