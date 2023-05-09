#ifndef FRACTION_H
#define FRACTION_H
#pragma once

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

namespace ariel {

    class Fraction {
        // Data members
    private:

        int numerator;
        int denominator;
        float value;
    public:
        // Constructors
        Fraction(); // default constructor
        Fraction(int numerator, int denominator);// constructor with parameters for numerator and denominator
        Fraction(float value);// constructor with parameters for float value

        // Getters
        int getNumerator() const;// returns the numerator
        int getDenominator() const;// returns the denominator

        // Operators
        Fraction &operator++();
        Fraction operator++(int);
        Fraction &operator--();
        Fraction operator--(int);

        friend Fraction operator+(const Fraction &fraction_a, const Fraction &fraction_b);
        friend Fraction operator+(const Fraction &fraction_a, const float &fraction_b);
        friend Fraction operator+(const float &fraction_a, const Fraction &fraction_b);

        friend Fraction operator-(const Fraction &fraction_a, const Fraction &fraction_b);
        friend Fraction operator-(const float &fraction_a, const Fraction &fraction_b);
        friend Fraction operator-(const Fraction &fraction_a, const float &fraction_b);

        friend Fraction operator*(const Fraction &fraction_a, const float &fraction_b);
        friend Fraction operator*(const float &fraction_a, const Fraction &fraction_b);
        friend Fraction operator*(const Fraction &fraction_a, const Fraction &fraction_b);

        friend Fraction operator/(const float &fraction_a, const Fraction &fraction_b);
        friend Fraction operator/(const Fraction &fraction_a, const float &fraction_b);
        friend Fraction operator/(const Fraction &fraction_a, const Fraction &fraction_b);

        friend ostream &operator<<(ostream &osstrea, const Fraction &fraction);
        friend istream &operator>>(istream &istrea, Fraction &fraction);

        friend bool operator==(const Fraction &fraction_a, const Fraction &fraction_b);
        friend bool operator==(const float &fraction_a, const Fraction &fraction_b);
        friend bool operator==(const Fraction &fraction_a, const float &fraction_b);

        friend bool operator!=(const Fraction &fraction_a, const Fraction &fraction_b);
        friend bool operator!=(const float &fraction_a, const Fraction &fraction_b);
        friend bool operator!=(const Fraction &fraction_a, const float &fraction_b);

        friend bool operator>(const Fraction &fraction_a, const Fraction &fraction_b);
        friend bool operator>(const float &fraction_a, const Fraction &fraction_b);
        friend bool operator>(const Fraction &fraction_a, const float &fraction_b);

        friend bool operator<(const Fraction &fraction_a, const float &fraction_b);
        friend bool operator<(const float &fraction_a, const Fraction &fraction_b);
        friend bool operator<(const Fraction &fraction_a, const Fraction &fraction_b);

        friend bool operator>=(const float &fraction_a, const Fraction &fraction_b);
        friend bool operator>=(const Fraction &fraction_a, const float &fraction_b);
        friend bool operator>=(const Fraction &fraction_a, const Fraction &fraction_b);

        friend bool operator<=(const float &fraction_a, const Fraction &fraction_b);
        friend bool operator<=(const Fraction &fraction_a, const Fraction &fraction_b);
        friend bool operator<=(const Fraction &fraction_a, const float &fraction_b);
        // Methods
        void MyGcd();
    };
};
#endif // FRACTION_H