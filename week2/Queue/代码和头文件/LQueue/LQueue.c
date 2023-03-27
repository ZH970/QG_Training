#include "../head/LQueue.h" 
#include <stdio.h>
#include <stdlib.h>

/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitLQueue(LQueue* Q){
	Q->front = NULL;
	Q->rear = NULL;
	Q->length = 0;
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q){
	Node* temp = Q->front;
	while (Q->front != NULL) {
		Q->front = Q->front->next;
		__vcrt_free_normal(temp);
		temp = Q->front;
	}
	Q->rear = NULL;
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q){
	if (Q->front == NULL && Q->rear == NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadLQueue(LQueue *Q, void *e){
	if (type == 'i') {
		(int*)e = Q->front->data;
	}
	else if (type == 'f') {
		(float*)e = Q->front->data;
	}
	else if (type == 'c') {
		(char*)e = Q->front->data;
	}
	return TRUE;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q){
	int length=1;
	Node* temp = Q->front;
	while (temp->next != NULL) {
		length += 1;
		temp = temp->next;
	}
	return length;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
 */
Status EnLQueue(LQueue *Q, void *data){
	Node* node = (Node*)malloc(sizeof(Node));
	
	if (!node) {
		return FALSE;
	}
	
	node->data = data;
	node->next = NULL;
	if (Q->front == NULL && Q->rear == NULL) {
		Q->front = node;
		Q->rear = node;
		return TRUE;
	}
	else {
		node->data = data;
		node->next = NULL;
		Q->rear->next = node;
		Q->rear = Q->rear->next;
		return TRUE;
	}
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q){
	if (Q->front == NULL && Q->rear == NULL) {
		//Firstly judge whether the queue is empty
		return FALSE;
	}
	else if (Q->front == Q->rear) {
		Node* temp = Q->front;
		Q->front = NULL;
		Q->rear = NULL;
		free(temp);
	}
	else {
		Node* temp = Q->front;
		Q->front = Q->front->next;
		free(temp);
	}
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q){
	while(Q->front != Q->rear) {
		DeLQueue(Q);
	}
	free(Q->rear);
	Q->front = NULL;
	Q->rear = NULL;
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q)){
	printf("\nIt will start from the L's position.\n");
	printf("Head node is recommanded\n");
	Node* temp = Q->front;
	void* q;
	if (Q != NULL) {
		while (temp != NULL) {
			q = temp->data;
			foo(q);
			temp = temp->next;
		}
	}
	else {
		printf("Don't input Nullptr!");
		return FALSE;
	}
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 
 *  @notice      : None
 */
void LPrint(void *q){
	if (type == 'i') {
		printf("%d\n", *(int*)q);
	}
	else if(type == 'f') {
		printf("%f\n", *(float*)q);
	}
	else if (type == 'c') {
		printf("%c\n", *(char*)q);
	}
}


void gettype() {
	printf("Please give me what kind of the data you want to keep:\n");
	printf("'i' means int, 'f' means float while 'c' means char!\n");
	scanf_s("%c", &type);
	while (type != 'i' && type != 'f' && type != 'c') {
		printf("Please input i/f/c\n");
		scanf_s("%c", &type,50);
	}
}

void gi(void** data) {
	//Get int
	int* i = malloc(sizeof(int));
	printf("Input Number:");
	scanf_s("%d", i, 50);
	*data = (void*)i;
}

void gc(void** data) {
	//Get char
	char c = malloc(sizeof(char));
	printf("Input char:");
	scanf_s("%c", c, 50);
	*data = (void*)c;
}

void gf(void** data) {
	//Get float
	float* f = malloc(sizeof(float));
	printf("Input float:");
	scanf_s("f", f, 50);
	*data = f;
}

void show(LQueue* q) {
	char flag = "0";
	int is = 0, bit = 0;
	void* data = NULL;
	void* e = NULL;
	printf("\n1.Create a queue\n");
	printf("2.Destry this queue\n");
	printf("3.See the head element\n");
	printf("4.Get the Length of queue\n");
	printf("5.Add a node to Queue\n");
	printf("6.Delete a node in Queue\n");
	printf("7.Clear the queue\n");
	printf("8.Print the queue\n");
	printf("9.Check whether the queue empty or not\n");
	printf("\n-----------------------\n");
	printf("Now please give me the number to finish the function(* to exit):\n");
	
	while (1) {
		int* num = malloc(sizeof(int));
		char* ch = malloc(sizeof(char));
		float* flo = malloc(sizeof(float));
		flag = getchar();
		is = isdigit(flag); //check whether c is num
		if (flag == '*') { is = 1; }
		bit = sizeof(flag); //judge whether c is 1 bit
		if (is != 0 && bit == 1) {
			if (flag == '1') {
				gettype();
				if (type == 'i') {
					data = (void*)malloc(sizeof(int));
					printf("Please input number in new node\n");
					scanf_s("%d", num);
					data = num;
				}
				else if (type == 'f') {
					data = (void*)malloc(sizeof(float));
					printf("Please input float in new node\n");
					scanf_s("%f", flo);
					data = flo;
				}
				else if (type == 'c') {
					data = (void*)malloc(sizeof(char));
					printf("Please input char in new node\n");
					scanf_s("%c", ch);
					data = ch;
				}

				EnLQueue(q, data);
			}
			else if (flag == '2') {
				if (IsEmptyLQueue(q) == TRUE) {
					printf("Please create queue firstly\n");
				}
				else {
					DestoryLQueue(q);
				}
			}
			else if (flag == '3') {
				if (IsEmptyLQueue(q) == TRUE) {
					printf("Please create queue firstly\n");
				}
				else {

					GetHeadLQueue(q, e);
					LPrint(e);
				}
			}
			else if (flag == '4') {
				if (IsEmptyLQueue(q) == TRUE) {
					printf("Please create queue firstly\n");
				}
				else {
					printf("This queue's length is %d\n", LengthLQueue(q));
				}
			}
			else if (flag == '5') {
				gettype();
				if (type == 'i') {
					data = (void*)malloc(sizeof(int));
					printf("Please input number in new node\n");
					scanf_s("%d", num);
					data = num;
				}
				else if (type == 'f') {
					data = (void*)malloc(sizeof(float));
					scanf_s("%f", flo);
					data = flo;
				}
				else if (type == 'c') {
					data = (void*)malloc(sizeof(char));
					scanf_s("%c", ch);
					data = ch;
				}

				EnLQueue(q, data);

			}
			else if (flag == '6') {
				if (IsEmptyLQueue(q) == TRUE) {
					printf("Please create queue firstly\n");
				}
				else {
					DeLQueue(q);
				}

			}
			else if (flag == '7') {
				ClearLQueue(q);
			}
			else if (flag == '8') {
				TraverseLQueue(q, LPrint);
			}
			else if (flag == '9') {
				if (IsEmptyLQueue(q) == TRUE) {
					printf("Empty\n");
				}
				else {
					printf("Isn't Empty\n");
				}
			}
			else if (flag == '*') {
				break;
			}
		}
		else {
			printf("Please input number\n");
		}
	}
}

void main() {
	char type = '0';
	LQueue* q = malloc(sizeof(LQueue));
	InitLQueue(q);
	show(q);
}
