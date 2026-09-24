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

```text
Polynomial{2, -3, 1}
       ↓
1x² - 3x + 2
```

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

For example:

```text
p(x) = x² - 3x + 2

p'(x) = 2x - 3
```

## Robotics Relevance

Although these libraries are not complete robotics systems, the mathematical abstractions they provide are relevant to robotics programming.

`pt::Points` can be used to represent:

* Robot positions
* Waypoints
* Distances between objects
* 2D movement
* Geometric transformations

`pt::Polynomial` provides mathematical operations that can be useful for:

* Interpolation
* Mathematical modeling
* Trajectory representation
* Motion-related calculations
* Sensor or calibration models

These projects were developed as an exploration of how mathematical concepts can be represented as reusable C++ abstractions.

## Technologies

* C++
* C++20 Concepts
* Templates
* STL
* Operator overloading
* Object-oriented programming
* Generic programming
* Mathematical algorithms

## Project Structure

```text
pt/
├── Points.hpp
├── Polynomials.hpp
└── README.md
```

## Motivation

These libraries were created to improve my understanding of C++ beyond basic procedural programming, particularly in designing reusable interfaces and translating mathematical concepts into software abstractions.

````

### One thing I'd add specifically for the robotics registration

I'd put a **very short intro above the technical details**, something that tells the reviewer *why they're seeing these projects*:

# About This Portfolio

This portfolio contains two of my C++ projects: `pt::Points` and `pt::Polynomial`.

Both projects focus on implementing mathematical concepts as reusable C++ abstractions. I developed them to strengthen my understanding of C++ templates, concepts, operator overloading, STL containers, and algorithm design.

While these are not complete robotics applications, the concepts represented by both libraries are directly applicable to robotics programming, particularly coordinate geometry, spatial calculations, mathematical modeling, and trajectory-related computation.

I am currently expanding my experience toward robotics software development and intend to apply these programming fundamentals to larger robotics projects.

I actually think that last paragraph is **important**.

Don't write something like:

> "This is my robotics project."

because it isn't.

Instead:

> **"These are my existing C++ projects, and here's how the skills behind them transfer to robotics."**

That's a much stronger presentation of your situation.

Also, I'd **absolutely include the source code**, not just screenshots. For a robotics team, a reviewer who knows C++ can learn considerably more from seeing something like:

```cpp
template <typename T>
concept numeric = std::integral<T> || std::floating_point<T>;
````

and

```cpp
Polynomial& operator*=(const Polynomial& other)
```

than from a pretty screenshot of the output.

One last thing: before submitting, I'd make **one tiny demo program** that uses *both* libraries together. For example, generate polynomial points:

```cpp
pt::Polynomial trajectory{0, 2, 1};

auto points = trajectory.plot_point(-5, 5, 0.1);
```

That would give you a very clean bridge between the two projects: **mathematical function → generated 2D points**. Even without the maze solver, that's a neat little demonstration of how your libraries can compose.
