/******************
Name: Jonathan Djerassi    
ID: 303013098
Assignment: ex4
*******************/
#include <stdio.h>
#include <stdlib.h>


#define MAX_GRID_SIZE 30
#define MAX_SLOTS 100
#define MAX_WORD_LENGTH 15

// Function prototypes
void displayMenu();
void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidation();
void task4QueensBattle();
void task5CrosswordGenerator();

// Recursively calculate unique robot paths
int robotPaths(int col, int row) {
    if (col < 0 || row < 0) return 0;
    if (col == 0 && row == 0) return 1;
    return robotPaths(col - 1, row) + robotPaths(col, row - 1);
}

// Task 1: Robot Paths
void task1RobotPaths() {
    int col, row;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &col, &row);
    if (col < 0 || row < 0) {
        printf("The total number of paths the robot can take to reach home is: 0\n");
        return;
    }
    int paths = robotPaths(col, row);
    printf("The total number of paths the robot can take to reach home is: %d\n", paths);
}

// Recursively calculate weight in a human pyramid
float humanPyramidWeight(int row, int col, float weights[], int level) {
    if (row < 0 || col < 0 || col > row) return 0;
    if (row == 0 && col == 0) return weights[0];

    float leftParent = humanPyramidWeight(row - 1, col - 1, weights, level);
    float rightParent = humanPyramidWeight(row - 1, col, weights, level);
    int index = (row * (row + 1)) / 2 + col;

    return weights[index] + 0.5 * (leftParent + rightParent);
}

// Recursively print pyramid weights
void printPyramidWeights(int row, int col, float weights[], int level) {
    if (row >= level) return;

    if (col > row) {
        printf("\n");
        printPyramidWeights(row + 1, 0, weights, level);
    } else {
        float totalWeight = humanPyramidWeight(row, col, weights, level);
        printf("%.2f ", totalWeight);
        printPyramidWeights(row, col + 1, weights, level);
    }
}

// Recursively collect weights
void collectWeights(float weights[], int index, int size) {
    if (index >= size) return;
    scanf("%f", &weights[index]);
    if (weights[index] < 0) {
        printf("Negative weights are not supported.\n");
        exit(0);
    }
    collectWeights(weights, index + 1, size);
}

// Task 2: Human Pyramid
void task2HumanPyramid() {
    float weights[15];
    printf("Please enter the weights of the cheerleaders:\n");
    collectWeights(weights, 0, 15);
    printPyramidWeights(0, 0, weights, 5);
}

// Recursively validate parentheses
int validateParentheses(const char *str, int index, int balance) {
    if (str[index] == '\0') return balance == 0;
    if (str[index] == '(') return validateParentheses(str, index + 1, balance + 1);
    if (str[index] == ')') return balance > 0 && validateParentheses(str, index + 1, balance - 1);
    return validateParentheses(str, index + 1, balance);
}

// Task 3: Parenthesis Validation
void task3ParenthesisValidation() {
    char term[1000];
    printf("Please enter a term for validation:\n");
    scanf("%s", term);
    if (validateParentheses(term, 0, 0)) {
        printf("The parentheses are balanced correctly.\n");
    } else {
        printf("The parentheses are not balanced correctly.\n");
    }
}

// Task 4: Queens Battle
// (Recursion-based N-Queens problem with additional constraints will be implemented here)
void task4QueensBattle() {
    printf("This task is not fully implemented in this version.\n");
}

// Task 5: Crossword Generator
// (Recursion-based crossword generation will be implemented here)
void task5CrosswordGenerator() {
    printf("This task is not fully implemented in this version.\n");
}

int main() {
    int choice;

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                task1RobotPaths();
                break;
            case 2:
                task2HumanPyramid();
                break;
            case 3:
                task3ParenthesisValidation();
                break;
            case 4:
                task4QueensBattle();
                break;
            case 5:
                task5CrosswordGenerator();
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}

// Display menu
void displayMenu() {
    printf("Choose an option:\n");
    printf("1. Robot Paths\n");
    printf("2. The Human Pyramid\n");
    printf("3. Parenthesis Validation\n");
    printf("4. Queens Battle\n");
    printf("5. Crossword Generator\n");
    printf("6. Exit\n");
}
