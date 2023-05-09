#include "Fraction.hpp"
#include <iostream>
#include <sstream>  // Include the <sstream> header for std::istringstream
#include <stdexcept>
#include <numeric>
#include <cmath>
#include <vector>
#include <limits>
const int max_int =std::numeric_limits<int>::max();
const int min_int =std::numeric_limits<int>::min();


using namespace std;

namespace ariel {

    Fraction::Fraction() {}
    // Helper function for the constructor

    //constructor with parameters for numerator and denominator
    Fraction::Fraction(int numerator, int denominator) {
        // Check if the denominator is zero and throw an exception
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        this->numerator = numerator;
        this->denominator = denominator;
        // Convert the fraction to a float
        this->value =  static_cast<float> (numerator) / denominator;
        MyGcd();
    }
    //constructor with parameters for float value
    Fraction::Fraction(float value) {
        //limit the value to three decimal places
        double limitedToThreeDecimals = std::round(value * 1000.0) / 1000.0;
        // Convert limitedToThreeDecimals to a fraction
        numerator = static_cast<int>(limitedToThreeDecimals * 1000);
        // The denominator is always 1000
        denominator = 1000;
        this->value = value;
        MyGcd();
    }
    //getters functions
    int Fraction::getNumerator() const {
        return this->numerator;
    }

    int Fraction::getDenominator() const {
        return this->denominator;
    }
    //operator++ function
    Fraction& Fraction::operator++() {
        // Increment the numerator by the denominator
        this->numerator += this->denominator;
        //make the value of the fraction
        this->value = (float) this->numerator / this->denominator;
        return *this;
    }
    //operator++ function with int
    Fraction Fraction::operator++(int) {
        Fraction old_value = *this;
        this->numerator += this->denominator;
        this->value = (float) this->numerator / this->denominator;
        return old_value;

    }
    //operator-- function
    Fraction& Fraction::operator--() {
        // Decrement the numerator by the denominator
        this->numerator -= this->denominator;
        this->value = (float) this->numerator / this->denominator;
        return *this;
    }
    //operator-- function with int
    Fraction Fraction::operator--(int) {
        Fraction old_value = *this;
        this->numerator -= this->denominator;
        this->value = (float) this->numerator / this->denominator;
        return old_value;
    }
    //operator+ function
    Fraction operator+(const Fraction& fraction_a, const Fraction& fraction_b) {
        // Check for overflow in the numerator and denominator before adding
        if(fraction_a.getNumerator() > 0 && fraction_b.getNumerator() > max_int - fraction_a.getNumerator()) {
            throw std::overflow_error("Overflow error");
        }
        if(fraction_a.getNumerator() < 0 && fraction_b.getNumerator() < min_int - fraction_a.getNumerator()) {
            throw std::overflow_error("Overflow error");
        }
        if(fraction_a.getDenominator() > 0 && fraction_b.getDenominator() > max_int - fraction_a.getDenominator()) {
            throw std::overflow_error("Overflow error");
        }
        if(fraction_a.getDenominator() < 0 && fraction_b.getDenominator() < min_int - fraction_a.getDenominator()) {
            throw std::overflow_error("Overflow error");
        }
        // Add the fractions
        return Fraction((fraction_a.getNumerator() * fraction_b.getDenominator()) +(fraction_b.getNumerator() * fraction_a.getDenominator()), fraction_a.getDenominator() * fraction_b.getDenominator());
    }
    //operator+ function with float
    Fraction operator+(const Fraction& fraction_a, const float& fraction_b) {
        return fraction_a + static_cast<Fraction>(static_cast<double>(fraction_b));
    }
    //operator+ function with float
    Fraction operator+(const float& fraction_a, const Fraction& fraction_b) {
        return Fraction(fraction_a) + fraction_b;
    }
    //operator- function
    Fraction operator-(const Fraction& fraction_a, const Fraction& fraction_b) {
        long long new_numerator = static_cast<long long>(fraction_a.getNumerator()) * fraction_b.getDenominator() -
                                  static_cast<long long>(fraction_b.getNumerator()) * fraction_a.getDenominator();
        int new_denominator = fraction_a.getDenominator() * fraction_b.getDenominator();
        if ((new_numerator > max_int || new_numerator < min_int ||
             new_denominator > max_int || new_denominator < min_int)) {
            throw std::overflow_error("Overflow error");
        }
        return Fraction(new_numerator, new_denominator);
    }
//operator- function with float
    Fraction operator-(const float& fraction_a, const Fraction& fraction_b) {
        return static_cast<Fraction>(static_cast<double>(fraction_a)) - fraction_b;
    }
//operator- function with float
    Fraction operator-(const Fraction& fraction_a, const float& fraction_b) {
        return fraction_a - Fraction(fraction_b);
    }
//operator* function with float
    Fraction operator*(const Fraction& fraction_a, const float& fraction_b) {
        //make operation and build new numerator and denominator
        //multiply the numerator by the float value and multiply the denominator by 1000
        long long new_numerator = std::round(static_cast<long long>(fraction_a.getNumerator()) * static_cast<double>(fraction_b) * 1000);
        long long new_denominator = fraction_a.getDenominator() * 1000;
        // Check for overflow in the numerator and denominator after multiplying
        if (new_numerator > max_int || new_numerator < min_int ||
            new_denominator > max_int || new_denominator < min_int) {
            throw std::overflow_error("Overflow error");
        }
        return Fraction(static_cast<int>(new_numerator), new_denominator);
    }


    Fraction operator*(const float& fraction_a, const Fraction& fraction_b) {
        return fraction_b * fraction_a;
    }
    //operator* function
    Fraction operator*(const Fraction& fraction_a, const Fraction& fraction_b) {
        //check for overflow
       if(fraction_a.getNumerator() > 0 && fraction_b.getNumerator() >max_int/fraction_a.getNumerator()){
           throw std::overflow_error("Overflow error");
         }
       if(fraction_a.getNumerator() < 0 && fraction_b.getNumerator() <max_int/fraction_a.getNumerator()){
           throw std::overflow_error("Overflow error");
         }
        if(fraction_a.getDenominator() > 0 && fraction_b.getDenominator() >max_int/fraction_a.getDenominator()){
            throw std::overflow_error("Overflow error");
        }
        if(fraction_a.getDenominator() < 0 && fraction_b.getDenominator() <max_int/fraction_a.getDenominator()){
            throw std::overflow_error("Overflow error");
        }
        return Fraction(((fraction_a.getNumerator())*fraction_b.getNumerator()), (fraction_a.getDenominator())*fraction_b.getDenominator());
    }

    Fraction operator/(const float& fraction_a, const Fraction& fraction_b) {
        return static_cast<Fraction>(static_cast<double>(fraction_a)) / fraction_b;
    }

    Fraction operator/(const Fraction& fraction_a, const float& fraction_b) {
        return fraction_a / static_cast<Fraction>(static_cast<double>(fraction_b));
    }
    //operator/ function
    Fraction operator/(const Fraction& fraction_a, const Fraction& fraction_b) {
        //check for division by zero
        if (fraction_b == 0) {
            throw std::runtime_error("Division by zero");
        }
        //check for overflow
        if(fraction_a.getNumerator() > 0 && fraction_b.getNumerator() >max_int/fraction_a.getNumerator()){
            throw std::overflow_error("Overflow error");
        }
        if(fraction_a.getNumerator() < 0 && fraction_b.getNumerator() <max_int/fraction_a.getNumerator()){
            throw std::overflow_error("Overflow error");
        }
        if(fraction_a.getDenominator() > 0 && fraction_b.getDenominator() >max_int/fraction_a.getDenominator()){
            throw std::overflow_error("Overflow error");
        }
        if(fraction_a.getDenominator() < 0 && fraction_b.getDenominator() <max_int/fraction_a.getDenominator()){
            throw std::overflow_error("Overflow error");
        }
        return Fraction(fraction_a.numerator* fraction_b.denominator, fraction_a.denominator* fraction_b.numerator);
    }

    // Output stream operator
    ostream& operator<<(ostream& os, const Fraction& fraction) {
        os << fraction.numerator << "/" << fraction.denominator;
        return os;
    }

    // Input stream operator
    std::istream &operator>>(std::istream &input, Fraction &frac)
    {
        int numerator, denominator;
        //check for invalid input
        if(!(input >> numerator >> denominator)){
            throw std::runtime_error("Invalid input");
        }
        //check for division by zero
        if(denominator == 0){
            throw std::runtime_error("Division by zero");
        }
        frac = Fraction(numerator, denominator);
        return input;
    }
    // Equality operator with another fraction
    bool operator==(const Fraction &fraction_a, const Fraction &fraction_b) {
        return fraction_a.numerator == fraction_b.numerator && fraction_a.denominator == fraction_b.denominator;
    }

    bool operator==(const float &fraction_a, const Fraction &fraction_b) {
        float float_a = fraction_a;
        return float_a == static_cast<float>(fraction_b.numerator) / fraction_b.denominator;
    }

    bool operator==(const Fraction &fraction_a, const float &fraction_b) {
        float float_b = fraction_b;
        return static_cast<float>(fraction_a.numerator) / fraction_a.denominator == float_b;
    }

    bool operator!=(const Fraction &fraction_a, const Fraction &fraction_b) {
        return !(fraction_a == fraction_b);
    }

    bool operator!=(const float &fraction_a, const Fraction &fraction_b) {
        return !(fraction_a == fraction_b);
    }

    bool operator!=(const Fraction &fraction_a, const float &fraction_b) {
        return !(fraction_a == fraction_b);
    }

    bool operator>(const Fraction &fraction_a, const Fraction &fraction_b) {
        return static_cast<float>(fraction_a.numerator) / fraction_a.denominator > static_cast<float>(fraction_b.numerator) / fraction_b.denominator;
    }

    bool operator>(const float &fraction_a, const Fraction &fraction_b) {
        float float_a = fraction_a;
        return float_a > static_cast<float>(fraction_b.numerator) / fraction_b.denominator;
    }

    bool operator>(const Fraction &fraction_a, const float &fraction_b) {
        float float_b = fraction_b;
        return static_cast<float>(fraction_a.numerator) / fraction_a.denominator > float_b;
    }

    bool operator<(const Fraction &fraction_a, const Fraction &fraction_b) {
        return static_cast<float>(fraction_a.numerator) / fraction_a.denominator < static_cast<float>(fraction_b.numerator) / fraction_b.denominator;
    }

    bool operator<(const float &fraction_a, const Fraction &fraction_b) {
        float float_a = fraction_a;
        return float_a < static_cast<float>(fraction_b.numerator) / fraction_b.denominator;
    }

    bool operator<(const Fraction &fraction_a, const float &fraction_b) {
        float float_b = fraction_b;
        return static_cast<float>(fraction_a.numerator) / fraction_a.denominator < float_b;
    }

    bool operator>=(const Fraction &fraction_a, const Fraction &fraction_b) {
        return fraction_a > fraction_b || fraction_a == fraction_b;
    }

    bool operator>=(const float &fraction_a, const Fraction &fraction_b) {
        return fraction_a > fraction_b || fraction_a == fraction_b;
    }

    bool operator>=(const Fraction &fraction_a, const float &fraction_b) {
        return fraction_a > fraction_b || fraction_a == fraction_b;
    }

    bool operator<=(const Fraction &fraction_a, const Fraction &fraction_b) {
        return fraction_a < fraction_b || fraction_a == fraction_b;
    }

    bool operator<=(const float &fraction_a, const Fraction &fraction_b) {
        return fraction_a < fraction_b || fraction_a == fraction_b;
    }

    bool operator<=(const Fraction &fraction_a, const float &fraction_b) {
        return fraction_a < fraction_b || fraction_a == fraction_b;
    }
    //gcd function to reduce fraction
    void Fraction::MyGcd() {
        //find gcd
        int gcd = __gcd(abs(numerator), abs(denominator));
        //divide by gcd
        numerator /= gcd;
        denominator /= gcd;
        //make sure denominator is positive
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }
}