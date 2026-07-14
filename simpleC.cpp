/*
 * simpleC — Simple Calculator
 * A lightweight terminal calculator with support for arithmetic expressions,
 * percentages, parentheses, and unary minus.
 * 
 * Licensed under GNU GPL v3.0 or later.
 * 
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Token structure for lexical analysis
// Each token represents a number, operator, or parenthesis
struct Token {
    string type;   // "number", "op", "lparen", "rparen"
    float value;   // numeric value (for "number" tokens)
    char op;       // operator character (for "op" tokens)
};

// Global variables for the recursive descent parser
vector<Token> tokens;  // list of tokens after tokenization
size_t pos = 0;           // current position in the token list
bool parseError = false; // error flag for invalid expressions

// Forward declaration: allows functions to call each other recursively
float parseExpression();

/*
 * parseFactor — Parses the smallest unit of an expression:
 *   - A number
 *   - A parenthesized expression ( ... )
 *   - A unary minus followed by a factor
 * 
 * This is the base of the recursion.
 */
float parseFactor() {
    // Check for unexpected end of input
    if (pos >= tokens.size()) {
        parseError = true;
        cout << "Error: unexpected end of expression" << endl;
        return 0;
    }

    Token current = tokens[pos];

    // Case 1: it's a number — return its value and advance
    if (current.type == "number") {
        pos++;
        return current.value;
    }

    // Case 2: unary minus — negate the following factor
    if (current.type == "op" && current.op == '-') {
        pos++;  // skip the minus sign
        return -parseFactor();
    }

    // Case 3: opening parenthesis — parse inner expression
    if (current.type == "lparen") {
        pos++;  // skip '('
        float result = parseExpression();
        // Expect a matching closing parenthesis
        if (pos < tokens.size() && tokens[pos].type == "rparen") {
            pos++;  // skip ')'
            return result;
        }
        parseError = true;
        cout << "Error: expected ')'" << endl;
        return 0;
    }

    // If none of the above matched, the input is invalid
    parseError = true;
    cout << "Error: expected a number or '('" << endl;
    return 0;
}

/*
 * parseTerm — Parses multiplication and division operations.
 * Multiplication and division have higher precedence than addition/subtraction.
 * 
 * Grammar: term → factor (('*' | '/') factor)*
 */
float parseTerm() {
    float left = parseFactor();
    if (parseError) return left;  // stop if an error occurred

    // Process all consecutive '*' and '/' operators
    while (pos < tokens.size() && tokens[pos].type == "op" &&
           (tokens[pos].op == '*' || tokens[pos].op == '/')) {
        char op = tokens[pos].op;
        pos++;  // skip the operator
        float right = parseFactor();
        if (parseError) return left;

        if (op == '*') {
            left = left * right;
        }
        else {  // division
            if (right == 0) {
                parseError = true;
                cout << "Error: division by zero" << endl;
                return left;
            }
            left = left / right;
        }
    }

    return left;
}

/*
 * parseExpression — Parses addition, subtraction, and percentage operations.
 * This is the top-level function that calls parseTerm for operands.
 * 
 * Grammar: expression → term (('+' | '-') term)*
 * 
 * Percentage: if a '%' token follows the second operand of '+' or '-',
 * it is interpreted as "percent of the current result".
 * Example: 100 + 10%  →  100 + (100 * 10/100) = 110
 */
float parseExpression() {
    float left = parseTerm();
    if (parseError) return left;

    // Process all consecutive '+' and '-' operators
    while (pos < tokens.size() && tokens[pos].type == "op" &&
           (tokens[pos].op == '+' || tokens[pos].op == '-')) {
        char op = tokens[pos].op;
        pos++;  // skip the operator
        float right = parseTerm();
        if (parseError) return left;

        // Handle percentage after the second operand
        // Example: "50 + 20%" — right=20, left=50, result = 50 + 50*0.2
        if (pos < tokens.size() && tokens[pos].type == "op" && tokens[pos].op == '%') {
            right = left * (right / 100.0);
            pos++;  // skip '%'
        }

        if (op == '+') {
            left = left + right;
        }
        else {
            left = left - right;
        }
    }

    return left;
}

/*
 * main — Entry point. Runs the REPL loop:
 *   - Reads user input
 *   - Tokenizes the input string
 *   - Parses and evaluates the expression
 *   - Prints the result or an error message
 *   - Exits on "exit" or "quit"
 */
int main() {
    string input;

    while (true) {
        cout << ">> ";
        getline(cin, input);

        // Check for exit commands
        if (input == "exit" || input == "quit") {
            cout << "Goodbye!" << endl;
            break;
        }

        // Skip empty input
        if (input.empty()) {
            continue;
        }

        // --- Tokenization: split the input string into tokens ---
        tokens.clear();
        string currentNumber;

        for (size_t i = 0; i < input.length(); i++) {
            char ch = input[i];

            // Ignore whitespace
            if (ch == ' ') {
                continue;
            }

            // Build a number from consecutive digits and dots
            if ((ch >= '0' && ch <= '9') || ch == '.') {
                currentNumber += ch;
            }
            else {
                // If we were building a number, save it as a token
                if (currentNumber != "") {
                    Token t;
                    t.type = "number";
                    t.value = stof(currentNumber);
                    tokens.push_back(t);
                    currentNumber = "";
                }

                // Classify the symbol
                if (ch == '(') {
                    Token t;
                    t.type = "lparen";
                    tokens.push_back(t);
                }
                else if (ch == ')') {
                    Token t;
                    t.type = "rparen";
                    tokens.push_back(t);
                }
                else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
                    Token t;
                    t.type = "op";
                    t.op = ch;
                    tokens.push_back(t);
                }
                // Unknown characters are silently ignored
            }
        }

        // Add the last number if there is one
        if (currentNumber != "") {
            Token t;
            t.type = "number";
            t.value = stof(currentNumber);
            tokens.push_back(t);
        }

        // --- Parsing: evaluate the token list ---
        pos = 0;
        parseError = false;
        float result = parseExpression();

        // Print result only if parsing succeeded
        if (!parseError) {
            cout << result << endl;
        }
    }

    return 0;
}
