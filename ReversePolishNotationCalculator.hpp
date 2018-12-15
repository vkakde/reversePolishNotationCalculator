/*@desc RPN Calculator (Accept infix expression from user, convert to postfix expression, evaluate postfix expression, display result)
 *@author Rahul_Sharma, Vishwajeet_Kakde
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <stack>
#include <queue>
#include <math.h>

using namespace std;

class postFixHandler{
public: 
    string infixExpression;

private:
    queue<char> infixQueue ;
    queue<char> postfixQueue;
    stack<char> operatorStack;
    
public:
    bool isOpeningParenthesis(char c);

    bool isClosingParenthesis(char c);

    bool isOperator(char c1, char c2, char c3);
    
    bool isOperator(char c);

    bool isOperand(char c);
    
    void printInfixQueue();

    void printPostfixQueue();
    
    int countOfOperands();
    
    int countOfOperators();

    bool parseInfixString();
    
    int assignOperatorPrecedence(char op);
    
    char whichHasHigherPrecedence(char operator1, char operator2);
    
    void convertInfixToPostfix();
    
    float evaluateExpression(int operand1, int operand2, char op);
    
    float postFixEvaluator();
};
