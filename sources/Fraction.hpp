#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <vector>

using namespace std;

namespace ariel {
    class Fraction {
        private:
            int numerator;
            int denominator;
        
        public:
            // Constructors.
            Fraction();
            Fraction(double decimal);
            Fraction(int complete);
            Fraction(int numerator, int denominator);

            // Getters & setters.
            int getNumerator() const;
            int getDenominator() const;
            void setNumerator (int numerator);
            void setDenominator(int denominator);

            // Operators.
            friend Fraction& operator + (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction& operator + (const Fraction& fraction1, const float& fraction2);
            friend Fraction& operator + (const float& fraction1, const Fraction& fraction2);
            friend Fraction& operator - (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction& operator - (const Fraction& fraction1, const float& fraction2);
            friend Fraction& operator - (const float& fraction1, const Fraction& fraction2);
            friend Fraction& operator / (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction& operator / (const Fraction& fraction1, const float& fraction2);
            friend Fraction& operator / (const float& fraction1, const Fraction& fraction2);
            friend Fraction& operator * (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction& operator * (const float& fraction1, const Fraction& fraction2);
            friend Fraction& operator * (const Fraction& fraction1, const float& fraction2);
            friend Fraction& operator ++ (Fraction& fraction);
            friend Fraction& operator ++ (Fraction& fraction, int);
            friend Fraction& operator -- (Fraction& fraction);
            friend Fraction& operator -- (Fraction& fraction, int);

            friend bool operator < (const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator < (const Fraction& fraction1, const float& fraction2);
            friend bool operator < (const float& fraction1, const Fraction& fraction2);
            friend bool operator > (const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator > (const Fraction& fraction1, const float& fraction2);
            friend bool operator > (const float& fraction1, const Fraction& fraction2);
            friend bool operator <= (const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator >= (const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator == (const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator == (const Fraction& fraction1, const float& fraction2);
            friend bool operator == (const float& fraction1, const Fraction& fraction2);

            friend ostream& operator << (ostream& output, const Fraction& fraction);
            friend istream& operator >> (istream& input, Fraction& fraction);
            
            // Printing & Calculations.
            string details();
            static Fraction& simplify(int numerator, int denominator);
            static Fraction& floatToFraction(float toConvert);
    };
};

#endif