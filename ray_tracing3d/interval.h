#ifndef INTERVAL_H
#define INTERVAL_H

#include <cmath> // for INFINITY

class interval {
  public:
    double min, max;

    interval() : min(+INFINITY), max(-INFINITY) {} // Default: empty

    interval(double _min, double _max) : min(_min), max(_max) {}

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }
    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty;
    static const interval universe;
};

// Static definitions
const interval interval::empty    = interval(+INFINITY, -INFINITY);
const interval interval::universe = interval(-INFINITY, +INFINITY);

#endif // INTERVAL_H