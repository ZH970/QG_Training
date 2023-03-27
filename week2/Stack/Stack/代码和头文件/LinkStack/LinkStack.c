#include "../head/LinkStack.h" 
#include <stdio.h>
#include <stdlib.h>
//��ջ

//��ʼ��ջ
Status initLStack(LinkStack *s){
	s->top = NULL;
	s->count = 0;
}

//�ж�ջ�Ƿ�Ϊ��
Status isEmptyLStack(LinkStack *s){
	if (s->count == 0) {
		return SUCCESS;
	}
	else {
		return ERROR;
	}
}

//�õ�ջ��Ԫ��
Status getTopLStack(LinkStack *s,ElemType *e){
	*e = s->top->data;
	return SUCCESS;
}

//���ջ
Status clearLStack(LinkStack *s){
	ElemType pop = 0;
	while (s->top != NULL) {
		popLStack(s,pop);
	}
	return SUCCESS;
}

//����ջ
Status destroyLStack(LinkStack *s){
	free(s);
	s = NULL;
	return SUCCESS;
}

//���ջ����
Status LStackLength(LinkStack *s,int *length){
	*length = 1;
	StackNode* temp = s->top;
	while (temp->next != NULL) {
		*length += 1;
		temp = temp->next;
	}
	return SUCCESS;
}

//��ջ
Status pushLStack(LinkStack *s,ElemType data){
	StackNode* node = malloc(sizeof(StackNode));
	node->data = data;
	node->next = s->top;
	s = node;
	return SUCCESS;
}

//��ջ
Status popLStack(LinkStack *s,ElemType *data){
	if (s->top) {
		StackNode* p = s->top;
		s->top = s->top->next;
		printf("Pop element:%d\n", p->data);
		if (s->top) {
			printf("Top:%d\n", s->top);
		}
		else {
			printf("Already empty\n");
		}
	}
	else {
		printf("Empty!\n");
		return ERROR;
	}
	return SUCCESS;
}

