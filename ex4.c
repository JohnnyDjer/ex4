/******************
Name: Jonathan Djerassi    
ID: 303013098
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>




#define COLUMNS 5
#define ROWS 5
#define MAXIMAL_SIZE 20
#define ASCII_NUM 128
#define MAX_GRID_SIZE 30
#define MAX_SLOTS 100
#define MAX_LENGTH_WORDS 16
#define MAX_WORDS 100

//this struct will hold the information about every slot in the crossword(word)
typedef struct{
    int row;
    int col;
    int len;
    char direction;
    int inserted;
} Slot;

int task1RobotPaths(int column, int row);
float task2HumanPyramid(float pyramid[COLUMNS][ROWS], int i, int j);
int task3ParenthesisValidator(char letter, char lastLetter, int x, int y, int z, int t);
int task4QueensBattle(char dimension[MAXIMAL_SIZE][MAXIMAL_SIZE],
int queenDimension[MAXIMAL_SIZE][MAXIMAL_SIZE],int columns[MAXIMAL_SIZE],int rows[MAXIMAL_SIZE],
int row,int col,int dimensionSize,int letterCheck[ASCII_NUM]);
int insertWord(char crossword[MAX_GRID_SIZE][MAX_GRID_SIZE], char str[], Slot slot, int index);
int task5CrosswordGenerator(char crossword[MAX_GRID_SIZE][MAX_GRID_SIZE],
Slot slot[MAX_SLOTS],int sizeofslots,int indexslot,char words[][MAX_LENGTH_WORDS],
int sizeofstr,int wordindex,int usedWords[]);
int deleteWord(char crossword[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, int index);

int main()
{
    //the variable we choose for cases initilized to none of the cases
    int task = -1;
    //loop to choose cases
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");
        //choose case
        if (scanf("%d", &task))
        {
            switch (task)
            {
            //choose this case to exit the program
            case 6:
                printf("Goodbye!\n");
                break;
            case 1:
            {
                int column, row, sumWays;
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d", &column);
                scanf("%d", &row);
                printf("The total number of paths the robot can take to reach home is: ");
                //the functions returns the number of possible ways to get to 0,0 to the variable
                sumWays = task1RobotPaths(column, row);
                //print the value of the function
                printf("%d\n", sumWays);
                break;
            }
            case 2:
            {
                int k = 0;
                float input = 0;
                //initilize the pyramid value to 0
                float pyramid[COLUMNS][ROWS] = {0};
                printf("Please enter the weights of the cheerleaders:\n");
                //the user chooses the value for every col
                for(int i = 0; i <= COLUMNS; i++)
                {
                 
                    for(int j = 0; j != k; j++)
                    {
                        scanf("%f", &input);
                        
                        if(input < 0){
                            printf("Negative weights are not supported.\n");
                            break;
                        }
                        //inserting user value to the people in the pyramid by order
                        pyramid[i][j] = input;
                    }
                    k++;
                  
                    if(input < 0)
                    {
                        break;
                    }
                }
               
                if(input < 0)
                {
                    break;
                }

                k = 0;
                printf("The total weight on each cheerleader is:\n");
                for(int i = 0; i <= COLUMNS; i++)
                {
                    for(int j = 0; j != k; j++)
                    {
                        /*only 2 numbers after the point '.', we call the recursion to print
                        the new wight num of the people in the pyramind*/
                        printf("%.2f ", task2HumanPyramid(pyramid, i, j));
                    }
                    printf("\n");
                    k++;
                }
                break;
            }
            case 3:
            {
                // Clear buffer from previous cases
                scanf("%*[^ \n]");
                scanf("%*c");
                printf("Please enter a term for validation:\n");
                // Call the function
                int result = task3ParenthesisValidator('\0', '\0', 0, 0, 0, 0);
                // Print once based on the result
                if (result == 1) {
                    printf("The parentheses are balanced correctly.\n");
                } else {
                    printf("The parentheses are not balanced correctly.\n");
                }
                break;
            }
            case 4:
            {
                int dimensionSize;
                //initilize the letters in the board
                char dimension[MAXIMAL_SIZE][MAXIMAL_SIZE] = {'\0'};
                //initilize the the numbers in the second queen board
                int queenDimension[MAXIMAL_SIZE][MAXIMAL_SIZE] = {0};
                //initilize all the letters in the array of the 'ASCII table'
                int letterCheck[ASCII_NUM] = {0};
                //initilize the columns
                int columns[MAXIMAL_SIZE] = {0};
                //initilize the rows
                int rows[MAXIMAL_SIZE] = {0};
                printf("Please enter the board dimensions:\n");
                scanf("%d", &dimensionSize);
                printf("Please enter a");
                printf(" %d*%d ", dimensionSize, dimensionSize);
                printf("puzzle board:\n");
                //taking the input from the user in rows and columns
                for (int row = 0; row < dimensionSize; row++)
                {
                    for (int col = 0; col < dimensionSize; col++)
                    {
                        scanf(" %c", &dimension[row][col]);
                    }
                }

                /*
                calling the recursive function, it will return either the print
                of the board and positive value or 0 and there is no solution
                */
                int result = task4QueensBattle(dimension, queenDimension, columns, rows,
                0, 0, dimensionSize, letterCheck);
                //if the function returned 0 and there is no solution
                if (result == 0)
                {
                    printf("This puzzle cannot be solved.\n");
                }
                break;
            }
            case 5:
            {
                int size, slots, numWords;
                char words[MAX_WORDS][MAX_LENGTH_WORDS] = {0};
                //initilized crossword grid
                char crossword[MAX_GRID_SIZE][MAX_GRID_SIZE] = {'\0'};
                int usedWords[MAX_WORDS] = {0};
                //array to store the struct information
                Slot slotsArr[MAX_SLOTS];

                //user will give dimension for the crossword
                printf("Please enter the dimensions of the crossword grid:\n");
                scanf("%d", &size);

                // user will give the num of slots
                printf("Please enter the number of slots in the crossword:\n");
                scanf("%d", &slots);

                // user will give the information to the array-struct
                printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
                for(int i = 0; i < slots; i++) {
                    //row
                    scanf("%d ", &slotsArr[i].row);
                    //column
                    scanf("%d ", &slotsArr[i].col);
                    //length
                    scanf("%d ", &slotsArr[i].len);
                    //direction 'H' for horizontal, 'V' for vertical
                    scanf(" %c", &slotsArr[i].direction);
                    //a flag to know if the word inserted or no
                    slotsArr[i].inserted = 0;
                }
                //user will choose the num of words
                printf("Please enter the number of words in the dictionary:\n");
                scanf("%d", &numWords);
                //compare the num of words to the num of slots, there should be more words than slots
                while(numWords < slots)
                {
                    printf("The dictionary must contain at least %d words. ", slots);
                    printf("Please enter a valid dictionary size:\n");
                    scanf("%d", &numWords);
                }

                // user will write the words themselfes the will inserted to the array of words
                printf("Please enter the words for the dictionary:\n");
                for(int i = 0; i < numWords; i++)
                {
                    scanf("%s", words[i]);
                }

                /*the function will generate the crossword if it will return a positive
                number, if it will return 0 then there no valid croossword*/
                if(task5CrosswordGenerator(crossword, slotsArr, slots,
                0, words, numWords,0, usedWords))
                {
                    //if the function returns 1, this will generate the crossword
                    //for every row
                    for (int i = 0; i < size; i++)
                    {
                        //and for every column
                        for (int j = 0; j < size; j++)
                        {
                            //if there no letter of word inserted in then write '#'
                            if(crossword[i][j] == '\0')
                            {
                                printf("| # ");
                                //else print the letter of the word
                            } else
                            {
                                printf("| %c ", crossword[i][j]); // Display the placed letter
                            }
                        }
                        //end of the row
                        printf("|\n");
                    }
                }
                else
                {
                    //if the function return 0 like I said then return 0
                    printf("This crossword cannot be solved.\n");
                }
                break;
            }
            default:
                //if the user will pick a case that not in the list
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            //if user enters invalid input
            scanf("%*s");
        }
    //while the user enter everything but 6, continue the loop
    } while (task != 6);
    //exit the program
    return 0;
}

int task1RobotPaths(int column, int row)
{
    // if either column or row is negative
    if(column < 0 || row < 0)
    {
        return 0;
    }
    //if the robot has reached the targer (0, 0)
    if(column == 0 && row == 0)
    {
        return 1;
    }
    //recursive to two possible positions, from the left or from below, and sum total num of paths
    return task1RobotPaths(column - 1, row) + task1RobotPaths(column, row - 1);
}

float task2HumanPyramid(float pyramid[COLUMNS][ROWS], int i, int j)
{
    //top of pyramid weight is their own weight.
    if(i == 0 && j == 0)
    {
        return pyramid[i][j];
    }
    //if out of bounds then stop
    if(i < 0 || j < 0)
    {
        return 0;
    }
    //there are two possible cheerleader, from the right and above, cut their weight in half
    float manFromRight = task2HumanPyramid(pyramid, i - 1, j - 1) * 0.5;
    float manFromAbove  = task2HumanPyramid(pyramid, i - 1, j) * 0.5;
    //total Weight of each man with the man above him
    return pyramid[i][j] + manFromAbove + manFromRight;
}

int task3ParenthesisValidator(char letter, char possibleLetter, int a, int b, int c, int d)
{
    char matchingBracket = '\0';
    //read each character in turn
    scanf("%c", &letter);
    //if it new line or the end of the string
    if (letter == '\n' || letter == '\0')
    {
        // If we are still expecting a closing bracket, it's not balanced
        if (possibleLetter != '\0')
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    //if this a number or letter, every but not bracket ignore
    if (letter != '[' && letter != ']' &&
        letter != '{' && letter != '}' &&
        letter != '(' && letter != ')' &&
        letter != '<' && letter != '>')
    {
        return task3ParenthesisValidator(letter, possibleLetter, a, b, c, d);
    }
    //if it a closed bracket
    if (letter == ']' || letter == '}' || letter == ')' || letter == '>')
    {
        // Must match the possibleLetter bracket
        if (letter == possibleLetter)
        {
            // if it closes the open bracket return positive num
            return 1;
        }
        else
        {
            //if it not closing the previous open bracket then return 0 and exit the function with imbalance
            scanf("%*[^ \n]");
            scanf("%*c");
            return 0;
        }
    }
    //if it is an opening bracket, figure the matching bracket
    if (letter == '[') matchingBracket = ']';
    if (letter == '{') matchingBracket = '}';
    if (letter == '(') matchingBracket = ')';
    if (letter == '<') matchingBracket = '>';
    //recurse to the next letter
    int innerOK = task3ParenthesisValidator('\0', matchingBracket, a, b, c, d);
    //if it didnt find the matching bracket then the function will return 0 and end the function here
    if (!innerOK)
    {
        return 0;
    }
    // if there no imbalance we found the matching bracket then continue
    return task3ParenthesisValidator('\0', possibleLetter, a, b, c, d);
}

int task4QueensBattle(char dimension[MAXIMAL_SIZE][MAXIMAL_SIZE],int queenDimension[MAXIMAL_SIZE][MAXIMAL_SIZE],
int columns[MAXIMAL_SIZE],int rows[MAXIMAL_SIZE],int row,int col,int dimensionSize,int letterCheck[ASCII_NUM])
{
    //if the board size is 1 then the automatic answer
    if (dimensionSize == 1)
    {
        printf("Solution:\nX\n"); // 'X' denotes a queen
        return 1;
    }

    /* there is a valid place for every queen and all the rows and columns are checked through,
    and print board*/
    if (row == dimensionSize)
    {
        printf("Solution:\n");
        for (int i = 0; i < dimensionSize; i++)
        {
            for (int j = 0; j < dimensionSize; j++)
            {
                if (queenDimension[i][j] == 1)
                {
                    printf("X ");
                }
                else
                {
                    printf("* ");
                }
            }
            //end of row in the board
            printf("\n");
        }
        //return positive num and the printed board
        return 1;
    }
    //if all the rows and column were checked through and there no place for all queens
    //backtrack by returning 0
    if (col == dimensionSize) {
        return 0;
    }
    /*
    checking the diagonal from above(because we starting from above
    there no point checking diagonal under), and also checking we arent on first row
    because there no point in checking diagonal where there no rows
    */
    if (row > 0)
    {
        //check left diagonal from above
        if ((col - 1 >= 0 && queenDimension[row - 1][col - 1] == 1) ||
            //check right diagonal from above
            (col + 1 < dimensionSize && queenDimension[row - 1][col + 1] == 1))
            {
            //if there are queens diagonal then go try next column
            return task4QueensBattle(dimension, queenDimension,
            columns, rows, row, col + 1, dimensionSize, letterCheck);
        }
    }
    //giving to a variable the letter in order to know if there are queen on this "color"
    int letter = dimension[row][col];
    /*check if the letter "color" was used already in the ASCII
    array - letterCheck, check if there queen in the row or column*/
    if (columns[col] == 1 || rows[row] == 1 ||
        queenDimension[row][col] == 1 || letterCheck[letter] == 1)
        {
        // if there is a queen in one of those option then try the next column
        return task4QueensBattle(dimension, queenDimension, columns, rows, row, col + 1, dimensionSize, letterCheck);
    }
    //I checked again if the letter is used or not because it gave me trouble overwise
    if (letterCheck[letter] == 0)
    {
        //placing the queen, marking the column, letter "color", row and the queen board
        queenDimension[row][col] = 1;
        columns[col] = 1;
        rows[row] = 1;
        letterCheck[letter] = 1;
        //recursive to try to play in the next row
        if (task4QueensBattle(dimension, queenDimension, columns, rows, row + 1, 0, dimensionSize, letterCheck))
        {
            //if there is a success to put a queen then return positive num and continue
            return 1;
        }
        // if there no succes in putting the queen then unplace the queen and mark the row, col, color and board as 0
        queenDimension[row][col] = 0;
        columns[col] = 0;
        rows[row] = 0;
        letterCheck[letter] = 0;
    }
    // contimnue trying placing a queen in the next column of the current row.
    if (task4QueensBattle(dimension, queenDimension, columns, rows, row, col + 1, dimensionSize, letterCheck))
    {
        //if success
        return 1;
    }
    //if no, then backtrack
    return 0;
}

int task5CrosswordGenerator(char crossword[MAX_GRID_SIZE][MAX_GRID_SIZE],Slot slot[MAX_SLOTS],
int sizeofslots,int indexslot,char words[][MAX_LENGTH_WORDS],int sizeofstr,int wordindex,int usedWords[])
{
    // all slots are filled.
    if (indexslot == sizeofslots)
    {
        //return positive num
        return 1;
    }
    // all words have been tried and no success
    if (wordindex == sizeofstr)
    {
        //backtrack
        return 0;
    }
    // temporary variable to hold the copy of the slot array i made in this undex
    Slot currentSlot = slot[indexslot];
    /*
    checking if the sord is already used, if word length does not match the slot's length.
    starting cell of the slot is already with a different letter.
    */
    if (usedWords[wordindex] ||
        currentSlot.len != (int)strlen(words[wordindex]) ||
        (crossword[currentSlot.row][currentSlot.col] != '\0' &&
         crossword[currentSlot.row][currentSlot.col] != words[wordindex][0]))
    {
        //if one of them is true then try different letter
        return task5CrosswordGenerator(crossword, slot, sizeofslots, indexslot,
                                       words, sizeofstr, wordindex + 1, usedWords);
    }
    // marking the word as used
    usedWords[wordindex] = 1;
    /*the function will return positive num if the word was inserted without problems, and the slot inserted will be
    marked as 1, or overwise if the insertWord function didnt get to insert the word*/
    slot[indexslot].inserted = insertWord(crossword, words[wordindex], currentSlot, 0);
    //if the slot inserted is marked as 1
    if (slot[indexslot].inserted)
    {
        // recursion to try the next slot with different word
        if (task5CrosswordGenerator(crossword, slot, sizeofslots, indexslot + 1,
                                    words, sizeofstr, 0, usedWords))
        {
            //place the other word in the other slot
            return 1;
        }

        //if there no success to try the next slot with other word then delete the previous word
        deleteWord(crossword, currentSlot, 0);
        //unmark the word that we used to use it again later
        usedWords[wordindex] = 0;
        //mark the slot inserted to 0 back
        slot[indexslot].inserted = 0;
    }
    //try the next word to the current slot
    return task5CrosswordGenerator(crossword, slot, sizeofslots, indexslot,
                                   words, sizeofstr, wordindex + 1, usedWords);
}


int insertWord(char crossword[MAX_GRID_SIZE][MAX_GRID_SIZE],char words[],Slot slot,int indexslot)
{
    // if all characters have been inserted.
    if (indexslot == slot.len)
    {
        return 1;
    }
    //determine the current position to insert the character.
    int row = slot.row;
    int col = slot.col;
    //choosing row or column based on the direction 'H' or 'V' to place the next character
    if (slot.direction == 'H')
    {
        col += indexslot;
    }
    else if (slot.direction == 'V')
    {
        row += indexslot;
    }
    //if the cell is already filled with a different letter, return 0
    if (crossword[row][col] != '\0' && crossword[row][col] != words[indexslot])
    {
        return 0;
    }
    //place the letter in the crossword board
    crossword[row][col] = words[indexslot];
    //recursion to insert the next  in the word
    return insertWord(crossword, words, slot, indexslot + 1);
}

int deleteWord(char crossword[MAX_GRID_SIZE][MAX_GRID_SIZE],
               Slot slot,
               int indexslot)
{
    //if all letters have been deleted
    if (indexslot == slot.len) {
        //return to the other function
        return 0;
    }

    //determine the current position to delete the letter
    int row = slot.row;
    int col = slot.col;

    //choosing row or column based on the direction 'H' or 'V' to delete the next letter
    if (slot.direction == 'H') {
        col += indexslot;
    } else if (slot.direction == 'V') {
        row += indexslot;
    }

    //making the place in the board already '#', it can be changed if there is a word that can be here
    crossword[row][col] = '#';

    //recursion to delete the next letter in the word
    return deleteWord(crossword, slot, indexslot + 1);
}
