#pragma once

#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <concepts>
#include <numbers>


namespace pt{
    
    using std::sin;
    using std::cos;

template <typename T>
    concept numeric = std::integral<T> || std::floating_point<T>;

template <numeric T>
struct Point{
    T x;
    T y;
};

// Point initializers

template <numeric T>
Point <T> MakePoint(const std::pair <T, T> &p){
    return {p.first, p.second};
}

template <numeric T>
Point <T> MakePoint(const T &x, const T &z){
    return {x, z};
}

// Point Operator controls
// ##### addition (+) #####
    template <numeric A>
    inline auto operator + (const Point<A>& a, const Point<A>& b){
        return Point <A> {a.x + b.x, a.y + b.y};
    }
    

// ##### subtraction (-) ####
    // make negative
    template <numeric T>
    inline Point<T> operator - (const Point<T> &a){
        return {
            -a.x,
            -a.y
        };
    }

    // Point with Point
    template <numeric T>
    inline Point<T>& operator -= (Point<T> &a, const Point<T>& b){
        a.x -= b.x;
        a.y -= b.y;
    
        return a;
    }

// ##### multiplier (*) ####
    // multiply with scalar
    template <numeric T>
    inline Point<T> operator * (const Point<T> a, const T b){
        return {
            a.x * b,
            a.y * b
        };
    }

    template <numeric T>
    inline Point<T>& operator *= (Point<T> &a, const T scalar){
        a.x *= scalar;
        a.y *= scalar;
        
        return a;
    }

// ##### divider (/) ####
    // divide with scalar
    template <numeric T>
    inline Point <T> operator / (const Point<T>& a, const T b){
        return {
            a.x / b,
            a.y / b
        };
    }
    
    // scalar
    template <numeric T>
    inline Point<T>& operator /= (Point<T> &a, const T scalar){
        a.x /= scalar;
        a.y /= scalar;
        
        return a;
    }


// Default Utility Points

template <numeric T>
inline constexpr Point <T> POINT_ZERO ={
    0,
    0
}; //default for point (0, 0)

inline double toRadian(double _angleInDegrees){
    return _angleInDegrees * std::numbers::pi / 180.0;
}

// --- distance functions ---

template <numeric T>
inline double ManhattanDis(const Point<T>& a, const Point<T>& b){
    return std::abs(b.x - a.x) + std::abs(b.y - a.y);
}

template <numeric T>
inline double EuclidDis(const Point<T>& a, const Point<T>& b){
    return std::hypot(a.x - b.x, a.y - b.y);
}

// Geometric transformation 
template <numeric T>
inline Point<T> Negative(const Point<T>& source){
    return {
        -source.x,
        -source.y
    };
}

template <numeric T>
Point <T>Translate(const Point<T> source, T translate_x, T translate_y){
    Point <T>retval ={
        source.x + translate_x,
        source.y + translate_y
    };

    return retval;
}

template <numeric T>
Point<T> Translate(const Point<T> &source, const Point<T> modifier){
    return source + modifier;
}

template <numeric T>
Point<T>  Dilate (const Point <T> &source,  T k, Point <T> pivot = POINT_ZERO<T>){
    Point <T>retval = Translate(source, Negative(pivot));
    retval *= k;
    return Translate(retval, pivot);
}

template <numeric T>
Point <T>Rotate(const Point<T> source,  double angle, Point<T> pivot = POINT_ZERO<T>){
    Point <T>retval = Translate(source, Negative(pivot));
    retval = {
        (retval.x * cos(angle)) - (retval.y * sin(angle)),
        (retval.x * sin(angle)) + (retval.y * cos(angle))
    };
    return Translate(retval, pivot);
}

template <numeric T>
Point<T> RotateClockwise(const Point<T> &source, const double angle, Point<T> pivot = POINT_ZERO<T>){
    return Rotate(source, -angle, pivot);
}

// quick transform using a 2x2 matrix
template <numeric T>
Point<T> TransformMTR(const Point<T> source, double _transformingMatrix[2][2]){
    Point <T>retval = {
        (source.x * _transformingMatrix[0][0]) + (source.y *_transformingMatrix[0][1]),
        (source.x * _transformingMatrix[1][0]) + (source.y *_transformingMatrix[1][1])
    };
    return retval;
}

// ##### Advanced array functions #####
// median point function
template <typename pointIterator, numeric T>
Point <T> MedianPoint(pointIterator start, pointIterator end) {

    auto dist = std::distance(start, end);
    std::vector<T> valx, valy;
    valx.reserve(dist);
    valy.reserve(dist);

    for (auto i = start; i != end; i++){
        valx.push_back(i->x);
        valy.push_back(i->y);
    }

    std::sort(valx.begin(), valx.end());
    std::sort(valy.begin(), valy.end());

    size_t n = valx.size();
    T px, py;

    if (n & 1) {
        px = valx[n / 2];
        py = valy[n / 2];
    } else {
        px = (valx[n/2] + valx[n/2 - 1]) / 2.0;
        py = (valy[n/2] + valy[n/2 - 1]) / 2.0;
    }

    return {px, py};
}

template <typename pointIterator, numeric T>
Point <T> AveragePoint(pointIterator first, pointIterator second){
    T n = static_cast <T>(std::distance(first, second));
    T sumx = 0, sumy = 0;
    for (auto i = first; i != second; i++){
        sumx += i->x;
        sumy += i->y;
    }
    return MakePoint(sumx / n, sumy / n);
}

}; // namespace pt