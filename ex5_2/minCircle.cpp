#include "minCircle.h"

Circle two_case(Point point1, Point point2) {
    return Circle(Point((point1.x + point2.x) / 2, (point1.y + point2.y) / 2), distance(point1,point2) / 2);
}

Circle three_case(Point point1, Point point2, Point point3) {

    Point middle1((point1.x + point2.x) / 2 , (point1.y + point2.y) / 2);
    Point middle2((point1.x + point3.x) / 2 , (point1.y + point3.y) / 2);

    float slope1 = - 1 / ((point2.y - point1.y) / (point2.x - point1.x));
    float slope2 = - 1 / ((point3.y - point1.y) / (point3.x - point1.x));

    float a1 = slope1 * middle1.x - middle1.y;
    float a2 = slope2 * middle2.x - middle2.y;
    float x = (a1 - a2) / (slope1 - slope2);

    float y = slope1 * (x - middle1.x) + middle1.y;

    Point center(x,y);

    return Circle(center, distance(center,point1));
}

Circle trivial(vector<Point> R) {
    switch (R.size()) {
        case 0:
            return Circle(Point(0, 0), 0);
        case 1:
            return Circle(R[0], 0);
        case 2:
            return two_case(R[0], R[1]);
        case 3:
            Circle D1 = two_case(R[0],R[1]);
            Circle D2= two_case(R[0],R[2]);
            Circle D3 = two_case(R[1],R[2]);

            if(distance(R[2], D1.center) <= D1.radius) {
                return D1;
            }
            if(distance(R[1], D2.center) <= D2.radius) {
                return D2;
            }
            if(distance(R[0], D3.center) <= D3.radius) {
                return D3;
            }
            return three_case(R[0],R[1],R[2]);
    }

}

float distance(Point point1, Point point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

bool check_p_in_D(Point point, Circle circle) {
    if(distance(point, circle.center) <= circle.radius) {
        return true;
    }
    return false;
}

Circle alg_welzl(Point** P, vector<Point> R, size_t n) {
    if( n == 0 || R.size() == 3) {
        return trivial(R);
    }

    int i = rand() % n;
    Point p(P[i]->x,P[i]->y);
    swap(P[i],P[n-1]);
    Circle D = alg_welzl(P,R,n-1);
    if (check_p_in_D(p, D)) {
        return D;
    }

    R.push_back(p);
    return alg_welzl(P, R, n-1);

}

Circle findMinCircle(Point** points, size_t size) {
    return alg_welzl(points,{}, size);
}

