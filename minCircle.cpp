/*
 * Author: 318324563 - Daniel Meir Karl
 */
#include "minCircle.h"
/**
 * finding the minCircle is based on welzl's algorithm
 */
/**
 * @param a is the 1st pnt
 * @param b is 2nd pnt
 * @return the distance between two points
 */
float distance(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
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
 /**
  * method to get a circle center defined by 3 points
  * @param diffX12 is the difference between the x's of the 1st point and the 2nd point
  * @param diffY12 is the difference between the y's of the 1st point and the 2nd point
  * @param diffX13 is the difference between the x's of the 1st point and the 3rd point
  * @param diffY13 is the difference between the Y's of the 1st point and the 3rd point
  * @return a center point of the circle when the 3 points intersects the circle.
  */
Point get_circle_center(float diffX12, float diffY12,
                        float diffX13, float diffY13)
{
    float B = diffX12 * diffX12 + diffY12 * diffY12;
    float C = diffX13 * diffX13 + diffY13 * diffY13;
    float D = diffX12 * diffY13 - diffY12 * diffX13;
    return { (((diffY13 * B - diffY12 * C) / (2 * D))),
             (((diffX12 * C - diffX13 * B) / (2 * D))) };
}

/**
 * @param p1 is the 1st point
 * @param p2 is the 2nd point
 * @param p3 is the 3rd point
 * @return a circle that intersects three points
 */
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
/**
 *
 * @param p1 is the 1st point
 * @param p2 is the 2nd point
 * @return a circle that intersects two points
 */
Circle circle_from(const Point& p1, const Point& p2)
{
    // the center is the midpoint of A and B
    Point center = { static_cast<float>((p1.x + p2.x) / 2.0), static_cast<float>((p1.y + p2.y) / 2.0) };

    // the radius is half the distance of AB
    return { center, static_cast<float>(distance(p1, p2) / 2.0) };
}
/**
 * check if all points are in certain circle
 * @param circle to check
 * @param pts vector of points
 * @return if all points are in certain circle
 */
bool is_valid_circle(const Circle& circle,
                     const vector<Point>& pts)
{
     // check all points if they inside the circle or not
    for (const Point& p : pts)
        if (!is_inside(circle, p))
            return false;
    return true;
}
// Function to return the minimum enclosing
// circle for N <= 3
/**
 *
 * @param pts vector of three or less points
 * @return return the minimum circle for points equal or less than 3
 */
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

/**
 *
 * @param pts is a vector of points
 * @param R is vector of points that lies on the circle boundary.
 * @param n number of points in pts that are not yet processed
 * @return the minimum circle
 */
Circle welzl_helper(vector<Point>& pts,
                    vector<Point> R, int n)
{
    // Base case when all points processed or |R| = 3
    if (n == 0 || R.size() == 3) {
        return min_circle_simple(R);
    }

    // take a random point randomly
    int idx = rand() % n;
    Point p = pts[idx];

    // Put the random point at the end of pts
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(pts[idx], pts[n - 1]);

    // Get the  circle from the set of points pts without the picked point
    Circle circle = welzl_helper(pts, R, n - 1);

    // If the circle contains p, return the circle
    if (is_inside(circle, p)) {
        return circle;
    }

    // Otherwise, the random point must be on the boundary of the circle
    R.push_back(p);

    // Return the circle for pts without the picked point
    return welzl_helper(pts, R, n - 1);
}
/**
 * shuffle the points and call for the welzl's algorithm.
 * @param pts is a vector of points
 * @return the minimum circle using welzl_helper method
 */
Circle welzl(const vector<Point>& pts)
{
    vector<Point> pts_copy = pts;
    random_shuffle(pts_copy.begin(), pts_copy.end());
    return welzl_helper(pts_copy, {}, pts_copy.size());
}
/**
 * @param points is an array of points
 * @param size is the number of elements in the vector of points
 * @return the minimum circle in which all points
 * are in the circle or on boundry.
 *
 */
Circle findMinCircle(Point** points,size_t size) {
    vector<Point> pts;
    for (int i = 0; i < size; ++i) {
        pts.push_back(*points[i]);
    }
    return welzl(pts);
}

