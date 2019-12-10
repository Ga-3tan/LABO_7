/* ---------------------------
Laboratoire : 07
Fichier : main.cpp
Auteur(s) : Besseau Austburger Zwick
Date : 05/12/19

But : Ecrire un programme convertissant les nombres écrits avec le système de numérotation
indo-arabe en nombres romains et vice-versa. Il lit les entrées ligne par ligne et détecte
dans quel sens doit s'effectuer la conversion. Si l'entrée est non valide, il écrit "Non valide".
Il s'arrête quand il reçoit une ligne vide. Il doit être capable de traiter au moins des nombres
entre I et MMMMCMXCIX, donc entre 1 et 4999.

Bien que l'usage romain varie, nous ne considérons ici comme valide que les nombres romains écrits
sans symbole se répétant plus de 3 fois, à l'exception du M. Ainsi 4 s'écrit IV et pas IIII,
99 s'écrit XCIX et pas LXXXXVIIII.
Les nombres romains ne respectant pas cette règle doivent être considérés non valides

Remarque(s) :

Compilateur : g++ 7.4.0

--------------------------- */
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

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
 * Get the roman symbol of a number
 * @param integer the integer to represent must be between 0 and 10 (n %10)
 * @param power the exponent of the integer (0 for digit, 1 for decade, 2 for hundred, 3 for thousand)
 * @example 6= VI, 40 = XL, 700 = DCC
 * @return a string containing the roman representation of the number
 */
string getRomanSymbol(int integer, int power);

/**
 * Convert an integer into its roman representation
 * @param input an integer between 1 and 4999
 * @return a string with the roman representation of the integer
 */
string decimalToRoman(int input);

/**
 * Get the numerical value of a roman character
 * @param romanNumber a char representing a roman character (I, V, X, L, C, D, M)
 * @return an integer with the corresponding value (I = 1, V = 5, X =10, L = 50, c = 100, D = 500, M = 1000).
 * 0 if character is not a roman character
 */
int getIntFromRoman(char romanNumber);

/**
 * Computes the integer value of a roman representation
 * @param input a string containing the roman representation
 * @attention returns -1 if the number is not valid, By example IVI returns -1
 * @return an integer containing the value. -1 if error
 */
int romanToDecimal(const string &input);

/**
 * Check if two adjacent Roman number are in the correct order
 * @param currentNumber the first character to compare
 * @param previousNumber the second character to compare
 * @return true if the order is valid, false otherwise
 */
bool checkRomanOrder(char currentNumber, char previousNumber);

/**
 * Verify if a string correspond to a roman numeral representation
 * @param input a string
 * @details Verify if input is constituted only from valid characters, if characters do not repeat too many times
 * if characters are in decreasing order (no I before M etc).
 * @attention No check to verify if addition subtraction rules is respected.
 * By example IVI is considered as valid by this function. For verification of this case see @function romanToDecimal
 * @return true if input is valid
 */
bool validateRomanString(const string &input);

/**
 * Get and validates an input (between 1(I) and 4999 (MMMMCMXCIX)) from the user and transform it
 * from decimal numeral to Roman numeral or vice-versa.
 * @param lowerBound the lower integer of the interval (included)
 * @param upperBound the upper integer of the interval (included)
 * @param error The error message to display to the user when an incorrect input is entered
 * @attention if the user enters an empty string, the empty string is returned
 * @return a string containing the transformed input
 */
string getInput(int lowerBound, int upperBound, const string &error);


int main() {
    const string ERROR = "Non valide";
    const int LOWER_BOUND = 1;
    const int UPPER_BOUND = 4999;
    string value;
    bool stop = false;
    // stop if empty string
    while (!stop) {
        value = getInput(LOWER_BOUND, UPPER_BOUND, ERROR);
        stop = value.empty();
        cout << value << endl;
    }
    return 0;
}


bool isBetweenBounds(int input, int lowerBound, int upperBound) {
    return input >= lowerBound && input <= upperBound;
}

string getRomanSymbol(int integer, int power) {
    const int THOUSAND_POWER = 6;
    const int NEXT_POWER_OF_TEN = 2;
    string output, symbol, nextPower;

    power *= NEXT_POWER_OF_TEN; // transform power to get only symbol factor of ten (I,X,C,M)
    symbol = ALPHABET.at(power);
    // avoid out of bounds if power is 6 (input = n*1000)
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
    // Roman representation digit by digit
    do {
        output = getRomanSymbol(input % 10, power) + output;
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
        default:
            return 0;
    }
}

bool checkRomanOrder(char currentNumber, char previousNumber) {
    // Check if rule of precedence is respected (bigger numbers first except for subtraction)
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
    const unsigned OCCURENCE_MAX = 2;
    const unsigned OCCURENCE_MAX_M = 3;

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
        if (occurrence > OCCURENCE_MAX) {
            if (s != ALPHABET.back() || occurrence > OCCURENCE_MAX_M) {
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
    int previous_subtraction = 0;
    if (input.length() > 1) {
        for (size_t i = 0; i < input.length() - 1; ++i) {
            int firstChar = getIntFromRoman(input[i]);
            int secondChar = getIntFromRoman(input[i + 1]);
            if (firstChar < secondChar) {
                previous_subtraction = firstChar;
                output += -firstChar;
            } else {
                // if addition is the opposite of the precedent subtraction, the number is invalid
                if (secondChar == previous_subtraction) {
                    return -1;
                }
                output += firstChar;
            }
        }
        // Check addition subtraction for last element
        if (input[input.length() - 1] == previous_subtraction) {
            // -1 is to signal error
            return -1;
        }
        // add last element to total
        output += getIntFromRoman(input[input.length() - 1]);
        return output;
    } else {
        return getIntFromRoman(input[0]);
    }
}

string getInput(int lowerBound, int upperBound, const string &error) {
    bool valid, romanToNumber;
    int number;
    string input, output;

    do {
        getline(cin, input);
        if (input.empty()) { // return empty string to signal end
            return string();
        }
        stringstream ss(input);
        if (ss >> number) { // test if number
            valid = isBetweenBounds(number, lowerBound, upperBound);
            romanToNumber = false;
        } else {
            valid = validateRomanString(input);
            romanToNumber = true;
        }
        if (!valid) {
            cout << error << endl;
        }

    } while (!valid);

    if (romanToNumber) {
        int value = romanToDecimal(input);
        output = (value == -1 ? error : to_string(value));
    } else {
        output = decimalToRoman(number);
    }

    return output;
}