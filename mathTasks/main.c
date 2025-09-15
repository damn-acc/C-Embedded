#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "main.h"

/* CONST STRINGS */
const char progDescription[] = "This is a small program in C for calculating two functions with the variable \"alpha\" with an accuracy of 6 digits:\n";

const char funcDescription[] =
    "\tfunction 1: z1 = (sin(2a) + sin(5a) - sin(3a)) / (cos(a) + 1 - 2sin(a)^2)\n"
    "\tfunction 2: z2 = 2sin(a)\n";

const char inputMessage[] = "Please enter the value of |alpha| < 3.4e38: ";

const char exitMessage[] = "\nPress 'esc' to exit the program, or any other key to continue: ";

const char errorMessage[] = "Input error! Please enter a valid number.\n";
/* CONST STRINGS END */ 

int main() {
    int key;
    float alpha;
    double z1, z2;

    printf("%s", progDescription);
    do {
        printf("%s%s", funcDescription, inputMessage);

        if (!inputNumber(&alpha) || fabs(alpha) > 3.4e38) {
            printf("%s", errorMessage);
            continue;
        }

        calculateFunctions(alpha, &z1, &z2);

        printf("z1 = %.6f\nz2 = %.6f\n%s", z1, z2, exitMessage);
        
        key = getchar();
        clearInputBuffer();
    } while (key != 27); // 27 is the ASCII code for 'esc'
    return 0;
}

bool inputNumber(float *number) {
    if (scanf("%f", number) != 1) {
        clearInputBuffer();
        return false;
    }
    clearInputBuffer();
    return true;
}

void calculateFunctions(float alpha, double *z1, double *z2) {
    *z1 = (sin(2.0 * alpha) + sin(5.0 * alpha) - sin(3.0 * alpha)) / (cos(alpha) + 1.0 - 2.0 * pow(sin(alpha), 2));
    *z2 = 2.0 * sin(alpha);
}

void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n'); // clear input buffer
}