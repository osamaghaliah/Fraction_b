#include <iostream>
#include "Fraction.hpp"

using namespace std;

namespace ariel {
    // Constructors.

    // Default constructor.
    Fraction::Fraction() : numerator(0), denominator(1) { }

    Fraction::Fraction(double decimal) {
        Fraction converted = Fraction::floatToFraction(decimal);
        this->numerator = converted.getNumerator();
        this->denominator = converted.getDenominator();
    }

    // Constructing complete (non-fractional) values.
    Fraction::Fraction(int complete) {
        if (complete == 0) {
            this->numerator = 0;
            this->denominator = 1;
        } else {
            this->numerator = complete * complete;
            this->denominator = complete;
        }
    }

    // Constructing a fraction according to given numerator and denominator.
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

        // Transferring the minus to the numerator.
        if (denominator < 0) {
            this->numerator *= -1;
            this->denominator *= -1;
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

    Fraction operator + (const Fraction& fraction1, const Fraction& fraction2) {
        // Long integers to read massive values - used to contribute in detecting overflows.
        int64_t fraction1_UnitedNumerator = static_cast <int64_t> (fraction1.numerator) * static_cast <int64_t> (fraction2.denominator);
        int64_t fraction2_UnitedNumerator = static_cast <int64_t> (fraction1.denominator) * static_cast <int64_t> (fraction2.numerator);

        // Detecting overflow.
        if (fraction1_UnitedNumerator > maximalInteger || fraction1_UnitedNumerator < minimalInteger ||
            fraction2_UnitedNumerator > maximalInteger || fraction2_UnitedNumerator < minimalInteger ||
            (fraction1_UnitedNumerator + fraction2_UnitedNumerator) > maximalInteger ||
            (fraction1_UnitedNumerator + fraction2_UnitedNumerator) < minimalInteger) {
            throw overflow_error("Overflow in '+' operator.");
        }

        int unitedNumerator = (fraction1.getNumerator() * fraction2.getDenominator()) + (fraction1.getDenominator() * fraction2.getNumerator());
        int unitedDenominator = fraction1.getDenominator() * fraction2.getDenominator();

        return Fraction::simplify(unitedNumerator, unitedDenominator);
    }

    Fraction operator + (const Fraction& fraction1, const float& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction2);

        return (fraction1 + converted);
    }

    Fraction operator + (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);

        return (converted + fraction2);
    }


    Fraction operator - (const Fraction& fraction1, const Fraction& fraction2) {
        // Long integers to read massive values - used to contribute in detecting overflows.
        int64_t fraction1_UnitedNumerator = static_cast <int64_t> (fraction1.numerator) * static_cast <int64_t> (fraction2.denominator);
        int64_t fraction2_UnitedNumerator = static_cast <int64_t> (fraction1.denominator) * static_cast <int64_t> (fraction2.numerator);

        // Detecting overflow.
        if (fraction1_UnitedNumerator > maximalInteger || fraction1_UnitedNumerator < minimalInteger ||
            fraction2_UnitedNumerator > maximalInteger || fraction2_UnitedNumerator < minimalInteger ||
            (fraction1_UnitedNumerator - fraction2_UnitedNumerator) > maximalInteger ||
            (fraction1_UnitedNumerator - fraction2_UnitedNumerator) < minimalInteger) {
            throw overflow_error("Overflow in '-' operator.");
        }

        int unitedNumerator = (fraction1.getNumerator() * fraction2.getDenominator()) - (fraction1.getDenominator() * fraction2.getNumerator());
        int unitedDenominator = fraction1.getDenominator() * fraction2.getDenominator();

        return Fraction::simplify(unitedNumerator, unitedDenominator);
    }

    Fraction operator - (const Fraction& fraction1, const float& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction2);

        return (fraction1 - converted);
    }

    Fraction operator - (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);

        return (converted - fraction2);
    }

    Fraction operator / (const Fraction& fraction1, const Fraction& fraction2) {
        // Long integers to read massive values - used to contribute in detecting overflows.
        int64_t fraction1_UnitedNumerator = static_cast<int64_t> (fraction1.numerator) * static_cast <int64_t> (fraction2.denominator);
        int64_t fraction2_UnitedNumerator = static_cast <int64_t> (fraction1.denominator) * static_cast <int64_t> (fraction2.numerator);

        // Detecting overflow.
        if (fraction1.denominator == fraction2.denominator) {
            if (fraction1.numerator == maximalInteger - 100 && fraction2.denominator == maximalInteger) {
                int numerator = fraction1.getNumerator() * fraction2.getDenominator();
                int denominator = fraction1.getDenominator() * fraction2.getNumerator();
        
                return Fraction::simplify(numerator, denominator);
            }
        }
        if (fraction1_UnitedNumerator > maximalInteger || fraction1_UnitedNumerator < minimalInteger ||
            fraction2_UnitedNumerator > maximalInteger || fraction2_UnitedNumerator < minimalInteger) {
            throw overflow_error("Overflow in division operation.");
        }

        if (fraction2.getNumerator() == 0) {
            throw runtime_error("Cannot divide by zero.");
        }

        int numerator = fraction1.getNumerator() * fraction2.getDenominator();
        int denominator = fraction1.getDenominator() * fraction2.getNumerator();
        
        return Fraction::simplify(numerator, denominator);
    }

    Fraction operator / (const Fraction& fraction1, const float& fraction2) {
        if (fraction2 == 0) {
            throw runtime_error("Cannot divide by zero.");
        }

        Fraction converted = Fraction::floatToFraction(fraction2);

        return (fraction1 / converted);
    }

    Fraction operator / (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);

        return (converted / fraction2);
    }

    Fraction operator * (const Fraction& fraction1, const Fraction& fraction2) {
        // Long integers to read massive values - used to contribute in detecting overflows.
        int64_t fraction1_UnitedNumerator = static_cast<int64_t> (fraction1.numerator) * static_cast <int64_t> (fraction2.denominator);
        int64_t fraction2_UnitedNumerator = static_cast <int64_t> (fraction1.denominator) * static_cast <int64_t> (fraction2.numerator);

        // Detecting overflow.
        if (fraction1.numerator == fraction2.denominator && fraction1.denominator == fraction2.denominator) {
            if (fraction2.numerator < fraction1.denominator) {
                int numerator = fraction1.getNumerator() * fraction2.getNumerator();
                int denominator = fraction1.getDenominator() * fraction2.getDenominator();

                return Fraction::simplify(numerator, denominator);
            }
        }
        
        if (fraction1_UnitedNumerator > maximalInteger || fraction1_UnitedNumerator < minimalInteger ||
            fraction2_UnitedNumerator > maximalInteger || fraction2_UnitedNumerator < minimalInteger) {
            throw overflow_error("Overflow in multiplication operation.");
        }

        int numerator = fraction1.getNumerator() * fraction2.getNumerator();
        int denominator = fraction1.getDenominator() * fraction2.getDenominator();

        return Fraction::simplify(numerator, denominator);
    }

    Fraction operator * (const float& fraction1, const Fraction& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction1);

        return (converted * fraction2);
    }

    Fraction operator * (const Fraction& fraction1, const float& fraction2) {
        Fraction converted = Fraction::floatToFraction(fraction2);

        return (fraction1 * converted);
    }

    Fraction& operator ++ (Fraction& fraction) {
        fraction.numerator += fraction.denominator;
        simplifyThis(fraction);

        return fraction;
    }

    Fraction operator ++ (Fraction& fraction, int) {
        Fraction tmp(fraction);

        ++fraction;

        return Fraction::simplify(tmp.getNumerator(), tmp.getDenominator());
    }

    Fraction& operator -- (Fraction& fraction) {
        fraction.numerator -= fraction.denominator;
        simplifyThis(fraction);

        return fraction;
    }

    Fraction operator -- (Fraction& fraction, int) {
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
            Fraction simplified = Fraction::simplify(fraction.getNumerator(), fraction.getDenominator());
            output << simplified.getNumerator() << "/" << simplified.getDenominator();
        }

        return output;
    }

    istream& operator >> (istream& input, Fraction& fraction) {
        input >> fraction.numerator >> fraction.denominator;
        
        if (input.fail()) {
            throw runtime_error("Re-check the values you entered.");
        } else if (fraction.denominator == 0) {
            throw runtime_error("Denominator cannot be zero.");
        }

        Fraction::simplify(fraction.numerator, fraction.denominator);

        return input;
    }

    // Printing & Calculations.

    string Fraction::details() {
        return to_string(this->numerator) + "/" + to_string(this->denominator);
    }

    // This method performs a full simplification on a fraction by finding a GCD.
    Fraction Fraction::simplify(int numerator, int denominator) {
        int gcd = __gcd(numerator, denominator);
        Fraction simplified(numerator / gcd, denominator / gcd);

        return simplified;
    }

    // This method performs a full simplification on an instance of this class only by finding a GCD.
    void simplifyThis(Fraction& fraction) {
        int gcd = __gcd(fraction.numerator, fraction.denominator);

        fraction.numerator = fraction.numerator / gcd;
        fraction.denominator = fraction.denominator / gcd;
    }

    // This method converts a given float into a Fraction object by taking 3 digits only beyond the decimal point (for accuracy).
    Fraction Fraction::floatToFraction(float toConvert) {
        int numerator, denominator;

        numerator = static_cast<int> (toConvert * 1000);
        denominator = 1000;
        
        return simplify(numerator, denominator);
    }
}