#define _CRT_SECURE_NO_WARNINGS 1
#include"ui.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "user.h"
#include "note.h"
#include "folder.h"
#include "tag.h"

//char*qiu(char*c)
//{
//	
//	
//}

Folder* root;
Folder* currentFolder;
char* creater;
char* noteTitle;
User* user;



//ʶ���û������ָ�ִ����Ӧ�Ĺ���
void input(char* command)
{
	char c[4][200];
	char* t;

	if (strstr(command, " "))
	{
		if (strstr(command, "grep"))
		{
			t = strtok(command, " ");
			strcpy(c[0], t);
			while (t != NULL)
			{
				t = strtok(NULL, " ");
				if (strstr(t, "-"))
				{
					strcpy(c[0], strcat(c[0], t));
					t = strtok(NULL, " ");
					strcpy(c[1], t);
					t = strtok(NULL, " ");
					strcpy(c[2], t);
					t = strtok(NULL, " ");
					strcpy(c[3], t);
				}
				else
				{
					strcpy(c[1], t);
					t = strtok(NULL, " ");
					strcpy(c[2], t);
					t = strtok(NULL, " ");
					strcpy(c[3], t);
				}
				break;
			}
			if (strcmp("grep", c[2]) == 0)
			{

				if (strcmp(searchNoteByName(c[1], c[3]), "SUCCESS") == 0)//��ʾ����ָ���ļ������еĴ����������ݵıʼ��ļ�.oooooooo
				{
					printf("�ɹ���\n");
				}
				else {
					printf("ʧ�ܣ�\n");
				}

			}
		}
		else
		{
			t = strtok(command, " ");
			strcpy(c[0], t);
			while (t != NULL)
			{
				t = strtok(NULL, " ");
				strcpy(c[1], t);
				t = strtok(NULL, " ");
				strcpy(c[2], t);
				break;
			}
			//if (strcmp("ls", c[0]) == 0)
			//{
			//	if (strcmp(showFoldersInDirectory(c[1]), "SUCCESS") == 0)//��ʾ����ָ���ļ������е��ļ���ooooooooo
			//	{
			//		printf("�ɹ���\n");
			//	}
			//	else {
			//		printf("ʧ�ܣ�\n");
			//	}
			//}
			//else 
			if (strcmp("cd", c[0]) == 0)
			{

				if (strcmp(moveDirectory(root, c[1]), "SUCCESS") == 0)//��·���л�Ϊ������������ļ���·��ooooooooooo
				{
					printf("�ɹ���\n");
				}
				else {
					printf("ʧ�ܣ�\n");
				}
			}
			else if (strcmp("mv", c[1]) == 0)
			{
				if (strstr(c[3], "'\'"))
				{
					if (strcmp(moveNoteToFolder(c[1], c[2], root), "SUCCESS") == 0)//��ָ���ıʼ��ļ����ƶ���Ŀ���ļ���Ŀ¼��.ooo!!!!
					{
						printf("�ɹ���\n");
					}
					else {
						printf("ʧ�ܣ�\n");
					}
				}
				else
				{
					if (strcmp(renameNote(c[1], c[2]), "SUCCESS") == 0)// �������ļ���.ooooooooooo
					{
						printf("�ɹ���\n");
					}
					else {
						printf("ʧ�ܣ�\n");
					}
				}
			}
			else if (strcmp("mv-r", c[0]) == 0)
			{

				if (strcmp(moveFolder(root, c[1], c[2]), "SUCCESS") == 0)//�ƶ��ļ��� !!!!!
				{
					printf("�ɹ���\n");
				}
				else {
					printf("ʧ�ܣ�\n");
				}
			}
			else if (strcmp("rm", c[0]) == 0)
			{
				if (strcmp(deleteNoteFromFolder(currentFolder, c[1]), "SUCCESS") == 0)// ɾ���ʼ��ļ���.ooo
				{
					printf("�ɹ���\n");
				}
				else {
					printf("ʧ�ܣ�\n");
				}
			}
			else if (strcmp("rm-r", c[0]) == 0)
			{

				if (strcmp(deleteNote(c[1]), "SUCCESS") == 0)// ��ָ���ʼ��ļ�����ɾ��.oooooooooooo
				{
					printf("�ɹ���\n");
				}
				else {
					printf("ʧ�ܣ�\n");
				}
			}
			else if (strcmp("tag", c[0]) == 0)
			{
				if (strstr(c[1], "'\'"))
				{
					if (strcmp(viewTagsInFolder(c[1]), "SUCCESS") == 0)//��ʾָ���ļ��еı�ǩooooooooo
					{
						printf("�ɹ���\n");
					}
					else {
						printf("ʧ�ܣ�\n");
					}
				}
				else
				{
					if (strcmp(viewTag(c[1]), "SUCCESS") == 0)//��ʾָ���ʼǵı�ǩooooooo
					{
						printf("�ɹ���\n");
					}
					else {
						printf("ʧ�ܣ�\n");
					}
				}
			}
			else if (strcmp("tag-add", c[0]) == 0)
			{
				if (strstr(c[1], "'\'"))
				{
					if (strcmp(addTagToFolder(c[1], c[2]), "SUCCESS") == 0)//����ļ��еı�ǩoooooooo
					{
						printf("�ɹ���\n");
					}
					else {
						printf("ʧ�ܣ�\n");
					}
				}
				else
				{
					if (strcmp(addTagToNote(c[1], c[2]), "SUCCESS") == 0)//��ӱʼǵı�ǩooooooo
					{
						printf("�ɹ���\n");
					}
					else {
						printf("ʧ�ܣ�\n");
					}
				}
			}
			else if (strcmp("tag-del", c[0]) == 0)
			{
				if (strstr(c[1], "'\'"))
				{
					if (strcmp(deleteTagFromFolder(c[1], c[2]), "SUCCESS") == 0)//ɾ��ָ���ļ��е�ָ����ǩ��ooooooooo
					{
						printf("�ɹ���\n");
					}
					else {
						printf("ʧ�ܣ�\n");
					}
				}
				else
				{
					if (strcmp(deleteTagFromNote(c[1], c[2]), "SUCCESS") == 0)//ɾ��ָ���ʼǵ�ָ����ǩ��oooooooooo
					{
						printf("�ɹ���\n");
					}
					else {
						printf("ʧ�ܣ�\n");
					}
				}
			}
			else if (strcmp("tag-s", c[0]) == 0)
			{
				if (strcmp(searchNotesInFolderByTag(c[1], c[2]), "SUCCESS") == 0)	//���ݱ�ǩ���ݣ��ڵ�ǰĿ¼�½��бʼ����������ƥ��ı�ǩ����Ӧ�ıʼ��ļ�����ooooo
				{
					printf("�ɹ���\n");
				}
				else {
					printf("ʧ�ܣ�\n");
				}
			}
			else if (strcmp("tag-sa", c[0]) == 0)
			{
				if (strcmp(searchNotesByTag(c[1]), "SUCCESS") == 0)//���ݱ�ǩ���ݣ������бʼǽ������������ƥ��ı�ǩ����Ӧ�ıʼǵ��ļ����Լ�����·��ooooooooooo
				{
					printf("�ɹ���\n");
				}
				else {
					printf("ʧ�ܣ�\n");
				}
			}
			else if (strcmp("mkdir", c[0]) == 0)
			{
				addNewNoteToFolder(currentFolder, creater, noteTitle);////�ڵ�ǰ�ļ��д����±ʼ��ļ�����Ӧmkdir <�ʼ��ļ���>oo
			}
			else if (strcmp("mkdir-r", c[0]) == 0)
			{
				addNewNoteToFolder(currentFolder, creater, noteTitle);//�����ʼ��ļ��С�oo	
			}
			else if (strcmp("sort", c[0]) == 0)
			{
				if (strcmp(sortNotesInFolder(c[1]), "SUCCESS") == 0)//��ָ���ļ����ڵıʼ��ļ����ļ�������ĸ��������ooooooooo
				{
					printf("�ɹ���\n");
				}
				else {
					printf("ʧ�ܣ�\n");
				}
			}
		}
	}
	else {
		strcpy(c[0], command);
		if (strcmp("ls", c[0]) == 0)
		{
			if (showFolders(root->path, 0))//��ʾ��ǰĿ¼�����еıʼǱ��ļ���.oooooooooooo
			{
				printf("�ɹ���\n");
			}
			else {
				printf("ʧ�ܣ�\n");
			}
		}
		else if (strcmp("cd", c[0]) == 0)
		{

			if (strcmp(moveUpDirectory(currentFolder), "SUCCESS") == 0)//��·���л�Ϊ��ǰĿ¼�ĸ�Ŀ¼. ���Ǹ�Ŀ¼���򲻽����л�
			{
				printf("�ɹ���\n");
			}
			else {
				printf("ʧ�ܣ�\n");
			}
		}
		else if (strcmp("ls-a", c[0]) == 0)
		{
			if (showFolderTree(root->path, 0))//������״�ṹ��ʾ���еıʼ��ļ���oooooooooo
			{
				printf("�ɹ���\n");
			}
			else {
				printf("ʧ�ܣ�\n");
			}
		}

	}



}

//��¼ע�����
void loginScreen()
{
	char r;
	printf("ע������'1',��¼���������ַ�\n");
	scanf("%c", &r);
	switch (r)//ѡ�����µ�¼�����޸����� 
	{
	case '1'://ע�� 
		registerUser(user);
		break;
	default://��¼
		loginUser(user);
		break;
	}
	system("cls");
}

//������
void mainScreen()
{
	printf("{project}/Note/md");

}
