#pragma once

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXSIZE 100 

typedef  char ElemType;
typedef  int Status;

typedef struct StackNode {
	ElemType data;
	struct StackNode* next;
	int stacksize;//Maximum capacity available for the stack
}StackNode, * LinkStack;

//Stack operation
Status InitStack(LinkStack S);
Status Push(LinkStack S, ElemType e);
ElemType Pop(LinkStack S);
ElemType GetTop(LinkStack S);

int ln(char ch); //Num or others
char Precede(char t, char ch); //Compare priority
int Operate(int a, char c, int b); //Performing an operation
int EvaluateExpression(); //push(Enable) value to stack or pop
