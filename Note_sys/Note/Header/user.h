#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<windows.h>


typedef struct User 
{
	char accoumt[200];//账号
	char pass[200];//密码 
	char name[200];//用户名 
	char find[200];//找回密码问题 		
//	OR order; //订单
//	float money;//资金 
//	OR foot;//足迹 
 }User; 
 
 
void registerUser(User*px);
void loginUser(User*px);
void listfindpass(User**px);
void quit(); 

