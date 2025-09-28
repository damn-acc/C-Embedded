#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

const char* filename = "data.txt";
const int choiceSize = 2;

/* MAIN FUNCTION -------------------------------------------*/
int main() {
    char key;
	char choice[choiceSize];

    List* list = readFromTxt(filename);
    if (!list) {
        list = createList();
    }

    printf("This is a small program for managing a linked list of books\n");
    do {
        printf("Select an option:\n"
            "1. add a book\n"
            "2. delete a book\n"
            "3. view all books\n"
            "4. view a book\n"
            "5. save and exit\n"
            "-> "
        );

		if (!fgets(choice, sizeof(choice), stdin)) {
			printf("Stdin error");
			break;
		}
        clearStdin();
        key = choice[0];
        
		switch (key) {
            case '1':
                createNode(list);
                break;
            case '2':
                deleteNode(list);
                break;
            case '3':
                viewAllBooks(list);
                break;
            case '4': 
                viewBook(list);
                break;
            case '5':
                printf("Exiting...\n");
                break;
            default:
                printf("Unknown option\n");
        }
    } while (key != '5');
    saveToTxt(list, filename);
    freeList(list);
    return 0;
}
/* MAIN FUNCTION END ---------------------------------------*/

List* createList() {
    List* list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void freeList(List* list) {
    if (!list) { return; }
    
    Node* node = list->head;

    if (list->head) {
        freeNode(node);
    }
    free(list);
}

void createNode(List* list) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) { 
        printf("No available memory");
        return; 
    }

    newNode->next = NULL;

    printf("Enter book name(max 50 latin characters): ");
    if (fgets(newNode->name, sizeof(newNode->name), stdin)) {
        newNode->name[strcspn(newNode->name, "\n")] = '\0';
    }

    printf("Enter language(max 50 latin characters): ");
    if (fgets(newNode->language, sizeof(newNode->language), stdin)) {
        newNode->language[strcspn(newNode->language, "\n")] = '\0';
    }

    newNode->price = enterFloat("Enter price(UAH): ");
    newNode->pages = enterInt("Enter number of pages: ");
    newNode->weight = enterFloat("Enter weight(kg): ");
    newNode->year = enterInt("Enter publish year: ");

    appendNode(list, newNode);
    printf("\n");
}

float enterFloat(const char* prompt) {
    float value;
    int res;
    do {
        printf("%s", prompt);
        res = scanf("%f", &value);
        clearStdin();
        if (res != 1) {
            printf("Invalid input. Try again. ");
        }
    } while (res != 1);
    return value;
}

int enterInt(const char* prompt) {
    int value;
    int res;
    do {
        printf("%s", prompt);
        res = scanf("%d", &value);
        clearStdin();
        if (res != 1) {
            printf("Invalid Input. Try again. ");
        }
    } while (res != 1);
    return value;
}

void appendNode(List* list, Node* newNode) {
    newNode->next = NULL;
    if (list->head == NULL) {
        list->head = newNode;
    }
    else {
        list->tail->next = newNode;
    }
    list->tail = newNode;
    list->size++;
}

void freeNode(Node* node) {
    if (node->next) {
        freeNode(node->next);
    }
    free(node);
}

void deleteNode(List* list) {
    if (!list || !list->head) {
        printf("List is empty.\n");
        return;
    }

    char target[STR_MAX];
    printf("Enter target to delele(max 50 latin characters): ");
    fgets(target, sizeof(target), stdin);
    clearStdin();
    target[strcspn(target, "\n")] = '\0';

    Node* curr = list->head;
    Node* prev = NULL;
    
    while (curr) {
        if (strcmp(curr->name, target) == 0) {
            if (prev == NULL) {
                list->head = curr->next;
            }
            else {
                prev->next = curr->next;
            }
            if (curr == list->tail) {
                list->tail = prev;
            }
            free(curr);
            list->size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("Node \"%s\" not found in the list.\n", target);
}

List* readFromTxt(const char* filename) {
    FILE *f = fopen(filename, "r");
    if (!f) { return NULL; }

    List* list = createList();
    char buff[256];

    while (fgets(buff, sizeof(buff), f)) {
        Node* newNode = malloc(sizeof(Node));
        if (!newNode) { break; }

        if (sscanf(buff, 
            "%" STR(STR_SCANF_SIZE) "[^;];"
            "%f;"
            "%d;"
            "%" STR(STR_SCANF_SIZE) "[^;];"
            "%f;"
            "%d",
                newNode->name,
                &newNode->price,
                &newNode->pages,
                newNode->language,
                &newNode->weight,
                &newNode->year) == 6)
        {
            appendNode(list, newNode);
        }
        else {
            printf("There are incorrect data in your file\n");
            free(newNode);
        }
    }
    fclose(f);
    return list;
}

void saveToTxt(List* list, const char* filename) {
    if (!list || !filename) {
        printf("An issue occured while saving data\n");
        return;
    }

    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Cant open file for writing\n");
        return;
    }

    Node* curr = list->head;
    while (curr) {
        fprintf(f, "%s;%f;%d;%s;%f;%d\n",
            curr->name,
            curr->price,
            curr->pages,
            curr->language,
            curr->weight,
            curr->year);
        curr = curr->next;
    }

    fclose(f);
}

void clearStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void viewAllBooks(List* list) {
    if (!list || !list->head) {
        printf("The list is empty.\n");
        return;
    }

    Node* current = list->head;
    int count = 1;
    while (current) {
        printf("Book %d:\n", count++);
        printf("    Name: %s\n", current->name);
        printf("    Price: %.2f\n", current->price);
        printf("    Pages: %d\n", current->pages);
        printf("    Language: %s\n", current->language);
        printf("    Weight: %.2f\n", current->weight);
        printf("    Year: %d\n", current->year);

        current = current->next;
    }
    printf("\n");
}

void viewBook(List* list) {
    if (!list || !list->head) {
        printf("The list is empty.\n");
        return;
    }

    char target[STR_MAX];
    printf("Enter target to view(max 50 latin characters): ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = '\0';

    Node* current = list->head;
    while (current) {
        if (strcmp(current->name, target) == 0) {
            printf("Book found:\n");
            printf("    Name: %s\n", current->name);
            printf("    Price: %.2f\n", current->price);
            printf("    Pages: %d\n", current->pages);
            printf("    Language: %s\n", current->language);
            printf("    Weight: %.2f\n", current->weight);
            printf("    Year: %d\n", current->year);
            printf("\n");
            return;
        }
        current = current->next;
    }
    printf("Book \"%s\" not found.\n", target);
}