#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<windows.h>


typedef struct User 
{
	char accoumt[200];//�˺�
	char pass[200];//���� 
	char name[200];//�û��� 
	char find[200];//�һ��������� 		
//	OR order; //����
//	float money;//�ʽ� 
//	OR foot;//�㼣 
 }User; 
 
 
void registerUser(User*px);
void loginUser(User*px);
void listfindpass(User**px);
void quit(); 

