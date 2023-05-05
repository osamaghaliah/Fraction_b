#include <iostream>
#include "Fraction.hpp"

using namespace std;

namespace ariel {
    // Constructors.
    Fraction::Fraction() : numerator(0), denominator(1) { }

    Fraction::Fraction(double decimal) {
        Fraction converted = Fraction::floatToFraction(decimal);
        this->numerator = converted.getNumerator();
        this->denominator = converted.getDenominator();
    }

    Fraction::Fraction(int complete) {
        if (complete == 0) {
            this->numerator = 0;
            this->denominator = 1;
        } else {
            this->numerator = complete * complete;
            this->denominator = complete;
        }
    }

    Fraction::Fraction(int numerator, int denominator) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        } else if (numerator == 0) {
            this->numerator = 0;
            this->denominator = denominator;
        } else {
            this->numerator = numerator;
            this->denominator = denominator;
        }
    }

    // Getters & Setters.
    int Fraction::getNumerator() const {
        return this->numerator;
    }

    int Fraction::getDenominator() const {
        return this->denominator;
    }

    void Fraction::setNumerator (int numerator) {
        this->numerator = numerator;
    }

    void Fraction::setDenominator(int denominator) {
        this->denominator = denominator;
    }

    // Operators.
    Fraction& operator + (const Fraction& fraction1, const Fraction& fraction2) {
        int unitedNumerator = (fraction1.getNumerator() * fraction2.getDenominator()) + (fraction1.getDenominator() * fraction2.getNumerator());
        int unitedDenominator = fraction1.getDenominator() * fraction2.getDenominator();
    
        return Fraction::simplify(unitedNumerator, unitedDenominator);
    }

    Fraction& operator + (const Fraction& fraction1, const float& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction2);

        return (fraction1 + converted);
    }

    Fraction& operator + (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);

        return (converted + fraction2);
    }


    Fraction& operator - (const Fraction& fraction1, const Fraction& fraction2) {
        int unitedNumerator = (fraction1.getNumerator() * fraction2.getDenominator()) - (fraction1.getDenominator() * fraction2.getNumerator());
        int unitedDenominator = fraction1.getDenominator() * fraction2.getDenominator();

        return Fraction::simplify(unitedNumerator, unitedDenominator);
    }

    Fraction& operator - (const Fraction& fraction1, const float& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction2);

        return (fraction1 - converted);
    }

    Fraction& operator - (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);

        return (converted - fraction2);
    }

    Fraction& operator / (const Fraction& fraction1, const Fraction& fraction2) {
        int numerator = fraction1.getNumerator() * fraction2.getDenominator();
        int denominator = fraction1.getDenominator() * fraction2.getNumerator();
        
        return Fraction::simplify(numerator, denominator);
    }

    Fraction& operator / (const Fraction& fraction1, const float& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction2);

        return (fraction1 / converted);
    }

    Fraction& operator / (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);

        return (converted / fraction2);
    }

    Fraction& operator * (const Fraction& fraction1, const Fraction& fraction2) {
        int numerator = fraction1.getNumerator() * fraction2.getNumerator();
        int denominator = fraction1.getDenominator() * fraction2.getDenominator();

        return Fraction::simplify(numerator, denominator);
    }

    Fraction& operator * (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);

        return (converted * fraction2);
    }

    Fraction& operator * (const Fraction& fraction1, const float& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction2);

        return (fraction1 * converted);
    }

    Fraction& operator ++ (Fraction& fraction) {
        fraction.numerator += fraction.denominator;

        return Fraction::simplify(fraction.getNumerator(), fraction.getDenominator());
    }

    Fraction& operator ++ (Fraction& fraction, int) {
        Fraction tmp(fraction);

        ++fraction;

        return Fraction::simplify(tmp.getNumerator(), tmp.getDenominator());
    }

    Fraction& operator -- (Fraction& fraction) {
        fraction.numerator -= fraction.denominator;

        return Fraction::simplify(fraction.getNumerator(), fraction.getDenominator());
    }

    Fraction& operator -- (Fraction& fraction, int) {
        Fraction tmp(fraction);

        --fraction;

        return Fraction::simplify(tmp.getNumerator(), tmp.getDenominator());
    }

    bool operator < (const Fraction& fraction1, const Fraction& fraction2) {
        Fraction extended1((fraction1.getNumerator() * fraction2.getDenominator()), (fraction1.getDenominator() * fraction2.getDenominator()));
        Fraction extended2((fraction2.getNumerator() * fraction1.getDenominator()), (fraction2.getDenominator() * fraction1.getDenominator()));
        
        return (extended1.getNumerator() < extended2.getNumerator());
    }

    bool operator < (const Fraction& fraction1, const float& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction2);
        
        return (fraction1 < converted);
    }

    bool operator < (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);
        
        return (converted < fraction2);
    }

    bool operator > (const Fraction& fraction1, const Fraction& fraction2) {
        return (fraction2 < fraction1);
    }

    bool operator > (const Fraction& fraction1, const float& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction2);

        return (fraction1 > converted);
    }

    bool operator > (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);

        return (converted > fraction2);
    }

    bool operator <= (const Fraction& fraction1, const Fraction& fraction2) {
        Fraction extended1((fraction1.getNumerator() * fraction2.getDenominator()), (fraction1.getDenominator() * fraction2.getDenominator()));
        Fraction extended2((fraction2.getNumerator() * fraction1.getDenominator()), (fraction2.getDenominator() * fraction1.getDenominator()));

        return (extended1.getNumerator() <= extended2.getNumerator());
    }

    bool operator >= (const Fraction& fraction1, const Fraction& fraction2) {
        Fraction extended1((fraction1.getNumerator() * fraction2.getDenominator()), (fraction1.getDenominator() * fraction2.getDenominator()));
        Fraction extended2((fraction2.getNumerator() * fraction1.getDenominator()), (fraction2.getDenominator() * fraction1.getDenominator()));

        return (extended1.getNumerator() >= extended2.getNumerator());
    }

    bool operator == (const Fraction& fraction1, const Fraction& fraction2) {
        if (fraction1.getNumerator() == 0 && fraction2.getNumerator() == 0) {
            return true;
        }

        Fraction extended1((fraction1.getNumerator() * fraction2.getDenominator()), (fraction1.getDenominator() * fraction2.getDenominator()));
        Fraction extended2((fraction2.getNumerator() * fraction1.getDenominator()), (fraction2.getDenominator() * fraction1.getDenominator()));

        return (extended1.getNumerator() == extended2.getNumerator());
    }

    bool operator == (const Fraction& fraction1, const float& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction2);

        return (fraction1 == converted);
    }
    
    bool operator == (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);

        return (converted == fraction2);
    }

    ostream& operator << (ostream& output, const Fraction& fraction) {
        if (fraction.getDenominator() == 0) {
            throw runtime_error("Denominator cannot be zero.");
        } else {
            Fraction::simplify(fraction.getNumerator(), fraction.getDenominator());
        }

        output << fraction.getNumerator() << "/" << fraction.getDenominator();

        return output;
    }

    istream& operator >> (istream& input, Fraction& fraction) {
        if (fraction.denominator == 0) {
            throw runtime_error("Denominator cannot be zero.");
        }

        input >> fraction.numerator >> fraction.denominator;
        
        if (input.fail()) {
            throw runtime_error("Re-check the values you entered.");
        }

        Fraction::simplify(fraction.numerator, fraction.denominator);

        return input;
    }

    // Printing & Calculations.
    string Fraction::details() {
        return to_string(this->numerator) + "/" + to_string(this->denominator);
    }

    Fraction& Fraction::simplify(int numerator, int denominator) {
        int gcd = __gcd(numerator, denominator);
        Fraction *simplified = new Fraction(numerator / gcd, denominator / gcd);

        return *simplified;
    }

    Fraction& Fraction::floatToFraction(float toConvert) {
        int numerator, denominator;

        numerator = static_cast<int> (toConvert * 1000);
        denominator = 1000;
        
        return simplify(numerator, denominator);
    }
}