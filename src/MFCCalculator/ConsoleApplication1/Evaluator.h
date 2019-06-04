#pragma once
#define _CRT_SECURE_NO_WARNINGS

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

