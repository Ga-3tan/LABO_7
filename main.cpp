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

using namespace std;

//test
const string ALPHABET = "IVXLCDM";

string getRomanString(int input, int power){
    string output;
    switch(power){
        case 0:

        case 1: ;
    }
    return output;
}

string decimalToRoman(int input){
    string output;
    int power = 0;
    do{
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

int romanToDecimal(string input){
    string test = "MMMMI";
    int output = 0;
    for (int i = test.length()-1; i >= 0; i--) {
        int temp = getIntFromRoman(test[i]);
        int temp2 = getIntFromRoman(test[i-1]);
        if (temp2 < temp && i != 0) {
            output += temp - temp2;
            i--;
        } else {
            output += temp;
        }
    }
    return output;
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
int validInput(int lowerBound, int upperBound, const string &question, const string &error) {
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

int main() {
    cout << romanToDecimal("a");
    return 0;
}
