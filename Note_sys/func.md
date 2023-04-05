需求拆分：文件、文件夹创建删除改名等     树    打印文件夹结构   

思路：

tag：笔记文件夹的名字

创建笔记：创建.md 文件

读取笔记：读取.md后缀名的文件，将信息储存在树的结点对应的笔记结构体内（树的创建、查找）（非二叉树）

命令部分：

ls下面有

rm：删除文件

cd 不重要，用system("cd")偷懒也行吧（如果没时间的话）

mkdir：创建文件夹

sort：读取该文件夹下的所有后缀名为.md 的文件，按首字母打印信息（一行行打印直观点？）



可能要用的函数：(供参考)

**创建文件夹**

```c
#include <io.h>
#include <direct.h>

// 创建文件夹
void CreateFolder () {
    // 文件夹名称
    char folderName [] = "RunData";
    // 文件夹不存在则创建文件夹
    if (_access (folderName, 0) == -1) {
        _mkdir (folderName);
    }
}
```

**创建文件**

```c
#include <stdio.h>

int main() {
    FILE *fp;
    fp = fopen("example.md", "w");
    fprintf(fp, "这是一个示例文件。");
    fclose(fp);
    return 0;
}
```

要指定路径：

`"../note/example.md"`

即可在上级文件夹的note文件下创建...

**ls -a**

```c

void TraverseDir(char *direntName, int level)
{
    //定义一个目录流指针
    DIR *p_dir = NULL;
 
    //定义一个目录结构体指针
    struct dirent *p_dirent = NULL;
 
    //打开目录，返回一个目录流指针指向第一个目录项
    p_dir = opendir(direntName);
    if(p_dir == NULL)
    {
        printf("opendir error\n");
    }
 
    //循环读取每个目录项, 当返回NULL时读取完毕
    while((p_dirent = readdir(p_dir)) != NULL)
    {
        //备份之前的目录名
        char *backupDirName = NULL;
		
        if(p_dirent->d_name[0] == '.' || p_dirent->d_name[0] == '..')
        {
            continue;
        }
 
        int i;
        for(i = 0; i < level; i++)
        {
            printf("|");
            printf("     ");
        }
        printf("|--- ");
        printf("%s\n", p_dirent->d_name);
 
        //如果目录项仍是一个目录的话，进入目录
        if(p_dirent->d_type == DT_DIR)
        {
            //当前目录长度
            int curDirentNameLen = strlen(direntName)+strlen(p_dirent->d_name) + 2;
 
            //准备下一级
            backupDirName = (char *)malloc(curDirentNameLen);
            memset(backupDirName, 0, curDirentNameLen);
            memcpy(backupDirName, direntName, curDirentNameLen);
 
            strcat(backupDirName, "/");
            strcat(backupDirName, p_dirent->d_name);
            PrintDirentStruct(backupDirName, level + 1);//递归调用
 
            free(backupDirName);
            backupDirName = NULL;
        }
    }
 
    closedir(p_dir);
}
 
int main（int argc，char **argv）
{
    if (argc < 2)
    {
        printf("please input dir name\n");
        return -1;
    }
 
    TraverseDir(argv[1], 0);
    return 0；

```

[C语言实现遍历目录并用树状打印_随心记IT的博客-CSDN博客](https://blog.csdn.net/wang93IT/article/details/85113467)

**输入命令**

```c
#include <stdio.h>
#include <string.h>

void cd() {
    printf("cd command\n");
}

void rm() {
    printf("rm command\n");
}

void tag() {
    printf("tag command\n");
}

void mkdir() {
    printf("mkdir command\n");
}

void sort() {
    printf("sort command\n");
}

void ls() {
    printf("ls command\n");
}

void command() {
    char str[100];
    scanf("%s", str);
    if (strcmp(str, "cd") == 0) {
        cd();
    } else if (strcmp(str, "rm") == 0) {
        rm();
    } else if (strcmp(str, "tag") == 0) {
        tag();
    } else if (strcmp(str, "mkdir") == 0) {
        mkdir();
    } else if (strcmp(str, "sort") == 0) {
        sort();
    } else if (strcmp(str, "ls") == 0) {
        ls();
    } else {
        printf("Warning: Invalid command.\n");
    }
}
```

将str[100]的空格前的命令截取出来的函数示范（将上面的str截取出第一个单词再用strcmp比对：

```c
#include <stdio.h>
#include <string.h>

int main()
{
    char str[100] = "Hello world!"; // example string
    char sub[100]; // substring to store the result
    int i = 0; // index variable
    while (str[i] != ' ' && str[i] != '\0') // loop until a space or end of string is encountered
    {
        sub[i] = str[i]; // copy the character to the substring
        i++; // increment the index
    }
    sub[i] = '\0'; // add a null terminator to the substring
    printf("The substring is: %s\n", sub); // print the result
    return 0;
}
```



**sort**

```c
#include <stdio.h>
#include <io.h>
#include <string.h>

void sort()
{
    // file information structure
    struct _finddata_t fileinfo;
    // save file handle
    long fHandle;
    // file name array
    char names[100][100];
    // file count
    int i = 0;
    // file name buffer
    char buffer[100];
    
    // search for all files with .md suffix in the current folder
    if( (fHandle=_findfirst ( "./*.md", &fileinfo )) == -1L )
    {
        printf( "No .md files found in the current folder\n");
        return 0;
    }
    else
    {
        do
        {
            // copy the file name to the array
            strcpy(names[i], fileinfo.name);
            i++;
        }while( _findnext (fHandle,&fileinfo)==0);
    }
    
    // close file handle
    _findclose ( fHandle );
    
    // sort the file names in alphabetical order using bubble sort
    for (int j = 0; j < i - 1; j++)
    {
        for (int k = 0; k < i - j - 1; k++)
        {
            if (strcmp(names[k], names[k+1]) > 0)
            {
                strcpy(buffer, names[k]);
                strcpy(names[k], names[k+1]);
                strcpy(names[k+1], buffer);
            }
        }
    }
    
    // print the sorted file names
    printf("The .md files in alphabetical order are:\n");
    for (int j = 0; j < i; j++)
    {
        printf("%s\n", names[j]);
    }
    
    return 0;
}
```