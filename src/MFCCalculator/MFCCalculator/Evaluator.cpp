
#include "stdafx.h"
#include "Evaluator.h"

double Evaluator::readNumber(char *& p)
{
	double res = *p - '0';
	while (isdigit(*++p))
		res = res * 10 + *p - '0';
	if ('.' != *p) return res;
	double frac = 1;
	while (isdigit(*++p))
		res += (*p - '0')*(frac /= 10);
	return res;
}

void Evaluator::readFunc(char*& p)
{
	string s;
	int idx = 0;
	while (isalpha(*p))
		s.push_back(*p++);
	for (int i = 0; i < 8; i++) {
		if (s == mathFunc[i]) {
			funcId.push(i);
			return;
		}
	}
}

Evaluator::Operator Evaluator::optr2rank(char op)
{
	switch (op) {
	case '+': return ADD; //加
	case '-': return SUB; //减
	case '*': return MUL; //乘
	case '/': return DIV; //除
	case '^': return POW; //乘方
	case '!': return FAC; //阶乘
	case '(': return L_P; //左括号
	case ')': return R_P; //右括号
	case '\0': return EOE; //起始符和终止符
	default: exit(-1);  //未知运算符
	}
}

char Evaluator::orderBetween(char op1, char op2)
{
	return pri[optr2rank(op1)][optr2rank(op2)];
}

void Evaluator::append(char *& rpn, double opnd)
{
	int n = strlen(rpn); //RPN当前长度(以'\0'结尾,长度n + 1)
	char buf[64];
	if (opnd != (double)(int)opnd) sprintf(buf, "%f \0", opnd); //浮点格式,或
	else sprintf(buf, "%d \0", (int)opnd); //整数格式
	rpn = (char*)realloc(rpn, sizeof(char) * (n + strlen(buf) + 1)); //扩展空间
	strcat(rpn, buf); //RPN加长
}

void Evaluator::append(char *& rpn, char optr)
{
	int n = strlen(rpn); //RPN当前长度(以'\0'结尾,长度n + 1)
	rpn = (char*)realloc(rpn, sizeof(char) * (n + 3)); //扩展空间(注重时间效率的场合注意!!!)
	sprintf(rpn + n, "%c ", optr); rpn[n + 2] = '\0'; //接入指定的运算符
}

void Evaluator::append(char*& rpn, const char* funcName)
{
	int n = strlen(rpn); //RPN当前长度(以'\0'结尾,长度n + 1)
	rpn = (char*)realloc(rpn, sizeof(char) * (n + strlen(funcName) + 2)); //扩展空间(注重时间效率的场合注意!!!)
	sprintf(rpn + n, "%s ", funcName); rpn[n + strlen(funcName) + 1] = '\0'; //接入指定的运算符
}

__int64 Evaluator::factorial(__int64 n)
{
	return n > 1 ? n * factorial(n - 1) : 1;
}
double Evaluator::calcu(char op, double pOpnd)
{
	if (op == '!') return (double)factorial((__int64)pOpnd);
	else exit(-1);
}

double Evaluator::calcu(double pOpnd1, char op, double pOpnd2)
{
	switch (op) {
	case '+': return pOpnd1 + pOpnd2;
	case '-': return pOpnd1 - pOpnd2;
	case '*': return pOpnd1 * pOpnd2;
	case '/': return pOpnd1 / pOpnd2;
	case '^': return pow(pOpnd1, pOpnd2);
	default: exit(-1);
	}
}

double Evaluator::calcu(double pOpnd)
{
	int i = funcId.top();  funcId.pop();
	switch (i)
	{
	case 0: return sin(pOpnd);
	case 1: return cos(pOpnd);
	case 2: return tan(pOpnd);
	case 3: return asin(pOpnd);
	case 4: return acos(pOpnd);
	case 5: return atan(pOpnd);
	case 6: return log10(pOpnd);
	case 7: return log(pOpnd);
	default: exit(-1);
	}
}

void Evaluator::deblank(char * str)
{
	for (char* p = str; *p != '\0'; p++)
		if (*p != ' ') *str++ = *p;
	*str = '\0';
}

Evaluator::Evaluator()
{
	while (!funcId.empty()) funcId.pop();
}

Evaluator::~Evaluator()
{
}

double Evaluator::evaluate(char * S, char *& RPN)
{
	*RPN = '\0'; //初始化逆波兰表达式
	deblank(S); //去除S的空格
	stack<double> opnd;
	stack<char> optr; //运算数栈,运算符栈
	optr.push('\0'); //尾哨兵'\0'也作为头哨兵先入栈
	while (!optr.empty()) { //在运算符栈非空之前,逐个处理表达式中各字符
		if (isdigit(*S)) { //若当前字符为操作数,则
			opnd.push(readNumber(S));
			append(RPN, opnd.top()); //读入操作数,并将其接至RPN末尾
		}
		else if (isalpha(*S)) { //是数学函数
			readFunc(S);
		}
		else //若当前字符为运算符,则
			switch (orderBetween(optr.top(), *S)) { //视其与栈顶运算符之间优先级高低分别处理
			case '<': //栈顶运算符优先级更低时
				optr.push(*S); S++; //计算推迟,当前运算符进栈
				break;
			case '=': //优先级相等(当前运算符为右括号或者尾部哨兵'\0')时
				if (*S == ')' && !funcId.empty()) { //含有数学函数
					append(RPN, mathFunc[funcId.top()]); //数学函数名续接至RPN末尾
					double pOpnd = opnd.top(); opnd.pop(); //只需取出一个操作数,并
					opnd.push(calcu(pOpnd)); //实施一元运算,结果入栈
				}
				optr.pop(); S++; //脱括号并接受下一个字符
				break;
			case '>': { //栈顶运算符优先级更高时,可实施相应的计算,并将结果重新入栈
				char op = optr.top(); optr.pop();
				append(RPN, op); //栈顶运算符出栈并续接至RPN末尾
				if ('!' == op) { //若属于一元运算符
					double pOpnd = opnd.top(); opnd.pop(); //只需取出一个操作数,并
					opnd.push(calcu(op, pOpnd)); //实施一元运算,结果入栈
				}
				else { //对于其他(二元)运算符
					double pOpnd2 = opnd.top(); opnd.pop();
					double pOpnd1 = opnd.top(); opnd.pop(); //取出后,前操作数
					opnd.push(calcu(pOpnd1, op, pOpnd2));
				}
				break;
			}
			default: exit(-1); //逢语法错误,不做处理直接退出
			} //switch
	} //while
	double rt = opnd.top(); opnd.pop();
	return rt; //弹出并返回最后的计算结果
}

