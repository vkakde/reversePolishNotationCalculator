#include "ReversePolishNotationCalculator.hpp"

bool postFixHandler::isOpeningParenthesis(char c){
    if(c=='(' || c=='{' || c=='['){
        return true;
    }
    return false;
}

bool postFixHandler::isClosingParenthesis(char c){
    if(c==')' || c=='}' || c==']'){
        return true;
    }
    return false;
}
bool postFixHandler::isOperator(char c1, char c2, char c3){
    if(c1=='+' || c1=='-' || c1=='*' || c1=='/' || c1=='%'){
        return true;
    }
    else if(c1=='P' && c2=='O' && c3=='W'){
        return true;
    }
    return false;
}
    
bool postFixHandler::isOperator(char c){
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='%' || c=='P'){
        return true;
    }
    return false;
}
bool postFixHandler::isOperand(char c){
    if((int)c>=48 && (int)c<=57){
        return true;
    }
    return false;
}

void postFixHandler::printInfixQueue(){
    queue<char> temp;
    temp = infixQueue;
    cout<<"\n\nInfix Queue (\'POW\' replaced with \'P\' for simplicity):  ";
    while(!temp.empty()){
        char element = temp.front();
        cout<<element;
        temp.pop();
    }
}

void postFixHandler::printPostfixQueue(){
    queue<char> temp;
    temp = postfixQueue;
    cout<<"\n\nPostfix Queue:  ";
    while(!temp.empty()){
        char element = temp.front();
        cout<<element;
        temp.pop();
    }
}

int postFixHandler::countOfOperands(){
    int count = 0;
    for (int i=0; i<infixExpression.length(); i++){
        if(isOperand(infixExpression[i])){
            while(isOperand(infixExpression[i+1])){
                i++;
            }
            count++;
        }
    }
    return count;
}

int postFixHandler::countOfOperators(){
    int count = 0;
    for (int i=0; i<infixExpression.length(); i++){
        if(isOperator(infixExpression[i])){
            count++;
        }
    }
    return count;
}

bool postFixHandler::parseInfixString(){
    for(int i=0; i<infixExpression.length();i++){
        if(countOfOperands()-countOfOperators()!=1){
            return false;
        }
        
        if(infixExpression[i]==' '){
            continue;
        }
        else if(isOperator(infixExpression[i], infixExpression[i+1], infixExpression[i+2])){
            if(infixExpression[i]=='P' && infixExpression[i+1]=='O' && infixExpression[i+2]=='W'){
                infixQueue.push('P');
                // infixQueue.push(' ');
                i+=2;
                continue;
            }
            
            infixQueue.push(infixExpression[i]);
            // infixQueue.push(' ');
            continue;
        }
        else if(isOpeningParenthesis(infixExpression[i]) || isClosingParenthesis(infixExpression[i])){
            infixQueue.push(infixExpression[i]);
            infixQueue.push(' ');
            continue;
        }
        else if(isOperand(infixExpression[i])){
            infixQueue.push(infixExpression[i]);
            while(isOperand(infixExpression[i+1])){
                infixQueue.push(infixExpression[i+1]);
                i++;
            }
            
            infixQueue.push(' ');
        }
        else{
            return false;          // invalid character detected in infix expression
        }
    }
    if(isOperator(infixQueue.front()) || isOperator(infixQueue.back())){    // infix expression cannot start or end with an operator
        return false;
    }
    return true;
}

int postFixHandler::assignOperatorPrecedence(char op){
    switch(op){
        case 'P': return 6;
                  break;
        case '%': return 5;
                  break;
        case '/': return 4;
                  break;
        case '*': return 3;
                  break;
        case '+': return 2;
                  break;
        case '-': return 1;
                  break;
        case '[': return 0;
                  break;
        case '{': return -1;
                  break;
        case '(': return -2;
                  break;
    }
}

char postFixHandler::whichHasHigherPrecedence(char operator1, char operator2){
    int operator1_Precedence = assignOperatorPrecedence(operator1);
    int operator2_Precedence = assignOperatorPrecedence(operator2);
    
    if(operator1_Precedence>=operator2_Precedence){
        return operator1;
    }
    else{
        return operator2;
    }
}

void postFixHandler::convertInfixToPostfix(){
    char element;
    
    while(!infixQueue.empty()){
        element = infixQueue.front();
        
        if(isOpeningParenthesis(element)){
            operatorStack.push(element);
            infixQueue.pop();
        }
        
        if(isClosingParenthesis(element)){
            // pop all operators from operating stack onto postfix queue, until you reach an opening paranthesis
            while(!isOpeningParenthesis(operatorStack.top())){
                postfixQueue.push(operatorStack.top());
                operatorStack.pop();
            }    
            // now, pop the opening parenthesis too
            operatorStack.pop();
        }
        
        if(isOperand(element)){
            postfixQueue.push(element);
            infixQueue.pop();
            element = infixQueue.front();
            while(isOperand(element)){
                postfixQueue.push(element);
                infixQueue.pop();
                element = infixQueue.front();
            }     
            postfixQueue.push(' ');
        }
        
        if(isOperator(element)){
            if(operatorStack.empty()){
                operatorStack.push(element);
                infixQueue.pop();
            }    
            else{
                char topMostOperatorInStack = operatorStack.top();
                
                if(whichHasHigherPrecedence(element, topMostOperatorInStack)==element){
                    operatorStack.push(element);
                    infixQueue.pop();
                }
                
                else if(whichHasHigherPrecedence(element, topMostOperatorInStack)==topMostOperatorInStack){
                    postfixQueue.push(topMostOperatorInStack);
                    operatorStack.pop();
                    
                    while(!operatorStack.empty() && whichHasHigherPrecedence(element,operatorStack.top())==operatorStack.top()){
                        postfixQueue.push(operatorStack.top());
                        operatorStack.pop();
                    }
                    
                    operatorStack.push(element);
                    infixQueue.pop();
                }                    
            }
            postfixQueue.push(' ');
        }
        
        else{
            infixQueue.pop();
            continue;
        }
    }
    // pop remaining operators from operator stack and push into pushfix queue
    while(!operatorStack.empty()){
        element = operatorStack.top();
        postfixQueue.push(element);
        operatorStack.pop();
    }
}

float postFixHandler::evaluateExpression(int operand1, int operand2, char op){
    switch(op){
        case '*': return ((float)operand1 * (float)operand2);
                  break;
        case '/': if(operand2==0){          // divide by zero error
                    return -99997;
                  }
                  else{
                    return ((float)operand1 / (float)operand2);
                  }
                  break;
        case '+': return ((float)operand1 + (float)operand2);
                  break;
        case '-': return ((float)operand1 - (float)operand2);
                  break;
        case '%': if(operand2==0){          // divide by zero error
                    return -99997;
                  }
                  else{
                    return (operand1 % operand2);
                  }
                  break;
                  
        case 'P': return pow((float)operand1, (float)operand2);
                  break;
    }
}

float postFixHandler::postFixEvaluator(){
    // step 1: parse infix string expression into an infix integer queue
    bool isInfixExpressionValid = parseInfixString();
    if(isInfixExpressionValid==false){
        return -99996;
    }
    
    // step 2: print the parsed infix queue
    printInfixQueue();
    Sleep(2500);
    
    // step 3: convert infix to postfix; store in postfix queue
    convertInfixToPostfix();
    
    // step 4: print the generated postfix queue
    printPostfixQueue();
    Sleep(2500);
    
    // step 5: evaluate the postfix expression and return result to main()
    stack<float> postfixEvaluationStack;
    float res;
    
    while(!postfixQueue.empty()){
        char element = postfixQueue.front();
        
        if(isOperand(element)){
            int operand = element-'0';
            postfixQueue.pop();
            while(isOperand(postfixQueue.front())){
                int nextDigit = postfixQueue.front();
                operand = (nextDigit-'0') + operand*10;
                postfixQueue.pop();
            }
            postfixEvaluationStack.push(operand);    
        }
        
        if(isOperator(element)){
            int operand2 = postfixEvaluationStack.top();
            postfixEvaluationStack.pop();
            
            int operand1 = postfixEvaluationStack.top();
            postfixEvaluationStack.pop();
            
            res = evaluateExpression(operand1, operand2, element);     // element = operator
            
            // push result onto postfix evaluation stack
            postfixEvaluationStack.push(res);
            postfixQueue.pop();
        }
        
        else{
            postfixQueue.pop();
            continue;
        }
        
    }
    
    return res;
}    

int main(int argc, char **argv)
{
    postFixHandler X; 
    
    while(X.infixExpression!="q" || X.infixExpression!="Q"){
        cout<<"\n\n\n\n||*** RPN Calculator (Infix->Postfix, Postfix Evaluation) ***||\n\n(Press Q to quit)\n\n\nEnter infix expression:    ";
        getline(cin, X.infixExpression);
    
        if(X.infixExpression=="q" || X.infixExpression=="Q"){
            cout<<"\n\nExiting program ...";
            Sleep(4000);
            exit(0);
        }
        
        cout<<"\nInfix Expression entered is:  "<<X.infixExpression;    
        Sleep(2500);
        
        float res = X.postFixEvaluator();
        if(res==-99996){
            cout<<"\n\nERROR: Invalid infix expression entered!!";
            Sleep(2000);
            continue;
        }
        if(res==-99997){
            cout<<"\n\nERROR: Cannot divide by ZERO!!";
            Sleep(2000);
            continue;
        }
        else{
            cout<<"\n\nResult of postfix evaluation:  "<<res;
            Sleep(4000);
        }
    }
    
	return 0;
}
