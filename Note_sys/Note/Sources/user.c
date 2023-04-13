#include <stdio.h>
#include <stdlib.h>
#include"user.h"

void registerUser(User*px)//创建用户账号 
{
	int e=1;//用于出判断账号是否重复的循环 
	int i;//用于遍历寻找未注册用户信息的数组下标 
	int u=1;//用于出大for循环 
	int h=1;//用于判断是否账号重复 
	int g;//用于遍历账号是否重复 
	for(i=0;u==1;i++)//遍历数组 
	{
		if(strcmp(px[i].accoumt,"\0")==0)//寻找到未注册用户信息的数组下标 (第一个用户登录的情况)
		{
			printf("现在开始创建第%d名新用户\n",i+1);
			printf("请输入用户名：");
			scanf("%s",&px[i].name); 
			if(i==0)
			{
				printf("请输入账号：");
				scanf("%s",&px[i].accoumt);
				printf("请输入密码：");
				scanf("%s",&px[i].pass); 
				printf("请输入找回密码所用的验证码(你喜欢看的动漫)：");
				scanf("%s",&px[i].find);
				printf("创建成功！\n");
				printf("你的用户名为:%s          ",px[i].name);
				printf("你的账号为:%s\n",px[i].accoumt);
				printf("你的密码为:%s          ",px[i].pass);
				printf("你找回密码所用的验证码(你的生日)为:%s\n",px[i].find);
				u=0;//用于出大for循环 
			}else//寻找到未注册用户信息的数组下标 (第二个及以上用户登录的情况)
			{
				while(e==1)//判断是否账号重复 
				{
					printf("请输入账号：");
					scanf("%s",&px[i].accoumt);
					for(g=0;g<i;g++)//遍历判断账号是否重复 
					{
						h=1;
						if(strcmp(px[i].accoumt,px[g].accoumt)==0)
						{
							printf("账号重复，请重新输入！\n");
							h=0;//用于判断账号重复
							break;
						}		
					}
					if(h==1)//用户名没重复，出循环进行下面操作 
					{
						e=0;
					}	
		 		}
				printf("请输入密码：");
				scanf("%s",&px[i].pass); 
				printf("请输入找回密码所用的验证码(你的生日)：");
				scanf("%s",&px[i].find);
				printf("创建成功！\n");
				printf("你的用户名为:%s          ",px[i].name);
				printf("你的账号为:%s\n",px[i].accoumt);
				printf("你的密码为:%s          ",px[i].pass);
				printf("你找回密码所用的验证码(你的生日)为:%s\n",px[i].find);
				u=0;//u=0，出大for循环 ,注册结束 
			}
		}
	}
}
void loginUser(User*px)//用户登录 
{	
	int o=1;//用于出大while循环 
	char r;//用于选择是否进行密码找回 
	char name1[20];char a[200];char b[200];char c[200];
	while(o==1)
	{
		printf("            登录\n");
		printf("请输入账号：");
		scanf("%s",&a); 
		printf("请输入密码：");
		scanf("%s",&b); 
		if(strcmp(px->accoumt,a)==0&&strcmp(px->pass,b)==0)//判断登录信息是否成立 
		{
			printf("信息正确！\n");
			printf("成功登录！\n");
			o=0;//o=0用于出大while循环 
		}else//判断登录信息不成立时 
		{
			printf("信息错误！\n");
			printf("登录失败！\n");
			printf("输入'1'重新输入登录信息！或者输入任意字符进行密码的找回！\n");
			scanf("%c",&r); 
			switch(r)//选择重新登录或者修改密码 
			{
				case '1'://重新登录 
					break;
				default://修改密码 
				 	listfindpass(&px);//找回密码的函数接口 
					printf("现在请重新输入登录信息！\n");
					break;
			}
			
		}
		
	}
}
void listfindpass(User**px)//找回密码 
{
	char k[200];char a[200];char b[200];int c=1;
	while(c==1)
	{
		printf("         验证信息\n");
		printf("请输入你的账号：");
		scanf("%s",&a);
		while (getchar()!='\n'); 
		printf("请输入你的生日：");
		scanf("%s",&k);
		while (getchar()!='\n');
		if(strcmp((*px)->find,k)==0&&strcmp((*px)->accoumt,a)==0)//验证信息正确时 
		{	
			printf("账号正确!\n");
			printf("验证码正确！\n");
			printf("请输入你想要的新密码:");
			scanf("%s",&(*px)->pass);
			printf("密码修改成功！\n");	
			c=0;//用于出while循环 
		}else//验证信息不成立时 
		{
			printf("验证信息错误！\n");
			printf("请重新输入你的验证信息\n");	
		}
   }
}
void quit()
{
	exit(0);
}
