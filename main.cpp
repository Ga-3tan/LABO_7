/* ---------------------------
Laboratoire : <nn>
Fichier : main.cpp
Auteur(s) : leonard
Date : 12/5/19

But :

Remarque(s) :

Compilateur : g++ 7.4.0

--------------------------- */
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//test
const string ALPHABET = "IVXLCDM";


/**
 * Verify if an input is inside an interval (Bounds included)
 * @param input the integer to check
 * @param lowerBound the lower integer of the interval (included)
 * @param upperBound the upper integer of the interval (included)
 * @return a boolean, true if the input is inside [lowerBound, upperBound], false otherwise
 */
bool isBetweenBounds(int input, int lowerBound, int upperBound);

/**
 * Get the roman representation of a number
 * @param integer the integer to represent must be between 0 and 10 (n %10)
 * @param power the exponent of the integer (0 for digit, 1 for decade, 2 for hundred, 3 for thousand)
 * @example 6= VI, 40 = XL, 700 = DCC
 * @return a string containing the roman representation of the number
 */
string getRomanString(int integer, int power);

/**
 * Convert an integer into its roman representation
 * @param input an integer between 1 and 4999
 * @return a string with the roman representation of the integer
 */
string decimalToRoman(int input);

int getIntFromRoman(char romanNumber);

int romanToDecimal(const string &input);

/**
 * Check if two adjacent Roman number are in the correct order
 * @param currentNumber the first character to compare
 * @param previousNumber the second character to compare
 * @return true if the order is valid, false otherwise
 */
bool checkRomanOrder(char currentNumber, char previousNumber);

bool validateRomanString(const string &input);

string getInput();


int main() {
    string value;
    bool stop = false;
    // stop if empty string
    while (!stop) {
        value = getInput();
        stop = value.empty();
        cout << value << endl;
    }
    return 0;
}


bool isBetweenBounds(int input, int lowerBound, int upperBound) {
    return input >= lowerBound && input <= upperBound;
}

string getRomanString(int integer, int power) {
    const int THOUSAND_POWER = 6;
    const int NEXT_POWER_OF_TEN = 2;
    string output, symbol, nextPower;

    power *= NEXT_POWER_OF_TEN; // transform power to get only symbol factor of ten (I,X,C,M)
    symbol = ALPHABET.at(power);
    nextPower = power < THOUSAND_POWER ? string() + ALPHABET.at(power + 1) : string();

    switch (integer) {
        case 3:
            output += symbol;
        case 2:
            output += symbol;
        case 1:
            output += symbol;
            return output;
        case 4: // IV (4) XL (45) CD (400) but MMMM (4000)
            return power < THOUSAND_POWER ? symbol + nextPower : symbol + symbol + symbol + symbol;
        case 8:
            output += symbol;
        case 7:
            output += symbol;
        case 6:
            output += symbol;
        case 5:
            output = nextPower + output;
            return output;
        case 9:
            nextPower = ALPHABET.at(power + NEXT_POWER_OF_TEN);
            return symbol + nextPower;
        default:
            return string();
    }
}

string decimalToRoman(int input) {
    string output;
    int power = 0;
    do {
        output = getRomanString(input % 10, power) + output;
        power++;
    } while (input /= 10);
    return output;
}

int getIntFromRoman(char romanNumber) {
    switch (romanNumber) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
    }
}

bool checkRomanOrder(char currentNumber, char previousNumber) {
    switch (currentNumber) {
        case 'M':
        case 'D':
            if (previousNumber == 'X' || previousNumber == 'D') {
                return false;
            }
        case 'L':
        case 'C':
            if (previousNumber == 'I' || previousNumber == 'L') {
                return false;
            }
        case 'V':
        case 'X':
            if (previousNumber == 'V') {
                return false;
            }
        default:
            return true;
    }
}


bool validateRomanString(const string &input) {
    unsigned occurrence = 0;
    char prevChar = '-';

    for (char s  : input) {
        bool isValid = false;
        // Verify if invalid character are in the string
        for (char t : ALPHABET) {
            if (t == s) {
                isValid = true;
                break;
            }
        }
        if (!isValid) {
            return false;
        }
        // Compute number of occurrence
        if (prevChar != s) {
            occurrence = 0;
        } else {
            ++occurrence;
        }

        //Verify number of occurrence
        if (occurrence > 2) {
            if (s != ALPHABET.back() || occurrence > 3) {
                return false;
            }
        }
        // Check if order of letter is correct
        if (prevChar != '-' && !checkRomanOrder(s, prevChar)) {
            return false;
        }
        prevChar = s;
    }
    // check
    if (input.length() > 1) {
        for (size_t i = 0; i < input.length() - 2; ++i) {
            int a = getIntFromRoman(input[i + 2]);
            int b = getIntFromRoman(input[i]);
            if (a > b) {
                return false;
            }
        }
    }

    return true;
}

int romanToDecimal(const string &input) {
    int output = 0;
    int sous = 0;
    if (input.length() > 1) {
        for (size_t i = 0; i < input.length() - 1; ++i) {
            int firstChar = getIntFromRoman(input[i]);
            int secondChar = getIntFromRoman(input[i + 1]);
            if (firstChar < secondChar) {
                sous = firstChar;
                output += -firstChar;
            } else {
                if (secondChar == sous) {
                    return -1;
                }
                output += firstChar;
            }
        }
        if (input[input.length() - 1] == sous) {
            return -1;
        }
        output += getIntFromRoman(input[input.length() - 1]);
        return output;
    } else {
        return getIntFromRoman(input[0]);
    }
}

string getInput() {
    bool valid;
    int number;
    bool romanToNumber = false;
    string input;
    do {
        getline(cin, input);
        if (input.empty()) {
            return string();
        }
        stringstream ss(input);
        if (ss >> number) {
            char nextChar = ss.peek();
            valid = isBetweenBounds(number, 1, 4999);
            romanToNumber = false;
        } else {
            valid = validateRomanString(input);
            romanToNumber = true;
        }
        if (!valid) {
            cout << "Non valide" << endl;
        }

    } while (!valid);
    string error = "Non valide";
    string output;
    if (romanToNumber) {
        int value = romanToDecimal(input);
        output = (value == -1 ? error : to_string(value));
    } else {
        output = decimalToRoman(number);
    }
    return output;
}