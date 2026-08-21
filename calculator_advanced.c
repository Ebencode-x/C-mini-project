#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define UNDERLINE "\x1b[4m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"
#define CYAN "\x1b[36m"

// Structure to hold calculator state
typedef struct {
    float result;
    char lastOperation;
    int operationCount;
} CalcState;

// Function declarations
void clearScreen();
void displayHeader();
void displayBasicMenu();
void displayAdvancedMenu();
void displayCompleteMenu();
void displayHistory(float history[], int count);
void clearInputBuffer();
int getValidChoice();
float getValidNumber();
void performBasicOperation(float a, float b, int choice, float *result);
void performAdvancedOperation(float a, int choice, float *result);
int validateInput(char *input);

// Clear console screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Display styled header
void displayHeader() {
    printf("\n%s%s╔══════════════════════════════════════╗%s\n", BOLD, CYAN, RESET);
    printf("%s%s║  %s🔢 ADVANCED CALCULATOR PRO 2.0 %s🔢  %s║%s\n", BOLD, CYAN, YELLOW, CYAN, RESET);
    printf("%s%s╚══════════════════════════════════════╝%s\n\n", BOLD, CYAN, RESET);
}

// Display basic operations menu
void displayBasicMenu() {
    printf("%s%sBASIC OPERATIONS:%s\n", BOLD, BLUE, RESET);
    printf("  %s[1]%s Addition (+)\n", GREEN, RESET);
    printf("  %s[2]%s Subtraction (-)\n", GREEN, RESET);
    printf("  %s[3]%s Multiplication (*)\n", GREEN, RESET);
    printf("  %s[4]%s Division (/)\n", GREEN, RESET);
    printf("  %s[5]%s Modulus (%%)\n\n", GREEN, RESET);
}

// Display advanced operations menu
void displayAdvancedMenu() {
    printf("%s%sADVANCED OPERATIONS:%s\n", BOLD, BLUE, RESET);
    printf("  %s[6]%s Square Root (√)\n", GREEN, RESET);
    printf("  %s[7]%s Power (x^y)\n", GREEN, RESET);
    printf("  %s[8]%s Percentage (%%)\n", GREEN, RESET);
    printf("  %s[9]%s Factorial (!)\n", GREEN, RESET);
    printf("  %s[10]%s Sine (sin)\n", GREEN, RESET);
    printf("  %s[11]%s Cosine (cos)\n", GREEN, RESET);
    printf("  %s[12]%s Tangent (tan)\n\n", GREEN, RESET);
}

// Display complete menu
void displayCompleteMenu() {
    clearScreen();
    displayHeader();
    displayBasicMenu();
    displayAdvancedMenu();
    printf("%s%sOTHER OPTIONS:%s\n", BOLD, BLUE, RESET);
    printf("  %s[13]%s Clear History\n", GREEN, RESET);
    printf("  %s[0]%s Exit Calculator\n\n", RED, RESET);
}

// Display calculation history
void displayHistory(float history[], int count) {
    if (count == 0) {
        printf("%s%sNo calculation history yet.%s\n", YELLOW, BOLD, RESET);
        return;
    }
    printf("\n%s%s━━ CALCULATION HISTORY ━━%s\n", BOLD, CYAN, RESET);
    for (int i = 0; i < count; i++) {
        printf("%s[%d]%s %.6g\n", GREEN, i + 1, RESET, history[i]);
    }
    printf("%s%s━━━━━━━━━━━━━━━━━━━━━━%s\n\n", BOLD, CYAN, RESET);
}

// Clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Get valid choice from user
int getValidChoice() {
    int choice;
    char input[10];
    
    while (1) {
        printf("%s%s➜ Enter your choice: %s", BOLD, CYAN, RESET);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            clearInputBuffer();
            printf("%s❌ Input error. Please try again.%s\n", RED, RESET);
            continue;
        }
        
        if (sscanf(input, "%d", &choice) == 1) {
            return choice;
        }
        printf("%s❌ Invalid input. Please enter a valid number.%s\n", RED, RESET);
    }
}

// Get valid float number from user
float getValidNumber() {
    float num;
    char input[50];
    
    while (1) {
        printf("%s%s➜ Enter number: %s", BOLD, CYAN, RESET);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            clearInputBuffer();
            printf("%s❌ Input error. Please try again.%s\n", RED, RESET);
            continue;
        }
        
        if (sscanf(input, "%f", &num) == 1) {
            return num;
        }
        printf("%s❌ Invalid input. Please enter a valid number.%s\n", RED, RESET);
    }
}

// Perform basic arithmetic operations
void performBasicOperation(float a, float b, int choice, float *result) {
    switch(choice) {
        case 1:
            *result = a + b;
            printf("%s%s✓ Result:%s %.6g %s+ %.6g = %s%.6g%s\n", 
                   GREEN, BOLD, RESET, a, CYAN, b, YELLOW, *result, RESET);
            break;
        case 2:
            *result = a - b;
            printf("%s%s✓ Result:%s %.6g %s- %.6g = %s%.6g%s\n", 
                   GREEN, BOLD, RESET, a, CYAN, b, YELLOW, *result, RESET);
            break;
        case 3:
            *result = a * b;
            printf("%s%s✓ Result:%s %.6g %s× %.6g = %s%.6g%s\n", 
                   GREEN, BOLD, RESET, a, CYAN, b, YELLOW, *result, RESET);
            break;
        case 4:
            if (b != 0) {
                *result = a / b;
                printf("%s%s✓ Result:%s %.6g %s÷ %.6g = %s%.6g%s\n", 
                       GREEN, BOLD, RESET, a, CYAN, b, YELLOW, *result, RESET);
            } else {
                printf("%s❌ Error: Cannot divide by zero!%s\n", RED, RESET);
                *result = 0;
            }
            break;
        case 5:
            if ((int)b != 0) {
                *result = fmod(a, b);
                printf("%s%s✓ Result:%s %.6g %s%% %.6g = %s%.6g%s\n", 
                       GREEN, BOLD, RESET, a, CYAN, b, YELLOW, *result, RESET);
            } else {
                printf("%s❌ Error: Modulus by zero is undefined!%s\n", RED, RESET);
                *result = 0;
            }
            break;
        default:
            printf("%s❌ Invalid operation!%s\n", RED, RESET);
    }
}

// Perform advanced operations
void performAdvancedOperation(float a, int choice, float *result) {
    float b, factorial;
    int n, i;
    
    switch(choice) {
        case 6:
            if (a >= 0) {
                *result = sqrt(a);
                printf("%s%s✓ Result:%s √(%.6g) = %s%.6g%s\n", 
                       GREEN, BOLD, RESET, a, YELLOW, *result, RESET);
            } else {
                printf("%s❌ Error: Cannot take square root of negative number!%s\n", RED, RESET);
                *result = 0;
            }
            break;
        case 7:
            printf("%s%s➜ Enter exponent: %s", BOLD, CYAN, RESET);
            scanf("%f", &b);
            clearInputBuffer();
            *result = pow(a, b);
            printf("%s%s✓ Result:%s %.6g %s^ %.6g = %s%.6g%s\n", 
                   GREEN, BOLD, RESET, a, CYAN, b, YELLOW, *result, RESET);
            break;
        case 8:
            printf("%s%s➜ Enter percentage: %s", BOLD, CYAN, RESET);
            scanf("%f", &b);
            clearInputBuffer();
            *result = (a * b) / 100;
            printf("%s%s✓ Result:%s %.2f%% of %.6g = %s%.6g%s\n", 
                   GREEN, BOLD, RESET, b, a, YELLOW, *result, RESET);
            break;
        case 9:
            n = (int)a;
            if (n < 0) {
                printf("%s❌ Error: Factorial of negative number is undefined!%s\n", RED, RESET);
                *result = 0;
            } else {
                factorial = 1;
                for (i = 2; i <= n; i++) {
                    factorial *= i;
                }
                *result = factorial;
                printf("%s%s✓ Result:%s %d! = %s%.0f%s\n", 
                       GREEN, BOLD, RESET, n, YELLOW, *result, RESET);
            }
            break;
        case 10:
            *result = sin(a * M_PI / 180);
            printf("%s%s✓ Result:%s sin(%.6g°) = %s%.6g%s\n", 
                   GREEN, BOLD, RESET, a, YELLOW, *result, RESET);
            break;
        case 11:
            *result = cos(a * M_PI / 180);
            printf("%s%s✓ Result:%s cos(%.6g°) = %s%.6g%s\n", 
                   GREEN, BOLD, RESET, a, YELLOW, *result, RESET);
            break;
        case 12:
            *result = tan(a * M_PI / 180);
            printf("%s%s✓ Result:%s tan(%.6g°) = %s%.6g%s\n", 
                   GREEN, BOLD, RESET, a, YELLOW, *result, RESET);
            break;
        default:
            printf("%s❌ Invalid operation!%s\n", RED, RESET);
    }
}

// Main program
int main() {
    float a, b, result = 0;
    int choice;
    float history[100];
    int historyCount = 0;
    
    while (1) {
        displayCompleteMenu();
        choice = getValidChoice();
        
        if (choice == 0) {
            clearScreen();
            displayHeader();
            printf("%s%sThank you for using Advanced Calculator Pro!%s\n", GREEN, BOLD, RESET);
            printf("%s%s━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━%s\n\n", CYAN, BOLD, RESET);
            break;
        }
        
        if (choice == 13) {
            historyCount = 0;
            printf("\n%s✓ History cleared!%s\n", GREEN, RESET);
            printf("%s%sPressing any key to continue...%s", YELLOW, BOLD, RESET);
            getchar();
            continue;
        }
        
        if (choice < 0 || choice > 13) {
            printf("%s❌ Invalid choice! Please select a valid option.%s\n", RED, RESET);
            printf("%s%sPressing any key to continue...%s", YELLOW, BOLD, RESET);
            getchar();
            continue;
        }
        
        // Get input for operations
        if (choice >= 1 && choice <= 5) {
            printf("\n%s%s━━ BASIC OPERATION ━━%s\n", CYAN, BOLD, RESET);
            printf("%s%sEnter two numbers:%s\n", BOLD, BLUE, RESET);
            a = getValidNumber();
            b = getValidNumber();
            performBasicOperation(a, b, choice, &result);
        } else if (choice >= 6 && choice <= 12) {
            printf("\n%s%s━━ ADVANCED OPERATION ━━%s\n", CYAN, BOLD, RESET);
            printf("%s%sEnter a number:%s\n", BOLD, BLUE, RESET);
            a = getValidNumber();
            performAdvancedOperation(a, choice, &result);
        }
        
        // Add to history
        if (choice >= 1 && choice <= 12) {
            if (historyCount < 100) {
                history[historyCount++] = result;
            }
        }
        
        // Display history
        if (historyCount > 0 && choice >= 1 && choice <= 12) {
            displayHistory(history, historyCount);
        }
        
        printf("%s%sPressing any key to continue...%s", YELLOW, BOLD, RESET);
        getchar();
    }
    
    return 0;
}
