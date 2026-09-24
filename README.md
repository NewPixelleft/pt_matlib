# pt Mathematical Library
A collection of C++ lightweight mathematical libraries by NewPixelleft (formerly Pixelleft) in practicing mathematical abstraction utilizing generic programming and operator overloading

## Libraries
### `Points.hpp`
A generic 2D Cartesian geometry library built around templated `pt::Point<T>` structure. This library rupports:
* Generic numeric types through C++20 concepts
* Point addition, subtraction, scalar multiplication, and division
* Compound assignment operators
* Translation
* Dilation/scaling around a pivot
* Rotation and clockwise rotation
* 2×2 matrix transformations
* Manhattan and Euclidean distance
* Average and median point calculations
* `std::pair` to Point conversion

Example
```cpp
Example:

#include <Points.hpp>

pt::Point<double> a{2.0, 3.0};
pt::Point<double> b{5.0, 7.0};

auto sum = a + b;
auto distance = pt::EuclidDis(a, b);

auto rotated = pt::Rotate(a, pt::toRadian(90));
```
The library is designed to make common 2D geometric operations concise and reusable.


---

### `pt::Polynomial`

A polynomial abstraction using a `std::vector<double>` to store coefficients.

Coefficients are stored from the constant term upward:

`Polynomial{2, -3, 1}` Equals $y = x^2 - 3x + 1$

The library supports:

* Polynomial construction from initializer lists
* Polynomial evaluation
* Derivative evaluation
* Definite integral evaluation
* Generating derivative polynomials
* Generating integral polynomials
* Polynomial addition and subtraction
* Polynomial multiplication
* Compound arithmetic operators
* Coefficient indexing
* Polynomial degree and size information
* Human-readable polynomial parsing
* Automatic removal of unnecessary trailing zero coefficients
* Horner's method for polynomial evaluation

Example:

```cpp
#include <Polynomials.hpp>

pt::Polynomial p{2, -3, 1};

double y = p.evaluate(5);

auto derivative = p.derivative();
auto integral = p.integral();

auto product = p * derivative;
```
Which equals: 

$p(x) = x² - 3x + 2$

$p'(x) = 2x - 3$

