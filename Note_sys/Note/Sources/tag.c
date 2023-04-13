#include "tag.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <limits.h>

// 获取文件名的扩展名
char* get_extension(char* filename) {
    char* dot = strrchr(filename, '.'); // 在文件名中查找最后一个点号
    if (!dot || dot == filename) {
        return "";  // 如果没有扩展名，则返回空字符串
    }
    return dot + 1;  // 返回扩展名（不含点号）
}

// 添加标签，内部调用
int addTag(struct tag** tagHead, char* tagName) {
    if (tagName == NULL || strlen(tagName) == 0) {
        return 0; // 标签名为空，添加失败
    }
    struct tag* newTag = (struct tag*)malloc(sizeof(struct tag));
    if (newTag == NULL) {
        return 0; // 内存分配失败，添加失败
    }
    strcpy(newTag->name, tagName); // 拷贝标签名
    newTag->next = *tagHead; // 将新标签插入链表头
    *tagHead = newTag;
    return 1; // 添加成功
}

// 删除标签，内部调用
int deleteTag(struct tag** tagHead, char* tagName) {
    if (*tagHead == NULL || tagName == NULL || strlen(tagName) == 0) {
        return 0; // 链表为空或标签名为空，删除失败
    }
    struct tag* p = *tagHead;
    struct tag* q = NULL;
    while (p != NULL && strcmp(p->name, tagName) != 0) { // 遍历整个链表寻找标签
        q = p;
        p = p->next;
    }
    if (p == NULL) { // 未找到标签
        return 0;
    }
    if (q == NULL) { // 找到的标签为链表头
        *tagHead = p->next;
    }
    else { // 找到的标签为链表中的结点
        q->next = p->next;
    }
    free(p); // 释放内存
    return 1; // 删除成功
}

// 是否包含标签，内部调用
int isTagContained(struct tag* tagHead, char* tagName) {
    if (tagName == NULL || strlen(tagName) == 0 || tagHead == NULL) {
        return 0; // 标签名为空或链表为空，认为未找到标签
    }
    struct tag* p = tagHead;
    while (p != NULL) { // 遍历链表
        if (strcmp(p->name, tagName) == 0) { // 判断标签是否相等
            return 1;
        }
        p = p->next;
    }
    return 0; // 未找到标签
}

// 添加笔记标签
Status addTagToNote(Note* note, char* tagName) {
    if (note == NULL || tagName == NULL || strlen(tagName) == 0) {
        return ERROR; // 笔记为空或标签名为空，返回错误状态
    }
    if (isTagContained(note->tagHead, tagName)) { // 如果已包含该标签，返回错误状态
        return ERROR;
    }
    Status status = addTag(&(note->tagHead), tagName); // 调用addTag函数添加标签
    if (status == ERROR) {
        free(status);       // 释放之前分配的内存
    }
    return status;
}

// 删除笔记标签
Status deleteTagFromNote(Note* note, char* tagName) {
    if (note == NULL || tagName == NULL || strlen(tagName) == 0) {
        return ERROR; // 笔记为空或标签名为空，返回错误状态
    }
    if (!isTagContained(note->tagHead, tagName)) { // 如果未包含该标签，返回错误状态
        return ERROR;
    }
    Status status = deleteTag(&(note->tagHead), tagName); // 调用deleteTag函数删除标签
    if (status == ERROR) {
        free(status);       // 释放之前分配的内存
    }
    return status;
}

// 显示标签，内部调用
void viewTag(struct tag* tagHead) {
    struct tag* p = tagHead;
    while (p != NULL) { // 遍历链表
        printf("%s ", p->name); // 输出标签名
        p = p->next;
    }
}

// 显示指定笔记的标签
Status viewTagsInNote(Note* note)
{
    if (note == NULL) {
        return ERROR; // 笔记为空，返回错误状态
    }
    printf("Tags for Note %s: ", note->name); // 输出笔记名
    viewTag(note->tagHead); // 输出该笔记的标签
    printf("\n");
    return SUCCESS; // 返回成功状态
}

// 添加文件夹标签(注意标签有重名检测，成功返回SUCCESS，失败返回ERROR)
Status addTagToFolder(Folder* folder, char* tagName) {
    if (folder == NULL || tagName == NULL) {
        return ERROR;
    }
    Tag* tag = *(folder->tags);
    while (tag != NULL) {
        if (strcmp(tag->name, tagName) == 0) {
            // 标签名已存在
            return ERROR;
        }
        tag = tag->next;
    }
    // 创建新节点
    Tag* newTag = (Tag*)malloc(sizeof(Tag));
    if (newTag == NULL) {
        return ERROR;   // 内存分配失败，返回错误状态
    }
    strncpy(newTag->name, tagName, 50);
    newTag->next = *(folder->tags);
    *(folder->tags) = newTag;
    return SUCCESS;
}

// 删除文件夹标签
Status deleteTagFromFolder(Folder* folder, char* tagName) {
    if (folder == NULL || tagName == NULL) {
        return ERROR;
    }
    Tag* tag = *(folder->tags);
    Tag* prevTag = NULL;
    while (tag != NULL) {
        if (strcmp(tag->name, tagName) == 0) {
            if (prevTag == NULL) {
                *(folder->tags) = tag->next;
            }
            else {
                prevTag->next = tag->next;
            }
            free(tag);
            return SUCCESS;
        }
        prevTag = tag;
        tag = tag->next;
    }
    // 标签不存在
    return ERROR;
}

// 显示指定文件夹的标签
Status viewTagsInFolder(Folder* folder) {
    if (folder == NULL) {
        return ERROR;
    }
    Tag* tag = folder->tags;
    while (tag != NULL) {
        printf("%s\n", tag->name);
        tag = tag->next;
    }
    return SUCCESS;
}

// 根据标签内容，在当前目录下进行笔记搜索，输出匹配的标签对应的笔记文件名
Status searchNotesInFolderByTag(Folder* folder, char* tagName) {
    if (folder == NULL || tagName == NULL) {
        return ERROR; // 文件夹为空或标签名为空，返回错误状态
    }
    if (folder->visited == 1) {
        return ERROR; // 已搜索过，不再重复搜索
    }
    folder->visited = 1; // 标记已搜索
    Note* note = folder->notes;
    while (note != NULL) { // 遍历该文件夹下所有笔记
        if (isTagContained(note->tagHead, tagName)) { // 如果标签包含该标签，输出文件名
            printf("%s\n", note->name);
        }
        note = note->next;
    }
    Folder* subFolder = folder->child;
    while (subFolder != NULL) { // 遍历该文件夹的子文件夹
        searchNotesInFolderByTag(subFolder, tagName); // 递归搜索子文件夹
        subFolder = subFolder->sibling;
    }
    return SUCCESS; // 返回成功状态
}

// 根据标签内容，对所有笔记进行搜索，输出匹配的标签所对应的笔记的文件名以及绝对路径
Status searchNotesByTag(char* tagName) {
    if (tagName == NULL || strlen(tagName) == 0) {
        return ERROR; // 标签名为空，返回错误状态
    }
    char* path = (char*)malloc(MAX_PATH * sizeof(char)); // 分配内存
    if (path == NULL) {
        return ERROR; // 内存分配失败，返回错误状态
    }
    if (_getcwd(path, MAX_PATH) == NULL) { // 获取当前工作目录的绝对路径
        free(path); // 获取绝对路径失败，释放内存并返回错误状态
        return ERROR;
    }
    Folder* root = (Folder*)malloc(sizeof(Folder)); // 创建虚拟根文件夹
    if (root == NULL) {
        free(path); // 内存分配失败，释放之前分配的内存并返回错误状态
        return ERROR;
    }
    memset(root, 0, sizeof(Folder));
    root->path = path; // 虚拟根文件夹的路径为当前工作目录
    root->parent = NULL;
    root->child = NULL;
    root->sibling = NULL;
    root->tags = NULL;
    root->num_notes = 0;
    root->visited = 0;
    readFolder(root); // 读取所有文件夹及文件
    Folder* folder = root;
    while (folder != NULL) { // 遍历所有文件夹
        searchNotesInFolderByTag(folder, tagName); // 在每个文件夹内搜索该标签的笔记
        folder = folder->sibling;
    }
    freeFolder(root); // 释放内存
    return SUCCESS; // 返回成功状态
}

//读取
Status view_tag() {
    int num = 0;
    int id = 0;
    char* p = &id;
    char username[20];
    char tag[50][20]; // 存储标签信息的二维字符数组
    char ch[10], name[50]; //username 用户名 name 笔记名 ch tag
    FILE* f = fopen("../doc/tag.txt", "r");
    while (fgets(tag[num], 50, f) != NULL) {
        p = strtok(tag[num], " ");
        strcpy(name, p);
        p = strtok(NULL, " ");
        strcpy(username, p);
        p = strtok(NULL, " ");
        strcpy(ch, p); // Read twice because you want to skip the previous characters
        if (strcmp(username, name) == 0) {
            printf("笔记：%s 创建者：%s tag：%s\n", name, username, ch);
            return SUCCESS;
        }
        num++; // 记录读取的行数
    }
    fclose(f);
}

//保存
Status create_tag(char* name, char* username, char* tagName) {
    FILE* tagFp = fopen("../doc/tag.txt", "a");
    if (tagFp == NULL) {
        printf("Failed to open tag.txt\n");
        return ERROR;
    }
    fprintf(tagFp, "%s,%s,%s\n", name, username, tagName); // 注意逗号
    fclose(tagFp);
    return SUCCESS;
}
