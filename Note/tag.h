#pragma once
#ifndef TAG_H
#define TAG_H

#define MAX_PATH 1024
#define CONTENT_SIZE 4096


/*typedef enum Status {
    ERROR = 0,
    SUCCESS = 1
} Status;*/

/*// 笔记结构体
typedef struct note {
    char name[50]; // 笔记名
    char title[100];//笔记主题
    char content[500]; // 笔记内容
    char path[100];//笔记实际路径
    char tags[50][50];  // 笔记标签列表
    int tagCount;  // 笔记标签数量
    Folder* folder;  // 笔记所在文件夹指针
    struct tag* tagHead; // 标签链表头指针
    struct note* next; // 下一篇笔记的指针
} Note;

//文件夹结构体
typedef struct Folder
{
    char name[100];      // 文件夹名
    char* path;
    struct folder* parent; //父文件夹
    struct folder* child; //第一个子文件夹
    struct folder* sibling; //下一个兄弟文件夹
    Tag* tag;          // 存储标签的链表头指针
    Note* notes;        // 指向笔记链表头的指针
    int num_notes;// 笔记数量
    int visited; //1代表已搜索
} Folder;*/

// 标签结构体
typedef struct tag {
    char name[20]; // 标签名
    struct tag* next; // 下一个标签的指针
} Tag;

// 添加标签，内部调用
int addTag(struct tag** tagHead, char* tagName);

// 删除标签，内部调用
int deleteTag(struct tag** tagHead, char* tagName);

// 是否包含标签，内部调用
int isTagContained(struct tag* tagHead, char* tagName);

// 添加笔记标签
Status addTagToNote(Note* note, char* tagName);

// 删除笔记标签
Status deleteTagFromNote(Note* note, char* tagName);

// 显示标签，内部调用
void viewTag(struct tag* tagHead);

// 显示指定笔记的标签
Status viewTagsInNote(Note* note);

// 添加文件夹标签(注意标签有重名检测，成功返回SUCCESS，失败返回ERROR)
Status addTagToFolder(Folder* folder, char* tagName);

// 删除文件夹标签
Status deleteTagFromFolder(Folder* folder, char* tagName);

// 显示指定文件夹的标签
Status viewTagsInFolder(Folder* folder);

Status searchNotesInFolderByTag(Folder* folder, char* tagName);

Status searchNotesByTag(char* tagName);

Status view_tag();

Status create_tag(char* name, char* username, char* tagName);
#endif
