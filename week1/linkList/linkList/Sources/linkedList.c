#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "..\Headers\linkedList.h"

Status InitList(LinkedList *L) {
	Status init = ERROR;
	(*L)->data = -22002072;
	(*L)->next = NULL;
	input(L);
	init = SUCCESS;
	return init;
}

Status InsertList(LNode *p, LNode *q) {
	Status insert = ERROR;
	q->next = p->next;
	p->next = q;
	insert = SUCCESS;
	return insert;
}

void DestroyList(LinkedList *L) {
	printf("\nIt will start from the L's position.\n");
	printf("Head node is recommanded\n");
	LNode *c = *L;
	LNode *n;
	while (c != NULL) {
		n = c->next;
		free(c);
		c = n;
	}
	(*L)->data = -22002072; //A special virtual node
	(*L)->next = NULL;
}

Status DeleteList(LNode *p, ElemType* e) {
	Status del = ERROR;
	*e = 0;
	LNode *next = p->next;
	if (next != NULL) {
		*e = next->data;
		p->next = p->next->next;
		free(next);
		del = SUCCESS;
		return del;
	}
	else { return del; }
}

void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
	printf("\nIt will start from the L's position.\n");
	printf("Head node is recommanded\n");
	LNode* temp = L;
	ElemType e = 0;
	if (L != NULL) {
		while (temp != NULL) {
			e = temp->data;
			if (e == -22002072) {
				visit(e);
				printf("(H)");
			}
			else {
				visit(e);
			}
			temp = temp->next;
		}
	}
	else {
		printf("Don't input Nullptr!");
	}
}

Status SearchList(LinkedList L, ElemType e) {
	LNode* find = L;
	printf("\nIt will start from the L's position.\n");
	printf("Head node is recommanded\n");
	Status search = ERROR;
	while (find != NULL) {
		if (find->data == e) {
			printf("There is %d in this linkedlist\n",e);
			search = SUCCESS;
			return search;
		}
		else {
			find = find->next;
		}
	}
	printf("Couldn't find it\n");
	return search;
}

Status ReverseList(LinkedList *L) {
	Status rev = ERROR;
	LinkedList previous = NULL;
	LinkedList current = *L;
	LinkedList next = NULL;
	while (current != NULL) {
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
		if (current != NULL) {
			next = current->next;
		}
	}
	*L = previous;
	rev = SUCCESS;
	return rev;
}

Status IsLoopList(LinkedList L) {
	Status loop = ERROR;
	LinkedList slow = L;
	LinkedList fast = L;
	while (fast != NULL && fast->next != slow) {
		if (fast->next == NULL) {
			fast = NULL;
		}
		else {
			fast = fast->next->next;
		}
		slow = slow->next;
	}
	if (fast == NULL) {
		printf("\nIsn't looplist: ERROR\n");
	}
	else {
		printf("LoopList: SUCCESS\n");
		loop = SUCCESS;
	}
	printf("\nNOTE:LoopList now only is supported by 1./3./7. func\n");
	printf("NOTE:And at the last printf, it must be closed manully!\n\n");
	return loop;
}

LNode* ReverseEvenList(LinkedList *L) {

	LinkedList previous = NULL;
	LinkedList current = *L;
	LinkedList next = current->next;

	if (IsLoopList(*L) == SUCCESS) { return *L;}
	else { printf("\nThe linkedlist isn't looplist\n"); }
	if (next->data == 0 || next->data == 2 || next->data == 4 || next->data == 6 || next->data == 8) {
		//make sure after reversing, *L still point to headnode 
		*L = next;
	}

	while (next != NULL ) {
		if (next->data == 0 || next->data == 2 || next->data == 4 || next->data == 6 || next->data == 8 ) {
			current->next = next->next;
			next->next = current;
			if (previous != NULL) {
				previous->next = next;
			}
			previous = next;
			next = current->next;
		}
		else {
			previous = previous->next;
			next = next->next;
			current = current->next;
		}
	}
	return *L;
}


LNode* FindMidNode(LinkedList *L) {
	LinkedList slow = malloc(sizeof(LNode));
	LinkedList fast = malloc(sizeof(LNode));
	slow = *L;
	fast = *L;
	printf("\nHead node is recommanded(If the list length is even, the output may be inaccurate)\n");
	while (fast != NULL) {
		if (fast->next == NULL) {
			fast = NULL;
			return slow;
		}
		else {
			fast = fast->next->next;
		}
		slow = slow->next;
	}
	return slow;
}

Status input(LinkedList *head) {
	Status i = ERROR;
	char j; //input
	int num = 0;
	printf("\n# is end and * is quit(o is looplist mode)\n");

	while ((j = getchar()) != '#' && j != '*' ) {
		LNode* new_node = malloc(sizeof(LNode));
		if (isdigit(j)) {
			num = j - '0';
		}
		else if (num > 0) {
			if ((*head)->data == -22002072 && (*head)->next == NULL) {
				//Input to Headnode, I direactly change it's num instead of
				//insert a new node(Locating headnode by special num)
				(*head)->data = num;
			}
			else {
				if (new_node == NULL) {
					printf("Memory allocation failed,please try again.\n");
					return i;
				}
				new_node->data = num;
				new_node->next = *head;
				*head = new_node;
				num = 0;
			}
		}
		else if (!isspace(j)) {
			//Determine whether it is a space
			if (j == '#' ||j == '*') { break; }
			else {
				if (j == 'o') {
					//It's ok to let this part out of while 
					LNode* right = *head;
					while (right->next != NULL) {
						right = right->next;
					}
					right->next = *head;
					i = SUCCESS;
					return i;
				}
				else {
					printf("ERROR! PLEASE INPUT NUMBER\n");
					input(head);
					return i;
				}
			}
		}
	}	
	
	if (j == '#') {
		if ((*head)->data == -22002072) {
			printf("Illegal Linkedlist!\nPlease try again!\n\n");
			input(head);
		}
		else {
			i = SUCCESS;
			return i; 
		}
	}
	else if (j == '*') {
		DestroyList(head);
		return i;
	}
}

/**
 *  @name        : Status JudgeList(LinkedList head)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node) judge(if it isn't inited truly, judge = ERROR)
 *	@return		 : Status
 *  @notice      : None
 */
Status JudgeList(LinkedList head) {
	Status judge = ERROR;
	if (head->data == -22002072) {
		printf("\nIllegal Linkedlist!\nPlease create it first!\n\n");
	}
	judge = SUCCESS;
	return judge;
}

void print(ElemType e) {
	printf("%d", e);
}

/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : Gets the DATA of the specified node and save it to a new node
 *	@param		 : L, location
 *	@return		 : LNode*
 *  @notice      : None
 */
LNode* GetDataNode(LinkedList L, int location) {
	LNode* node = malloc(sizeof(LNode));
	for (int i = 0; i < location; i++) {
		node->data = L->next->data;
		node->next = NULL;
		if (node == NULL) {
			printf("ERROR!The num is greater than the linkedlist's length\n");
			printf("Return the last node...\n");
			return node; 
		}
	}
	return node;
}

/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : Gets the specified node
 *	@param		 : L, location
 *	@return		 : LNode*
 *  @notice      : None
 */
LNode* GetNode(LinkedList L, int location) {
	LNode* node = malloc(sizeof(LNode));
	for (int i = 0; i < location; i++) {
		node = L->next;
		if (node == NULL) {
			printf("ERROR!The num is greater than the linkedlist's length\n");
			printf("Return the last node...\n");
			return node;
		}
	}
	return node;
}


void main() {
	LinkedList L = malloc(sizeof(LNode));//Create a list
	L->next = NULL;
	char c = '0'; //Option
	int temp = 0,is = 0,bit = 0;
	void (*visit)(ElemType e);
	visit = &printf;
	printf("1.Create and init a list\n");
	printf("2.Destroy the recent list\n");
	printf("3.Insert a number in the recent list\n");
	printf("4.Delete a element\n");
	printf("5.Search the element in the list\n");
	printf("6.Reverse list\n");
	printf("7.Whether it is loop list\n");
	printf("8.Reverse the even num in the list\n");
	printf("9.Find the mid node\n");
	printf("**NOTE:This program has a node created firstly to be a virtual node/headnode**\n\n");
	printf("\n--------------------------------\n");
	printf("Please chose mode(push * to quit):\n");
	while (c != '*') {
		c = getchar();
		is = isdigit(c); //check whether c is num
		bit = sizeof(c); //judge whether c is 1 bit
		if (is != 0 && bit == 1) {
			if (c == '1') {
				InitList(&L);
			}

			if (JudgeList(L) != SUCCESS) {
				printf("Illegal/Empty list!\nPlease create it first!\n\n");
				InitList(&L);
			}

			if (c == '2') {
				JudgeList(L);
				DestroyList(&L);
			}
			if (c == '3') {
				printf("Input the num behind the linkedlist headnode(* to skip and ** to quit):\n");
				
				while (scanf_s("%d", &temp) == 0 && getchar () != '*') {
					printf("Please input number!/n");
				}
				LNode* node = GetNode(L, temp);
				printf("Now input the insertnode's data:\n");
				LNode* insertnode = malloc(sizeof(LNode)); //It'll insert to another node.
				scanf_s("%d", &temp);
				insertnode->data = temp;
				InsertList(node, insertnode);
			}
			if (c == '4') {
				printf("Input the num behind the linkedlist headnode:\n");
				scanf_s("%d", &temp);
				LNode* node = GetNode(L, temp);
				DeleteList(node, &temp);
			}
			if (c == '5') {
				printf("Please input the num that you want to find:(** to exit)\n");
				while (scanf_s("%d", &temp) == 0 && getchar() != '*') {
					printf("Please input number!\n");
				}
				if (getchar() != "*") {
					SearchList(L, temp);
				}
			}
			if (c == '6') {
				ReverseList(&L);
			}
			if (c == '7') {
				IsLoopList(L);
			}
			if (c == '8') {
				ReverseEvenList(&L);
			}
			if (c == '9') {
				printf("The mid num is %d\n", FindMidNode(&L)->data);
			}

		}
		else if (c!='*') { printf("PLEASE INPUT NUMBER(PUSH * TO QUIT)\n"); }
	}

	printf("\n%c\n", c);
	TraverseList(L, print);
}