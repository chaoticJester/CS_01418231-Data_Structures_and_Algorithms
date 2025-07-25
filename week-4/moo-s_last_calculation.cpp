#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cctype>
#include <iomanip>

//เปรียบเทียบลำดับของ operator
int checkPrecedence(char op) {
    if(op == '+' || op == '-') {
        return 1;
    }
    if(op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

//เช็คว่า c เป็น operator หรือไม่
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//เช็คว่า input ที่รับเข้ามามีอัขระประหลาดหรือไม่
bool isCharacterValid(const std::string& input) {
    for(char c : input) {
        if(!isdigit(c) && !isOperator(c) &&
            c != '(' && c != ')' && c != '.' && c != ' ') {
            return false;
        }
    }
    return true;
}

//นับว่าวงเล็บสมดุลหรือไม่
bool isParenthesisBalanced(const std::string& input) {
    int balance = 0;
    for(char c : input) {
        if(c == '(') {
            balance++;
        } else if(c == ')') {
            balance--;
        }
        if(balance < 0) {
            return false;
        }
    }
    return balance == 0;
}

//เช็คว่า expression มี syntax ผิดหรือเปล่า
bool isExpressionInvalid(const std::string& input) {
    bool lastWasOperator = true;
    bool lastWasDot = false;
    int parenthesisDepth = 0;

    for (int i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (c == ' ') {
            continue;
        }
        if (isdigit(c)) {
            lastWasOperator = false;
            lastWasDot = false;
        } else if (c == '.') {
            if (lastWasDot || lastWasOperator) {
                return true;
            } 
            lastWasDot = true;
        } else if (isOperator(c)) {
            if (lastWasOperator && !(c == '-' || c == '+')) {
                return true;
            }
            lastWasOperator = true;
            lastWasDot = false;
        } else if (c == '(') {
            parenthesisDepth++;
            lastWasOperator = true;
        } else if (c == ')') {
            parenthesisDepth--;
            if (parenthesisDepth < 0 || lastWasOperator) {
                return true;
            }
            lastWasDot = false;
        } else {
            return true;
        }
    }

    return lastWasOperator || parenthesisDepth != 0;
}

//แยก operand กับ operator ด้วย Shunting Yard Algorithm
void seperateinput(std::queue<std::string> &postfix, const std::string& input) {
    std::stack<char> operatorStack;
    std::string num = "";
    char prev = 0;

    for (int i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (c == ' ') {
            continue;
        }

        if (isdigit(c) || c == '.') {
            num += c;
        } else {
            if ((c == '-' || c == '+') && 
                (i == 0 || input[i - 1] == '(' || isOperator(input[i - 1]))) {
                num += c;
                continue;
            } else {
                if (!num.empty()) {
                    postfix.push(num);
                    num.clear();
                }

                if (c == '(') {
                    operatorStack.push(c);
                } else if (c == ')') {
                    while (!operatorStack.empty() && operatorStack.top() != '(') {
                        postfix.push(std::string(1, operatorStack.top()));
                        operatorStack.pop();
                    }
                    if (!operatorStack.empty()) operatorStack.pop(); // pop '('
                } else if (isOperator(c)) {
                    while (!operatorStack.empty() &&
                        checkPrecedence(operatorStack.top()) >= checkPrecedence(c)) {
                        postfix.push(std::string(1, operatorStack.top()));
                        operatorStack.pop();
                    }
                    operatorStack.push(c);
                }
            }
        }
        prev = c;
    }

    if (!num.empty()) {
        postfix.push(num);
    }

    while (!operatorStack.empty()) {
        postfix.push(std::string(1, operatorStack.top()));
        operatorStack.pop();
    }
}

bool isTokenValid(std::string token) {
    bool foundDot = false;
    for(int i = 0; i < token.length(); i++) {
        if(token[i] == '.') {
            if(foundDot) {
                return false;
            } else {
                foundDot = true;
            }
        } else if(isOperator(token[i]) && i < token.length() - 1 && token[i] == token[i+1]) {
            return false;
        }
    }
    return true;
}


//คำนวนผลลัพธ์
bool calculateAnswer(std::queue<std::string> postfix, double &result) {
    std::stack<double> operands;

    while (!postfix.empty()) {
        std::string token = postfix.front();
        postfix.pop();

        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            if(isTokenValid(token)) {
                operands.push(std::stod(token));
            } else {
                return false;
            }
        } else if (isOperator(token[0])) {
            if (operands.size() < 2) {
                return false;
            }

            double right = operands.top(); operands.pop();
            double left = operands.top(); operands.pop();

            if (token == "/" && right == 0) {
                return false;
            }
            if (token == "+") {
                operands.push(left + right);
            } else if (token == "-") {
                operands.push(left - right);
            } else if (token == "*") {
                operands.push(left * right);
            } else if (token == "/") {
                operands.push(left / right);
            }
        } else {
            return false; // unknown token
        }
    }

    if (operands.size() != 1) {
        return false;
    } 

    result = operands.top();
    return true;
}

int main() {
    std::string input;
    std::getline(std::cin, input);

    std::queue<std::string> postfix;
    double result;

    if (!isCharacterValid(input)) {
        std::cout << "ERROR : Invalid character" << '\n';
    } else if (!isParenthesisBalanced(input)) {
        std::cout << "ERROR : Unbalanced parenthesis" << '\n';
    } else if (isExpressionInvalid(input)) {
        std::cout << "ERROR : Invalid expression" << '\n';
    } else {
        seperateinput(postfix, input);
        if (!calculateAnswer(postfix, result)) {
            std::cout << "ERROR : Invalid expression" << '\n'; 
        } else {
            std::cout << std::fixed << std::setprecision(2) << "Final Result : " << result << '\n';
        }
    }

    return 0;
}
