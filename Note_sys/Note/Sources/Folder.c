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
	// ��Ŀ¼
	HANDLE hFind;
	WIN32_FIND_DATAA findData;
	char pattern[MAX_PATH];
	sprintf_s(pattern, sizeof(pattern), "%s\\*", path);
	hFind = FindFirstFileA(pattern, &findData);

	// ����Ƿ�򿪳ɹ�
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("Error opening directory %s\n", path);
		return ERROR;
	}

	// ����Ŀ¼�е������ļ�����Ŀ¼
	do {
		// ����.��..���������Ŀ¼
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) {
			continue;
		}

		// ��ӡ�ļ���
		printf("%s\n", findData.cFileName);

		// �����һ����Ŀ¼���ݹ�����Լ�
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			char subpath[MAX_PATH];
			sprintf_s(subpath, sizeof(subpath), "%s\\%s", path, findData.cFileName);
			showFolders(subpath, depth + 1);
		}
	} while (FindNextFileA(hFind, &findData));

	// �ر�Ŀ¼
	FindClose(hFind);
	return SUCCESS;
}

// һ���������������ڴ�ӡ����
void print_indent(int depth) {
	for (int i = 0; i < depth; i++) {
		printf(" |-");
	}
}


/*
description: һ���ݹ麯�������ڱ���Ŀ¼����ӡ�ļ���
path: Ҫ������Ŀ¼
depth: ��ǰĿ¼����ȣ����ڴ�ӡ����
*/
Status showFolderTree(char* path, int depth) {
	// ��Ŀ¼
	HANDLE hFind;
	WIN32_FIND_DATAA findData;
	char pattern[MAX_PATH];
	sprintf_s(pattern,sizeof(pattern), "%s\\*", path);
	hFind = FindFirstFileA(pattern, &findData);

	// ����Ƿ�򿪳ɹ�
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("Error opening directory %s\n", path);
		return ERROR;
	}

	// ����Ŀ¼�е������ļ�����Ŀ¼
	do {
		// ����.��..���������Ŀ¼
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) {
			continue;
		}

		// ��ӡ�������ļ���
		print_indent(depth);
		printf("%s\n", findData.cFileName);

		// �����һ����Ŀ¼���ݹ�����Լ�
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			char subpath[MAX_PATH];
			sprintf_s(subpath,sizeof(subpath), "%s\\%s", path, findData.cFileName);
			showFolderTree(subpath, depth + 1);
		}
	} while (FindNextFileA(hFind, &findData));

	// �ر�Ŀ¼
	FindClose(hFind);
	return SUCCESS;
}

////����һ�����ڵ�Ľṹ
//typedef struct Folder {
//    char* name; //�ļ��е�����
//    struct Folder** children; //�ӽڵ���б�
//    int size; //�ӽڵ�ĸ���
//} Folder;

//����һ�����ڵ㣬�������ڴ�
Folder* createTreeNode(char* name, char* path) {
	Folder* node = (Folder*)malloc(sizeof(Folder));
	strcpy(node->name, name);
	node->child = NULL;
	node->parent = NULL;
	node->sibling = NULL;
	node->path = path;
	return node;
}

////��һ�����ڵ����һ���ӽڵ㣬�������ڴ�
//void addChild(Folder* parent, Folder* child) {
//    parent->child = child;
//    parent->children[parent->size - 1] = child;
//}

//�Զ���ĺ��������ڶ�ȡָ��·���µ������ļ��У��������Ǵ���Ϊ��
Folder* readFolders(char* path) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	//����Ҫ�������ļ���ģʽ
	char pattern[MAX_PATH];
	sprintf_s(pattern, sizeof(pattern), "%s\\*", path);
	//����FindFirstFile����
	hFind = FindFirstFileA(pattern, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return NULL;
	}
	//����һ�����ڵ㣬��ʾ��ǰ·��
	Folder* node = createTreeNode("node", path);
	//ѭ������FindNextFile����
	do {
		//�ж��ҵ����Ƿ���һ���ļ���
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			//����"."��".."������������ļ���
			if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0) {
				continue;
			}
			//ƴ�����ļ��е�����·��
			char subpath[MAX_PATH];
			/*strcpy(subpath, path);
			strcat(subpath, "\\");
			strcat(subpath, FindFileData.cFileName);*/
			sprintf(subpath, "%s\\%ws", path, FindFileData.cFileName);
			//�ݹ�ص����Զ��庯������ȡ���ļ����µ������ļ��У�����Ϊ�ӽڵ���ӵ���ǰ�ڵ�
			//addChild(root, readFolders(subpath));
			node->child = readFolders(subpath);
			node->child->parent = node;
		}
		//�������һ���ļ��У����Ը���Ŀ
	} while (FindNextFile(hFind, &FindFileData));
	//����Ƿ񵽴�����������������
	if (GetLastError() != ERROR_NO_MORE_FILES) {
		printf("FindNextFile failed (%d)\n", GetLastError());
		return NULL;
	}
	//�ر��������
	FindClose(hFind);
	//���ظ��ڵ�
	return node;
}

Folder* searchTree(char* path) {
	Folder* current = root->child; //��ʾ��������һ��
	Folder* cur_sib = current; // cur_sib������¼��ǰ�ڵ���ֵܽڵ��εı���
	while (current != NULL) { //ѭ��ֱ���ҵ�ƥ����ļ��л��ߵ���ĩβ

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
			if (strcmp(a, "md") == 0) { //�ж�·���Ƿ��Է�б�ܽ�β
				printf("��·���Ǹ�Ŀ¼��\n");
				sprintf(&p, "%s\\%s", path, name); //ƴ��·��
				if (_mkdir(&p) == -1) {
					return NULL;
				}

				Folder* new_folder = (Folder*)malloc(sizeof(Folder));
				strcpy(new_folder->name, name); //�����ļ�����
				new_folder->path = (char*)malloc(strlen(path) + strlen(name) + 2); //����·���ռ�
				//sprintf(new_folder->path, "%s\\%s", path, name); //ƴ��·��
				strcpy(new_folder->path, &p);
				new_folder->parent = root; //���ø��ڵ�Ϊ���ڵ�
				new_folder->child = NULL; //�����ӽڵ�Ϊ��
				new_folder->sibling = root->child; //�����ֵܽڵ�Ϊԭ���ĵ�һ���ӽڵ�
				root->child = new_folder; //�������ļ���Ϊ��һ���ӽڵ�
				printf("Create folder Success\n");
				return new_folder;
			}
			else {
				searchTree(path);
				////char* first = strtok(path, "\\"); //�÷�б�ָܷ�·��
				//Folder* current = root->child; //�Ӹ��ڵ�ĵ�һ���ӽڵ㿪ʼ����
				//Folder* cur_sib = current; // cur_sib������¼��ǰ�ڵ���ֵܽڵ��εı���
				//while (current != NULL) { //ѭ��ֱ���ҵ�ƥ����ļ��л��ߵ���ĩβ
				//	if (strcmp(current->path, path) != 0) { //����ҵ�ƥ���·��
				//		
				//		while (cur_sib->path != p) {
				//			cur_sib = cur_sib->sibling;
				//			if (cur_sib == NULL) {
				//				break;
				//			}
				//		}
				//		current = current->child;

				//		createFolder(current, rest, name); //�ݹ���ú�������ƥ����ļ����´������ļ���
				return NULL;
			
					//else {
					//	Folder* new_folder = (Folder*)malloc(sizeof(Folder));
					//	strcpy(new_folder->name, name); //�����ļ�����
					//	new_folder->path = (char*)malloc(strlen(path) + strlen(name) + 2); //����·���ռ�
					//	sprintf(new_folder->path, "%s\\%s", path, name); //ƴ��·��
					//	new_folder->parent = current; //���ø��ڵ�Ϊ��ǰ�ڵ�
					//	new_folder->child = NULL; //�����ӽڵ�Ϊ��
					//	new_folder->sibling = current->child; //�����ֵܽڵ�Ϊԭ���ĵ�һ���ӽڵ�
					//	current->child = new_folder; //�������ļ���Ϊ��һ���ӽڵ�
					//}

				}
		}
		else {
			printf("·�������ڡ�\n");
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

	createFolder("test", "J:\\Programing\\C\\QG_Training\\Note_sys\\Note\\md\\test");//�벻Ҫ������\\
	return 0;
}
