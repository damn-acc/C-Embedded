#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int strMaxSize = 12; // 10 + 1(\n) + 1('0')

void convertString(char *string) {
	for (int i = 0; string[i] != '\n'; i++) {
		if (string[i] >= 'a' && string[i] <= 'z') {
			string[i] -= 'a' - 'A';
		}
	}
}

char* inputString() {
	char *string = malloc(strMaxSize * sizeof(char));
	if (fgets(string, strMaxSize, stdin) != NULL) {
		if (!strchr(string, '\n')) {
			printf("text limit");
			return NULL;
		}
		return string;
	}
	else {
		printf("stdin error");
		return NULL;
	}
}

void clearStdin() {
	int i;
	while ((i = getchar()) != '\n' && i != '\0'){}
}

int main() {
	char *userStr;
	int key;
	
	do {
		userStr = inputString();
		
		key = getchar();
		clearStdin();
	} while (key != 27);
}
