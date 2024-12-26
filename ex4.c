/******************
Name: Jonathan Djerassi    
ID: 303013098
Assignment: ex4
*******************/
#include <stdio.h>


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
int collectWeights(float weights[], int index, int size) {
    if (index >= size) return 1;  // All weights collected successfully
    int result = scanf("%f", &weights[index]);

    // If input fails or a negative weight is entered
    if (result != 1 || weights[index] < 0) {
        printf("Negative weights are not supported.\n");
        return 0;  // Return 0 to indicate invalid input
    }

    // Continue recursively collecting weights
    return collectWeights(weights, index + 1, size);
}

// Task 2: Human Pyramid
void task2HumanPyramid() {
    float weights[15];
    printf("Please enter the weights of the cheerleaders:\n");

    // Collect weights and handle invalid input
    if (collectWeights(weights, 0, 15) == 0) {
        return;  // If invalid input, return to the main menu (exit the task)
    }

    // Print pyramid weights
    printf("The total weight on each cheerleader is:\n");
    printPyramidWeights(0, 0, weights, 5);
}



// Helper function to check if characters are matching parentheses
int isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

// Recursively validate parentheses
int validateParentheses(const char *str, int index, char lastOpened) {
    if (str[index] == '\0') return lastOpened == '\0';  // Base case: no more parentheses left to check

    // Opening parentheses, push onto stack (or just track it with lastOpened)
    if (str[index] == '(' || str[index] == '[' || str[index] == '{') {
        return validateParentheses(str, index + 1, str[index]);
    }

    // Closing parentheses, check if it matches the last opened one
    if ((str[index] == ')' || str[index] == ']' || str[index] == '}') && lastOpened != '\0') {
        if (isMatching(lastOpened, str[index])) {
            return validateParentheses(str, index + 1, '\0');  // Matched, continue with empty lastOpened
        } else {
            return 0;  // Mismatch
        }
    }

    // Ignore non-parentheses characters and continue checking
    return validateParentheses(str, index + 1, lastOpened);
}

// Task 3: Parenthesis Validation
void task3ParenthesisValidation() {
    char term[1000];
    printf("Please enter a term for validation:\n");
    scanf("%s", term);  // Read the input string

    if (validateParentheses(term, 0, '\0')) {
        printf("The parentheses are balanced correctly.\n");
    } else {
        printf("The parentheses are not balanced correctly.\n");
    }
}
// Function prototypes for Task 4
int isSafe(int board[MAX_GRID_SIZE][MAX_GRID_SIZE], int row, int col, int n, int rows[MAX_GRID_SIZE], int cols[MAX_GRID_SIZE], char areas[MAX_GRID_SIZE][MAX_GRID_SIZE]);
int solveQueensBattle(int board[MAX_GRID_SIZE][MAX_GRID_SIZE], int n, int rows[MAX_GRID_SIZE], int cols[MAX_GRID_SIZE], int row, char areas[MAX_GRID_SIZE][MAX_GRID_SIZE]);
void printBoard(int board[MAX_GRID_SIZE][MAX_GRID_SIZE], int n);
void readGrid(char areas[MAX_GRID_SIZE][MAX_GRID_SIZE], int n);

// Check if it is safe to place a queen in the given position
int isSafe(int board[MAX_GRID_SIZE][MAX_GRID_SIZE], int row, int col, int n, int rows[MAX_GRID_SIZE], int cols[MAX_GRID_SIZE], char areas[MAX_GRID_SIZE][MAX_GRID_SIZE]) {
    // Check if the cell is restricted
    if (areas[row][col] == 'X') {
        return 0;  // Restricted cell
    }

    // Check if the row or column already has a queen
    if (rows[row] || cols[col]) return 0;

    // Check diagonals for existing queens
    for (int i = 0; i < row; i++) {
        // Check left diagonal
        if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1) {
            return 0;
        }
        // Check right diagonal
        if (col + (row - i) < n && board[i][col + (row - i)] == 1) {
            return 0;
        }
    }

    return 1; // Safe to place queen
}

// Recursively solve the Queens Battle problem
int solveQueensBattle(int board[MAX_GRID_SIZE][MAX_GRID_SIZE], int n, int rows[MAX_GRID_SIZE], int cols[MAX_GRID_SIZE], int row, char areas[MAX_GRID_SIZE][MAX_GRID_SIZE]) {
    if (row == n) {
        return 1;  // Solution found
    }

    // Try each column in the current row
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n, rows, cols, areas)) {
            // Place queen
            board[row][col] = 1;
            rows[row] = 1;
            cols[col] = 1;

            // Recurse to the next row
            if (solveQueensBattle(board, n, rows, cols, row + 1, areas)) {
                return 1;  // Solution found
            }

            // Backtrack
            board[row][col] = 0;
            rows[row] = 0;
            cols[col] = 0;
        }
    }

    return 0; // No solution found
}

// Print the board
void printBoard(int board[MAX_GRID_SIZE][MAX_GRID_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1) {
                printf("X ");
            } else {
                printf("* ");
            }
        }
        printf("\n");
    }
}

// Read the grid
void readGrid(char areas[MAX_GRID_SIZE][MAX_GRID_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &areas[i][j]);  // Read each character
        }
    }
}

// Task 4: Queens Battle
void task4QueensBattle() {
    int n;
    printf("Please enter the board dimensions:\n");
    scanf("%d", &n);

    // Read the grid layout
    char areas[MAX_GRID_SIZE][MAX_GRID_SIZE];
    printf("Please enter a %d*%d puzzle board:\n", n, n);
    readGrid(areas, n);

    int board[MAX_GRID_SIZE][MAX_GRID_SIZE] = {0};
    int rows[MAX_GRID_SIZE] = {0}, cols[MAX_GRID_SIZE] = {0};

    // Solve the problem
    if (solveQueensBattle(board, n, rows, cols, 0, areas)) {
        printf("Solution:\n");
        printBoard(board, n);
    } else {
        printf("This puzzle cannot be solved.\n");
    }
}

// Task 5: Crossword Generator

// Define a struct to store slot information (row, column, length, direction)
typedef struct {
    int row;
    int col;
    int length;
    char direction; // 'H' for horizontal, 'V' for vertical
} Slot;

// Function prototypes for task 5
void initializeGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int size, int row, int col);
int canPlaceWord(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, const char *word, int index);
void placeWord(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, const char *word, int index, int place);
int fillSlot(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slots[], int slotIndex, int totalSlots, char words[MAX_SLOTS][MAX_WORD_LENGTH + 1], int wordUsed[MAX_SLOTS], int totalWords);
void printGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int size, int row, int col);

// Initialize the grid to all '#' characters (empty spaces)
void initializeGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int size, int row, int col) {
    if (row >= size) return;
    if (col >= size) {
        initializeGrid(grid, size, row + 1, 0);
        return;
    }
    grid[row][col] = '#'; // Empty spaces marked as '#'
    initializeGrid(grid, size, row, col + 1);
}

// Check if a word can be placed in a given slot
int canPlaceWord(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, const char *word, int index) {
    if (index >= slot.length) return 1;

    int row = slot.row + (slot.direction == 'V' ? index : 0);
    int col = slot.col + (slot.direction == 'H' ? index : 0);

    // If the position is not an empty space or matches the word's character, it can't be placed
    if (grid[row][col] != '#' && grid[row][col] != word[index]) {
        return 0;
    }

    return canPlaceWord(grid, slot, word, index + 1); // Move to the next character
}

// Place a word in a given slot (either horizontally or vertically)
void placeWord(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, const char *word, int index, int place) {
    if (index >= slot.length) return;

    int row = slot.row + (slot.direction == 'V' ? index : 0);
    int col = slot.col + (slot.direction == 'H' ? index : 0);

    grid[row][col] = (place ? word[index] : '#'); // If placing, put the word, else reset to '#'
    placeWord(grid, slot, word, index + 1, place); // Recursively place the next character
}

// Recursively try to fill all crossword slots with words
int fillSlot(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slots[], int slotIndex, int totalSlots, char words[MAX_SLOTS][MAX_WORD_LENGTH + 1], int wordUsed[MAX_SLOTS], int totalWords) {
    if (slotIndex >= totalSlots) return 1; // All slots filled, return success

    for (int i = 0; i < totalWords; i++) {
        if (!wordUsed[i] && canPlaceWord(grid, slots[slotIndex], words[i], 0)) {
            wordUsed[i] = 1; // Mark word as used
            placeWord(grid, slots[slotIndex], words[i], 0, 1); // Place the word

            if (fillSlot(grid, slots, slotIndex + 1, totalSlots, words, wordUsed, totalWords)) {
                return 1; // If the next slot is filled, return success
            }

            placeWord(grid, slots[slotIndex], words[i], 0, 0); // Backtrack and remove word
            wordUsed[i] = 0; // Unmark word as used
        }
    }

    return 0; // No solution found for this slot, return failure
}

// Print the crossword grid with '|' separating the cells
void printGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int size, int row, int col) {
    if (row >= size) return; // Base case: all rows printed
    if (col >= size) {
        printf("|\n");
        printGrid(grid, size, row + 1, 0); // Move to the next row
        return;
    }

    printf("| %c ", grid[row][col]); // Print each cell
    printGrid(grid, size, row, col + 1); // Move to the next column
}

// Function prototypes for task 5
void initializeGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int size, int row, int col);
int canPlaceWord(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, const char *word, int index);
void placeWord(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, const char *word, int index, int place);
int fillSlot(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slots[], int slotIndex, int totalSlots, char words[MAX_SLOTS][MAX_WORD_LENGTH + 1], int wordUsed[MAX_SLOTS], int totalWords);
void printGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int size, int row, int col);

void task5CrosswordGenerator() {
    int gridSize, totalSlots, totalWords;
    char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
    Slot slots[MAX_SLOTS];
    char words[MAX_SLOTS][MAX_WORD_LENGTH + 1];
    int wordUsed[MAX_SLOTS] = {0};

    // Input for grid size
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf("%d", &gridSize);

    // Input for number of slots
    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d", &totalSlots);

    // Input for slot details (row, column, length, direction)
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < totalSlots; i++) {
        scanf("%d %d %d %c", &slots[i].row, &slots[i].col, &slots[i].length, &slots[i].direction);
    }

    // Input for number of words in the dictionary with validation
    printf("Please enter the number of words in the dictionary:\n");
    do {

        scanf("%d", &totalWords);
        if (totalWords < 4) {
            printf("The dictionary must contain at least 4 words. Please enter a valid dictionary size:\n");
        }
    } while (totalWords < 4);  // Keep asking until a valid number is entered

    // Input for the words in the dictionary
    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < totalWords; i++) {
        scanf("%s", words[i]);
    }

    // Initialize the grid
    initializeGrid(grid, gridSize, 0, 0);

    // Try to fill the crossword
    if (fillSlot(grid, slots, 0, totalSlots, words, wordUsed, totalWords)) {

        printGrid(grid, gridSize, 0, 0); // Print the filled grid
    } else {
        printf("This crossword cannot be solved.\n");
    }
}


// Main menu and driver function
void displayMenu() {
    printf("Choose an option:\n");
    printf("1. Robot Paths\n");
    printf("2. The Human Pyramid\n");
    printf("3. Parenthesis Validation\n");
    printf("4. Queens Battle\n");
    printf("5. Crossword Generator\n");
    printf("6. Exit\n");
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
        }
    } while (choice != 6);

    return 0;
}
