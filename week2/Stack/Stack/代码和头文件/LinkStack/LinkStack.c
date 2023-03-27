#include "../head/LinkStack.h" 
#include <stdio.h>
#include <stdlib.h>
//Á´Õ»

//³õÊ¼»¯Õ»
Status initLStack(LinkStack *s){
	s->top = NULL;
	s->count = 0;
}

//ÅÐ¶ÏÕ»ÊÇ·ñÎª¿Õ
Status isEmptyLStack(LinkStack *s){
	if (s->count == 0) {
		return SUCCESS;
	}
	else {
		return ERROR;
	}
}

//µÃµ½Õ»¶¥ÔªËØ
Status getTopLStack(LinkStack *s,ElemType *e){
	*e = s->top->data;
	return SUCCESS;
}

//Çå¿ÕÕ»
Status clearLStack(LinkStack *s){
	ElemType pop = 0;
	while (s->top != NULL) {
		popLStack(s,pop);
	}
	return SUCCESS;
}

//Ïú»ÙÕ»
Status destroyLStack(LinkStack *s){
	free(s);
	s = NULL;
	return SUCCESS;
}

//¼ì²âÕ»³¤¶È
Status LStackLength(LinkStack *s,int *length){
	*length = 1;
	StackNode* temp = s->top;
	while (temp->next != NULL) {
		*length += 1;
		temp = temp->next;
	}
	return SUCCESS;
}

//ÈëÕ»
Status pushLStack(LinkStack *s,ElemType data){
	StackNode* node = malloc(sizeof(StackNode));
	node->data = data;
	node->next = s->top;
	s = node;
	return SUCCESS;
}

//³öÕ»
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

