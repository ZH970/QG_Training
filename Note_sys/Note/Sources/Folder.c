#define _CRT_SECURE_NO_WARNINGS
#include "../Header/Folder.h"
#include <sys/types.h> 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include <io.h>

Folder* root;

Status showFolders(char* path, int depth) {
	// 打开目录
	HANDLE hFind;
	WIN32_FIND_DATAA findData;
	char pattern[MAX_PATH];
	sprintf_s(pattern, sizeof(pattern), "%s\\*", path);
	hFind = FindFirstFileA(pattern, &findData);

	// 检查是否打开成功
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("Error opening directory %s\n", path);
		return ERROR;
	}

	// 遍历目录中的所有文件和子目录
	do {
		// 跳过.和..两个特殊的目录
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) {
			continue;
		}

		// 打印文件名
		printf("%s\n", findData.cFileName);

		// 如果是一个子目录，递归调用自己
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			char subpath[MAX_PATH];
			sprintf_s(subpath, sizeof(subpath), "%s\\%s", path, findData.cFileName);
			showFolders(subpath, depth + 1);
		}
	} while (FindNextFileA(hFind, &findData));

	// 关闭目录
	FindClose(hFind);
	return SUCCESS;
}

// 一个辅助函数，用于打印缩进
void print_indent(int depth) {
	for (int i = 0; i < depth; i++) {
		printf(" |-");
	}
}


/*
description: 一个递归函数，用于遍历目录并打印文件树
path: 要遍历的目录
depth: 当前目录的深度，用于打印缩进
*/
Status showFolderTree(char* path, int depth) {
	// 打开目录
	HANDLE hFind;
	WIN32_FIND_DATAA findData;
	char pattern[MAX_PATH];
	sprintf_s(pattern,sizeof(pattern), "%s\\*", path);
	hFind = FindFirstFileA(pattern, &findData);

	// 检查是否打开成功
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("Error opening directory %s\n", path);
		return ERROR;
	}

	// 遍历目录中的所有文件和子目录
	do {
		// 跳过.和..两个特殊的目录
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) {
			continue;
		}

		// 打印缩进和文件名
		print_indent(depth);
		printf("%s\n", findData.cFileName);

		// 如果是一个子目录，递归调用自己
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			char subpath[MAX_PATH];
			sprintf_s(subpath,sizeof(subpath), "%s\\%s", path, findData.cFileName);
			showFolderTree(subpath, depth + 1);
		}
	} while (FindNextFileA(hFind, &findData));

	// 关闭目录
	FindClose(hFind);
	return SUCCESS;
}

////定义一个树节点的结构
//typedef struct Folder {
//    char* name; //文件夹的名称
//    struct Folder** children; //子节点的列表
//    int size; //子节点的个数
//} Folder;

//创建一个树节点，并分配内存
Folder* createTreeNode(char* name, char* path) {
	Folder* node = (Folder*)malloc(sizeof(Folder));
	strcpy(node->name, name);
	node->child = NULL;
	node->parent = NULL;
	node->sibling = NULL;
	node->path = path;
	return node;
}

////向一个树节点添加一个子节点，并分配内存
//void addChild(Folder* parent, Folder* child) {
//    parent->child = child;
//    parent->children[parent->size - 1] = child;
//}

//自定义的函数，用于读取指定路径下的所有文件夹，并把它们储存为树
Folder* readFolders(char* path) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	//设置要搜索的文件名模式
	char pattern[MAX_PATH];
	sprintf_s(pattern, sizeof(pattern), "%s\\*", path);
	//调用FindFirstFile函数
	hFind = FindFirstFileA(pattern, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return NULL;
	}
	//创建一个树节点，表示当前路径
	Folder* node = createTreeNode("node", path);
	//循环调用FindNextFile函数
	do {
		//判断找到的是否是一个文件夹
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			//忽略"."和".."这两个特殊的文件夹
			if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0) {
				continue;
			}
			//拼接子文件夹的完整路径
			char subpath[MAX_PATH];
			/*strcpy(subpath, path);
			strcat(subpath, "\\");
			strcat(subpath, FindFileData.cFileName);*/
			sprintf(subpath, "%s\\%ws", path, FindFileData.cFileName);
			//递归地调用自定义函数，获取子文件夹下的所有文件夹，并作为子节点添加到当前节点
			//addChild(root, readFolders(subpath));
			node->child = readFolders(subpath);
			node->child->parent = node;
		}
		//如果不是一个文件夹，忽略该项目
	} while (FindNextFile(hFind, &FindFileData));
	//检查是否到达搜索结束或发生错误
	if (GetLastError() != ERROR_NO_MORE_FILES) {
		printf("FindNextFile failed (%d)\n", GetLastError());
		return NULL;
	}
	//关闭搜索句柄
	FindClose(hFind);
	//返回根节点
	return node;
}

Folder* searchTree(char* path) {
	Folder* current = root->child; //表示在树的哪一层
	Folder* cur_sib = current; // cur_sib用来记录当前节点的兄弟节点层次的遍历
	while (current != NULL) { //循环直到找到匹配的文件夹或者到达末尾

		while (cur_sib->path != path) {
			cur_sib = cur_sib->sibling;
			if (cur_sib == NULL) {
				current = current->child;
				cur_sib = current;
				continue;
			}
			if (strcmp(cur_sib->path, path) == 0) {
				return cur_sib;
			}
		}
	}
}


Folder* createFolder (char* name, char* path) {
	if (root == NULL || path == NULL || name == NULL) return;

	else {
		char p[MAX_PATH];
		int len = strlen(path);
		char* a = path + len - 2;
		if (_access(path, 0) == 0) {
			if (strcmp(a, "md") == 0) { //判断路径是否以反斜杠结尾
				printf("该路径是根目录。\n");
				sprintf(&p, "%s\\%s", path, name); //拼接路径
				if (_mkdir(&p) == -1) {
					return NULL;
				}

				Folder* new_folder = (Folder*)malloc(sizeof(Folder));
				strcpy(new_folder->name, name); //复制文件夹名
				new_folder->path = (char*)malloc(strlen(path) + strlen(name) + 2); //分配路径空间
				//sprintf(new_folder->path, "%s\\%s", path, name); //拼接路径
				strcpy(new_folder->path, &p);
				new_folder->parent = root; //设置父节点为根节点
				new_folder->child = NULL; //设置子节点为空
				new_folder->sibling = root->child; //设置兄弟节点为原来的第一个子节点
				root->child = new_folder; //设置新文件夹为第一个子节点
				printf("Create folder Success\n");
				return new_folder;
			}
			else {
				searchTree(path);
				////char* first = strtok(path, "\\"); //用反斜杠分割路径
				//Folder* current = root->child; //从根节点的第一个子节点开始遍历
				//Folder* cur_sib = current; // cur_sib用来记录当前节点的兄弟节点层次的遍历
				//while (current != NULL) { //循环直到找到匹配的文件夹或者到达末尾
				//	if (strcmp(current->path, path) != 0) { //如果找到匹配的路径
				//		
				//		while (cur_sib->path != p) {
				//			cur_sib = cur_sib->sibling;
				//			if (cur_sib == NULL) {
				//				break;
				//			}
				//		}
				//		current = current->child;

				//		createFolder(current, rest, name); //递归调用函数，在匹配的文件夹下创建新文件夹
				return NULL;
			
					//else {
					//	Folder* new_folder = (Folder*)malloc(sizeof(Folder));
					//	strcpy(new_folder->name, name); //复制文件夹名
					//	new_folder->path = (char*)malloc(strlen(path) + strlen(name) + 2); //分配路径空间
					//	sprintf(new_folder->path, "%s\\%s", path, name); //拼接路径
					//	new_folder->parent = current; //设置父节点为当前节点
					//	new_folder->child = NULL; //设置子节点为空
					//	new_folder->sibling = current->child; //设置兄弟节点为原来的第一个子节点
					//	current->child = new_folder; //设置新文件夹为第一个子节点
					//}

				}
		}
		else {
			printf("路径不存在。\n");
			return NULL;
		}
		
	}
}


int main() {
	char curdir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, curdir);
	printf("Current directory: %s\n", curdir);
	showFolderTree(curdir, 0);
	printf("\n");
	showFolders(curdir, 0);
	root = readFolders(strcat(curdir, "\\md"));

	createFolder("test", "J:\\Programing\\C\\QG_Training\\Note_sys\\Note\\md\\test");//请不要在最后加\\
	return 0;
}
