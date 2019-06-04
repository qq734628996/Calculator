#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <cassert>

#include <iostream>
#include <algorithm>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Evaluator
{
#define N_OPTR 9 //运算符总数
	typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //运算符集合
	//加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

	const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
		/*              |-------------------- 当 前 运 算 符 --------------------| */
		/*              +      -      *      /      ^      !      (      )      \0 */
		/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
		/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
		/* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* 运  ^ */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
		/* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
		/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
		/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
	};

	const char* mathFunc[8] = {
		"sin","cos","tan",
		"asin","acos","atan",
		"log","ln"
	};

	stack<int> funcId;

	double readNumber(char*& p);
	void readFunc(char*& p);
	Operator optr2rank(char op);
	char orderBetween(char op1, char op2);
	void append(char*& rpn, double opnd);
	void append(char*& rpn, char optr);
	void append(char*& rpn, const char* funcName);
	__inline __int64 factorial(__int64 n);
	double calcu(char op, double pOpnd);
	double calcu(double pOpnd1, char op, double pOpnd2);
	double calcu(double pOpnd);
	void deblank(char* str);

public:
	Evaluator();
	~Evaluator();
	double evaluate(char* S, char*& RPN);
};

