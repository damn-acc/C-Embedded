#pragma once

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define STR_MAX 51
#define STR_SCANF_SIZE 50

#define ESC 27

typedef struct Node {
    char name[STR_MAX];
    float price;
    int pages;
    char language[STR_MAX];
    float weight;
    int year;
    struct Node* next;
} Node;

typedef struct List {
    struct Node* head;
    struct Node* tail;
    int size;
} List;

struct List* createList();
void appendNode(List* list, Node* node);
void freeList(List* list);
void freeNode(Node* node);
struct List* readFromTxt(const char* filename);
void saveToTxt(List* list, const char* filename);
void createNode(List* list);
void deleteNode(List* list);
void viewAllBooks(List* list);
void viewBook(List* list);
void clearStdin();
int enterInt(const char* prompt);
float enterFloat(const char* prompt);