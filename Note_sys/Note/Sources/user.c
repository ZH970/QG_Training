#include <stdio.h>
#include <stdlib.h>
#include"user.h"

void registerUser(User*px)//�����û��˺� 
{
	int e=1;//���ڳ��ж��˺��Ƿ��ظ���ѭ�� 
	int i;//���ڱ���Ѱ��δע���û���Ϣ�������±� 
	int u=1;//���ڳ���forѭ�� 
	int h=1;//�����ж��Ƿ��˺��ظ� 
	int g;//���ڱ����˺��Ƿ��ظ� 
	for(i=0;u==1;i++)//�������� 
	{
		if(strcmp(px[i].accoumt,"\0")==0)//Ѱ�ҵ�δע���û���Ϣ�������±� (��һ���û���¼�����)
		{
			printf("���ڿ�ʼ������%d�����û�\n",i+1);
			printf("�������û�����");
			scanf("%s",&px[i].name); 
			if(i==0)
			{
				printf("�������˺ţ�");
				scanf("%s",&px[i].accoumt);
				printf("���������룺");
				scanf("%s",&px[i].pass); 
				printf("�������һ��������õ���֤��(��ϲ�����Ķ���)��");
				scanf("%s",&px[i].find);
				printf("�����ɹ���\n");
				printf("����û���Ϊ:%s          ",px[i].name);
				printf("����˺�Ϊ:%s\n",px[i].accoumt);
				printf("�������Ϊ:%s          ",px[i].pass);
				printf("���һ��������õ���֤��(�������)Ϊ:%s\n",px[i].find);
				u=0;//���ڳ���forѭ�� 
			}else//Ѱ�ҵ�δע���û���Ϣ�������±� (�ڶ����������û���¼�����)
			{
				while(e==1)//�ж��Ƿ��˺��ظ� 
				{
					printf("�������˺ţ�");
					scanf("%s",&px[i].accoumt);
					for(g=0;g<i;g++)//�����ж��˺��Ƿ��ظ� 
					{
						h=1;
						if(strcmp(px[i].accoumt,px[g].accoumt)==0)
						{
							printf("�˺��ظ������������룡\n");
							h=0;//�����ж��˺��ظ�
							break;
						}		
					}
					if(h==1)//�û���û�ظ�����ѭ������������� 
					{
						e=0;
					}	
		 		}
				printf("���������룺");
				scanf("%s",&px[i].pass); 
				printf("�������һ��������õ���֤��(�������)��");
				scanf("%s",&px[i].find);
				printf("�����ɹ���\n");
				printf("����û���Ϊ:%s          ",px[i].name);
				printf("����˺�Ϊ:%s\n",px[i].accoumt);
				printf("�������Ϊ:%s          ",px[i].pass);
				printf("���һ��������õ���֤��(�������)Ϊ:%s\n",px[i].find);
				u=0;//u=0������forѭ�� ,ע����� 
			}
		}
	}
}
void loginUser(User*px)//�û���¼ 
{	
	int o=1;//���ڳ���whileѭ�� 
	char r;//����ѡ���Ƿ���������һ� 
	char name1[20];char a[200];char b[200];char c[200];
	while(o==1)
	{
		printf("            ��¼\n");
		printf("�������˺ţ�");
		scanf("%s",&a); 
		printf("���������룺");
		scanf("%s",&b); 
		if(strcmp(px->accoumt,a)==0&&strcmp(px->pass,b)==0)//�жϵ�¼��Ϣ�Ƿ���� 
		{
			printf("��Ϣ��ȷ��\n");
			printf("�ɹ���¼��\n");
			o=0;//o=0���ڳ���whileѭ�� 
		}else//�жϵ�¼��Ϣ������ʱ 
		{
			printf("��Ϣ����\n");
			printf("��¼ʧ�ܣ�\n");
			printf("����'1'���������¼��Ϣ���������������ַ�����������һأ�\n");
			scanf("%c",&r); 
			switch(r)//ѡ�����µ�¼�����޸����� 
			{
				case '1'://���µ�¼ 
					break;
				default://�޸����� 
				 	listfindpass(&px);//�һ�����ĺ����ӿ� 
					printf("���������������¼��Ϣ��\n");
					break;
			}
			
		}
		
	}
}
void listfindpass(User**px)//�һ����� 
{
	char k[200];char a[200];char b[200];int c=1;
	while(c==1)
	{
		printf("         ��֤��Ϣ\n");
		printf("����������˺ţ�");
		scanf("%s",&a);
		while (getchar()!='\n'); 
		printf("������������գ�");
		scanf("%s",&k);
		while (getchar()!='\n');
		if(strcmp((*px)->find,k)==0&&strcmp((*px)->accoumt,a)==0)//��֤��Ϣ��ȷʱ 
		{	
			printf("�˺���ȷ!\n");
			printf("��֤����ȷ��\n");
			printf("����������Ҫ��������:");
			scanf("%s",&(*px)->pass);
			printf("�����޸ĳɹ���\n");	
			c=0;//���ڳ�whileѭ�� 
		}else//��֤��Ϣ������ʱ 
		{
			printf("��֤��Ϣ����\n");
			printf("���������������֤��Ϣ\n");	
		}
   }
}
void quit()
{
	exit(0);
}
