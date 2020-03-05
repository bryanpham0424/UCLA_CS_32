#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>


using namespace std;

bool isValidinfix(string& infix); //Checks whether it is valid or not and all lowercase
void inToPost(string infix, string& result); //converts infix to postfix
bool isOperand(char test); // checks if the current index is an operand
bool isOperator(char test); // if current is an operator
int precedence(char test); // precedence of the symbols
bool evenParen(string test); // checks if there are the same amount of '(' as ')'
int postEval(string& postfix, const Map& values); // evaluates the equation after the postfix conversion
bool correctParen(string& check); // checks if the parentheses are in the correct places
bool allLowercase(string& check); // checks if all operands are lowercase
int evaluate(string infix, const Map& values, string& postfix, int& result); //evaluates the postfix

int main() {
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+" && answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	//// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*" && answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+" && answer == -1);
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/" && answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 &&
		pf == "a" && answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a" && answer == 3);
	cout << "Passed all tests" << endl;
	
} 

bool isValidinfix(string& infix) {
	if (infix.empty()) {
		return false;
	}
	if (!allLowercase(infix)) {
		return false;
	}
	if (!evenParen(infix)) {
		return false;
	}
	if (!correctParen(infix)) {
		return false;
	}
	if (isOperator(infix[infix.size() - 1])) {
		return false;
	}
	if (infix[0] != '(' && !(isOperand(infix[0])) && infix[0] != ' ') {
		return false;
	}

	if (infix[infix.length() - 1] == '(') {
		return false;
	}
	int opCount = 0;
	int operands = 0;
	int parenthesis = 0;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == ' '){
			continue;
		}
		if (isOperator(infix[i])) {
			opCount += 1;
		}
		else if (isOperand(infix[i])) {
			operands += 1;
		}
		else if (infix[i] == '(')
		{
			if (i < infix.length()-1 && infix[i+1] == ')')
				return false;
			parenthesis += 1;
		}
		else if (infix[i] == ')') {
			parenthesis += 1;
		}
	}

	if (opCount == 0) {
		if (parenthesis%2 == 0 && operands == 1)
			return true;
		return false;
	}
	
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == ' ') {
			continue;
		}
		if (infix[i] == '(') {
			if ((i < infix.size() - 1) && (infix[i + 1] == ')')) {
				return false;
			}
		}
		if (infix[i] == '(') { // case "(+"
			if ((i < infix.size() - 1) && isOperator(infix[i + 1])) {
				return false;
			} 
		}
		if (infix[i] == ')') { // case ")a"
			if ((i < infix.size() - 1) && isOperand(infix[i + 1])) {
				return false;
			}
		}
		if (isOperand(infix[i])) { // two operands next to each other or the case "a("
			if (((i < infix.size() - 1) && isOperand(infix[i + 1]))) {
				return false;
			}
		}

		if (isOperand(infix[i])) {
			if ((i < infix.size() - 1) && infix[i + 1] == '(') {
				return false;
			}
		}
		if (isOperator(infix[i])) { // two operators next to each other
			if ((i < infix.size() - 1) && isOperator(infix[i + 1])) {
				return false;
			}
		}
		
	
	}
	return true;
}

void inToPost(string infix, string& result) {
	result = "";
	
	stack<char> postfix;
	for (int i = 0; i < infix.size(); i++) {
		char curr = infix[i];
		if (curr == ' ') {
			continue;
		}
		else if (isOperand(curr)) { // if the current index is an operand
			result += curr;
		}
		else if (curr == '(') { // if current is a open-parenth
			postfix.push(curr);
		}
		else if (curr == ')') { // if closes parenth
			while (postfix.top() != '(') {
				if (postfix.top() == ' ') {
					continue;
				}
				result += postfix.top();
				postfix.pop();
			}
			postfix.pop();
		}
		else if (isOperator(curr)) {
			while (postfix.size() != 0 && postfix.top() != '(') {
				if (precedence(curr) <= precedence(postfix.top())) {
					result += postfix.top();
					postfix.pop();
				}
				else
					break;
			}
			postfix.push(curr);
		}

	}
	while (postfix.size() != 0) {

		result += postfix.top();
		postfix.pop();
	}
}

bool isOperand(char test) {
	if (test >= 'a' && test <= 'z') {
		return true;
	}
	return false;
}

bool isOperator(char test) {
	if (test == '+' || test == '-' || test == '*' || test == '/') {
		return true;
	}
	return false;
}

bool allLowercase(string& check) {
	for (int i = 0; i < check.size(); i++) {
		if (check[i] >= 'A' && check[i] <= 'Z') {
		
			if (!(isOperand(check[i]))) {
				return false;
			}
		}
	}
	return true;
}

int precedence(char test) {
	switch (test) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default: return 0;
	}
	
}

bool evenParen(string test) {
	int open = 0;
	int closed = 0;
	for (int i = 0; i < test.size(); i++) {
		if (test[i] == '(') {
			open += 1;
		}
		if (test[i] == ')') {
			closed += 1;
		}
	}
	if (open != closed) {
		return false;
	}
	return true;
}

bool correctParen(string& check) {
	int mark = 0;
	for (int i = 0; i < check.size(); i++) {
		if (check[i] == '(') {
			mark += 1;
		}
		if (check[i] == ')') {
			if (mark == 0) {
				return false;
			}
			mark += 1;
		}
	}
	return true;
}

int postEval(string& postfix, const Map& values) {
	stack<int> valStack;
	for (int i = 0; i < postfix.size(); i++) {
		if (isOperand(postfix[i])) {
			if (!(values.contains(postfix[i]))) {
				return 7;
			}
			int value;
			values.get(postfix[i], value);
			valStack.push(value);
		}
		else{
			int operand_2 = valStack.top();
			valStack.pop();
			int operand_1 = valStack.top();
			valStack.pop();
			char oper = postfix[i];
			int resulting;
			switch (oper) {
			case '+':
				resulting = operand_1+operand_2;
				break;
			case '-':
				resulting = operand_1-operand_2;
				break;
			case '*':
				resulting = operand_1*operand_2;
				break;
			case '/':
				if (operand_2 == 0) {
					return 5;
				}
				resulting = operand_1/operand_2;
				break;
			}
			valStack.push(resulting);
		}
		
	}
	return valStack.top();
}

int evaluate(string infix, const Map& values, string& postfix, int& result) {
	
	if (!(isValidinfix(infix))) {
		return 1;
	}
	if (isValidinfix(infix)) {
		inToPost(infix, postfix);
		if (postfix.size() == 1) {
			int x;
			values.get(postfix[0], x);
			result = x;
			return 0;
		}
		if (postEval(postfix, values) == 7) {
			return 2;
			}
		else if (postEval(postfix, values) == 5) {
				return 3;
		}
		else {
				result = postEval(postfix, values);
				return 0;
		}
				
			
		
	}
}
