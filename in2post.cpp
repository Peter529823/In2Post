#include <iostream>
#include <string>
#include <sstream>
#include <stack> // Ensure this header is included
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <stdexcept>

/**
 * Checks if a given string represents a valid number (integer or floating-point).
 * The input string to check.
 * True if the string is a valid number, false otherwise.
 */
// Helper function to check if a string is a number (int or float)
bool isNumber(const std::string &s) {
    try {
        std::stod(s);  // try to convert string to double
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

/**
 * Determines the precedence of an operator.
 * The operator as a string.
 * An integer representing the precedence level (higher value = higher precedence).
 */
// Helper function to determine operator precedence
int precedence(const std::string &op) {
    if (op == "+" || op == "-") return 1; // Lowest precedence
    if (op == "*" || op == "/") return 2; // Higher precedence
    return -1; // Invalid operator
}

/**
 * Performs arithmetic operations based on the given operator.
 * The first operand.
 * The second operand.
 * The operator as a string.
 * The result of the operation.
 * std::invalid_argument If the operator is invalid or division by zero occurs.
 */
// Helper function to perform arithmetic operations
double applyOperator(double op1, double op2, const std::string &op) {
    if (op == "+") return op1 + op2;
    if (op == "-") return op1 - op2;
    if (op == "*") return op1 * op2;
    if (op == "/") {
        if (op2 == 0) {
            throw std::invalid_argument("Error: Division by zero");
        }
        return op1 / op2;
    }
    throw std::invalid_argument("Error: Invalid operator '" + op + "'");
}

/**
 * Evaluates a postfix expression and computes its result.
 * The postfix expression as a string.
 * The result of the evaluation as a double.
 * std::invalid_argument If the expression is invalid.
 */
// Function to evaluate the postfix expression
double evaluatePostfix(const std::string &postfix) {
    std::stack<double> operand_stack;  // operand stack for evaluation
    std::istringstream iss(postfix);
    std::string token;

    while (iss >> token) {
        if (isNumber(token)) {
            operand_stack.push(std::stod(token));  // push operand to stack
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (operand_stack.size() < 2) {
                throw std::invalid_argument("Error: Not enough operands for operation '" + token + "'");
            }
            double op2 = operand_stack.top(); operand_stack.pop();
            double op1 = operand_stack.top(); operand_stack.pop();
            double result = applyOperator(op1, op2, token);
            operand_stack.push(result);  // push the result back onto the stack
        } else {
            throw std::invalid_argument("Error: Invalid token in postfix expression: '" + token + "'");
        }
    }

    if (operand_stack.size() != 1) {
        throw std::invalid_argument("Error: The postfix expression is invalid.");
    }

    return operand_stack.top();  // final result
}

/**
 * Converts an infix expression to a postfix expression.
 * The infix expression as a string.
 * The equivalent postfix expression as a string.
 * std::invalid_argument If the infix expression is invalid.
 */
// Function to convert infix to postfix
std::string infixToPostfix(const std::string &infix) {
    std::stack<std::string> op_stack;  // operator stack
    std::string postfix;
    std::istringstream iss(infix);
    std::string token;
    std::string lastToken = "";

    while (iss >> token) {
        // If the token is an operand (number or variable), add it to the output
        if (isNumber(token) || (token.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)) {
            postfix += token + " ";
            lastToken = token;
        }
        // If the token is an operator
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (lastToken == "+" || lastToken == "-" || lastToken == "*" || lastToken == "/" || lastToken == "(") {
                throw std::invalid_argument("Error: Invalid expression. Operator can't follow another operator or left parenthesis.");
            }
            // Pop operators from the stack with higher precedence and add to postfix
            while (!op_stack.empty() && precedence(op_stack.top()) >= precedence(token)) {
                postfix += op_stack.top() + " ";
                op_stack.pop();
            }
            // Push the current operator onto the stack
            op_stack.push(token);
            lastToken = token;
        }
        // If the token is a right parenthesis ")"
        else if (token == ")") {
            if (lastToken == "+" || lastToken == "-" || lastToken == "*" || lastToken == "/" || lastToken == "(") {
                throw std::invalid_argument("Error: Invalid expression. Operator can't follow a parenthesis.");
            }
            // Pop operators until a "(" is found
            while (!op_stack.empty() && op_stack.top() != "(") {
                postfix += op_stack.top() + " ";
                op_stack.pop();
            }
            if (op_stack.empty()) {
                throw std::invalid_argument("Error: Mismatched parentheses - missing '('");
            }
            op_stack.pop(); // pop the left parenthesis
            lastToken = token;
        }
        // If the token is a left parenthesis "("
        else if (token == "(") {
            op_stack.push(token);  // push it onto the stack
            lastToken = token;
        } else {
            throw std::invalid_argument("Error: Invalid token in expression: " + token);
        }
    }

    // After the entire input has been read, pop all remaining operators from the stack
    while (!op_stack.empty()) {
        if (op_stack.top() == "(") {
            throw std::invalid_argument("Error: Mismatched parentheses - missing ')'");
        }
        postfix += op_stack.top() + " ";
        op_stack.pop();
    }

    return postfix;
}

/**
 * The main function of the program. It allows the user to input infix expressions,
 * converts them to postfix, evaluates the result, and displays the output.
 * The program continues until the user enters "exit".
 */
int main() {
    std::string infix;

    while (true) {
        try {
            std::cout << "Enter an infix expression (or 'exit' to quit): ";
            std::getline(std::cin, infix);

            if (infix.empty()) {
                std::cerr << "Error: Empty input. Please enter a valid expression." << std::endl;
                continue;
            }

            if (infix == "exit") {
                break;
            }

            // Convert infix to postfix and evaluate the result
            std::string postfix = infixToPostfix(infix);

            if (!postfix.empty()) {
                double result = evaluatePostfix(postfix);
                std::cout << "Postfix: " << postfix << std::endl;
                std::cout << "Result: " << result << std::endl;
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
