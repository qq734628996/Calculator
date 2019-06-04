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
#define N_OPTR 9 //���������
	typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //���������
	//�ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��

	const char pri[N_OPTR][N_OPTR] = { //��������ȵȼ� [ջ��] [��ǰ]
		/*              |-------------------- �� ǰ �� �� �� --------------------| */
		/*              +      -      *      /      ^      !      (      )      \0 */
		/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
		/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
		/* ջ  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* ��  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* ��  ^ */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* ��  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
		/* ��  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
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

