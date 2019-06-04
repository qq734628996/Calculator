#pragma once
#define _CRT_SECURE_NO_WARNINGS

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

	double readNumber(char*& p);
	Operator optr2rank(char op);
	char orderBetween(char op1, char op2);
	void append(char*& rpn, double opnd);
	void append(char*& rpn, char optr);
	__inline __int64 factorial(__int64 n);
	double calcu(char op, double pOpnd);
	double calcu(double pOpnd1, char op, double pOpnd2);
	void deblank(char* str);

public:
	Evaluator();
	~Evaluator();
	double evaluate(char* S, char*& RPN);
};

