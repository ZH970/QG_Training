#include "tag.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <limits.h>

// ��ȡ�ļ�������չ��
char* get_extension(char* filename) {
    char* dot = strrchr(filename, '.'); // ���ļ����в������һ�����
    if (!dot || dot == filename) {
        return "";  // ���û����չ�����򷵻ؿ��ַ���
    }
    return dot + 1;  // ������չ����������ţ�
}

// ��ӱ�ǩ���ڲ�����
int addTag(struct tag** tagHead, char* tagName) {
    if (tagName == NULL || strlen(tagName) == 0) {
        return 0; // ��ǩ��Ϊ�գ����ʧ��
    }
    struct tag* newTag = (struct tag*)malloc(sizeof(struct tag));
    if (newTag == NULL) {
        return 0; // �ڴ����ʧ�ܣ����ʧ��
    }
    strcpy(newTag->name, tagName); // ������ǩ��
    newTag->next = *tagHead; // ���±�ǩ��������ͷ
    *tagHead = newTag;
    return 1; // ��ӳɹ�
}

// ɾ����ǩ���ڲ�����
int deleteTag(struct tag** tagHead, char* tagName) {
    if (*tagHead == NULL || tagName == NULL || strlen(tagName) == 0) {
        return 0; // ����Ϊ�ջ��ǩ��Ϊ�գ�ɾ��ʧ��
    }
    struct tag* p = *tagHead;
    struct tag* q = NULL;
    while (p != NULL && strcmp(p->name, tagName) != 0) { // ������������Ѱ�ұ�ǩ
        q = p;
        p = p->next;
    }
    if (p == NULL) { // δ�ҵ���ǩ
        return 0;
    }
    if (q == NULL) { // �ҵ��ı�ǩΪ����ͷ
        *tagHead = p->next;
    }
    else { // �ҵ��ı�ǩΪ�����еĽ��
        q->next = p->next;
    }
    free(p); // �ͷ��ڴ�
    return 1; // ɾ���ɹ�
}

// �Ƿ������ǩ���ڲ�����
int isTagContained(struct tag* tagHead, char* tagName) {
    if (tagName == NULL || strlen(tagName) == 0 || tagHead == NULL) {
        return 0; // ��ǩ��Ϊ�ջ�����Ϊ�գ���Ϊδ�ҵ���ǩ
    }
    struct tag* p = tagHead;
    while (p != NULL) { // ��������
        if (strcmp(p->name, tagName) == 0) { // �жϱ�ǩ�Ƿ����
            return 1;
        }
        p = p->next;
    }
    return 0; // δ�ҵ���ǩ
}

// ��ӱʼǱ�ǩ
Status addTagToNote(Note* note, char* tagName) {
    if (note == NULL || tagName == NULL || strlen(tagName) == 0) {
        return ERROR; // �ʼ�Ϊ�ջ��ǩ��Ϊ�գ����ش���״̬
    }
    if (isTagContained(note->tagHead, tagName)) { // ����Ѱ����ñ�ǩ�����ش���״̬
        return ERROR;
    }
    Status status = addTag(&(note->tagHead), tagName); // ����addTag������ӱ�ǩ
    if (status == ERROR) {
        free(status);       // �ͷ�֮ǰ������ڴ�
    }
    return status;
}

// ɾ���ʼǱ�ǩ
Status deleteTagFromNote(Note* note, char* tagName) {
    if (note == NULL || tagName == NULL || strlen(tagName) == 0) {
        return ERROR; // �ʼ�Ϊ�ջ��ǩ��Ϊ�գ����ش���״̬
    }
    if (!isTagContained(note->tagHead, tagName)) { // ���δ�����ñ�ǩ�����ش���״̬
        return ERROR;
    }
    Status status = deleteTag(&(note->tagHead), tagName); // ����deleteTag����ɾ����ǩ
    if (status == ERROR) {
        free(status);       // �ͷ�֮ǰ������ڴ�
    }
    return status;
}

// ��ʾ��ǩ���ڲ�����
void viewTag(struct tag* tagHead) {
    struct tag* p = tagHead;
    while (p != NULL) { // ��������
        printf("%s ", p->name); // �����ǩ��
        p = p->next;
    }
}

// ��ʾָ���ʼǵı�ǩ
Status viewTagsInNote(Note* note)
{
    if (note == NULL) {
        return ERROR; // �ʼ�Ϊ�գ����ش���״̬
    }
    printf("Tags for Note %s: ", note->name); // ����ʼ���
    viewTag(note->tagHead); // ����ñʼǵı�ǩ
    printf("\n");
    return SUCCESS; // ���سɹ�״̬
}

// ����ļ��б�ǩ(ע���ǩ��������⣬�ɹ�����SUCCESS��ʧ�ܷ���ERROR)
Status addTagToFolder(Folder* folder, char* tagName) {
    if (folder == NULL || tagName == NULL) {
        return ERROR;
    }
    Tag* tag = *(folder->tags);
    while (tag != NULL) {
        if (strcmp(tag->name, tagName) == 0) {
            // ��ǩ���Ѵ���
            return ERROR;
        }
        tag = tag->next;
    }
    // �����½ڵ�
    Tag* newTag = (Tag*)malloc(sizeof(Tag));
    if (newTag == NULL) {
        return ERROR;   // �ڴ����ʧ�ܣ����ش���״̬
    }
    strncpy(newTag->name, tagName, 50);
    newTag->next = *(folder->tags);
    *(folder->tags) = newTag;
    return SUCCESS;
}

// ɾ���ļ��б�ǩ
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
    // ��ǩ������
    return ERROR;
}

// ��ʾָ���ļ��еı�ǩ
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

// ���ݱ�ǩ���ݣ��ڵ�ǰĿ¼�½��бʼ����������ƥ��ı�ǩ��Ӧ�ıʼ��ļ���
Status searchNotesInFolderByTag(Folder* folder, char* tagName) {
    if (folder == NULL || tagName == NULL) {
        return ERROR; // �ļ���Ϊ�ջ��ǩ��Ϊ�գ����ش���״̬
    }
    if (folder->visited == 1) {
        return ERROR; // ���������������ظ�����
    }
    folder->visited = 1; // ���������
    Note* note = folder->notes;
    while (note != NULL) { // �������ļ��������бʼ�
        if (isTagContained(note->tagHead, tagName)) { // �����ǩ�����ñ�ǩ������ļ���
            printf("%s\n", note->name);
        }
        note = note->next;
    }
    Folder* subFolder = folder->child;
    while (subFolder != NULL) { // �������ļ��е����ļ���
        searchNotesInFolderByTag(subFolder, tagName); // �ݹ��������ļ���
        subFolder = subFolder->sibling;
    }
    return SUCCESS; // ���سɹ�״̬
}

// ���ݱ�ǩ���ݣ������бʼǽ������������ƥ��ı�ǩ����Ӧ�ıʼǵ��ļ����Լ�����·��
Status searchNotesByTag(char* tagName) {
    if (tagName == NULL || strlen(tagName) == 0) {
        return ERROR; // ��ǩ��Ϊ�գ����ش���״̬
    }
    char* path = (char*)malloc(MAX_PATH * sizeof(char)); // �����ڴ�
    if (path == NULL) {
        return ERROR; // �ڴ����ʧ�ܣ����ش���״̬
    }
    if (_getcwd(path, MAX_PATH) == NULL) { // ��ȡ��ǰ����Ŀ¼�ľ���·��
        free(path); // ��ȡ����·��ʧ�ܣ��ͷ��ڴ沢���ش���״̬
        return ERROR;
    }
    Folder* root = (Folder*)malloc(sizeof(Folder)); // ����������ļ���
    if (root == NULL) {
        free(path); // �ڴ����ʧ�ܣ��ͷ�֮ǰ������ڴ沢���ش���״̬
        return ERROR;
    }
    memset(root, 0, sizeof(Folder));
    root->path = path; // ������ļ��е�·��Ϊ��ǰ����Ŀ¼
    root->parent = NULL;
    root->child = NULL;
    root->sibling = NULL;
    root->tags = NULL;
    root->num_notes = 0;
    root->visited = 0;
    readFolder(root); // ��ȡ�����ļ��м��ļ�
    Folder* folder = root;
    while (folder != NULL) { // ���������ļ���
        searchNotesInFolderByTag(folder, tagName); // ��ÿ���ļ����������ñ�ǩ�ıʼ�
        folder = folder->sibling;
    }
    freeFolder(root); // �ͷ��ڴ�
    return SUCCESS; // ���سɹ�״̬
}

//��ȡ
Status view_tag() {
    int num = 0;
    int id = 0;
    char* p = &id;
    char username[20];
    char tag[50][20]; // �洢��ǩ��Ϣ�Ķ�ά�ַ�����
    char ch[10], name[50]; //username �û��� name �ʼ��� ch tag
    FILE* f = fopen("../doc/tag.txt", "r");
    while (fgets(tag[num], 50, f) != NULL) {
        p = strtok(tag[num], " ");
        strcpy(name, p);
        p = strtok(NULL, " ");
        strcpy(username, p);
        p = strtok(NULL, " ");
        strcpy(ch, p); // Read twice because you want to skip the previous characters
        if (strcmp(username, name) == 0) {
            printf("�ʼǣ�%s �����ߣ�%s tag��%s\n", name, username, ch);
            return SUCCESS;
        }
        num++; // ��¼��ȡ������
    }
    fclose(f);
}

//����
Status create_tag(char* name, char* username, char* tagName) {
    FILE* tagFp = fopen("../doc/tag.txt", "a");
    if (tagFp == NULL) {
        printf("Failed to open tag.txt\n");
        return ERROR;
    }
    fprintf(tagFp, "%s,%s,%s\n", name, username, tagName); // ע�ⶺ��
    fclose(tagFp);
    return SUCCESS;
}
