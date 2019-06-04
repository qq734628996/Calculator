
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
	case '+': return ADD; //��
	case '-': return SUB; //��
	case '*': return MUL; //��
	case '/': return DIV; //��
	case '^': return POW; //�˷�
	case '!': return FAC; //�׳�
	case '(': return L_P; //������
	case ')': return R_P; //������
	case '\0': return EOE; //��ʼ������ֹ��
	default: exit(-1);  //δ֪�����
	}
}

char Evaluator::orderBetween(char op1, char op2)
{
	return pri[optr2rank(op1)][optr2rank(op2)];
}

void Evaluator::append(char *& rpn, double opnd)
{
	int n = strlen(rpn); //RPN��ǰ����(��'\0'��β,����n + 1)
	char buf[64];
	if (opnd != (double)(int)opnd) sprintf(buf, "%f \0", opnd); //�����ʽ,��
	else sprintf(buf, "%d \0", (int)opnd); //������ʽ
	rpn = (char*)realloc(rpn, sizeof(char) * (n + strlen(buf) + 1)); //��չ�ռ�
	strcat(rpn, buf); //RPN�ӳ�
}

void Evaluator::append(char *& rpn, char optr)
{
	int n = strlen(rpn); //RPN��ǰ����(��'\0'��β,����n + 1)
	rpn = (char*)realloc(rpn, sizeof(char) * (n + 3)); //��չ�ռ�(ע��ʱ��Ч�ʵĳ���ע��!!!)
	sprintf(rpn + n, "%c ", optr); rpn[n + 2] = '\0'; //����ָ���������
}

void Evaluator::append(char*& rpn, const char* funcName)
{
	int n = strlen(rpn); //RPN��ǰ����(��'\0'��β,����n + 1)
	rpn = (char*)realloc(rpn, sizeof(char) * (n + strlen(funcName) + 2)); //��չ�ռ�(ע��ʱ��Ч�ʵĳ���ע��!!!)
	sprintf(rpn + n, "%s ", funcName); rpn[n + strlen(funcName) + 1] = '\0'; //����ָ���������
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
	*RPN = '\0'; //��ʼ���沨�����ʽ
	deblank(S); //ȥ��S�Ŀո�
	stack<double> opnd;
	stack<char> optr; //������ջ,�����ջ
	optr.push('\0'); //β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�����ջ
	while (!optr.empty()) { //�������ջ�ǿ�֮ǰ,���������ʽ�и��ַ�
		if (isdigit(*S)) { //����ǰ�ַ�Ϊ������,��
			opnd.push(readNumber(S));
			append(RPN, opnd.top()); //���������,���������RPNĩβ
		}
		else if (isalpha(*S)) { //����ѧ����
			readFunc(S);
		}
		else //����ǰ�ַ�Ϊ�����,��
			switch (orderBetween(optr.top(), *S)) { //������ջ�������֮�����ȼ��ߵͷֱ���
			case '<': //ջ����������ȼ�����ʱ
				optr.push(*S); S++; //�����Ƴ�,��ǰ�������ջ
				break;
			case '=': //���ȼ����(��ǰ�����Ϊ�����Ż���β���ڱ�'\0')ʱ
				if (*S == ')' && !funcId.empty()) { //������ѧ����
					append(RPN, mathFunc[funcId.top()]); //��ѧ������������RPNĩβ
					double pOpnd = opnd.top(); opnd.pop(); //ֻ��ȡ��һ��������,��
					opnd.push(calcu(pOpnd)); //ʵʩһԪ����,�����ջ
				}
				optr.pop(); S++; //�����Ų�������һ���ַ�
				break;
			case '>': { //ջ����������ȼ�����ʱ,��ʵʩ��Ӧ�ļ���,�������������ջ
				char op = optr.top(); optr.pop();
				append(RPN, op); //ջ���������ջ��������RPNĩβ
				if ('!' == op) { //������һԪ�����
					double pOpnd = opnd.top(); opnd.pop(); //ֻ��ȡ��һ��������,��
					opnd.push(calcu(op, pOpnd)); //ʵʩһԪ����,�����ջ
				}
				else { //��������(��Ԫ)�����
					double pOpnd2 = opnd.top(); opnd.pop();
					double pOpnd1 = opnd.top(); opnd.pop(); //ȡ����,ǰ������
					opnd.push(calcu(pOpnd1, op, pOpnd2));
				}
				break;
			}
			default: exit(-1); //���﷨����,��������ֱ���˳�
			} //switch
	} //while
	double rt = opnd.top(); opnd.pop();
	return rt; //�������������ļ�����
}

