/**
 * This class represents a fraction object in the following format: numerator/denominator.
 * It provides overloaded operators among fractions including inputting and outputting. Besides, it contains an overflow detector.
 * An instance of this class is always displayed in its simplified form.
 * 
 * @author Osama M. Ghaliah
*/

#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <limits>

using namespace std;

namespace ariel {
    // To detect overflows.
    static const int maximalInteger = numeric_limits <int> :: max();
    static const int minimalInteger = numeric_limits <int> :: min();

    class Fraction {
        private:
            // Upper part of the fraction.
            int numerator;
            // Lower part of the fraction.
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
            friend Fraction operator + (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction operator + (const Fraction& fraction1, const float& fraction2);
            friend Fraction operator + (const float& fraction1, const Fraction& fraction2);
            friend Fraction operator - (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction operator - (const Fraction& fraction1, const float& fraction2);
            friend Fraction operator - (const float& fraction1, const Fraction& fraction2);
            friend Fraction operator / (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction operator / (const Fraction& fraction1, const float& fraction2);
            friend Fraction operator / (const float& fraction1, const Fraction& fraction2);
            friend Fraction operator * (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction operator * (const float& fraction1, const Fraction& fraction2);
            friend Fraction operator * (const Fraction& fraction1, const float& fraction2);
            friend Fraction& operator ++ (Fraction& fraction);
            friend Fraction operator ++ (Fraction& fraction, int);
            friend Fraction& operator -- (Fraction& fraction);
            friend Fraction operator -- (Fraction& fraction, int);

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
            
            // Printing, simplification and conversion.
            string details();
            static Fraction simplify(int numerator, int denominator);
            friend void simplifyThis(Fraction& fraction);
            static Fraction floatToFraction(float toConvert);
    };
};

#endif