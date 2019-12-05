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
            return power < 6 ? output + ALPHABET.at(power + 1) : output + output + output + output;
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
        input = (input / 10);
        nbIter--;
    } while (nbIter >= 0);
    return output;
}

int main() {
    while (true) {
        int test;
        cin >> test;
        cout << decimalToRoman(test);

    }
    return 0;
}
