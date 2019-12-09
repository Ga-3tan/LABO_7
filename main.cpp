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
#include <cmath>
#include <limits>
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
bool isBetweenBounds(int input, int lowerBound, int upperBound) {
    return input >= lowerBound && input <= upperBound;
}

string getRomanString(int input, int power) {
    string output;
    output = ALPHABET.at(power);
    string nextPower;
    nextPower = power < 6 ? string() + ALPHABET.at(power + 1) : string();
    switch (input) {
        case 1:
            return output;
        case 2:
            return output + output;
        case 3:
            return output + output + output;
        case 4:
            return power < 6 ? output + nextPower : output + output + output + output;
        case 5:
            return nextPower;
        case 6:
            return nextPower + output;
        case 7:
            return nextPower + output + output;
        case 8:
            return nextPower + output + output + output;
        case 9:
            nextPower = ALPHABET.at(power + 2);
            return output + nextPower;
        default:
            return string();
    }
}

string decimalToRoman(int input) {
    string output;
    int power = 0;
    int nbIter = log10(input);
    do {
        output = getRomanString(input % 10, power * 2) + output;
        power++;
    }while(input/=10);
    return output;
}

int getIntFromRoman(char romanNumber){
    switch (romanNumber) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
    }
    return 0;
}

string romanToDecimal(string input) {
    int output = 0;
    for (int i = input.length() - 1; i >= 0; i--) {
        int temp = getIntFromRoman(input[i]);
        int temp2 = getIntFromRoman(input[i - 1]);
        if (temp2 < temp && i != 0) {
            output += temp - temp2;
            i--;
        } else {
            output += temp;
        }
    }
    return to_string(output);
}

/**
 * Ask a valid input in an interval to the user
 * @details ask an input in the interval from the user and validates it.
 * If the input is invalid, loop until the input is valid.
 * @param lowerBound the lower integer of the interval (included)
 * @param upperBound the upper integer of the interval (included)
 * @param question a string containing the question to ask the user
 * @param error a string to indicate the user that an error has occurred
 * @return the validated integer entered by the user
 */
int validInteger(int lowerBound, int upperBound, const string &question, const string &error) {
    bool valid;
    int input;
    do {
        cin >> input;
        //check if next stream entry is empty
        char nextChar = cin.peek();
        valid = !cin.fail() && isBetweenBounds(input, lowerBound, upperBound) &&
                (nextChar == '\n' || nextChar == ' ' || nextChar == '\t');

        if (!valid) {
            cout << error << endl;
        }
        //clear buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (!valid);
    return input;
}

bool checkRomanOrder(char currentNumber, char previousNumber) {
    switch (currentNumber) {
        case 'D':
            if (previousNumber == 'X') {
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
    // check if string composed of valid caracter
    unsigned occurrence = 0;
    char prevChar = '-';
    for (char s  : input) {
        bool isValid = false;
        for (char t : ALPHABET) {
            if (t == s) {
                isValid = true;
                break;
            }
        }
        if (!isValid) {
            return false;
        }
        if (prevChar != s) {
            occurrence = 0;
        } else {
            ++occurrence;
        }


        if (occurrence > 2 && s != ALPHABET.back()) {
            return false;
        }
        bool temp = checkRomanOrder(s, prevChar);
        if (prevChar != '-' && !temp) {
            return false;
        }
        prevChar = s;
    }
    return true;
}

/**
 *
 *
1
I
4
IV
8
VIII
19
XIX
65
LXV
421
CDXXI
1973
MCMLXXIII
MCMXLIV
1944
MMXV
2015
DCLXVI
666
CMXCIX
999
MCMIIII
Non valide
 */

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
    string output = (romanToNumber ? romanToDecimal(input) : decimalToRoman(number));
    return output;
}

int main() {
    string value;
    bool stop = false;
    while (!stop) {
        value = getInput();
        stop = value.empty();
        cout << value << endl;
    }
    return 0;
}
