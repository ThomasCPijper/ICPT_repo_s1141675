#include <stdlib.h>
#include <stdio.h>

#define STANDARD_VALUE 0
#define NEWLINE "\n"

char* board[6][7] = { NULL };
char star = '*';
char power = '^';
char line = '-';
int finished = 0;
char winner;

void printScreen() {
    for (int i = 1; i < 8; ++i) {
        printf("%d ", i);
    }
    printf(NEWLINE);

    for (int i = 1; i < 8; ++i) {
        printf("%c ", line);
    }
    printf(NEWLINE);


    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (board[i][j] == NULL) {
                printf("0 ");
            } else {
                printf("%c ", *board[i][j]);
            }
        }
        printf(NEWLINE);
    }
}
free(arr);

int makeMove(char* token) {
    int userInput;
    printf("Please enter an integer (1-7): ");
    scanf("%d", &userInput);

    if (userInput < 1 || userInput > 7) {
        printf("Invalid column! Please choose a number between 1 and 7.\n");
        return 0;
    }

    for (int i = 5; i >= 0; --i) {
        if (board[i][userInput - 1] == NULL) {
            board[i][userInput - 1] = token;
            printScreen();
            return 1;
        }
    }

    printf("Column %d is full! Choose a different column.\n", userInput);
    return 0;
}

int checkBoard() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] != NULL && board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2] && board[i][j] == board[i][j+3]) {
                return 1;
            }
        }
    }

    for (int j = 0; j < 7; ++j) {
        for (int i = 0; i < 3; ++i) {
            if (board[i][j] != NULL && board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j] && board[i][j] == board[i+3][j]) {
                return 1;
            }
        }
    }

    return 0;
}

int isBoardFull() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (board[i][j] == NULL) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {
    int round = 0;
    printScreen();
    while (!finished) {
        round++;
        if (!checkBoard()) {
            makeMove(round % 2 == 0 ? &star : &power);
        } else {
            finished = 1;
        }

        if (isBoardFull()) {
            printf("The board is full! It's a draw!\n");
            finished = 1;
        }
    }

    if (!isBoardFull()) {
        winner = (round % 2 == 0) ? power : star;
        printf("Player %d wins! (%c)\n", (round % 2 == 0) ? 2 : 1, winner);
    }

    return 0;
}