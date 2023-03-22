#include <iostream>
#include <string>
#include <map>
#include <regex>

using namespace std;

bool isValidRomanNumeral(string s) {
    regex pattern("^(M{0,4})?(CM|CD|D?C{0,3})?(XC|XL|L?X{0,3})?(IX|IV|V?I{0,3})?$");
    return regex_match(s, pattern);
}

int romanToDecimal(string s) {
    if (!isValidRomanNumeral(s)) {
        throw invalid_argument("Invalid Roman numeral");
    }

    map<char, int> romanToDecimal = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}};
    int result = 0;
    for (int i = 0; i < s.length(); i++) {
        int value = romanToDecimal[s[i]];
        if (i + 1 < s.length() && romanToDecimal[s[i+1]] > value) {
            result -= value;
        } else {
            result += value;
        }
    }

    if (result < 1 || result > 100) {
        throw out_of_range("Number out of range");
    }

    return result;
}

string decimalToRoman(int n) {
    if (n < 1 || n > 100) {
        throw out_of_range("Number out of range");
    }

    map<int, string> decimalToRoman = {{1, "I"}, {4, "IV"}, {5, "V"}, {9, "IX"}, {10, "X"},
    {40, "XL"}, {50, "L"}, {90, "XC"}, {100, "C"}};

    string result = "";
    auto it = decimalToRoman.rbegin();
    while (n > 0 && it != decimalToRoman.rend()) {
        if (n >= it->first) {
            result += it->second;
            n -= it->first;
        } else {
            it++;
        }
    }

    return result;
}

int main() {
    string input1, input2, op;

    cout << "Enter first Roman numeral (1-100): ";
    cin >> input1;
    int num1 = romanToDecimal(input1);

    cout << "Enter second Roman numeral (1-100): ";
    cin >> input2;
    int num2 = romanToDecimal(input2);

    cout << "Enter operator (+, -, *, /): ";
    cin >> op;

    int result;
    if (op == "+") {
        result = num1 + num2;
    } else if (op == "-") {
        result = num1 - num2;
    } else if (op == "*") {
        result = num1 * num2;
    } else if (op == "/") {
        result = num1 / num2;
    } else {
        cout << "Invalid operator\n";
        return 1;
    }

    string output = decimalToRoman(result);
    cout << "Result: " << output << "\n";

    return 0;
}
