
#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <Points.hpp>


namespace pt{

class Polynomial{
public:
    Polynomial() = default;

    Polynomial(std::initializer_list<double> coefficients)
        : args(coefficients){
        trim();
    }

    explicit Polynomial(std::size_t degree, double value = 0)
        : args(degree + 1, value){
        trim();
    }


    // ----- Evaluation -----

    double evaluate(double x) const{
        double result = 0;

        // Horner's method
        for (std::size_t i = args.size(); i-- > 0;){
            result = result * x + args[i];
        }

        return result;
    }

    double evaluate_Derivative(double x) const{
        if (args.size() <= 1)
            return 0;

        double result = 0;

        for (std::size_t i = args.size(); i-- > 1;){
            result = result * x + static_cast<double>(i) * args[i];
        }

        return result;
    }

    double evaluate_Integral(double a, double b) const{
        if (a == b)
            return 0;

        double result_a = 0;
        double result_b = 0;

        double power_a = a;
        double power_b = b;

        for (std::size_t i = 0; i < args.size(); i++){
            const double coefficient =
                args[i] / static_cast<double>(i + 1);

            result_a += coefficient * power_a;
            result_b += coefficient * power_b;

            power_a *= a;
            power_b *= b;
        }

        return result_b - result_a;
    }


    // ----- Derivative / Integral -----

    Polynomial derivative() const{
        if (args.size() <= 1)
            return Polynomial{0.0};

        Polynomial result(args.size() - 2);

        for (std::size_t i = 1; i < args.size(); i++){
            result[i - 1] = args[i] * static_cast<double>(i);
        }

        result.trim();

        return result;
    }

    Polynomial integral(double constant = 0) const{
        Polynomial result(args.size(), 0);
        result[0] = constant;

        for (std::size_t i = 0; i < args.size(); i++){
            result[i + 1] =
                args[i] / static_cast<double>(i + 1);
        }

        result.trim();

        return result;
    }


    // ----- Coefficient access -----

    double& operator[](std::size_t index){
        return args[index];
    }

    const double& operator[](std::size_t index) const{
        return args[index];
    }


    // ----- Information -----

    std::size_t degree() const{
        return args.empty() ? 0 : args.size() - 1;
    }

    std::size_t size() const{
        return args.size();
    }

    bool empty() const{
        return args.empty();
    }


    // ----- String representation -----

    std::string parse() const{
        std::string result;

        for (std::size_t i = args.size(); i-- > 0;){
            const double coefficient = args[i];

            if (coefficient == 0)
                continue;

            const bool positive = coefficient > 0;

            if (!result.empty()){
                result += positive ? " + " : " - ";
            }
            else if (!positive){
                result += "-";
            }

            const double absolute = std::fabs(coefficient);

            const bool show_coefficient =
                i == 0 || absolute != 1;

            if (show_coefficient)
                result += num_to_string(absolute);

            if (i >= 1){
                result += "x";

                if (i >= 2){
                    result += "^";
                    result += std::to_string(i);
                }
            }
        }

        if (result.empty())
            return "0";

        return result;
    }


    // ----- Operators -----

    Polynomial& operator+=(const Polynomial& other){
        const std::size_t required_size =
            std::max(args.size(), other.args.size());

        args.resize(required_size, 0);

        for (std::size_t i = 0; i < other.args.size(); i++){
            args[i] += other[i];
        }

        trim();

        return *this;
    }

    Polynomial& operator-=(const Polynomial& other){
        const std::size_t required_size =
            std::max(args.size(), other.args.size());

        args.resize(required_size, 0);

        for (std::size_t i = 0; i < other.args.size(); i++){
            args[i] -= other[i];
        }

        trim();

        return *this;
    }

    Polynomial& operator*=(const Polynomial& other){
        if (args.empty() || other.empty()){
            args.clear();
            return *this;
        }

        std::vector<double> result(
            args.size() + other.size() - 1,
            0
        );

        for (std::size_t i = 0; i < args.size(); i++){
            for (std::size_t j = 0; j < other.size(); j++){
                result[i + j] += args[i] * other[j];
            }
        }

        args = std::move(result);
        trim();

        return *this;
    }


private:
    std::vector<double> args;


    std::string num_to_string(double value) const{
        std::ostringstream stream;
        stream << value;

        return stream.str();
    }

    void trim(){
        while (args.size() > 1 && args.back() == 0)
            args.pop_back();
    }
};


inline Polynomial operator+(const Polynomial& a, const Polynomial& b){
    Polynomial result = a;
    result += b;

    return result;
}

inline Polynomial operator-(const Polynomial& a, const Polynomial& b){
    Polynomial result = a;
    result -= b;

    return result;
}

inline Polynomial operator*(const Polynomial& a, const Polynomial& b){
    Polynomial result = a;
    result *= b;

    return result;
}

}; // namespace pt
