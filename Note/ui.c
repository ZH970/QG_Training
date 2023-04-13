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



//识别用户输入的指令并执行相应的功能
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

				if (strcmp(searchNoteByName(c[1], c[3]), "SUCCESS") == 0)//显示命令指定文件下所有的带有搜索内容的笔记文件.oooooooo
				{
					printf("成功！\n");
				}
				else {
					printf("失败！\n");
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
			//	if (strcmp(showFoldersInDirectory(c[1]), "SUCCESS") == 0)//显示命令指定文件下所有的文件夹ooooooooo
			//	{
			//		printf("成功！\n");
			//	}
			//	else {
			//		printf("失败！\n");
			//	}
			//}
			//else 
			if (strcmp("cd", c[0]) == 0)
			{

				if (strcmp(moveDirectory(root, c[1]), "SUCCESS") == 0)//将路径切换为命令中输入的文件夹路径ooooooooooo
				{
					printf("成功！\n");
				}
				else {
					printf("失败！\n");
				}
			}
			else if (strcmp("mv", c[1]) == 0)
			{
				if (strstr(c[3], "'\'"))
				{
					if (strcmp(moveNoteToFolder(c[1], c[2], root), "SUCCESS") == 0)//将指定的笔记文件夹移动到目标文件夹目录下.ooo!!!!
					{
						printf("成功！\n");
					}
					else {
						printf("失败！\n");
					}
				}
				else
				{
					if (strcmp(renameNote(c[1], c[2]), "SUCCESS") == 0)// 重命名文件夹.ooooooooooo
					{
						printf("成功！\n");
					}
					else {
						printf("失败！\n");
					}
				}
			}
			else if (strcmp("mv-r", c[0]) == 0)
			{

				if (strcmp(moveFolder(root, c[1], c[2]), "SUCCESS") == 0)//移动文件夹 !!!!!
				{
					printf("成功！\n");
				}
				else {
					printf("失败！\n");
				}
			}
			else if (strcmp("rm", c[0]) == 0)
			{
				if (strcmp(deleteNoteFromFolder(currentFolder, c[1]), "SUCCESS") == 0)// 删除笔记文件名.ooo
				{
					printf("成功！\n");
				}
				else {
					printf("失败！\n");
				}
			}
			else if (strcmp("rm-r", c[0]) == 0)
			{

				if (strcmp(deleteNote(c[1]), "SUCCESS") == 0)// 对指定笔记文件进行删除.oooooooooooo
				{
					printf("成功！\n");
				}
				else {
					printf("失败！\n");
				}
			}
			else if (strcmp("tag", c[0]) == 0)
			{
				if (strstr(c[1], "'\'"))
				{
					if (strcmp(viewTagsInFolder(c[1]), "SUCCESS") == 0)//显示指定文件夹的标签ooooooooo
					{
						printf("成功！\n");
					}
					else {
						printf("失败！\n");
					}
				}
				else
				{
					if (strcmp(viewTag(c[1]), "SUCCESS") == 0)//显示指定笔记的标签ooooooo
					{
						printf("成功！\n");
					}
					else {
						printf("失败！\n");
					}
				}
			}
			else if (strcmp("tag-add", c[0]) == 0)
			{
				if (strstr(c[1], "'\'"))
				{
					if (strcmp(addTagToFolder(c[1], c[2]), "SUCCESS") == 0)//添加文件夹的标签oooooooo
					{
						printf("成功！\n");
					}
					else {
						printf("失败！\n");
					}
				}
				else
				{
					if (strcmp(addTagToNote(c[1], c[2]), "SUCCESS") == 0)//添加笔记的标签ooooooo
					{
						printf("成功！\n");
					}
					else {
						printf("失败！\n");
					}
				}
			}
			else if (strcmp("tag-del", c[0]) == 0)
			{
				if (strstr(c[1], "'\'"))
				{
					if (strcmp(deleteTagFromFolder(c[1], c[2]), "SUCCESS") == 0)//删除指定文件夹的指定标签。ooooooooo
					{
						printf("成功！\n");
					}
					else {
						printf("失败！\n");
					}
				}
				else
				{
					if (strcmp(deleteTagFromNote(c[1], c[2]), "SUCCESS") == 0)//删除指定笔记的指定标签。oooooooooo
					{
						printf("成功！\n");
					}
					else {
						printf("失败！\n");
					}
				}
			}
			else if (strcmp("tag-s", c[0]) == 0)
			{
				if (strcmp(searchNotesInFolderByTag(c[1], c[2]), "SUCCESS") == 0)	//根据标签内容，在当前目录下进行笔记搜索，输出匹配的标签所对应的笔记文件名。ooooo
				{
					printf("成功！\n");
				}
				else {
					printf("失败！\n");
				}
			}
			else if (strcmp("tag-sa", c[0]) == 0)
			{
				if (strcmp(searchNotesByTag(c[1]), "SUCCESS") == 0)//根据标签内容，对所有笔记进行搜索，输出匹配的标签所对应的笔记的文件名以及绝对路径ooooooooooo
				{
					printf("成功！\n");
				}
				else {
					printf("失败！\n");
				}
			}
			else if (strcmp("mkdir", c[0]) == 0)
			{
				addNewNoteToFolder(currentFolder, creater, noteTitle);////在当前文件夹创建新笔记文件，对应mkdir <笔记文件名>oo
			}
			else if (strcmp("mkdir-r", c[0]) == 0)
			{
				addNewNoteToFolder(currentFolder, creater, noteTitle);//创建笔记文件夹。oo	
			}
			else if (strcmp("sort", c[0]) == 0)
			{
				if (strcmp(sortNotesInFolder(c[1]), "SUCCESS") == 0)//对指定文件夹内的笔记文件按文件名首字母进行排序。ooooooooo
				{
					printf("成功！\n");
				}
				else {
					printf("失败！\n");
				}
			}
		}
	}
	else {
		strcpy(c[0], command);
		if (strcmp("ls", c[0]) == 0)
		{
			if (showFolders(root->path, 0))//显示当前目录下所有的笔记本文件夹.oooooooooooo
			{
				printf("成功！\n");
			}
			else {
				printf("失败！\n");
			}
		}
		else if (strcmp("cd", c[0]) == 0)
		{

			if (strcmp(moveUpDirectory(currentFolder), "SUCCESS") == 0)//将路径切换为当前目录的父目录. 若是根目录则则不进行切换
			{
				printf("成功！\n");
			}
			else {
				printf("失败！\n");
			}
		}
		else if (strcmp("ls-a", c[0]) == 0)
		{
			if (showFolderTree(root->path, 0))//按照树状结构显示所有的笔记文件夹oooooooooo
			{
				printf("成功！\n");
			}
			else {
				printf("失败！\n");
			}
		}

	}



}

//登录注册界面
void loginScreen()
{
	char r;
	printf("注册输入'1',登录输入任意字符\n");
	scanf("%c", &r);
	switch (r)//选择重新登录或者修改密码 
	{
	case '1'://注册 
		registerUser(user);
		break;
	default://登录
		loginUser(user);
		break;
	}
	system("cls");
}

//主界面
void mainScreen()
{
	printf("{project}/Note/md");

}
