#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

#define ESC 27

const int strMaxSize = 12; // 10 + 1(\n) + 1('0')
const int choiceSize = 2;

/* CONST STRINGS */
const char *progMess = "This is a small program in C for converting all lowercase Latin letters to uppercase in your sentence.";
const char *inputMess = "Please enter a string (max 10 characters): ";
const char *resultMess = "Converted string: ";
const char *errorMess = "Input error! Enter no more than 10 characters";
const char *exitMess = "Press 'esc' to exit the program, or any other key to continue: ";
/* CONST STRINGS END*/

int main() {
	char *userStr;
	char key;
	char choice[2];
	
	printf("%s\n", progMess);
	do {
		printf("%s", inputMess);
		userStr = inputString(strMaxSize);

		if (userStr != NULL) {
			convertString(userStr);
			printf("%s%s", resultMess, userStr);
			free(userStr);
		}
		
		printf("%s", exitMess);
		if (fgets(choice, choiceSize, stdin) == NULL) {
			printf("Stdin error");
			break;
		}
		key = choice[0];
		printf("\n");
	} while (key != ESC);
}

void convertString(char *string) {
	for (int i = 0; string[i] != '\n'; i++) {
		if (string[i] >= 'a' && string[i] <= 'z') {
			string[i] -= 'a' - 'A';
		}
	}
}

char* inputString(int maxSize) {
	char *string = malloc(maxSize * sizeof(char));
	if (fgets(string, maxSize, stdin) != NULL) {
		if (!strchr(string, '\n')) {
			printf("%s\n", errorMess);
			clearStdin();
			free(string);
			return NULL;
		}
		return string;
	}
	else {
		printf("Stdin error");
		return NULL;
	}
}

void clearStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}