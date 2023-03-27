#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "..\head\cal.h"

StackNode* p;
LinkStack OPND; // Operand Stack
LinkStack OPTR; // Operater Stack

Status InitStack(LinkStack S) {
	S->data = 0;
	S->stacksize = 0;
	S->next = NULL;
	return OK;
}


Status Push(LinkStack S, ElemType e) {
	p = (StackNode*)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S;
	S = p;
	return OK;
}


ElemType Pop(LinkStack S) {
	char e;
	if (S == NULL)  return ERROR;
	e = S->data;//Assign the stack top element to e
	p = S;//Use p to temporarily save stack top space for release
	S = S->next;//Modify stack top pointer
	return (int)e;
}


ElemType GetTop(LinkStack S) {
	//Returns the stack top element of S without modifying the stack top pointer
	if (S != NULL) {
		return S->data;
	}
}


int ln(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#' || ch == '\n') {
		return 1;
	}
	else {
		return 0;
	}
}


char Precede(char t, char ch) {
	switch (ch)
	{
	case '(':
	{
		return '<';
		break;
	}
	case '*':
	{
		if (t == '+' || t == '(' || t == '-' || t == '#')
			return '<';
		else
			return '>';
		break;
	}
	case '/':
	{
		if (t == '+' || t == '(' || t == '-' || t == '#')
			return '<';
		else
			return '>';
		break;
	}

	case '+':
	{
		if (t == '#' || t == '(')
			return '<';
		else
			return '>';
		break;
	}
	case '-':
	{
		if (t == '#' || t == '(')
			return '<';
		else
			return '>';
		break;
	}
	case ')':
	{
		if (t != '(')
			return '=';
		break;
	}
	case '#':
	{
		if (t != '#')
			return '>';
		break;
	}
	case '\n':
	{
		if (t == '#' || t == '+' || t == '-' || t == '*' || t == '/' || t == '(' || t == ')') {
			return '>';
		}
		break;
	}
	}
}

int Operate(int a, char c, int b)
{
	int t = 0;
	switch (c)
	{
	case '+':
		t = a + b; break;
	case '-':
		t = a - b; break;
	case '*':
		t = a * b; break;
	case '/':
		t = a / b; break;
	}
	return t;
}


int EvaluateExpression() {
	//Set OPTR and OPEN as operator stations and operand stacks
	InitStack(OPND);//Init
	InitStack(OPTR);

	Push(OPTR, '#');
	OPTR = p;
	char ch, theta, a, b;
	int a1, b1; 
	ch = getchar();
	while (ch != '#' || GetTop(OPTR) != '#')//# as END
	{
		if (!ln(ch)) {
			//If ch is not an operator, it enters the OPND stack and reads the next character
			Push(OPND, ch);
			OPND = p;
			ch = getchar();
		}
		else {
			switch (Precede(GetTop(OPTR), ch))
			{
			case'<':
			{
				Push(OPTR, ch);//Find that cann't operate OPND in func so had to make it out...
				OPTR = p;
				ch = getchar();
				break;
			}
			case'>':
			{
				theta = Pop(OPTR);//Pop up the operator at the top of the OPTR stack
				OPTR = OPTR->next;
				free(p);
				a = Pop(OPND);
				OPND = OPND->next;//Find that cann't operate OPND in func so had to make it out...
				free(p);
				b = Pop(OPND);
				OPND = OPND->next;
				free(p);
				a1 = a - '0';//Convert characters to decimal
				b1 = b - '0';
				Push(OPND, Operate(b1, theta, a1) + '0');//Because the data in OPND is character type, the calculation result is converted to character type
				OPND = p;
				if (ch == '\n') {
					ch = '#';
				}
				break;
			}
			case'=':
			{
				a = Pop(OPND);
				OPND = OPND->next;
				free(p);
				b = Pop(OPND);
				OPND = OPND->next;
				free(p);
				theta = Pop(OPTR);
				OPTR = OPTR->next;
				free(p);
				a1 = a - '0';
				b1 = b - '0';
				Push(OPND, Operate(b1, theta, a1) + '0');
				OPND = p;
				Pop(OPTR);
				OPTR = OPTR->next;//Pop up the "(" at the top of the OPTR stack and read in the next character ch
				free(p);
				//Push(OPTR, '#'); OPTR = p;
				ch = getchar();
				break;
			}
			}

		}

	}
	printf("Result£º%d\n", GetTop(OPND) - '0');//Because the data in OPND is char,converting it to int	    
}

void main()
{
	OPND = malloc(sizeof(StackNode));
	OPTR = malloc(sizeof(StackNode));
	printf("Sorry, now it can noly caculate 1bit num and ENTER to exit\n\n");
	printf("Please enter an expression to evaluate:");
	while (1) {
		EvaluateExpression();
	}
}